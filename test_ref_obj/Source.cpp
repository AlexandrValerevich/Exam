#include <iostream>
#include <string>
#include <clocale>
#include <vector>


using namespace std;

enum class Professions
{
    TECHNIK = 1,
    ENGINEER,
    SN_ENGINEER,
};

string GetProfession(Professions pr)
{
    switch (pr)
    {
    case Professions::TECHNIK:
        return "Техник";
        break;
    case Professions::ENGINEER:
        return "Инженер";
        break;
    case Professions::SN_ENGINEER:
        return "Старший инженер";
        break;
    default:
        return "";
        break;
    }
}

double GetSalary(Professions pr)
{
    switch (pr)
    {
    case Professions::TECHNIK:
        return 500.50;
        break;
    case Professions::ENGINEER:
        return 700.70;
        break;
    case Professions::SN_ENGINEER:
        return 1000.00;
        break;
    default:
        return 0;
        break;
    }
}

class Worker
{
private:
    string surname;
    string profession;
    double salary;

public:
    static vector<Worker*>* workers;
    Worker() : surname(""), profession(""), salary(0) {
        workers->push_back(this);
    };
    Worker(string sur, Professions pr) : surname(sur) {
        profession = GetProfession(pr);
        salary = GetSalary(pr);
        workers->push_back(this);
    };
    Worker(string sur, Professions pr, double sal) : surname(sur), salary(sal) {
        profession = GetProfession(pr);
        workers->push_back(this);
    };
    Worker(string sur, string pr, double sal) : surname(sur), profession(pr), salary(sal) {
        workers->push_back(this);
    };
    ~Worker() {
        for (size_t i = 0; i < workers->size(); i++)
        {
            if (workers->at(i) == this)
            {
                workers->erase(workers->cbegin() + i);
                break;
            }
        }
    };

    static void PlusToSalary()
    {
        if (workers->empty())
        {
            return;
        }
        for (size_t i = 0; workers->size() > i; i++)
        {
            workers->at(i)->salary *= 1.15;
        }
    }
    static void IvanEngineer()
    {
        if (workers->empty())
        {
            return;
        }
        for (size_t i = 0; i < workers->size(); i++)
        {
            string temp = workers->at(i)->surname;
            if (temp.empty() || temp == "")
            {
                continue;
            }
            if (temp.compare(0, 4, "Иван") == 0)
            {
                workers->at(i)->profession = "Инженер";
                workers->at(i)->salary = 700.70;
            }
        }
    }

    string ToString()
    {
        string temp;
        temp = "Фамилия: ";
        temp += surname;
        temp += "\nДолжность: ";
        temp += profession;
        temp += "\nОклад: ";
        temp += to_string(salary);
        temp += " руб.\n";
        return temp;
    }




};

vector<Worker*>* Worker::workers = new vector<Worker*>();

int main()
{
    setlocale(0, "");
    Worker w1("Иванов", static_cast<Professions>(1));
    cout << w1.ToString() << endl;

    Worker::PlusToSalary();

    cout << w1.ToString() << endl;

    Worker::IvanEngineer();

    cout << w1.ToString() << endl;
    return 0;
}