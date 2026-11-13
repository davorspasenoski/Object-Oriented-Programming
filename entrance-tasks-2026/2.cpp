// Да се дефинира класа Book во која се чуваат информации за:

// Наслов на книгата (низа од најмногу 50 знаци) - default вредност book-title
// Автор на книгата (низа од најмногу 50 знаци) - default вредност author
// ISBN на книгата (низа од најмногу 20 знаци) - default вредност 978-00-00000-00-0
// Број на издавачи (цел број) - default вредност 0

// За класата да се дефинираат потребните конструктори и:

// Да се преоптовари оператор << за печатење - кој печати информации за книгата во форматот како во тест примерите.
// Метод bool checkISBN() - кој враќа информација дали isbn форматот е правилен, односно дали книгата е валидна.
// Еден isbn е правилен: 

// Доколку започнува на 978- 
// Вкупно треба 4 пати да се појави карактерот "-"
// Вкупно треба да има 13 цифри
// Пример правилен формат 978-00-00000-00-0 
// Да се дополни главната функција на означеното место со читање на број N, па информации за N книги и книгите да се додадат во низата books.


#include <cstring>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * Your code here!
 * */
class Book {
private:
    string naslov;
    string avtor;
    string ISBN;
    int brizdavaci = 0;
public:
    Book(string naslov = "book-title", string avtor = "author", string ISBN = "978-00-00000-00-0", int brizdavaci = 0) {
        this->naslov = naslov;
        this->avtor = avtor;
        this->ISBN = ISBN;
        this->brizdavaci = brizdavaci;
    }

    friend std::ostream & operator<<(std::ostream &os, const Book &obj) {
        os<<obj.naslov<<" - "<<obj.avtor<<" : "<<obj.ISBN<<endl;
        os<<"Publishers: "<<obj.brizdavaci;
        return os;
    }

    bool checkIsbn() {
        if(ISBN[0] != '9' || ISBN[1] != '7' || ISBN[2] != '8' || ISBN[3] != '-') {
            return false;
        }

        int crticki = 0;
        for (int i = 0; i < ISBN.length(); i++) {
            if (ISBN[i] == '-') {
                crticki++;
            }
        }
        int cifri = 0;
        for (int i = 0; i < ISBN.length(); i++) {
            if (isdigit(ISBN[i])) {
                cifri++;
            }
        }

        if (cifri == 13 && crticki == 4) {
            return true;
        }
        return false;
    }
};
int main() {
    Book books[50];
    int N;

    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; i++) {
        string n, a, isbn;
        int b;
        getline(cin, n);
        getline(cin, a);
        getline(cin, isbn);
        cin >> b;
        cin.ignore();
        books[i] = Book(n, a, isbn, b);
    }

    int choice;
    cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < N; ++i) {
            cout << books[i] << endl;
        }
    } else if (choice == 2) {
        for (int i = 0; i < N; ++i) {
            if (books[i].checkIsbn()) {
                cout << "VALID ISBN" << endl;
            } else {
                cout << "INVALID ISBN" << endl;
            }
        }
    } else {
        cout << "Test default constructor" << endl;
        cout << books[N] << endl;
    }

    return 0;
}
