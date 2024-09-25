#pragma once

#include <iostream>
#include <string>
using namespace std;

class Sotrudnik
{
private:
   string fio;       // Фамилия и инициалы
   int yearOfBirth;  // Год рождения
   float salary;     // Оклад
   string dateAdm;   // Дата поступения на работу в формате ДД.ММ.ГГГГ

public:
   Sotrudnik() {}
   Sotrudnik(const string& fio, const int yearOfBirth, const float salary, const string& dateAdm);

   void set_fio(const string& f);
   void set_yearOfBirth(const int year);
   void set_salary(const float s);
   void set_dateAdm(const string& date);
   void set_all(const string& f, const int year, const float s, const string& date);

   string get_fio();
   int get_yearOfBirth();
   float get_salary();
   string get_dateAdm();
   void get_all(string& f, int& year, float& s, string& date) const;

   void printInfo();
   void inputInfo();
};