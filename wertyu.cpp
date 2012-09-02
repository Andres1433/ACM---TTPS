#include <iostream>
#include <map>
#include <utility>

using namespace std;
typedef map<char,char> Mapa;

void crear_teclado(Mapa& teclado)
{
  teclado.insert(make_pair('1','`'));
  teclado.insert(make_pair('2','1'));
  teclado.insert(make_pair('3','2'));
  teclado.insert(make_pair('4','3'));
  teclado.insert(make_pair('5','4'));
  teclado.insert(make_pair('6','5'));
  teclado.insert(make_pair('7','6'));
  teclado.insert(make_pair('8','7'));
  teclado.insert(make_pair('9','8'));
  teclado.insert(make_pair('0','9'));
  teclado.insert(make_pair('-','0'));
  teclado.insert(make_pair('=','-'));
  teclado.insert(make_pair('W','Q'));
  teclado.insert(make_pair('E','W'));
  teclado.insert(make_pair('R','E'));
  teclado.insert(make_pair('T','R'));
  teclado.insert(make_pair('Y','T'));
  teclado.insert(make_pair('U','Y'));
  teclado.insert(make_pair('I','U'));
  teclado.insert(make_pair('O','I'));
  teclado.insert(make_pair('P','O'));
  teclado.insert(make_pair('[','P'));
  teclado.insert(make_pair(']','['));
  teclado.insert(make_pair('\\',']'));
  teclado.insert(make_pair('S','A'));
  teclado.insert(make_pair('D','S'));
  teclado.insert(make_pair('F','D'));
  teclado.insert(make_pair('G','F'));
  teclado.insert(make_pair('H','G'));
  teclado.insert(make_pair('J','H'));
  teclado.insert(make_pair('K','J'));
  teclado.insert(make_pair('L','K'));
  teclado.insert(make_pair(';','L'));
  teclado.insert(make_pair('\'',';'));
  teclado.insert(make_pair('X','Z'));
  teclado.insert(make_pair('C','X'));
  teclado.insert(make_pair('V','C'));
  teclado.insert(make_pair('B','V'));
  teclado.insert(make_pair('N','B'));
  teclado.insert(make_pair('M','N'));
  teclado.insert(make_pair(',','M'));
  teclado.insert(make_pair('.',','));
  teclado.insert(make_pair('/','.'));
}
int main(){
  Mapa keyboard;
  crear_teclado(keyboard);
  string linea;
  while (getline(cin,linea)){
    for (int i=0;i < linea.size();i++){
      cout << ((linea[i]==' ')?' ':keyboard[linea[i]]);
    }
    cout << endl;
  }
  return 0;
}
