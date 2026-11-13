// Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

// име (динамички алоцирана низа од знаци)
// пол (bool)
// возраст (цел број) (5 поени).
// За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

// Дополнително за оваа класа да се преоптоварат:

// оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
// операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
// Да се дефинира класа Maraton за кој се чуваат:

// локација (низа од максимум 100 знаци)
// низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
// број на учесници (цел број) (5 поени).
// За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:

// оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
// prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
// pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;
class Ucesnik {
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik(char *ime = "", bool pol = false, int vozrast = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik &u) {
        this->ime = new char[strlen(u.ime) + 1];
        strcpy(this->ime, u.ime);
        this->pol = u.pol;
        this->vozrast = u.vozrast;
    }
    Ucesnik& operator=(const Ucesnik &u) {
        if (this != &u) {
            delete [] ime;
            this->ime = new char[strlen(u.ime) + 1];
            strcpy(this->ime, u.ime);
            this->pol = u.pol;
            this->vozrast = u.vozrast;
        }
        return *this;
    }
    ~Ucesnik() {
        delete [] ime;
    }
    bool operator>(const Ucesnik &u) const {
        return this->vozrast > u.vozrast;
    }
    friend ostream& operator<<(ostream& out, const Ucesnik& obj) {
        if (obj.vozrast < 35) {
            out << obj.ime << endl;
            if (!obj.pol) out << "zhenski" << endl;
            else out << "mashki" << endl;
            out << obj.vozrast << endl;
        }
        return out;
    }
    int getvozrast() const {
        return vozrast;
    }
    const char* getime() const {
        return ime;
    }
};

class Maraton {
private:
    char lokacija[101];
    Ucesnik niza[100];
    int brucenici;
public:
    Maraton(char *lok = "") {
        strcpy(this->lokacija, lok);
        this->brucenici = 0;
    }
    Maraton& operator+=(const Ucesnik& u) {
        if (this->brucenici < 100) {
            this->niza[this->brucenici] = u;
            this->brucenici++;
        }
        return *this;
    }
    double prosecnoVozrast() {
        if (brucenici == 0) return 0;
        double suma = 0;
        for (int i = 0; i < brucenici; i++) {
            suma += niza[i].getvozrast();
        }
        return suma / (double)brucenici;
    }
    void pecatiPomladi(const Ucesnik &u) {
        for (int i = 0; i < brucenici; i++) {
            if (u > niza[i]) {
                cout << niza[i].getime() << " (" << niza[i].getvozrast() << ")" << endl;
            }
        }
    }
};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    for(int i = 0; i < n; i++) {
        cout << *u[i];
    }
    cout << m.prosecnoVozrast() << endl;


    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
