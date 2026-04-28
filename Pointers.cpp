#include <iostream>
#include "Pointers.h"
#include "util.h"
#include "types.h"

using namespace std;

template <typename T>
void Print(T n) { cout << "valor: " << n << endl; }

// C/C++/C++11...
void f1(TI  n)  { ++n; }

// C++98, C++11...
// n es un parametro por referencia
// n se sobrepone solo con variables del mismo tipo
void f2(TI &n)  { ++n; } 

// C++11 ...
void f3(const TI &ri) {}

// C, C++98, C++11...
// Esto es un paso de puntero por valor
// La variable o contenido apuntado por pi
// nunca pasa realmente pero se puede sobreescribir
// porque el puntero lo está apuntando
// y puedo acceder a él con *pi
void f4(TI *pi)  { ++*pi;  pi = nullptr; }

// C++98, C++11...
// Esto si es un paso de puntero por referencia
// Se puede sobreescribir el puntero
// rpi es una referencia
void f5(TI *&rpi) { ++*rpi;    rpi = nullptr; }

void f6(TI **ppi)  { ++**ppi;  ppi  = nullptr; }
void f7(TI **&rppi){ ++**rppi; rppi = nullptr; }

void DemoPointers1() {
  TI a = 10, b = 20, &ref = a;
  TI *p   = nullptr, *q; // q apunta a un lugar impredecible
  TI **pp = nullptr;

  p  = &a;   q = &b;
  pp = &p;

  cout << "a: " << a << "\t&a: " << &a << endl;
  cout << "p: " << p << "\t&p: " << &p << endl;
  cout << "b: " << b << "\t&b: " << &b << endl;
  cout << "q: " << q << "\t&q: " << &q << endl;
  
  cout << "*p: " << *p << endl;

  cout << "\nCaso #1\n";
  f1(a);   Print(a);
  f1(ref); Print(a);
  f1(5); 
  f1(a+10); 
  f1(*p);   Print(a);
  f1(**pp); Print(a);

  cout << "\nCaso #2\n";
  a = 20;    b = 20;
  f2(a);    Print(a);
  f2(ref);  Print(a);
  // f2(5); // error 
  // f2(a+10); // error
  f2( *p ); Print(a);
  f2(**pp); Print(a);

  cout << "\nCaso #3\n";
  a = 30;    b = 20;
  f3(a);    Print(a);
  f3(ref);  Print(a);
  f3(5);    Print(a);
  f3(a+10); Print(a);
  f3( *p ); Print(a);
  f3(**pp); Print(a);

  cout << "\nCaso #4\n";
  a = 40;    b = 20;
  f4(&a);    Print(a);
  f4(&ref);  Print(a);
  f4(p);     Print(a);
  f4(*pp);   Print(a);

  cout << "\nCaso #5\n";
  a = 50;    b = 20;
  // f4(&a);    Print(a); // error
  // f4(&ref);  Print(a); // error
  f5(p);     Print(a);
  cout << "p: " << p << endl;
  p = &a;
  f5(*pp);   Print(a);
  p = &a;

  cout << "\nCaso #6\n";
  a = 60;    b = 20;
  f6(&p);    Print(a);
  f6(pp);    Print(a);

  cout << "\nCaso #7\n";
  a = 70;    b = 20;
  f7(pp);    Print(a);
  // f7(&p);
  cout << "pp: " << pp << endl;
}