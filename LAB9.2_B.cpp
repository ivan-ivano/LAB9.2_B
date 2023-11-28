#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>


using namespace std;

enum Spec { Comp_Nauk, Inf, Mat_Econ, Fiz_Inf, Trud_Navch };
string specStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
    string prizv;
    int kyrs;
    Spec spec;
    int fiz;
    int mat;
    union
    {
        int prog;
        int chsl_metod;
        int ped;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string& prizv, const int kyrs, const int mat);



int main()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];
    Create(p, N);
    Print(p, N);

    Sort(p, N);
    Print(p, N);
    PrintIndexSorted(p, IndexSort(p, N), N);


    if (BinSearch(p, N, "Мельник", 1, 5) != -1)
        cout << "Знайдено студента з прізвищем Мельник на 1 курсі з оцінкою з математики 5" << endl;
    else
        cout << "Такого студента не знайдено" << endl;

    return 0;
}


void Create(Student* p, const int N)
{
    int spec;
    string prizvList[] = {
        "Панчишин", "Сидоренко", "Коваленко", "Мельник", "Мороз", "Григоренко", "Ковальчук", "Павленко",
        "Бойко", "Лисенко", "Шевченко", "Бондаренко", "Ткаченко", "Кузьменко", "Козак", "Кучер", "Василенко", "Остапенко",
        "Попов", "Литвин", "Гончаренко", "Панченко", "Єфіменко", "Кравченко", "Захарченко", "Онопрієнко", "Савченко"
    };
    for (int i = 0; i < N; i++)
    {
        p[i].prizv = prizvList[rand() % 4];
        p[i].kyrs = rand() % 4 + 1;
        p[i].spec = static_cast<Spec>(rand() % 5);
        switch (p[i].spec)
        {
        case Comp_Nauk:
            p[i].prog = rand() % 5 + 1;
            break;
        case Inf:
            p[i].chsl_metod = rand() % 5 + 1;
            break;
        default:
            p[i].ped = rand() % 5 + 1;
            break;
        }
        p[i].fiz = rand() % 5 + 1;
        p[i].mat = rand() % 5 + 1;
    }
}


void Print(Student* p, const int N)
{
    cout << "===================================================================================================================================" << endl;
    cout << "|  № | Прізвище       | Курс | Спеціальність                 | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(15) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kyrs << " "
            << "| " << setw(30) << left << specStr[p[i].spec]
            << "| " << setw(6) << setprecision(2) << fixed << right << p[i].fiz
            << " | " << setw(10) << setprecision(2) << fixed << right << p[i].mat;
        switch (p[i].spec)
        {
        case Comp_Nauk:
            cout << " | " << setw(13) << setprecision(2) << fixed << p[i].prog << " |";
            cout << setw(16) << setprecision(2) << fixed << right << "" << " |";
            cout << setw(10) << setprecision(2) << fixed << right << "" << "  |" << endl;
            break;
        case Inf:
            cout << " | " << setw(13) << setprecision(2) << fixed << right << "";
            cout << " |" << setw(16) << setprecision(2) << fixed << right << p[i].chsl_metod << " |";
            cout << setw(10) << setprecision(2) << fixed << right << "" << "  |" << endl;
            break;
        default:
            cout << " | " << setw(13) << setprecision(2) << fixed << right << "" << " |";
            cout << setw(16) << setprecision(2) << fixed << right << "";
            cout << " | " << setw(10) << setprecision(2) << fixed << right << p[i].ped << " |" << endl;
            break;
        }

    }
    cout << "===================================================================================================================================" << endl;
    cout << endl;
}




void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].kyrs > p[i1 + 1].kyrs)
                ||
                (p[i1].kyrs == p[i1 + 1].kyrs && p[i1].mat < p[i1 + 1].mat)
                ||
                ((p[i1].mat == p[i1 + 1].mat && p[i1].prizv < p[i1 + 1].prizv)))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((p[I[j]].kyrs > p[value].kyrs)
                ||
                (p[I[j]].kyrs == p[value].kyrs && p[I[j]].mat < p[value].mat)
                ||
                ((p[I[j]].mat == p[value].mat && p[I[j]].prizv > p[value].prizv)));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}


void PrintIndexSorted(Student* p, int* I, const int N)
{
    cout << "===================================================================================================================================" << endl;
    cout << "|  № | Прізвище       | Курс | Спеціальність                 | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(15) << left << p[I[i]].prizv
            << "| " << setw(4) << right << p[I[i]].kyrs << " "
            << "| " << setw(30) << left << specStr[p[I[i]].spec]
            << "| " << setw(6) << setprecision(2) << fixed << right << p[I[i]].fiz
            << " | " << setw(10) << setprecision(2) << fixed << right << p[I[i]].mat;
        switch (p[I[i]].spec)
        {
        case Comp_Nauk:
            cout << " | " << setw(13) << setprecision(2) << fixed << p[I[i]].prog << " |";
            cout << setw(16) << setprecision(2) << fixed << right << "" << " |";
            cout << setw(10) << setprecision(2) << fixed << right << "" << "  |" << endl;
            break;
        case Inf:
            cout << " | " << setw(13) << setprecision(2) << fixed << right << "";
            cout << " |" << setw(16) << setprecision(2) << fixed << right << p[I[i]].chsl_metod << " |";
            cout << setw(10) << setprecision(2) << fixed << right << "" << "  |" << endl;
            break;
        default:
            cout << " | " << setw(13) << setprecision(2) << fixed << right << "" << " |";
            cout << setw(16) << setprecision(2) << fixed << right << "";
            cout << " | " << setw(10) << setprecision(2) << fixed << right << p[I[i]].ped << " |" << endl;
            break;
        }

    }
    cout << "===================================================================================================================================" << endl;
    cout << endl;
}



int BinSearch(Student* p, const int N, const string& prizv, const int kyrs, const int mat) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].kyrs == kyrs && p[m].mat == mat)
            return m;
        if ((p[m].kyrs < kyrs)

            ||
            (p[m].kyrs == kyrs && p[m].mat > mat)
            ||
            (p[m].mat == mat && p[m].prizv > prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
