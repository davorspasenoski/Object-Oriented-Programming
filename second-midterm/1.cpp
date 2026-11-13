// Да се дефинира класа Vozac во која се чуваат информации за:

// име (низа од максимум 100 знаци)
// возраст (цел број)
// број на трки (цел број)
// дали е ветеран (да/не).
// Да се преоптоварат:

// операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
// операторот == за споредување на два возачи според заработувачката по трка.
// Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

// За автомобилистот дополнително се чува:

// цена на автомобилот (децимален број).
// За мотоциклистот дополнително се чува:

// моќност на мотор (цел број).
// Заработувачката по трка на возачите се пресметува како:

// за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
// за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
// Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

// за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
// за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
// Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

#include "iostream"
#include "cstring"
#include "iomanip"
using namespace std;
class Vozac {
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool veteran;

public:
    Vozac(const char *ime = "", int vozrast = 0, int trki = 0, bool veteran = false) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->trki = trki;
        this->veteran = veteran;
    }

    Vozac(const Vozac &v) {
        strcpy(this->ime, v.ime);
        this->vozrast = v.vozrast;
        this->trki = v.trki;
        this->veteran = v.veteran;
    }

    virtual ~Vozac() {}

    virtual double zarabotuvackaPoTrka() const = 0;
    virtual double danok() const = 0;

    virtual void print(ostream &os) const {
        os << ime << endl;
        os << vozrast << endl;
        os << trki << endl;
        if (veteran) {
            os << "VETERAN" << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const Vozac &v) {
        v.print(os);
        return os;
    }

    bool operator==(const Vozac &v) const {
        return this->zarabotuvackaPoTrka() == v.zarabotuvackaPoTrka();
    }
};

class Avtomobilist : public Vozac {
private:
    float cenaauto;

public:
    Avtomobilist(const char *ime = "", int vozrast = 0, int trki = 0, bool veteran = false, float cenaauto = 0.0)
        : Vozac(ime, vozrast, trki, veteran) {
        this->cenaauto = cenaauto;
    }

    double zarabotuvackaPoTrka() const override {
        return cenaauto / 5.0;
    }

    double danok() const override {
        if (trki > 10) {
            return zarabotuvackaPoTrka() * 0.15;
        } else {
            return zarabotuvackaPoTrka() * 0.10;
        }
    }
};

class Motociklist : public Vozac {
private:
    int moknost;

public:
    Motociklist(const char *ime = "", int vozrast = 0, int trki = 0, bool veteran = false, int moknost = 0)
        : Vozac(ime, vozrast, trki, veteran) {
        this->moknost = moknost;
    }

    double zarabotuvackaPoTrka() const override {
        return moknost * 20.0;
    }

    double danok() const override {
        if (veteran) {
            return zarabotuvackaPoTrka() * 0.25;
        } else {
            return zarabotuvackaPoTrka() * 0.20;
        }
    }
};

int soIstaZarabotuvachka(Vozac** vozaci, int n, Vozac* v) {
    int brojac = 0;
    for (int i = 0; i < n; i++) {
        if (*vozaci[i] == *v) {
            brojac++;
        }
    }
    return brojac;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;

    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }

    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }

    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);

    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx) << endl;

    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;

    return 0;
}
