// Во програмскиот јазик C++ да се креира класа Laptop за опишување на спецификациите на даден преносен компјутер. Класата треба да содржи: (5 поени)

// Фирма која го произведува ( низа од 100 знаци)
// Големина на монитор во инчи (реален број)
// Дали е со touch или не (булова променлива)
// Цена (цел број)
// Да се креира класа ITStore, што содржи: (5 поени)

// Име на продавницата (низа од 100 знаци)
// Локација (низа од 100 знаци)
// Низа од достапни лаптопи (низа од максимум 100 елементи од класата Laptop)
// Број на елементи во низата (цел број)
// Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

// [Ime na prodavnicata] [Lokacija]
// [Marka1] [dim_monitor1] [Cena1]
// [Marka2] [dim_monitor2] [Cena2]
// [Marka3] [dim_monitor3] [Cena3]
// ...
// Да се креира функција najeftina_ponuda, што прима низа од објекти од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*

// Да се дополни функцијата main (10 поени).

// Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.

#include <iostream>
#include <cstring>
using namespace std;
class laptop {
private:
    char firma[100];
    float inci;
    bool touch;
    int cena;
public:
    laptop(char firma[] = "", float inci = 0, bool touch = 0, int cena = 0) {
        strcpy(this->firma, firma);
        this->inci = inci;
        this->touch= touch;
        this->cena = cena;
    }

    const char* getfirma() {
        return firma;
    }
    float getinci() {
        return inci;
    }
    int getcena() {
        return cena;
    }
    float gettouch() {
        return touch;
    }
};

class itstore {
private:
    char imeprodavnica[100];
    char lokacija[100];
    laptop laptopi[100];
    int brelementi;
public:
    itstore(char imeprodavnica[] = "", char lokacija[] = "",laptop laptopi[] = NULL, int brelementi = 0 ) {
        strcpy(this->imeprodavnica,imeprodavnica);
        strcpy(this->lokacija,lokacija);
        this->brelementi = brelementi;
        if (NULL != laptopi) {
            for (int i = 0; i < brelementi; i++) {
                this->laptopi[i] = laptopi[i];
            }
        }
    }
    void print() {
        cout<<imeprodavnica<<" "<<lokacija<<endl;
        for (int i = 0; i < brelementi; i++) {
            cout<<laptopi[i].getfirma()<<" "<<laptopi[i].getinci()<<" "<<laptopi[i].getcena()<<endl;
        }
    }
    int getbrelementi() {
        return brelementi;
    }
    laptop getlaptop(int index) {
        return laptopi[index];
    }
    const char* getimeprodavnica() {
        return imeprodavnica;
    }
    const char* getlokacija() {
        return lokacija;
    }
};
void najeftina_ponuda(itstore niza[], int n) {
    int minindex = 0;
    int mincena = 99999;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < niza[i].getbrelementi(); j++) {
            if (niza[i].getlaptop(j).gettouch()) {
                int momentalnacenac = niza[i].getlaptop(j).getcena();

                if (mincena == 0 || momentalnacenac < mincena){
                    mincena = momentalnacenac;
                    minindex = i;
                }
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata:"<<endl;
    cout<<niza[minindex].getimeprodavnica()<<" "<<niza[minindex].getlokacija()<<endl;
    cout<<"Najniskata cena iznesuva: "<<mincena<<endl;
}
int main() {
    int n;
    cin>>n;

    itstore store[100];
    for (int i =0; i < n; i++) {
        char imeprodavnica[100];
        char lokacija[100];
        int brelementi;
        cin>>imeprodavnica>>lokacija>>brelementi;


        laptop laptopi[100];
        for (int j =0; j < brelementi; j++) {
            char firma[100];
            float inci;
            bool touch;
            int cena;
            cin>>firma>>inci>>touch>>cena;
            laptopi[j] = laptop(firma,inci,touch,cena);
        }
        store[i] = itstore(imeprodavnica,lokacija,laptopi,brelementi);

    }
    for (int i =0; i < n; i++) {
        store[i].print();

    }
    najeftina_ponuda(store, n);

    return 0;
}
