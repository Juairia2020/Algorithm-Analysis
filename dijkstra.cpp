#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>>graph;
vector<int>dist;
vector<vector<int>>parent,ways;
vector<int>path;

void paths(int cur, vector<int>&par)
{

    if(par.size()==0)
    {
        ways.push_back(path);
        return;
    }

    path.push_back(cur);
    for(auto &x:par)
    {
        paths(x, parent[x]);
    }
    if(!path.empty())path.pop_back();

}



void dijsktra(int src, int dest)
{

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    pq.push({0,src});
    dist[src] = 0;
    parent[src].push_back(0);
    while(!pq.empty())
    {

        int wt = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if(wt!=dist[cur]) continue;

        for(auto [child,wtc]: graph[cur])
        {
            if(dist[child] > wt + wtc)
            {
                dist[child] = wt + wtc;
                pq.push({dist[child],child});

                parent[child].clear();
                parent[child].push_back(cur);
            }
            else if(dist[child] == wt + wtc)
            {
                parent[child].push_back(cur);
            }

        }

    }

    if(dist[dest]==INT_MAX)
    {
        cout<<"Destination unreachable\n";
        return;
    }

    cout<<"\nShortest paths:\n";
    paths(dest, parent[dest]);
    for(auto &x:ways)
    {
        for(int i=x.size()-1; i>=0; i--)cout<<x[i]<<" ";
        cout<<endl;
    }
    cout<<"Shortest distant: "<<dist[dest]<<endl;

}


int main()
{

    int n,edge;
    cin>>n>>edge;
    graph.resize(n+1);
    dist.assign(n+1, INT_MAX);
    parent.resize(n+1);


    for(int i=0; i<edge; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});


    }

    int src,dest;
    cin>>src>>dest;

    dijsktra(src,dest);

}
