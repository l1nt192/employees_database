#include "Sotrudnik.h"
#include "Baza.h"

#include <locale>

int main()
{
   setlocale(LC_ALL, "Russian");
   Baza baza;
   baza.menu();

   return 0;
}  