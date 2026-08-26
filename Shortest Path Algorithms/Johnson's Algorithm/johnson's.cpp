#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define lmax LLONG_MAX

vector<vector<pair<int,ll>>>graph;

vector<ll> bford(int node,int src)
{
    vector<ll>dist(node, lmax);
    dist[src] = 0;

    for(int i=0; i<node-1; i++)
    {
        for(int u=0; u<node; u++)
        {
            if(dist[u] == lmax) continue;

            for(auto &[v,w]:graph[u])
                dist[v] = min(dist[v], dist[u] + w);
        }
    }

    for(int u=0; u<node; u++)
    {
        if(dist[u] == lmax) continue;

        for(auto &[v,w]:graph[u])
        {
            if(dist[v] > dist[u] + w)
            {
                cout<<"Negative cycle detected\n";
                exit(0);
            }
        }
    }

    return dist;
}


pair<vector<ll>, vector<vector<int>>> dijkstra(int node, int src)
{
    vector<ll>dist(node,lmax);
    vector<int>parent(node);
    vector<vector<int>>path(node);

    dist[src] = 0;
    parent[src] = -1;
    path[src] = {src};

    priority_queue<pair<ll,int>>pq;
    pq.push({0,src});

    while(!pq.empty())
    {
        int u = pq.top().second;
        ll d = -pq.top().first;
        pq.pop();

        if(d != dist[u]) continue;

        for(auto &[v,wt]:graph[u])
        {
            if(dist[v] > dist[u] + wt)
            {
                dist[v] = dist[u] + wt;
                pq.push({-dist[v],v});

                parent[v] = u;
            }
        }
    }

    for(int i=0; i<node; i++)
    {
        if(i==src) continue;
        if(dist[i]==lmax)
        {
            path[i].push_back(-1);
            continue;
        }

        int cur = i;
        while(cur!=-1)
        {
            path[i].push_back(cur);
            cur = parent[cur];
        }

        reverse(path[i].begin(), path[i].end());

    }

    return {dist,path};
}

void print_johnson(int node, vector<ll>& h)
{
    for(int i = 0; i < node; i++)
    {
        auto [dist,path] = dijkstra(node,i);
        for(int j = 0; j < node; j++)
        {
            cout<<i<< " -> " << j << " : ";
            if(dist[j] == lmax) cout << "Cost = INF, Path = -1";
            else
            {
                ll cost = dist[j] - h[i] + h[j];  //Fixing weights
                cout << "Cost = " << cost << ", Path = ";
                for(int k = 0; k < path[j].size(); k++)
                {
                    cout << path[j][k];
                    if(k != path[j].size() - 1) cout << " -> ";
                }
            }
            cout << "\n";
        }
    }
}

int main()
{
    int node,edge;
    cin>>node>>edge;

    graph.resize(node+1);

    for(int i=0; i<edge; i++)
    {
        int u,v;
        ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
    }

    //Adding super node
    for(int i=0; i<node; i++) graph[node].push_back({i,0});


    //Bellman-ford from super node
    vector<ll>h = bford(node+1,node);

    //Reweighting graph
    for(int u=0; u<node; u++)
    {
        for(auto &[v,w]:graph[u]) w = w + h[u] - h[v];
    }

    //Removing super node
    graph.pop_back();

    //Result printing of johnson
    print_johnson(node,h);
}
