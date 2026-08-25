#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>graph;
vector<vector<vector<int>>>path;

int main(){

  int node,edge;
  cin>>node>>edge;

  graph.assign(node,vector<int>(node,INT_MAX));
  path.assign(node,vector<vector<int>>(node));

  for(int i=0; i<node; i++){
     graph[i][i] =0;
     path[i][i] = {i};
  }


  for(int i=0; i<edge; i++){
    int u,v,w;
    cin>>u>>v>>w;
    graph[u][v] = w;
    path[u][v] = {u,v};
  }

  for(int k=0; k<node; k++){
    for(int i=0; i<node; i++){
        for(int j=0; j<node; j++){
            if(graph[i][k]!= INT_MAX && graph[k][j]!=INT_MAX && graph[i][j]>graph[i][k] + graph[k][j]){
                        graph[i][j] = graph[i][k] + graph[k][j];
                        path[i][j] = path[i][k];

                        for(auto &x: path[k][j]){
                            if(x!=k) path[i][j].push_back(x);
                        }

            }
        }
    }
  }


  cout<<"\nCost\n";
  for(auto &x:graph){
    for(auto &y:x){
        if(y!=INT_MAX)cout<<y<<" ";
        else cout<<-1<<" ";
    }
    cout<<endl;
  }

  cout<<"\nPaths\n";
  for(int i=0; i<path.size(); i++){
    for(int j=0; j<path[i].size(); j++){
        if(graph[i][j]!=INT_MAX){
        for(auto &z:path[i][j])cout<<z<<" ";
        cout<<" ";
       }
       else cout<<"INF ";
    }
    cout<<endl;
  }

}
