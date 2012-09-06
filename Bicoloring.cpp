#include <iostream>
#include <list>
using namespace std;

typedef struct{
  int color;
  list<int> adjacents;
} Vertex;

bool dfs(int vertex,Vertex graph[],bool visited[]){
  visited[vertex]=true;
  list<int>::iterator j;
  for(j=graph[vertex].adjacents.begin();j!=graph[vertex].adjacents.end();j++){
      if(graph[*j].color == graph[vertex].color){ // retorno falso si algun vertice adyacente tiene el mismo color
        return false;
      }
      else{
        if (!visited[*j]){ // sino pinto del color opuesto todos los adyacentes y llamo a dfs
          graph[*j].color=!graph[vertex].color;
          return (dfs(*j,graph,visited));
        }
      }
    }
  return true;
}

int main(){
  int numOfEdges,adj1,adj2,numOfVertex,i;
  cin >> numOfVertex;
  while (numOfVertex != 0){
    Vertex graph[numOfVertex];
    for (i=0;i < numOfVertex;i++) graph[i].color=3;  // creo grafo y pinto todos los vertices con un color "indefinido"
    cin >> numOfEdges;
    while (numOfEdges > 0){
      cin >> adj1;
      cin >> adj2;
      graph[adj1].adjacents.push_back(adj2);
      graph[adj2].adjacents.push_back(adj1);
      numOfEdges--;
    }
    // Termine de crear el grafo
    bool visited[numOfVertex];for(i=0;i < numOfVertex;i++) visited[i]=false;
    graph[0].color=false;
    if (dfs(0,graph,visited)){cout << "BICOLORABLE." << endl;}
    	else{cout << "NOT BICOLORABLE." << endl;
    }
    cin >> numOfVertex;
  }
  return 0;  
}

