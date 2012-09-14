#include <queue>
#include <utility>
#include <map>
#include <vector>

using namespace std;
// Declaracion del grafo
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
//Fin Declaracion del grafo

class CompareElements { //Comparador para min-heap
public:
    bool operator()(pair<int,Vertex> & e1, pair<int,Vertex> & e2)
    {
      return (e1.first > e2.first);
    }
};

void dijkstra(map<int,Vertex> & graph,int s,vector<int> & path){
  priority_queue<pair<int,Vertex>,vector< pair<int,Vertex> >,CompareElements> heap; //pair<int,Vertex> puede sustituirse con un typdef pair<int,Vertex> distV
  vector<int> dv(graph.size()+1,9999); // inicializo vector de distancias
  vector<int> pv(graph.size()+1,0); // inicializo vector de camino minimo
  vector<bool> known(graph.size()+1,false); // inicializo vector de conocidos
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
  path=pv;
}

