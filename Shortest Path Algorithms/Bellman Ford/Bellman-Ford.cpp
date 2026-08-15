#include <bits/stdc++.h>
using namespace std;

vector<tuple<int,int,int>> graph;
vector<int> dist, path, active;
vector<vector<int>> parent, ways;

void paths(int cur, vector<int>& par)
{
    if(active[cur])
        return;

    active[cur] = 1;

    if(par.empty())
    {
        ways.push_back(path);
        active[cur] = 0;
        return;
    }

    path.push_back(cur);

    for(auto &x : par)
    {
        if(x != -1)
            paths(x, parent[x]);
    }

    path.pop_back();
    active[cur] = 0;
}

bool bellman_ford(int nodes, int src, int dest)
{
    dist[src] = 0;
    parent[src].push_back(-1);

    for(int i = 0; i < nodes - 1; i++)
    {
        bool change = false;

        for(auto &[u, v, w] : graph)
        {
            if(dist[u] == INT_MAX)
                continue;

            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v].clear();
                parent[v].push_back(u);
                change = true;
            }
            else if(dist[v] == dist[u] + w)
            {
                parent[v].push_back(u);
            }
        }

        if(!change)
            break;
    }

    for(auto &[u, v, w] : graph)
    {
        if(dist[u] != INT_MAX && dist[v] > dist[u] + w)
            return true;
    }

    if(dist[dest] == INT_MAX)
    {
        cout << "Unreachable\n";
        return false;
    }

    cout << "Shortest distance: " << dist[dest] << '\n';

    path.clear();
    ways.clear();
    active.assign(nodes, 0);

    cout << "\nShortest paths:\n";

    paths(dest, parent[dest]);

    for(auto &x : ways)
    {
        for(int i = x.size() - 1; i >= 0; i--)
            cout << x[i] << " ";

        cout << '\n';
    }

    return false;
}

int main()
{
    int n, edge;
    cin >> n >> edge;

    dist.assign(n, INT_MAX);
    parent.resize(n);

    for(int i = 0; i < edge; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.push_back({u, v, w});
    }

    int src, dest;
    cin >> src >> dest;

    if(bellman_ford(n, src, dest))
        cout << "Negative cycle found\n";
}
