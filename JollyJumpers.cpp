#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
  int a,b,n,count,n_original;
  while (cin >> n){
   if ( n == 1 ){
      cin >> n;
      cout << "Jolly" << endl;
    }
    else{
      count=0;
      n_original=n;
      bool visitados[n];for (int i=0;i < n; i++){visitados[i]=false;}
      cin >> a;
      while (n-- > 1){
        cin >> b;
        if ((abs(a-b) < n_original) && (abs(a-b) != 0) && !(visitados[abs(a-b)])){
          visitados[abs(a-b)]=true;
          count++;
        }
        a=b;
      }
      if (count == (n_original-1)){cout << "Jolly" << endl;}
      else{cout << "Not jolly" << endl;}
    }
  }
  return 0; 
}
