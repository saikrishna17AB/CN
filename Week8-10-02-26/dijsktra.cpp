#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<vector>
class Edge{
public:
    int v;
    int wt;

    Edge(int v,int wt){
        this->v=v;
        this->wt=wt;
    }
};

void dijkstra(int src,vector<vector<Edge>> graph,int V){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    //pair (dist[v],v)
    vector<int> dist(V,INT_MAX);
    vector<int> parent(V,-1);
    
    pq.push(make_pair(0,src));
    dist[src]=0;

    while(pq.size()>0){
        int u=pq.top().second;
        pq.pop();
        
        for(Edge e:graph[u]){
            if(dist[e.v]>dist[u]+e.wt){
                dist[e.v]=dist[u]+e.wt;
                
                parent[e.v]=u;

                pq.push(make_pair(dist[e.v],e.v));
                
            }
        }
        
    }
    
    //printiting the shortest paths to each node

    cout<<"Source\t Destination \t\t\t\t\t Cost \t\t\t NextHop \t\t NextHopCost"<<endl;
    for(int i=0;i<V;i++){
        vector<int> path;
        int current=i;
        path.push_back(current);
        while(parent[current]!=-1){
            path.push_back(parent[current]);
            current=parent[current];
        }
        reverse(path.begin(),path.end());

        cout<<"Shortest path to reach "<<i<<" from "<<src<<":";
        for(int j=0;j<path.size();j++){
            cout<<path[j];
            if(j!=path.size()-1){
                cout<<"->";
            }
        }
        cout<<"\t\t\t"<<dist[i];
        if(i!=0){
            cout<<"\t\t\t"<<path[1]<<"\t\t\t"<<dist[i];
        }
            cout<<endl;

    }

    //Routing table(Included above)


    for(int i=0;i<V;i++){
        vector<int> path;
        int current=i;
        path.push_back(i);

    }
}

int main(){
    int V=5;
    vector<vector<Edge>> graph(V);
    
    graph[0].push_back(Edge(1, 2));
    graph[0].push_back(Edge(3, 1));

    graph[1].push_back(Edge(0, 2));
    graph[1].push_back(Edge(2, 3));
    graph[1].push_back(Edge(4, 4));

    graph[2].push_back(Edge(1, 3));
    graph[2].push_back(Edge(3, 5));
    graph[2].push_back(Edge(4, 6));

    graph[3].push_back(Edge(0, 1));
    graph[3].push_back(Edge(2, 5));
    graph[3].push_back(Edge(4, 7));

    graph[4].push_back(Edge(1, 4));
    graph[4].push_back(Edge(2, 6));
    graph[4].push_back(Edge(3, 7));


    dijkstra(0,graph,V);
    return 0;

}