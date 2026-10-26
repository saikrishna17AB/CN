#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ForwardTable{
    int no;
    string subnetAddress;
    string subnetMask;
    string firstHost;
    string lastHost;
    string broadcastAddress;
    int hosts;
};

string makeIP(int ip[]){
    return to_string(ip[0]) + "." + to_string(ip[1]) + "."+ to_string(ip[2]) + "." + to_string(ip[3]);
}

int main(){
    int ip[4], cidr, requiredSubnets;
    char dot;

    cout << "Enter Base Network Address: ";
    cin >> ip[0] >> dot >> ip[1] >> dot >> ip[2] >> dot >> ip[3];

    cout << "Enter CIDR Prefix: ";
    cin >> cidr;

    cout << "Enter Number of Required Subnets: ";
    cin >> requiredSubnets;

    if (cidr < 0 || cidr > 30 || requiredSubnets <= 0)
    {
        cout << "Invalid input";
        return 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (ip[i] < 0 || ip[i] > 255)
        {
            cout << "Invalid IP address";
            return 0;
        }
    }

    int borrowed = 0;
    int count = 1;

    while (count < requiredSubnets)
    {
        count *= 2;
        borrowed++;
    }

    int newCidr = cidr + borrowed;

    if (newCidr > 30)
    {
        cout << "Not enough addresses for the required subnets";
        return 0;
    }

    int hostBits = 32 - newCidr;
    int subnetSize = 1;

    for (int i = 0; i < hostBits; i++)
        subnetSize *= 2;

    int hosts = subnetSize - 2;

    int mask[4] = {0, 0, 0, 0};

    for (int i = 0; i < newCidr; i++)
        mask[i / 8] += 1 << (7 - i % 8);

    string subnetMask = makeIP(mask);

    int originalMask[4] = {0, 0, 0, 0};

    for (int i = 0; i < cidr; i++)
        originalMask[i / 8] += 1 << (7 - i % 8);

    int network[4] = {ip[0], ip[1], ip[2], ip[3]};

    for (int i = 0; i < 4; i++)
    {
        if (originalMask[i] != 255)
        {
            int block = 256 - originalMask[i];
            network[i] = (network[i] / block) * block;

            for (int j = i + 1; j < 4; j++)
                network[j] = 0;

            break;
        }
    }

    vector<ForwardTable> table;

    for (int i = 0; i < requiredSubnets; i++)
    {
        int sub[4] = {network[0], network[1], network[2], network[3]};
        int increment = i * subnetSize;

        for (int j = 3; j >= 0; j--)
        {
            sub[j] += increment % 256;
            increment /= 256;

            if (sub[j] > 255)
            {
                sub[j] -= 256;
                increment++;
            }
        }

        int bc[4] = {sub[0], sub[1], sub[2], sub[3]};
        int remaining = subnetSize - 1;

        for (int j = 3; j >= 0; j--)
        {
            bc[j] += remaining % 256;
            remaining /= 256;

            if (bc[j] > 255)
            {
                bc[j] -= 256;
                remaining++;
            }
        }

        int first[4] = {sub[0], sub[1], sub[2], sub[3]};
        int last[4] = {bc[0], bc[1], bc[2], bc[3]};

        first[3]++;
        last[3]--;

        ForwardTable entry;

        entry.no = i + 1;
        entry.subnetAddress = makeIP(sub);
        entry.subnetMask = subnetMask;
        entry.firstHost = makeIP(first);
        entry.lastHost = makeIP(last);
        entry.broadcastAddress = makeIP(bc);
        entry.hosts = hosts;

        table.push_back(entry);
    }

    cout << "\nForwarding Table\n\n";

    cout << "No. | Subnet Address | Subnet Mask | First Host | Last Host | Broadcast Address | Hosts\n";

    for (int i = 0; i < table.size(); i++)
    {
        cout << table[i].no << " | "
             << table[i].subnetAddress << " | "
             << table[i].subnetMask << " | "
             << table[i].firstHost << " | "
             << table[i].lastHost << " | "
             << table[i].broadcastAddress << " | "
             << table[i].hosts << endl;
    }

    cout << "\nTotal Subnets: " << requiredSubnets;
    cout << "\nNew CIDR Prefix: /" << newCidr;
    cout << "\nHosts Per Subnet: " << hosts << endl;

    return 0;
}