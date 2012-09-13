#include<iostream>
#include<vector>
#include<queue>
#include<map>
// test case 7 10 1 2 30 1 3 15 1 4 10 2 4 25 2 5 60 3 4 40 3 6 20 4 7 35 5 7 20 6 7 30 1 7 99 5 6 1 2 999 2 3 999 3 5 999 5 4 999 1 4 999 1 5 999 1 5 99 0 0
//  6 10 5 6 55 2 3 50 1 5 45 2 5 40 5 3 35 1 4 30 2 6 25 4 6 20 3 6 15 1 2 10 1 3 99 0 0

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
      return (e1.weight < e2.weight);
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

bool dfs(map<int,Vertex> & maxTree,vector<bool> & visited,int act,int dest,vector<int> & path){
  visited[act]=true;
  if (act==dest) return true;
  for (vector<Edge>::iterator e=maxTree[act].adjacency.begin();e!=maxTree[act].adjacency.end();++e){
    if (!(visited[(*(*e).destination).dato])){
      if(dfs(maxTree,visited,(*(*e).destination).dato,dest,path)){
        path.push_back((*e).weight);
        return true;
      }
    }
  }
  return false;
}

int buscarMinimo(map<int,Vertex> & maxTree,int startCity,int destCity){
  vector<bool> visited(maxTree.size()+1,false);
  vector<int> path;
  if (dfs(maxTree,visited,startCity,destCity,path)){}
  int min=9999;
  for (vector<int>::iterator p=path.begin();p!=path.end();++p){
    min=((*p)<min)?(*p):min;
  }
  return min-1;
}

int main(){
  int numOfCities,numOfRoads,adj1,adj2,limit,startCity,destCity,numOfPassengers;
  int scenario=1;
  cin >> numOfCities >> numOfRoads;
  while (numOfCities!=0 && numOfRoads!=0){
    map<int,Vertex> graph,maxTree;
    for (int i=1;i<=numOfCities;i++){
      addVertex(graph,i);
      addVertex(maxTree,i);
    }
    for(;numOfRoads>0;numOfRoads--){
      cin >> adj1 >> adj2 >> limit;
      link(graph,adj1,adj2,limit);
      link(graph,adj2,adj1,limit);
    }
    cin >> startCity >> destCity >> numOfPassengers;
    Kruskal(graph,maxTree);
    cout << "Scenario #" << scenario << endl;
    int trips;
    if ((startCity == destCity) || (numOfPassengers==0)){ 
      trips=0;
    }
    else{
      trips=buscarMinimo(maxTree,startCity,destCity);
      trips=(numOfPassengers % trips == 0)?(numOfPassengers / trips):(numOfPassengers / trips)+1;
    }
    cout << "Minimum Number of Trips = " << trips << endl;
    cout << endl;
    cin >> numOfCities >> numOfRoads;
    scenario++;
  }
  return 0;
}
