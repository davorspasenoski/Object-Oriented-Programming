// Да се креира класа Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

// Потоа да се креирa класа ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

// Треба да се напише функција

// void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
// во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.


#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
using namespace std;
class voz {
private:
    char relacija[50];
    float kilometri;
    int brpatnici;
public:
    voz(char relacija[] = "", float kilometri = 0, int brpatnici = 0) {
        strcpy(this->relacija, relacija);
        this->kilometri = kilometri;
        this->brpatnici = brpatnici;
    }
    const char * getrelacija() {
        return relacija;
    }
    float getkilometri() {
        return kilometri;
    }
};
class zeleznickastanica{
private:
    char grad[20];
    voz vozovi[31];
    int brvozovi;
public:
    zeleznickastanica(char grad[] = "", voz *v = NULL, int brvozovi = 0) {
        strcpy(this->grad, grad);
        this->brvozovi = brvozovi;
        for (int i = 0; i < brvozovi; i++) {
            this->vozovi[i] = v[i];
        }
    }
    const char* getgrad() {
        return this->grad;
    }
    int getbrvozovi() {
        return this->brvozovi;
    }
    voz getvoz(int index) {
        return vozovi[index];
    }
};

void najkratkaRelacija(zeleznickastanica* zs, int n, char* grad) {
    for (int i = 0; i < n; i++) {
        if (strcmp(zs[i].getgrad(), grad) == 0) {
            if (zs[i].getbrvozovi() == 0) {
                return;
            }
            voz najkratok = zs[i].getvoz(0);
            for (int j = 0; j < zs[i].getbrvozovi(); j++){
                voz momentalen = zs[i].getvoz(j);

                if (momentalen.getkilometri() <= najkratok.getkilometri()) {
                    najkratok = momentalen;
                }
            }
            cout << "Najkratka relacija: " << najkratok.getrelacija()
                 << " (" << najkratok.getkilometri() << " km)" << endl;
            return;
        }
    }
}
int main() {
    int n;
    cin>>n;
    zeleznickastanica stanici[100];
    char grad[21];
    int brVozovi;
    for (int i = 0; i < n; i++) {
        cin >> grad >> brVozovi;
        voz v[31];
        for (int j = 0; j < brVozovi; j++) {
            char relacija[51];
            float kilometri;
            int brpatnici;
            cin >> relacija >> kilometri >> brpatnici;
            v[j] = voz(relacija, kilometri, brpatnici);
        }

        stanici[i] = zeleznickastanica(grad, v, brVozovi);
    }

    char baranGrad[21];
    cin >> baranGrad;

    najkratkaRelacija(stanici, n, baranGrad);


    return 0;
}
