#include <bits/stdc++.h>
#include <string>
using namespace std;
ofstream g("date.out");
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

class Vaccin : public IoBase {
    protected:
        int pret,temperatura;
        vector <string> substante;
    public:

    Vaccin(int pret, int temperatura, const vector<string> &substante);

    Vaccin();

    virtual void schema(){}

    istream &read(istream &is) override;;

    ostream &write(ostream &os) const override;;


};

Vaccin::Vaccin(int pret, int temperatura, const vector<string> &substante) : pret(pret), temperatura(temperatura),
                                                                             substante(substante) {}
Vaccin::Vaccin() {}

istream &Vaccin::read(istream &is) {
    IoBase::read(is);
    cout << "Introduceti pret";
    is >> pret;
    cout << "Introduceti temperatura de depozitare";
    is >> temperatura;
    int n;
    string substanta;
    cout << "Introduceti numarul de substante din compozitie : ";
    cin >> n;
    for (int i=0; i<n ; i++){
        cin >> substanta;
        substante.push_back(substanta);
    }
    return is;
}

ostream &Vaccin::write(ostream &os) const {
    IoBase::write(os);
    cout << "Pretul : ";
    os << pret << endl;
    cout << "Temperatura : ";
    os << temperatura << endl;
    cout << "Lista de substante din compozitie : ";
    for ( auto x : substante)
        cout << x;
    cout << endl;
    return os;
}

class Antigripal : public Vaccin {
private:
    string tulpina;
    bool OMS;
public:
    Antigripal();

   Antigripal(int pret, int temperatura, const vector<string> &substante, const string &tulpina, bool OMS);

   void schema() override;

   istream &read(istream &is) override;

    ostream &write(ostream &os) const override;;

};


Antigripal::Antigripal() {}
Antigripal::Antigripal(int pret, int temperatura, const vector<string> &substante, const string &tulpina, bool OMS) : Vaccin(pret, temperatura, substante), tulpina(tulpina), OMS(OMS){}

void Antigripal::schema() {
    cout << " Vaccinul Antigripal se administrează la adulți o doză de 0.5 ml, iar la copii și adolescenți o doză de 0.3 ml, repetându-se din 2 în 2 ani";
}

istream &Antigripal::read(istream &is) {
    Vaccin::read(is);
    return is;
}

ostream &Antigripal::write(ostream &os) const {
    Vaccin::write(os);
    return os;
}



class Antihepatita : public Vaccin {
private:
    char hepatita;
    string mod;
public:
    Antihepatita();
    Antihepatita(int pret, int temperatura, const vector<string> &substante, char hepatita, const string &mod);
    void schema() override;
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
Antihepatita::Antihepatita() {}
Antihepatita::Antihepatita(int pret, int temperatura, const vector<string> &substante, char hepatita, const string &mod) : Vaccin(pret, temperatura, substante), hepatita(hepatita), mod(mod){}
void Antihepatita::schema() {
    cout << "A și B, la copii cu vârstă mai mică de 1 an se adminstrează 2\ninjectări la un interval de o lună, a treia injectare după 6 luni de la prima administrare, la adulți\nconform schemei de imunizare recomandată de medic; cel Antihepatită C doar la recomandarea\nmedicului";
}

istream &Antihepatita::read(istream &is) {
    Vaccin::read(is);
    cout << "Tipul hepatitei : ";
    is >> hepatita;
    cout << "Modalitate vaccinare : ";
    is >> mod;
    return is;

}
ostream &Antihepatita::write(ostream &os) const {
    Vaccin::write(os);
    cout << "Tipul hepatitei : ";
    os << hepatita << endl;
    cout << "Modalitate vaccinare : ";
    os << mod << endl;
    return os;
}


class Sarscov2 : public Vaccin {
private:
    vector <string> reactii;
    float eficienta;
    vector <string> medicamente;
public:
    Sarscov2();
    Sarscov2(int pret, int temperatura, const vector<string> &substante,const vector<string> &reactii, float eficienta, const vector <string> &medicamente);
    void schema() override;
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

Sarscov2::Sarscov2() {}
Sarscov2::Sarscov2(int pret, int temperatura, const vector<string> &substante, const vector<string> &reactii,
                   float eficienta, const vector<string> &medicamente) : Vaccin(pret, temperatura, substante),reactii(reactii), eficienta(eficienta), medicamente(medicamente) {}

void Sarscov2::schema() {
    cout << "se administrează persoanelor cu vârstă de peste 16 ani, 2 doze la o\nperioadă de 21 zile.";
}

istream &Sarscov2::read(istream &is) {
    Vaccin::read(is);
    int n1,n2;
    string reactie,medicament;
    cout << "Introduceti nr reactii : ";
    cin >> n1;
    for(int i=0;i<n1;i++){
        cin >> reactie;
        reactii.push_back(reactie);
    }
    cout << "Introduceti eficienta : ";
    is >> eficienta;
    cout << "Introduceti nr medicamente : ";
    cin >> n2;
    for(int i=0;i<n2;i++){
        cin >> medicament;
        medicamente.push_back(medicament);
    }

    return is;
}

ostream &Sarscov2::write(ostream &os) const {
    Vaccin::write(os);
    cout << "Reactii adverse : " ;
    for (auto i:reactii)
        os << i << " ";
    cout << endl;
    cout << "Eficienta: ";
    os << eficienta;
    for (auto x:medicamente)
        os << x << " ";
    cout << endl;
    return os;

}

shared_ptr<Vaccin> citireVaccin() {
    shared_ptr<Vaccin> v;
    int tip;
    cout << "1.Antigripal\n2.Antihepatic\n3.Sarscov2";
    cin >> tip;
    if (tip == 1)
        v = make_shared<Antigripal>();
    else if(tip == 2)
        v = make_shared<Antihepatita>();
    else if(tip == 3)
        v = make_shared<Sarscov2>();
    else return nullptr;
    cin >> *v;
    return v;

}
class Comenzi : public IoBase {
private:
    vector <shared_ptr<Vaccin>> vaccinuri;
    int cantitate;
    unsigned int ID;
    static unsigned int staticID;
    string data;
    string numeClient;
public:

shared_ptr<Comenzi> readComanda();

istream &read(istream &is) override;
ostream &write(ostream &os) const override;


};

istream &Comenzi::read(istream &is) {
    int nr;
    cout << "Introduceti data : ";
    is >> data;
    cout << "Introduceti nume client: ";
    is >> numeClient;
    cout << "Numar vaccinuri : ";
    is >> nr;
    for(int i=0;i<nr;i++)
        vaccinuri.push_back(citireVaccin());

    return is;
}

ostream &Comenzi::write(ostream &os) const {
    for(int i=0;i<vaccinuri.size();i++){
        os << "Vaccin "<< endl;
        os << *vaccinuri[i] << endl;}
    return os;

}

shared_ptr<Comenzi> citireComanda() {
    shared_ptr<Comenzi> c;
    c = make_shared<Comenzi>();
    cin >> *c;
    return c;
}

class ListComenzi : public IoBase {
private:
    shared_ptr<Comenzi> comenzi;
public:


};

class Menu : public IoBase {
private:
    vector <shared_ptr<Comenzi>> comenzi;
    vector <shared_ptr<Vaccin>> vaccinuri;
public:
    void showOptions(){
        cout << "1.Adaugare vaccin nou" << endl;
        cout << "2.Afisare vaccinuri" << endl;
        //cout << "3.Numele producatorilor pentru toate vaccinurile" << endl;
        cout << "4.Adaugarea unei comenzi" << endl;
        cout << "5.Afisarea tuturor comenzilor" << endl;
        //cout << "6.Valoarea comenzilor dintr-o anumita zi" << endl;
        cout << "7.Afisarea schemei de vaccinare" << endl;
        cout << "8.Exportul comenzilor intr-un fisier .txt" << endl;

    }
    void run(){
        showOptions();
        int option;
        cin >> option;
        while(option > 0 && option < 9){
        if(option == 1)
            adaugareVaccin();
        else if(option == 2)
            afisareVaccin();
        else if(option == 7)
            afisareSchema();
        else if(option == 4)
            adaugareComanda();
        else if(option == 5)
            afisareComenzi();
        else if(option == 8)
            afisareTXT();
        else {
            cout << "Programul s-a incheiat cu succes !" ;
            break;
        }
            showOptions();
            cin >> option; } }

    void adaugareVaccin();
    void afisareVaccin();
    void afisareSchema();
    void adaugareComanda();
    void afisareComenzi();
    void afisareTXT();
//    void operator+=(citireComanda());


};

    void Menu::adaugareVaccin() {
    vaccinuri.push_back(citireVaccin());
}
    void Menu::afisareVaccin() {
    for(int i=0; i<vaccinuri.size(); i++)
        cout << *vaccinuri[i] << "--------" << endl;
}
    void Menu::afisareSchema() {
        Vaccin* list[3];
        list[0]=new Antigripal();
        list[1]=new Antihepatita ();
        list[2]=new Sarscov2();
        cout << "Alegeti tipul vaccinului : ";
        cout << "1.Antigripal\n2.Antihepatic\n3.Antisarscov2";
        int opt;
        cin >> opt;
        list[opt-1]->schema();
    }
    void Menu::adaugareComanda() {
        comenzi.push_back(citireComanda());
    }
    void Menu::afisareComenzi() {
        for(int i=0;i<comenzi.size();i++)
            cout << *comenzi[i] << "--------" << endl;
    }
    void Menu::afisareTXT(){
        for(int i=0;i<comenzi.size();i++)
            g << *comenzi[i] << "--------" << endl;
    }
int main(){
//    Antigripal a;
//    Antihepatita b;
//    Sarscov2 c;
//    cin>>a>>b>>c;
//    cout<<a<<b<<c;
 Menu meniu;
 meniu.run();
 return 0; }
