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
      cout << "Сотрудник успешно добавлен\n" << endl;
   }
   else
   {
      cout << "[!] Ошибка: переполнение базы" << endl;
   }
}

void Baza::add_employee(const Sotrudnik& emp)
{
   if (overflowCheck() == true)
   {
      storage[size] = emp;
      size++;
      cout << "Сотрудник успешно добавлен\n" << endl;
   }
   else
   {
      cout << "[!] Ошибка: переполнение базы" << endl;
   }
}

void Baza::delete_employee()
{
   string name;
   cout << "Введите фамилию и инициалы для удаления данных: ";
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
      cout << "[!] Ошибка: сотрудник не был найден" << endl;
      return;
   }

   size--;
   for (int i = num; i < size; i++)
   {
      storage[i] = storage[i + 1];
   }

   cout << "Сотрудник успешно удалён" << endl;
}

void Baza::correctionInform()
{
   string name;
   cout << "Введите фамилию и инициалы для корректировки данных: ";
   cin.ignore();
   getline(cin, name);
   cout << endl;

   const int num = findEmp(name);
   if (num == -1)
   {
      cout << "[!] Ошибка, сотрудник не был найден" << endl;
      return;
   }

   storage[num].inputInfo();
   cout << "Информация о сотруднике успешно изменена" << endl;
}

void Baza::readFromFile()
{
   string fileName;
   cout << "Введите имя файла из котрого необходимо считать данные \
(введите \"-\" для использования файла по умолчанию): ";
   cin >> fileName;

   if (fileName == "-")
   {
      fileName = "sotrudnik.txt";
   }

   ifstream file(fileName);
   if (!file.is_open())
   {
      cout << "[!] Ошибка открытия файла\n" << endl;
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
         cout << "[!] Ошибка: переполнение базы\n" << endl;
         file.close();
         return;
      }

      storage[size].set_all(f + " " + ff, y, s, d);
      size++;
   }

   file.close();

   cout << "Данные успешно считаны из файла\n" << endl;
}

void Baza::printStorage() const
{
   for (int i = 0; i < size; i++)
   {
      cout << "Сотрудник №" << i + 1 << endl;
      storage[i].printInfo();
   }

   cout << endl;
}

void Baza::checkExperience() const
{
   int choice = 0;
   int exp = 0;

   cout << "Выберите действие:" << endl;
   cout << "1. Вывести данные о сотрудниках стаж которых больше n-лет" << endl;
   cout << "2. Вывести данные о сотрудниках стаж которых меньше n-лет" << endl;
   cout << "3. Вывести данные о сотрудниках стаж которых равен n-лет" << endl;
   cout << ": ";
   cin >> choice;
   cout << endl;

   cout << "Введите стаж: ";
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
      cout << "[!] Ошибка: неверное действие" << endl;
      break;
   }
   }
}

void Baza::checkExperience(const int exp, const char comp) const
{
   bool found = false;
   float averageSalary = 0;
   int count = 0;

   cout << "Информация о сотрудниках, стаж которых ";
   if (comp == '>')
   {
      cout << "больше";
   }
   else if (comp == '<')
   {
      cout << "меньше";
   }
   else if (comp == '=')
   {
      cout << "равен";
   }
   cout << " " << exp << " лет:" << endl;

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
      cout << "Сотрудников со стажем " << (comp == '=' ? "равным" : comp == '>' ? "больше" : "меньше")
         << " " << exp << " лет не найдено." << endl;
   }
   else
   {
      cout << "Средний оклад сотрудников составил " << float(averageSalary) / count << "\n" << endl;
   }
}

void Baza::copy_base(const Baza& other)
{
   if (other.size > MAX_NUM_EMPLOYEES)
   {
      cout << "[!] Ошибка: нельзя скопировать базу, недопустимые размеры." << endl;
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

   cout << "База успешно скопирована." << endl;
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
      cout << "----- Меню -----" << endl;

      cout << "Выберите действие:" << endl;
      cout << "1. Загрузить базу данных из файла" << endl;
      cout << "2. Добавить сотрудника" << endl;
      cout << "3. Удалить сотрудника" << endl;
      cout << "4. Обновить данные сотрудника" << endl;
      cout << "5. Вывести всех сотрудников" << endl;
      cout << "6. Вывести информацию о сотрудниках стаж которых меньше/больше/равен n-лет" << endl;
      cout << "7. Копировать базу данных" << endl;
      cout << "0. Выйти" << endl;

      int choice = 0;
      cout << " - ";
      cin >> choice;
      cout << endl;

      switch (choice)
      {
      case 0:
      {
         cout << "Закрытие программы" << endl;
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
         cout << "Неверный выбор" << endl;
         break;
      }
      }
   }
}
