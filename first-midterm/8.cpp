// Да се дефинира класа Пица за која ќе се чуваат податоци за:

// име на пицата (низа од 15 знаци)
// цена (цел број)
// состојки (динамички алоцирана низа од знаци)
// намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
// За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

// pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
// istiSe(Pica p) - функција за споредба на две пици според состојките :
// Да се дефинира класа Picerija во која се чуваат:

// име (низа од максимум 15 знаци)
// динмички алоцирана низа од објекти од класата Pica
// број на пици (цел број)
// За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

// dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
// void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

#include <iostream>
#include <cstring>
using namespace std;
class Pica {
private:
    char ime[20];
    int cena;
    char *sostojki;
    int namaluvanje;
public:
    Pica() {
        this->sostojki = nullptr;
        this->cena = 0;
        this->namaluvanje = 0;
        this->ime[0] = '\0';
    }
    Pica( char *ime, int cena, char *sostojki, int namaluvanje){
        strcpy(this->ime, ime);
        this->ime[19] = '\0';
        this->cena = cena;
        this->namaluvanje = namaluvanje;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
    }
    Pica(const Pica &a) {
        strcpy(this->ime, a.ime);
        this->cena = a.cena;
        this->namaluvanje = a.namaluvanje;
        if (a.sostojki != nullptr) {
            this->sostojki = new char[strlen(a.sostojki) + 1];
            strcpy(this->sostojki, a.sostojki);
        } else {
            this->sostojki = nullptr;
        }
    }
    ~Pica() {
        delete[] sostojki;
    }
    Pica& operator=(const Pica &a) {
        if (this != &a) {
            delete[] sostojki;
            strcpy(this->ime, a.ime);
            this->cena = a.cena;
            this->namaluvanje = a.namaluvanje;
            if (a.sostojki != nullptr) {
                this->sostojki = new char[strlen(a.sostojki) + 1];
                strcpy(this->sostojki, a.sostojki);
            } else {
                this->sostojki = nullptr;
            }
        }
        return *this;
    }
    const char* getsostojki()const{
    return sostojki;
}
    int getNamaluvanje()const{
    return namaluvanje;
}
    void pecati() {
        int cenaSoPopust = cena - (cena * namaluvanje / 100);
    cout << ime << " - " << sostojki << ", " << cena << " " << cenaSoPopust << endl;
    }
};
class Picerija {
private:
    char imepicerija[20];
    Pica *objekti;
    int brpici;
public:
    Picerija(const char *ime = "") {
        strcpy(this->imepicerija, ime);
        this->imepicerija[19] = '\0';
        this->objekti = nullptr;
        this->brpici = 0;
    }
    Picerija(const Picerija &p) {
        strcpy(this->imepicerija, p.imepicerija);
        this->brpici = p.brpici;
        if (p.objekti != nullptr) {
            this->objekti = new Pica[p.brpici];
            for (int i = 0; i < p.brpici; i++) {
                this->objekti[i] = p.objekti[i];
            }
        } else {
            this->objekti = nullptr;
        }
    }
    ~Picerija() {
        delete[] objekti;
    }
    const char* getIme(){
        return imepicerija;
    }

    void setIme(const char *ime){
        strncpy(this->imepicerija, ime,19);
        this->imepicerija[19]='\0';
    }
    Picerija& operator+=(const Pica &p) {
        for (int i = 0; i < brpici; i++) {
            if (strcmp(objekti[i].getsostojki(), p.getsostojki()) == 0) {
                return *this;
            }
        }
        Pica *temp = new Pica[brpici + 1];
        for (int i = 0; i < brpici; i++) {
            temp[i] = objekti[i];
        }
        temp[brpici] = p;
        delete[] objekti;
        objekti = temp;
        brpici++;
        return *this;
    }
    void piciNaPromocija() {
        for (int i = 0; i < brpici; i++) {
            if (objekti[i].getNamaluvanje() > 0) {
                objekti[i].pecati();
            }
        }
    }
};
int main() {
    int n;
    char ime[20];
    cin >> ime >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1 += p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2 += p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
