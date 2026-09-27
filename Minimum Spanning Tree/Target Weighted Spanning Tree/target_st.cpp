#include<bits/stdc++.h>
using namespace std;

//DSU for cycle detection
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i) {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
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

//Edge and graph
struct Edge{
  int u,v,w;
};
vector<Edge>G;

//Bounding (and Criterion) function

bool valid(DSU &dsu, Edge &e, int wt, int st, int V, int target) {
    if (st == V - 1)
        return false;


    return dsu.find(e.u) != dsu.find(e.v)
        && wt + e.w <= target;
}


//Recursive function

pair<int, vector<Edge>> solve(DSU dsu, vector<Edge>&st, int V, int target, int weight, int idx){

    //Spanning tree generated
    if(st.size()==V-1){
            if(weight== target) return {weight,st};
            return {-1,st};
    }

    if(idx == G.size()) return {-1,st};

    //Not enough edges left
    if (G.size() - idx < V - 1 - st.size())
        return {-1,st};


    if(valid(dsu, G[idx], weight, st.size(), V, target)){

        //Take G[idx]
        DSU temp_dsu = dsu;
        temp_dsu.unite(G[idx].u, G[idx].v);
        st.push_back(G[idx]);

        auto ans = solve(temp_dsu,st,V, target, weight+G[idx].w, idx+1);

        if(ans.first!=-1) return ans;
        else st.pop_back();
    }

    //Skip G[idx]
    return solve(dsu,st,V,target,weight,idx+1);
}



int main(){

    int V, edges, target;
    cin >>V>>edges>>target;

    for(int i=0; i<edges; i++){
        int u,v,w;
        cin>>u>>v>>w;
        G.push_back({u,v,w});
    }
    vector<Edge>st;

    DSU dsu(V);
    auto ans = solve(dsu, st, V, target, 0, 0);
    if(ans.first == -1)cout<<"Target not possible";
    else{
        cout<<"MST\n";
        for(auto &[x,y,z]: ans.second)cout<<x<<" "<<y<<" "<<z<<endl;
    }

}
