#include<iostream>
#include<vector>
#include<queue>
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
  graph.insert(make_pair(num,v));
}
class CompareEdge {
public:
    bool operator()(Edge& e1, Edge& e2)
    {
      return (e1.weight > e2.weight);
    }
};

void Kruskal(map<int,Vertex> & graph,map<int,Vertex> & maxTree){
  priority_queue<Edge,vector<Edge>,CompareEdge > q; //ver el compare
  for (map<int,Vertex>::iterator gr=graph.begin();gr!= graph.end();++gr){
    for (vector<Edge>::iterator ed=(*gr).second.adjacency.begin();ed!=(*gr).second.adjacency.end();++ed){
      q.push(*ed);
    }
  }
  vector<int> pertenece(graph.size()+1,-1);//inicializamos conjuntos virtuales en vacio
  bool belong;
  int numEdges=1;
  int source , destination,i;
  while (numEdges < graph.size()){
    belong=false;
    Edge e=q.top();
    source= (*e.source).dato;
    destination= (*e.destination).dato;
    i=destination;
    while (pertenece[i]!=destination && pertenece[i]!=-1){
      if(pertenece[i]==source){belong=true;} 
      i=pertenece[i];
    }
    if (!belong){
      if (pertenece[source]==-1 && pertenece[destination]==-1){
         pertenece[source]=destination;
         pertenece[destination]=source;
      }
      else{
        if (pertenece[source]==-1){
          pertenece[source]=pertenece[destination];
          pertenece[destination]=source;
        }
        else{
          if (pertenece[destination]==-1){
            pertenece[destination]=pertenece[source];
            pertenece[source]=destination;
          }
          else{
            int aux=pertenece[destination];
            pertenece[destination]=pertenece[source];
            pertenece[source]=aux;
          }  
        }
      }
      link(maxTree,source,destination,e.weight);//agrego arista al grafo
      link(maxTree,destination,source,e.weight);
      numEdges++;
    }
    q.pop();
  }
}

int main(){
  map<int,Vertex> graph;
  map<int,Vertex> maxTree;
  addVertex(graph,1);
  addVertex(graph,2);
  addVertex(graph,3);
  addVertex(graph,4);
  addVertex(graph,5);
  addVertex(graph,6);
  link(graph,1,2,10);
  link(graph,2,1,10);
  link(graph,1,4,30);
  link(graph,4,1,30);
  link(graph,1,5,45);
  link(graph,5,1,45);
  link(graph,2,3,50);
  link(graph,3,2,50);
  link(graph,2,5,40);
  link(graph,5,2,40);
  link(graph,2,6,25);
  link(graph,6,2,25);
  link(graph,3,5,35);
  link(graph,5,3,35);
  link(graph,3,6,15);
  link(graph,3,6,15); 
  link(graph,4,6,20);
  link(graph,6,4,20);
  link(graph,5,6,55);
  link(graph,6,5,55);
  Kruskal(graph,maxTree);
  return 0;
}
