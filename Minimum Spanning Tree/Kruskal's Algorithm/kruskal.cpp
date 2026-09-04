#include<bits/stdc++.h>
using namespace std;

bool comp(vector<int>&t1, vector<int>&t2)
{
    if(t1[2]!=t2[2]) return t1[2]<t2[2];
    if(t1[0]!=t2[0]) return t1[0]<t2[0];

    return t1[1]<t2[1];
}

class DSU
{

public:
    vector<int>parent,size;

    DSU(int node)
    {
        parent.resize(node);
        size.assign(node,1);

        for(int i=0; i<node; i++)
        {
            parent[i] = i;
        }
    }

    int find(int a)
    {
        if (a == parent[a]) return a;
        return parent[a] = find(parent[a]);
    }

    void unite(int a, int b)
    {

        a = find(a);
        b = find(b);

        if(a == b)
            return;

        if(size[a] < size[b])
            swap(a,b);

        parent[b] = a;
        size[a] += size[b];
    }

};


int main()
{
    int node,edge;
    cin>>node>>edge;

    vector<vector<int>>graph;
    vector<vector<pair<int,int>>>mst(node);
    for(int i=0; i<edge; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph.push_back({u,v,w});
    }

    DSU dsu(node);
    int total =0;
    bool cycle = false;

    sort(graph.begin(), graph.end(), comp);
    for(auto &edge: graph)
    {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        if(dsu.find(u)!=dsu.find(v))
        {
            mst[u].push_back({v,w});
            dsu.unite(u,v);
            total+=w;
        }
        else
        {
            cycle = true;
        }
    }

    int tree=0;
    vector<int>mark(node,-1);

    for(int i = 0; i < node; i++)
    {
        int root = dsu.find(i);

        if(mark[root] == -1)
            mark[root] = tree++;

        mark[i] = mark[root];
    }


    for(int i=0; i<tree; i++)
    {
        cout<<"\nTree "<<i+1<<": \n";

        cout<<"Vertices: ";
        for(int u=0; u<node; u++)
        {
            if(mark[u] == i) cout << u << " ";
        }
        cout<<endl;


        cout<<"Edges:"<<endl;
        int mst_wt=0;
        for(int u=0; u<node; u++)
        {
            if(mark[u] != i) continue;
            for(auto &[v,w] : mst[u]){
                cout << u << " " << v << " -> " << w << endl;
                mst_wt+=w;
            }
        }
          cout<<"MST weight: "<<mst_wt<<endl;
    }



    cout<<"\nTotal MSF weight: "<<total<<endl;
    if(cycle)cout<<"\nCycle found\n";
}
