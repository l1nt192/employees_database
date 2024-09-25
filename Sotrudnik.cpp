#include "Sotrudnik.h"

Sotrudnik::Sotrudnik(const string& fio, const int yearOfBirth, const float salary, const string& dateAdm) 
   : fio(fio), yearOfBirth(yearOfBirth), salary(salary), dateAdm(dateAdm) {}

void Sotrudnik::set_fio(const string& f)
{
   fio = f;
}

void Sotrudnik::set_yearOfBirth(const int year)
{
   yearOfBirth = year;
}

void Sotrudnik::set_salary(const float s)
{
   salary = s;
}

void Sotrudnik::set_dateAdm(const string& date)
{
   dateAdm = date;
}

void Sotrudnik::set_all(const string& f, const int year, const float s, const string& date)
{
   fio = f;
   yearOfBirth = year;
   salary = s;
   dateAdm = date;
}

string Sotrudnik::get_fio()
{
   return fio;
}

int Sotrudnik::get_yearOfBirth()
{
   return yearOfBirth;
}

float Sotrudnik::get_salary()
{
   return salary;
}

string Sotrudnik::get_dateAdm()
{
   return dateAdm;
}

void Sotrudnik::get_all(string& f, int& year, float& s, string& date) const
{
   f = fio;
   year = yearOfBirth;
   s = salary;
   date = dateAdm;
}

void Sotrudnik::printInfo()
{
   cout << "ФИО: " << fio << endl;
   cout << "Год рождения : " << yearOfBirth << endl;
   cout << "Оклад: " << salary << endl;
   cout << "Дата поступения на работу: " << dateAdm << endl << endl;
}

void Sotrudnik::inputInfo()
{
   cout << "Введите фамилию и инициалы работника: ";
   cin.ignore();
   getline(cin, fio);
   cout << "Введите год рождения: ";
   cin >> yearOfBirth;
   cout << "Введите оклад";
   cin >> salary;
   cout << "Введите дату поступения на работу в формате ДД.ММ.ГГГГ: ";
   cin >> dateAdm;
   cout << "Данные успешно введены\n" << endl;
}