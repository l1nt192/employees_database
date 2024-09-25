#pragma once

#include <fstream>
#include <ctime>
#include <sstream>

#include "Sotrudnik.h"

class Baza
{
private:
   enum { MAX_NUM_EMPLOYEES = 100 };

   Sotrudnik* storage;
   int size;

   bool overflowCheck();
   int findEmp(const string& name) const;
   int calculateYearsOfService(const string& dateAdm) const;

public:
   Baza();
   Baza(const Baza& other);
   ~Baza();

   void add_employee();
   void add_employee(const Sotrudnik& emp);
   void delete_employee();
   void delete_employee(const string& name);
   void correctionInform();

   void readFromFile();

   void printStorage() const;
   void checkExperience() const;
   void checkExperience(const int exp, const char comp) const;

   void copy_base(const Baza& other);
   Baza get_baza() const;

   void menu();
};