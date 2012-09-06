#include <iostream>
using namespace std;

int main(){
  int numOfTestCases,days,numParties,tot,result,hartal,i;
  cin >> numOfTestCases;
  while (numOfTestCases > 0){
    cin >> days;
    bool calendar[days+1];for(i=1;i<days+1;i++)calendar[i]=false;
    result=0;
    cin >> numParties;
    while  (numParties > 0){
      cin >> hartal;
      tot=hartal;
      while (tot <= days){
        if (!calendar[tot] && (tot%7!=6) && (tot%7!=0)){
          calendar[tot]=true;
          result++;
        }
        tot+=hartal;
      }
      numParties--;
    }
    cout << result << endl;
    numOfTestCases--;
  }
  return 0;
}

