//---------------------//
//Is bigger smarter?  //
//-------------------//
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct elephant{
  int id, weight, IQ; 
};

bool compareElephants(elephant e1, elephant e2){
  if(e1.weight != e2.weight) return(e1.weight < e2.weight);
  else return(e1.IQ < e2.IQ);
}

int LIS(vector<elephant> & herd, vector<int> & predecesor, vector<int> & dp){
  int max = -1;
  for(vector<elephant>::iterator i=herd.begin();i!=herd.end();++i){
    for(vector<elephant>::iterator j=herd.begin();j < i;++j){
      if(((*j).IQ  > (*i).IQ) && (dp[(*i).id] < dp[(*j).id] + 1)){  //si el elefante j-esimo anterior al actual tiene mayor IQ y su subseq. maxima + 1 es mayor al del actual , se actualizan los datos
        dp[(*i).id]=dp[(*j).id] + 1;
        predecesor[(*i).id] = (*j).id;
      }
    }
    max=(dp[max] < dp[(*i).id])?(*i).id:max;
  }
  
  return max;
}

void generateResults(vector<int> & predecesor, vector<int> & v, int maxLis){
  v.push_back(maxLis);
  while(predecesor[maxLis] != -1){
    v.push_back(predecesor[maxLis]);
    maxLis = predecesor[maxLis];
  }
  reverse(v.begin(),v.end());
}

int main(){
  vector<elephant> herd;
  elephant e;
  int id=1;
  while (cin >> e.weight >> e.IQ && e.weight != 0 && e.IQ != 0){
    e.id=id++;
    herd.push_back(e);
  }
  sort(herd.begin(), herd.end(), compareElephants);//ordeno el vector de elefantes por peso creciente
  
  vector<int> predecesor(herd.size()+1,-1);
  vector<int> dp(herd.size()+1,1);
  int maxLis = LIS(herd,predecesor,dp); //genero LIS
  
  vector<int> listResult;
  generateResults(predecesor, listResult, maxLis); //genero resultados a partir de la lista de predecesores
  cout << dp[maxLis] << endl; //imprimo resultados
  for(vector<int>::iterator it=listResult.begin();it!=listResult.end();++it){
    cout << (*it) << endl;
  }
}
