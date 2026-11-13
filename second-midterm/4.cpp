// Да се дефинира класа ExamResult за претставување на резултат од испит на даден студент.

// Во класата да се чуваат следните информации:

// индекс на студентот (string)

// име на студентот (string)

// поени од прв колоквиум (int)

// поени од втор колоквиум (int)

// За класата да се имплементираат:

// Потребните конструктори

// Виртуелен метод int finalPoints() const кој го враќа вкупниот број на освоени поени според формулата:

// (поени_к1 + поени_к2) / 2

// Виртуелен метод bool passed() const кој враќа true доколку студентот го положил испитот (има најмалку 50 поени), во спротивно враќа false

// Виртуелен метод void print() const за печатење на информациите во формат даден во тест примерите

// Виртуелен метод void writeReport(ofstream &out) const кој запишува извештај за студентот во излезна датотека. Форматот е ист како и во методот print().

// Да се дефинира класа ProjectAndExamResult која наследува од ExamResult и претставува резултат од испит кој покрај колоквиумите содржи и студентски проект.

// Во класата дополнително да се чуваат:

// поени од проект (int)

// процент на сличност на проектот со други проекти (int од 0 до 100)

// За класата да се имплементираат:

// Потребните конструктори

// Метод finalPoints() кој ги пресметува вкупните поени според формулата:

// (поени_к1 + поени_к2) * 0.35 + поени_проект

// Метод passed() кој враќа true доколку:

// процентот на сличност е помал или еднаков на 30

// вкупните поени се најмалку 50

// поените од проектот се најмалку 10

// Во спротивно методот враќа false.

// Да се имплементираат следните функции:

// ExamResult* readExamResult(ifstream &in)

// Функцијата чита податоци за резултат од испит на еден студент од еден ред од отворена датотека и враќа покажувач кон ExamResult.

// Форматот на податоците е:

// E – обичен испит

// P – испит со проект

// Пример:

// E 231001 Stefan 24 31
// P 231002 Ana 20 28 18 10

// Функцијата треба да фрли исклучок од тип InvalidStudentIDException доколку студентскиот индекс не е валиден.

// Индексот е валиден доколку:

// содржи точно 6 знаци

// сите знаци се цифри

// ExamResult** readExamResults(ifstream &in, int &n)

// Функцијата чита податоци за резултати од испити за повеќе студенти од отворена датотека и враќа динамички алоцирана низа од покажувачи кон ExamResult.

// Во референцата n треба да се запише бројот на успешно прочитани резултати.

// Во датотеката најпрво е запишан бројот N – број на резултати, а потоа во нов ред следуваат информациите за резултатите во форматот дефиниран во претходната функција.

// За читањето на секој студент задолжително да се користи функцијата readExamResult.

// Доколку се фати исклучок, потребно е:

// да се испечати пораката:

// {ID} is not valid index

// резултатот за тој студент да се игнорира и да не се додаде во низата

// void writePassedStudentsReport(ExamResult **results, int n, const string & filename)

// Функцијата креира излезна датотека filename и во неа ги запишува сите студенти кои го положиле испитот.

#include <fstream>




#include <iostream>
#include <cstring>
using namespace std;

class ExamResult {
protected:
    string index;
    string name;
    int poeni_k1;
    int poeni_k2;
public:
    ExamResult (string index = "", string name = "", int poeni_k1 = 0, int poeni_k2 = 0) {
        this->index = index;
        this->name = name;
        this->poeni_k1 = poeni_k1;
        this->poeni_k2=poeni_k2;
    }
    virtual int finalPoints() const {
        return (poeni_k1+poeni_k2) / 2;
    }
    virtual bool passed() const {
        if (finalPoints() >= 50) {
            return true;
        }
        else {
            return false;
        }
    }
    void print() const {
        cout<<index<< " " << name << " " << finalPoints();

        if (passed()) {
            cout<<" PASSED"<<endl;
        } else {
            cout<<" FAILED"<<endl;
        }
    }
    void writeReport(ofstream &out) const {
        cout<<"NEMAM UCENO DATOTEKI"<<endl;
    }
};
class ProjectAndExamResult : public ExamResult {
private:
    int proekt_poeni;
    int procent_na_slicnost;
public:
    ProjectAndExamResult(string index = "", string name = "", int poeni_k1 = 0, int poeni_k2 = 0, int proekt_poeni = 0, int procent_na_slicnost = 0) : ExamResult(index, name, poeni_k1, poeni_k2) {
        this->proekt_poeni = proekt_poeni;
        this->procent_na_slicnost = procent_na_slicnost;
    }

    int finalPoints() const  {
        return (poeni_k1 + poeni_k2) * 0.35 + proekt_poeni;
    }
    bool passed() const {
        if (procent_na_slicnost <= 30 && finalPoints() >= 50 && proekt_poeni >= 10) {
            return true;
        }
        return false;
    }
};
ExamResult* readExamResult(ifstream &in) {

}


void writeToFile(const string &fileName) {
    ofstream fout(fileName);
    string line;
    while (getline(cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }


    fout.close();
}

void readFromFile(const string &fileName) {
    ifstream fin(fileName);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}
