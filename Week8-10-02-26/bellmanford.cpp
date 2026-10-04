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

void bellmanford(vector<vector<Edge>> graph, int V,int src){
    vector<int> dist(V,INT_MAX);
    dist[0]=0;
    for(int i=0;i<V-1;i++){             //V-1
        for(int u=0;u<V;u++){           //E
            for(Edge e:graph[u]){
                
                if(dist[u]!=INT_MAX && dist[e.v]>dist[u]+e.wt){
                    dist[e.v]=dist[u]+e.wt;
                    
                }
            }
        }
    }


    for(int i=0;i<V;i++){
        cout<<dist[i]<<" ";
    }
    
}

int main(){
    int V = 4;
    vector<vector<Edge>> graph(V);

    graph[0].push_back(Edge(1, 1));
    graph[0].push_back(Edge(2, 4));

    graph[1].push_back(Edge(0, 1));
    graph[1].push_back(Edge(2, 2));
    graph[1].push_back(Edge(3, 6));

    graph[2].push_back(Edge(0, 4));
    graph[2].push_back(Edge(1, 2));
    graph[2].push_back(Edge(3, 3));

    graph[3].push_back(Edge(1, 6));
    graph[3].push_back(Edge(2, 3));
    
    bellmanford(graph,V,0);
    return 0;
}