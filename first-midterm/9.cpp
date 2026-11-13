// Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

// OperativenSistem
// Во класата OperativenSistem треба да се чуваат следниве податоци:

// име на оперативниот систем (динамички алоцирана низа од знаци)
// верзија (float)
// тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
// големина (во GB) (float)
// Дополнително, во рамките на класата потребно е да се дефинира:

// конструктори со и без параметри
// copy constructor
// destructor
// преоптоварување на операторот =
// метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
// метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
// метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
// метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
// Repozitorium
// Во класата Repozitorium треба да се чуваат следниве податоци:

// име на репозиториумот (низа од 20 знака)
// динамички алоцирана низа од OperativenSistem
// број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
// Дополнително, во рамките на класата потребно е да се дефинира:

// конструктор Repozitorium(const char *ime)
// деструктор
// метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
// метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
// метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
// Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
// Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.



#include<iostream>
#include<cstring>
using namespace std;

enum Tip { LINUX, UNIX, WINDOWS };
class OperativenSistem {
private:
    char *ime;
    float verzija;
    float golemina;
    Tip tipp;
public:
    OperativenSistem(const char *ime = "", float verzija = 0, Tip t = LINUX, float golemina = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->golemina = golemina;
        this->tipp = t;
    }
    OperativenSistem(const OperativenSistem &os) {
        this->verzija = os.verzija;
        this->golemina = os.golemina;
        this->tipp = os.tipp;
        this->ime = new char[strlen(os.ime) + 1];
        strcpy(this->ime, os.ime);
    }

    ~OperativenSistem() {
        delete[] ime;
    }

    OperativenSistem &operator=(const OperativenSistem &os){
        if (this != &os) {
            delete[] ime;
            this->ime = new char[strlen(os.ime) + 1];
            strcpy(this->ime, os.ime);
            this->verzija = os.verzija;
            this->golemina = os.golemina;
            this->tipp = os.tipp;
        }
        return *this;
    }

    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tipp << " Golemina:" << golemina << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        return (strcmp(this->ime, os.getime()) == 0 &&
                this->verzija == os.verzija &&
                this->tipp == os.tipp &&
                this->golemina == os.golemina);
    }
    int sporediVerzija(const OperativenSistem &os) {
        if (this->verzija == os.verzija) {
            return 0;
        }
        if (this->verzija < os.verzija) {
            return -1;
        }else {
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &sporedba) {
        return (strcmp(this->ime, sporedba.ime) == 0 && this->tipp == sporedba.tipp);
    }

    const char* getime() const { return ime; }
};

class Repozitorium {
private:
    char repozitoriumIme[21];
    OperativenSistem *sistemi;
    int br;
public:
    Repozitorium(const char *imeRepo = "") {
        strcpy(this->repozitoriumIme, imeRepo);
        this->sistemi = nullptr;
        this->br = 0;
    }

    ~Repozitorium() {
        delete[] sistemi;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << this->repozitoriumIme << endl;
        for (int i = 0; i < br; i++) {
            sistemi[i].pecati();
        }
    }

    void dodadi(const OperativenSistem &nov) {
        for (int i = 0; i < br; i++) {
            if (sistemi[i].istaFamilija(nov) && sistemi[i].sporediVerzija(nov) == -1) {
                sistemi[i] = nov;
                return;
            }
        }
        OperativenSistem *tmp = new OperativenSistem[br + 1];
        for (int i = 0; i < br; i++) {
            tmp[i] = sistemi[i];
        }
        tmp[br] = nov;
        br++;
        delete[] sistemi;
        sistemi = tmp;
    }

    void izbrishi(const OperativenSistem &zaBrishenje) {
        int index = -1;
        for (int i = 0; i < br; i++) {
            if (sistemi[i].ednakviSe(zaBrishenje)) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            if (br == 1) {
                delete[] sistemi;
                sistemi = nullptr;
                br = 0;
            } else {
                OperativenSistem *tmp = new OperativenSistem[br - 1];
                int j = 0;
                for (int i = 0; i < br; i++) {
                    if (i != index) {
                        tmp[j++] = sistemi[i];
                    }
                }
                delete[] sistemi;
                sistemi = tmp;
                br--;
            }
        }
    }
};

int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium(repoName);

    int n;
    cin >> n;
    char ime[20];
    float verzija, golemina;
    int tipInt;

    for (int i = 0; i < n; i++) {
        cin >> ime >> verzija >> tipInt >> golemina;
        OperativenSistem os(ime, verzija, (Tip)tipInt, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();

    cin >> ime >> verzija >> tipInt >> golemina;
    OperativenSistem osZaBrishenje(ime, verzija, (Tip)tipInt, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(osZaBrishenje);
    repozitorium.pecatiOperativniSistemi();

    return 0;
}
