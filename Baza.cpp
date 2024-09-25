#include "Baza.h"

bool Baza::overflowCheck()
{
   return size < MAX_NUM_EMPLOYEES;
}

int Baza::findEmp(const string& name) const
{
   for (int i = 0; i < size; i++)
   {
      if (storage[i].get_fio() == name)
      {
         return i;
      }
   }

   return -1;
}

int Baza::calculateYearsOfService(const string& dateAdm) const
{
   int day = 0;
   int month = 0;
   int year = 0;
   char delimiter = ' ';
   stringstream ss(dateAdm);
   ss >> day >> delimiter >> month >> delimiter >> year;

   time_t t = time(nullptr);
   tm now;
   localtime_s(&now, &t);

   const int currentYear = now.tm_year + 1900;
   const int yearsOfService = currentYear - year;

   return yearsOfService;
}

Baza::Baza()
{
   storage = new Sotrudnik[MAX_NUM_EMPLOYEES];
   size = 0;
}

Baza::Baza(const Baza& other)
{
   copy_base(other);
}

Baza::~Baza()
{
   if (storage != nullptr)
   {
      delete[] storage;
      storage = nullptr;
   }
}

void Baza::add_employee()
{
   if (overflowCheck() == true)
   {
      storage[size].inputInfo();
      size++;
      cout << "��������� ������� ��������\n" << endl;
   }
   else
   {
      cout << "[!] ������: ������������ ����" << endl;
   }
}

void Baza::add_employee(const Sotrudnik& emp)
{
   if (overflowCheck() == true)
   {
      storage[size] = emp;
      size++;
      cout << "��������� ������� ��������\n" << endl;
   }
   else
   {
      cout << "[!] ������: ������������ ����" << endl;
   }
}

void Baza::delete_employee()
{
   string name;
   cout << "������� ������� � �������� ��� �������� ������: ";
   cin.ignore();
   getline(cin, name);
   cout << endl;

   delete_employee(name);
}

void Baza::delete_employee(const string& name)
{
   const int num = findEmp(name);
   if (num == -1)
   {
      cout << "[!] ������: ��������� �� ��� ������" << endl;
      return;
   }

   size--;
   for (int i = num; i < size; i++)
   {
      storage[i] = storage[i + 1];
   }

   cout << "��������� ������� �����" << endl;
}

void Baza::correctionInform()
{
   string name;
   cout << "������� ������� � �������� ��� ������������� ������: ";
   cin.ignore();
   getline(cin, name);
   cout << endl;

   const int num = findEmp(name);
   if (num == -1)
   {
      cout << "[!] ������, ��������� �� ��� ������" << endl;
      return;
   }

   storage[num].inputInfo();
   cout << "���������� � ���������� ������� ��������" << endl;
}

void Baza::readFromFile()
{
   string fileName;
   cout << "������� ��� ����� �� ������� ���������� ������� ������ \
(������� \"-\" ��� ������������� ����� �� ���������): ";
   cin >> fileName;

   if (fileName == "-")
   {
      fileName = "sotrudnik.txt";
   }

   ifstream file(fileName);
   if (!file.is_open())
   {
      cout << "[!] ������ �������� �����\n" << endl;
      return;
   }

   string f;
   string ff;
   int y = 0;
   float s = 0;
   string d;

   while (file >> f >> ff >> y >> s >> d)
   {
      if (overflowCheck() == false)
      {
         cout << "[!] ������: ������������ ����\n" << endl;
         file.close();
         return;
      }

      storage[size].set_all(f + " " + ff, y, s, d);
      size++;
   }

   file.close();

   cout << "������ ������� ������� �� �����\n" << endl;
}

void Baza::printStorage() const
{
   for (int i = 0; i < size; i++)
   {
      cout << "��������� �" << i + 1 << endl;
      storage[i].printInfo();
   }

   cout << endl;
}

void Baza::checkExperience() const
{
   int choice = 0;
   int exp = 0;

   cout << "�������� ��������:" << endl;
   cout << "1. ������� ������ � ����������� ���� ������� ������ n-���" << endl;
   cout << "2. ������� ������ � ����������� ���� ������� ������ n-���" << endl;
   cout << "3. ������� ������ � ����������� ���� ������� ����� n-���" << endl;
   cout << ": ";
   cin >> choice;
   cout << endl;

   cout << "������� ����: ";
   cin >> exp;
   cout << endl;

   switch (choice)
   {
   case 1:
   {
      checkExperience(exp, '>');
      break;
   }
   case 2:
   {
      checkExperience(exp, '<');
      break;
   }
   case 3:
   {
      checkExperience(exp, '=');
      break;
   }
   default:
   {
      cout << "[!] ������: �������� ��������" << endl;
      break;
   }
   }
}

void Baza::checkExperience(const int exp, const char comp) const
{
   bool found = false;
   float averageSalary = 0;
   int count = 0;

   cout << "���������� � �����������, ���� ������� ";
   if (comp == '>')
   {
      cout << "������";
   }
   else if (comp == '<')
   {
      cout << "������";
   }
   else if (comp == '=')
   {
      cout << "�����";
   }
   cout << " " << exp << " ���:" << endl;

   for (int i = 0; i < size; i++)
   {
      const int yearsOfService = calculateYearsOfService(storage[i].get_dateAdm());
      if ((comp == '>' && yearsOfService > exp) ||
         (comp == '<' && yearsOfService < exp) ||
         (comp == '=' && yearsOfService == exp))
      {
         storage[i].printInfo();
         averageSalary += storage[i].get_salary();
         count++;
         found = true;
      }
   }

   if (!found)
   {
      cout << "����������� �� ������ " << (comp == '=' ? "������" : comp == '>' ? "������" : "������")
         << " " << exp << " ��� �� �������." << endl;
   }
   else
   {
      cout << "������� ����� ����������� �������� " << float(averageSalary) / count << "\n" << endl;
   }
}

void Baza::copy_base(const Baza& other)
{
   if (other.size > MAX_NUM_EMPLOYEES)
   {
      cout << "[!] ������: ������ ����������� ����, ������������ �������." << endl;
      return;
   }
   if (storage != nullptr)
   {
      delete[] storage;
   }

   storage = new Sotrudnik[MAX_NUM_EMPLOYEES];

   for (int i = 0; i < other.size; i++)
   {
      storage[i] = other.storage[i];
   }

   size = other.size;

   cout << "���� ������� �����������." << endl;
}

Baza Baza::get_baza() const
{
   return Baza(*this);
}

void Baza::menu()
{
   Baza copy;

   while (true)
   {
      cout << "----- ���� -----" << endl;

      cout << "�������� ��������:" << endl;
      cout << "1. ��������� ���� ������ �� �����" << endl;
      cout << "2. �������� ����������" << endl;
      cout << "3. ������� ����������" << endl;
      cout << "4. �������� ������ ����������" << endl;
      cout << "5. ������� ���� �����������" << endl;
      cout << "6. ������� ���������� � ����������� ���� ������� ������/������/����� n-���" << endl;
      cout << "7. ���������� ���� ������" << endl;
      cout << "0. �����" << endl;

      int choice = 0;
      cout << " - ";
      cin >> choice;
      cout << endl;

      switch (choice)
      {
      case 0:
      {
         cout << "�������� ���������" << endl;
         return;
      }
      case 1:
      {
         readFromFile();
         break;
      }
      case 2:
      {
         add_employee();
         break;
      }
      case 3:
      {
         delete_employee();
         break;
      }
      case 4:
      {
         correctionInform();
         break;
      }
      case 5:
      {
         printStorage();
         break;
      }
      case 6:
      {
         checkExperience();
         break;
      }
      case 7:
      {
         copy.copy_base(*this);
         break;
      }
      default:
      {
         cout << "�������� �����" << endl;
         break;
      }
      }
   }
}
