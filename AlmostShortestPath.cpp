#include<iostream>
#include<queue>
#include<utility>
#include<vector>
#include<map>

using namespace std;

struct Edge;
struct Vertex{
  int dato;
  vector<Edge> adjacency;
};

struct Edge{
  int weight;
  Vertex * source;
  Vertex * destination;
};

void link(map<int,Vertex> & graph,int v1,int v2,int aWeight){
  Edge anEdge;
  anEdge.weight=aWeight;
  anEdge.source= &(graph[v1]);
  anEdge.destination= &(graph[v2]);
  graph[v1].adjacency.push_back(anEdge);
} 

void addVertex(map<int,Vertex> & graph,int num){
  Vertex v;
  v.dato=num;
  graph.insert(make_pair(num,v)); //porque es un map , sino graph.push_back(v)
}

void removeLink(map<int,Vertex> & graph,int v1,int v2){
  for(vector<Edge>::iterator e=graph[v1].adjacency.begin();e!=graph[v1].adjacency.end();++e){
    if((*(*e).destination).dato==v2){
      graph[v1].adjacency.erase(e);
      break;
    }
  }
}

class CompareElements { //Comparador para min-heap
public:
    bool operator()(pair<int,Vertex> & e1, pair<int,Vertex> & e2)
    {
      return (e1.first > e2.first);
    }
};

void dijkstra(map<int,Vertex> & graph,int s,vector<int> & path){
  priority_queue<pair<int,Vertex>,vector< pair<int,Vertex> >,CompareElements> heap; //pair<int,Vertex> puede sustituirse con un typdef pair<int,Vertex> distV
  vector<int> dv(graph.size(),9999); // inicializo vector de distancias
  vector<int> pv(graph.size(),0); // inicializo vector de camino minimo
  vector<bool> known(graph.size(),false); // inicializo vector de conocidos
  dv[graph[s].dato]=0;
  heap.push(make_pair(0,graph[s]));
  while (!heap.empty()){
    pair<int,Vertex> p=heap.top();
    heap.pop();
    Vertex u=p.second;
    known[u.dato]=true;
    for (vector<Edge>::iterator e=u.adjacency.begin();e!=u.adjacency.end();++e){
      if(!(known[(*(*e).destination).dato])){
        if(((*e).weight + p.first) < dv[(*(*e).destination).dato]){ //(*(*e).destination).dato puede cambiar po Vertex dest=(*(*e).destination).dato
	  dv[(*(*e).destination).dato]=(*e).weight + p.first;
	  pv[(*(*e).destination).dato]=u.dato;
	  heap.push(make_pair((*e).weight + p.first,(*(*e).destination)));
	}
      }
    }
  }
  path=dv;
}

int main(){
  int N,M,startingPoint,destinationPoint,U,V,P;
  cin >> N >> M;
  while (N!=0 && M!=0){
    map<int,Vertex> graphS,graphD;
    for(int i=0;i<N;i++){
      addVertex(graphS,i);
      addVertex(graphD,i);
    }
    cin >> startingPoint >> destinationPoint;
    for(;M>0;M--){
      cin >> U >> V >> P;
      link(graphS,U,V,P);
      link(graphD,V,U,P);
    }
    vector<int> distancesFromStart;
    vector<int> distanceFromDestination;  
    dijkstra(graphS,startingPoint,distancesFromStart);
    if (distancesFromStart[destinationPoint]!=9999){
      dijkstra(graphD,destinationPoint,distanceFromDestination);
      for (map<int,Vertex>::iterator v=graphS.begin();v!=graphS.end();++v){
        for(vector<Edge>::iterator e=(*v).second.adjacency.begin();e!=(*v).second.adjacency.end();++e){
          if (distancesFromStart[(*(*e).source).dato]+(*e).weight+distanceFromDestination[(*(*e).destination).dato] == distancesFromStart[destinationPoint]){
            removeLink(graphS,(*(*e).source).dato,(*(*e).destination).dato);
            e--;
          }
        }
      }
      dijkstra(graphS,startingPoint,distancesFromStart);
      int dist=(distancesFromStart[destinationPoint]==9999)?-1:distancesFromStart[destinationPoint];
      cout << dist << endl;
    }
    else{
      cout << -1 << endl;
    }
    cin >> N >> M; 
  }
  return 0;
}
/*
7 9 
0 6
0 1 1 
0 2 1
0 3 2
0 4 3
1 5 2
2 6 4
3 6 2
4 6 4
5 6 1
4 6
0 2
0 1 1
1 2 1
1 3 1
3 2 1
2 0 3
3 0 2
6 8 
0 1
0 1 1
0 2 2
0 3 3
2 5 3
3 4 2
4 1 1
5 1 1
3 0 1
0 0
*/
