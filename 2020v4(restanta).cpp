#include <bits/stdc++.h>
#include <string>
using namespace std;
class IoBase{
public:
    virtual istream &read(istream &is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const { // nu este nevoie de obiectul citit, pt ca avem this
        return os; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // ...
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    // empty vector:
    vec.clear();
    // read length:
    int n;
    cout << "Introduceti numarul de elemente: ";
    cin >> n;
    // read items
    for (int i = 0; i < n; ++i) {
        T var;
        cin >> var;
        vec.push_back(var);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "[ ";
    for(auto& var : vec) {
        os << var << " ; ";
    }
    os << ']';

    return os;
}

class Produs : public IoBase {
protected:
        float pret;
        int cantitate;
        unsigned int ID;
        static unsigned int staticID;
public:
        Produs();
        Produs(float pret,unsigned int ID,int cantitate);
        istream &read(istream &is) override;
        ostream &write(ostream &os) const override;
        float getPret();
        int getCantitate();

    };
unsigned int Produs::staticID = 0;
Produs::Produs() : ID(++staticID) {}
Produs::Produs(float pret, unsigned int ID, int cantitate) : pret(pret),ID(++staticID),cantitate(cantitate) {}

float Produs::getPret() {
    return pret;
}
int Produs::getCantitate() {
    return cantitate;
}

istream &Produs::read(istream &is) {
    IoBase::read(is);
    cout << "Introduceti pretul : " << endl;
    is >> pret;
    cout << "Introduceti cantitatea : " << endl;
    is >> cantitate;
    return is;
}

ostream &Produs::write(ostream &os) const {
    IoBase::write(os);
    cout << "ID : ";
    os << ID << endl;
    cout << "Pretul : ";
    os << pret << endl;
    cout << "Cantitatea : ";
    os << cantitate << endl;
    return os;
}

class Carte : public Produs{
private:
    string titlu;
    vector <string> autori;
    string editura;
public:
    Carte();
    Carte(float pret, unsigned int ID, int cantitate, const string &titlu, const vector <string> &autori, const string &editura);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    string getTitlu();


};



string Carte::getTitlu() {
    return titlu;
}
Carte::Carte() {}
Carte::Carte(float pret, unsigned int ID, int cantitate, const string &titlu, const vector<string> &autori, const string &editura) : Produs(pret,ID,cantitate), titlu(titlu), autori(autori), editura(editura){}

istream &Carte::read(istream &is) {
    Produs::read(is);
    cout << "Introduceti titlul : " << endl;
    is >> titlu;
    cout << "Introduceti nr autorilor : " << endl;
    int n; string autor;
    cin >> n;
    cout << "Introduceti autorii : " << endl;
    for (int i=0;i<n;i++){
        cin >> autor;
        autori.push_back(autor);
    }
    cout << "Introduceti editura : " << endl;
    is >> editura;
    return is;
}
ostream &Carte::write(ostream &os) const {
    Produs::write(os);
    cout << "Titlu : ";
    os << titlu << endl;
    cout << "Autori : ";
    for(auto x : autori)
        os << x << " ";
    cout << "\nEditura: ";
    os << editura << endl;
    return os;
}

class DVD : public Produs {
protected:
    int nrMinute;
public:
    DVD();
    DVD(float pret, unsigned int ID, int cantitate, int nrMinute);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
DVD::DVD() {}
DVD::DVD(float pret, unsigned int ID, int cantitate, int nrMinute) : Produs(pret,ID,cantitate), nrMinute(nrMinute){}

istream &DVD::read(istream &is) {
    Produs::read(is);
    cout << "Introduceti nr minute : " << endl;
    is >> nrMinute;
    return is;
}

ostream &DVD::write(ostream &os) const {
    Produs::write(os);
    cout << "Nr minute : ";
    os << nrMinute;
    return os;
}

class Muzica : public DVD {
private:
    string numeAlbum;
    vector <string> interpreti;
public:
    Muzica();
    Muzica(float pret, unsigned int ID, int cantitate, int nrMinute, const string &numeAlbum, const vector <string> &interpreti);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};
Muzica::Muzica() {}
Muzica::Muzica(float pret, unsigned int ID, int cantitate, int nrMinute, const string &numeAlbum,
               const vector<string> &interpreti) : DVD(pret,ID, cantitate, nrMinute), numeAlbum(numeAlbum), interpreti(interpreti){}

istream &Muzica::read(istream &is) {
    DVD::read(is);
    cout << "Introduceti nume album : " << endl;
    is >> numeAlbum;
    int n; string inter;
    cout << "Introduceti nr interpreti : " << endl;
    for(int i=0;i<n;i++){
        cin >> inter;
        interpreti.push_back(inter);
    }
    return is;
}

ostream &Muzica::write(ostream &os) const {
    DVD::write(os);
    cout << "Nume album : ";
    os << numeAlbum << endl;
    cout << "Interpreti : ";
    for(auto item : interpreti)
        os << item << " ";
    cout << endl;
    return os;
}

class Filme : public DVD {
private:
    string numeFilm;
    string gen;
public:
    Filme();
    Filme(float pret, unsigned int ID, int cantitate, int nrMinute, const string &numeFilm, const string &gen);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};

Filme::Filme() {}
Filme::Filme(float pret, unsigned int ID, int cantitate, int nrMinute, const string &numeFilm, const string &gen) : DVD(pret,ID,cantitate,nrMinute), numeFilm(numeFilm), gen(gen){}

istream &Filme::read(istream &is) {
    DVD::read(is);
    cout << "Introduceti nume film : " << endl;
    is >> numeFilm;
    cout << "Introduceti gen : " << endl;
    is >> gen;
    return is;
}
ostream &Filme::write(ostream &os) const {
    DVD::write(os);
    cout << "Nume film : ";
    os << numeFilm << endl;
    cout << "Gen : ";
    os << gen << endl;
    return os;
}

class Colectie : public Produs {
protected:
    string denumire;
public:
    Colectie();
    Colectie(float pret,unsigned int ID,int cantitate, const string &denumire);
    istream &read(istream &is);
    ostream &write(ostream &os) const;

};
Colectie::Colectie() {};
Colectie::Colectie(float pret, unsigned int ID, int cantitate, const string &denumire) : Produs(pret,ID,cantitate), denumire(denumire) {}

istream &Colectie::read(istream &is) {
    Produs::read(is);
    cout << "Introduceti denumirea : " << endl;
    is >> denumire;
    return is;
}
ostream &Colectie::write(ostream &os) const {
    Produs::write(os);
    cout << "Denumire : " ;
    os << denumire << endl;
    return os;
}

class Figurina : public Colectie {
private:
    string categorie;
    string brand;
    string material;
public:
    Figurina();
    Figurina(float pret, unsigned int ID, int cantitate, const string &denumire, const string &format, const string &categorie, const string &brand, const string &material);
    istream &read(istream &is);
    ostream &write(ostream &os) const;

};
Figurina::Figurina() {}
Figurina::Figurina(float pret, unsigned int ID, int cantitate, const string &denumire, const string &format,
                   const string &categorie, const string &brand, const string &material) : Colectie( pret, ID , cantitate, denumire), categorie(categorie), brand(brand), material(material) {}

istream &Figurina::read(istream &is) {
    Colectie::read(is);
    cout << "Introduceti categoria : " << endl;
    is >> categorie;
    cout << "Introduceti brandul : " << endl;
    is >> brand;
    cout << "Introduceti materialul: " << endl;
    is >> material;
    return is;
}

ostream &Figurina::write(ostream &os) const {
    Colectie::write(os);
    cout << "Categoria : ";
    os << categorie << endl;
    cout << "Brand : ";
    os << brand << endl;
    cout << "Material : ";
    os << material << endl;
    return os;
}
class Poster : public Colectie {
private:
    string format;
public:
    Poster();
    Poster(float pret, unsigned int ID, int cantitate, const string &denumire, const string &format);
    istream &read(istream &is);
    ostream &write(ostream &os) const;
};
Poster::Poster() {}
Poster::Poster(float pret, unsigned int ID, int cantitate, const string &denumire, const string &format) : Colectie(pret,ID,cantitate, denumire ), format(format) {}

istream &Poster::read(istream &is) {
    Colectie::read(is);
    cout << "Introduceti formatul ( ex A4 )" << endl;
    is >> format;
    return is;
}

ostream &Poster::write(ostream &os) const {
    Colectie::write(os);
    cout << "Format : ";
    os << format << endl;
    return os;
}

shared_ptr<Produs> citireProdus() {
    shared_ptr<Produs> x;
    cout << "1.Carte\n2.DVD\n3.Colectie";
    int option;
    cin >> option;
    if(option == 1)
        x = make_shared<Carte>();
    else if(option == 2){
        cout << "1.Muzica\n2.Filme";
        int option2;
        cin >> option2;
        if(option2 == 1)
            x = make_shared<Muzica>();
        else if(option2 == 2)
            x = make_shared<Filme>();
        else return nullptr;
    }
    else if(option == 3){
        cout << "1.Figurina\n2.Poster";
        int option3;
        cin >> option3;
        if(option3 == 1)
            x = make_shared<Figurina>();
        else if(option3 == 2)
            x = make_shared<Poster>();
        else return nullptr;
    }
    else return nullptr;
    cin >> *x;
    return x;
}

class Meniu : public IoBase {
private:
    vector<shared_ptr<Produs>> produse;
public:
    void showOptions(){
        cout << "1.Citirea n produse\n2.Afisare produse citite\n 3.Editarea unui produs\n4.Ordonarea crescatoare a produselor dupa pret\n5.Cautarea unei carti dupa titlu\n6.Afisarea produsului cu cea mai mare cantitate disponibila";

    }
    void run(){
        int option;
        showOptions();
        cin >> option;
        while (option > 0 && option < 8) {
            if(option == 1)
                citire();
            if(option == 2)
                afisare();
            if(option == 4)
                ordonarePret();
            if(option == 5)
                titlu();
            if(option == 6)
                cantitate();
            showOptions();
            cin >> option;
        }
    }

    void citire(){
        cout << "Introduceti nr de produse : ";
        int n; cin >> n;
        for(int i=0;i<n;i++)
            produse.push_back(citireProdus());

    }
    void afisare(){
        for(int i=0;i<produse.size();i++)
            cout<<*produse[i]<<endl;
    }
    void ordonarePret(){
        for(int i=0;i<produse.size();i++)
            for(int j=i+1;j<produse.size();j++)
                if(produse[i]->getPret() > produse[j]->getPret())
                    swap(produse[i],produse[j]);

    }
    void cantitate(){
        int maxi = 0;
        int cnt;
        for(int i=0;i<produse.size();i++)
            if(produse[i]->getCantitate() > maxi){
                maxi = produse[i]->getCantitate();
                cnt = i; }
        cout << *produse[cnt];
    }
    void titlu(){
        string search;
        cin >> search;
        for(int i=0; i<produse.size();i++){
            auto* copy = dynamic_cast<Carte*>(produse[i].get());
            if(copy != nullptr){
                if(copy->getTitlu() == search )
                    cout << *produse[i];
            }
        }
    }
};

int main(){
    Meniu m;
    m.run();
    return 0;
}
