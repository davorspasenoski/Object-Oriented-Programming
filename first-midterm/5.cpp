// Во програмскиот јазик С++ да се креира класа Vozenje за опишување на адреналински возења во забавен парк. Класата треба да содржи: (5 поени)

// Име на возењето ( низа од 100 знаци)
// Времетраење во минути (цел број)
// Цена (децимален број)
// Дали има студентски попуст (1-да, 0-не)
// Да се креира класа ZabavenPark, што содржи: (10 поени)

// Име на забавниот парк (низа од 100 знаци)
// Локација (низа од 100 знаци)
// Низа од адреналински возења во паркот (низа од максимум 100 елементи од класата Vozenje)
// Број на елементи во низата (цел број)
// Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)

// [Ime na parkot] [Lokacija]
// [Ime1] [Vremetraenje1] [Cena1]
// [Ime2] [Vremetraenje2] [Cena2]
// [Ime3] [Vremetraenje3] [Cena3]
// ...
// Да се креира функција najdobar_park, што прима низа од објекти од типот ZabavenPark и го печати името и локацијата на паркот кој е најефтин за посета од страна на студенти. Најефтин парк е оној што содржи најголем број возења со студентски попуст. Ако повеќе паркови ги делат овие карактеристики, да се испечати паркот со најголемото времетраење од сите возења.* (20 поени)*

// Да се дополни функцијата main (5 поени).


#include<iostream>
#include <cstring>
#include <iomanip>
using namespace std;
class Vozenje{
private:
    char ime[101];
    int vremetraenje;
    float cena;
    bool studentskiPopust;
public:
    Vozenje(){}
    Vozenje(char ime[], int vremetraenje,float cena,bool studentskiPopust){
        strcpy(this->ime,ime);
       this-> vremetraenje = vremetraenje;
        this-> cena = cena;
        this-> studentskiPopust = studentskiPopust;
    }
    Vozenje(const Vozenje &v) {
        strcpy(this->ime,v.ime);
        this-> vremetraenje = v.vremetraenje;
        this-> cena = v.cena;
        this-> studentskiPopust = v.studentskiPopust;
    }
    const char* getime() {
        return ime;
    }
    int getvremetraenje() {
        return vremetraenje;
    }
    float getcena() {
        return cena;
    }

    bool imaPopust() {
        return studentskiPopust;
    }
};
class ZabavenPark{
    private:
    char imezabavenpark[101];
    char lokacija[101];
    Vozenje adrenalinskovozenje[101];
    int brelementi;
public:
    ZabavenPark(){}
    ZabavenPark(char imezabavenpark[], char lokacija[], Vozenje v[], int brelementi){
        strcpy(this->imezabavenpark, imezabavenpark);
        strcpy(this->lokacija, lokacija);
        this->brelementi = brelementi;
        for (int i = 0; i < brelementi; i++) {
            this->adrenalinskovozenje[i] = v[i];
        }
    }
    ZabavenPark(const ZabavenPark &z){
        strcpy(imezabavenpark,z.imezabavenpark );
        strcpy(lokacija,z.lokacija);
        this->brelementi = z.brelementi;
    }
    int getBrElementi() {
        return brelementi;
    }
    const char* getIme() {
        return imezabavenpark;
    }
    const char* getLokacija() {
        return lokacija;
    }
    int getVkupnoVreme(){
        int vkupno = 0;
        for(int i = 0; i < brelementi; i++) {
            vkupno = vkupno + adrenalinskovozenje[i].getvremetraenje();
        }
        return vkupno;
    }
    void print(){
        cout << imezabavenpark << " " << lokacija << endl;
        for (int i = 0; i < brelementi; i++) {
            cout << adrenalinskovozenje[i].getime() << " "
                 << adrenalinskovozenje[i].getvremetraenje() << " "
                 << fixed << setprecision(2) << adrenalinskovozenje[i].getcena() << endl;
        }
    }
};
void najdobar_park(ZabavenPark ff[], int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (ff[i].getBrElementi() > ff[maxIndex].getBrElementi()) {
            maxIndex = i;
        }else if (ff[i].getBrElementi() == ff[maxIndex].getBrElementi()) {
            if (ff[i].getVkupnoVreme() > ff[maxIndex].getVkupnoVreme()) {
                maxIndex = i;
            }
        }
    }
    cout << "Najdobar park: " << ff[maxIndex].getIme() << " " << ff[maxIndex].getLokacija() << endl;
}

int main()
{
    int n;
    cin>>n;

    ZabavenPark ff[100];
    char imezabavenpark[101];
    char lokacija[101];
    int brelementi;


    for (int i = 0; i < n; i++){
        cin>>imezabavenpark>>lokacija>>brelementi;
        Vozenje v[100];
        for (int j = 0; j < brelementi; j++){
            char imeVozenje[101];
            int vreme;
            float cena;
            int popustInt;
            cin >>imeVozenje>>vreme>>cena>>popustInt;
            v[j] = Vozenje(imeVozenje,vreme,cena,popustInt == 1);
        }
        ff[i] = ZabavenPark(imezabavenpark,lokacija,v,brelementi);
    }
    for(int i=0; i<n; i++) {
        ff[i].print();
    }

    najdobar_park(ff,n);
    return 0;
}
