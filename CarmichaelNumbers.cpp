#include <iostream>
#include <vector>

using namespace std;

long carmichaels[] = { 561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973 }

bool isCarmichael(long num){
  for(int i=0;i < 15;i++)if(carmichaels[i]==num) return true;
  return false;
}

int main(){
  long num;
  while(cin >> num && num !=0){
    if(isCarmichael(num)) cout << "The number "<< num <<" is a Carmichael number." << endl;
	else cout << num << " is normal." << endl;
  }
  return 0;
}