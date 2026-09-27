#include<bits/stdc++.h>
using namespace std;

//DSU for cycle detection
class DSU
{
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i)
    {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j)
    {
        int a = find(i);
        int b = find(j);

        if (a == b)
            return;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;
        rank[a] += rank[b];
    }
};

//Edge
struct Edge
{
    int u,v,w;
};
vector<Edge>G;

int best,V;
vector<Edge>st,ans;

//Bounding (and Criterion) function

bool valid(DSU &dsu, Edge &e)
{
    if (st.size() == V - 1)
        return false;

    return dsu.find(e.u) != dsu.find(e.v);
}


//To update or not to update?

void solve(DSU dsu, int target, int weight, int idx)
{

    //Spanning tree generated
    if(st.size()==V-1)
    {
        if(abs(weight-target)<abs(target-best))
        {
            best = weight;
            ans = st;
        }
        return;

    }

    if(idx == G.size()) return;

    //Not enough edges left
    if (G.size() - idx < V - 1 - st.size())
        return;


    if(valid(dsu, G[idx]))
    {

        //Take G[idx]
        DSU temp_dsu = dsu;
        temp_dsu.unite(G[idx].u, G[idx].v);
        st.push_back(G[idx]);

        solve(temp_dsu,target, weight+G[idx].w, idx+1);

        st.pop_back();
    }

    //Skip G[idx]
    solve(dsu,target,weight,idx+1);
}

//Find target
int avgWT(int V)
{
    sort(G.begin(), G.end(), [](Edge a, Edge b)
    {
        return a.w < b.w;
    });
    DSU min_dsu(V), max_dsu(V);

    int minwt=0, maxwt =0;
    for(int i=0; i<G.size(); i++)
    {
        if(min_dsu.find(G[i].u) != min_dsu.find(G[i].v))
        {
            min_dsu.unite(G[i].u, G[i].v);
            minwt+= G[i].w;
        }
    }

    reverse(G.begin(), G.end());
    for(int i=0; i<G.size(); i++)
    {
        if(max_dsu.find(G[i].u) != max_dsu.find(G[i].v))
        {
            max_dsu.unite(G[i].u, G[i].v);
            maxwt+= G[i].w;
        }
    }
    cout<<"Max: "<<maxwt<<" Min: "<<minwt<<" Avg: "<< (minwt+maxwt)/2;
    return (minwt+maxwt)/2;
}

int main()
{

    int edges, target;
    cin>>V>>edges;

    for(int i=0; i<edges; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        G.push_back({u,v,w});
    }

    target = avgWT(V);
    best = INT_MAX;

    vector<Edge>st;

    DSU dsu(V);
    solve(dsu,target, 0, 0);
    cout<<"\nClosest to average : "<<best<<"\nMST\n";
    for(auto &[x,y,z]: ans)cout<<x<<" "<<y<<" "<<z<<endl;

}


