#include <iostream>
#include <iomanip>
#include <limits>
#include "zdarzenie.h"
#include "terminarz.h"

using namespace std;

void instrukcja (){
    cout<<"\t###### PIERWSZE I NAJWAZNIEJSZE! #####\n### Wpisuj daty i godziny z wiodacymi zerami, tzn. zamiast napisac 'godz 9:30' lub '1/2/2019'"
        <<"napisz: 'godz 09:30' lub '01/02/2019' ###\n### Jezeli zdecydujesz sie podac zarowno date jak i godzine, wpisz najpierw date, pozniej godzine. ###\n"
        <<"W naszym terminarzu mozesz umieszczac daty na wiele sposobow:\n"
        <<"\t1. Podaj pelna date. Mozesz podac zarowno w postaci 12.05.2019 godz 17:30 czy 12/05/2019 17:30. Znaki oddzielajace sa nieistotne.\n"
        <<"\t2. Podaj sama godzine. Nalezy zaznaczyc ze wpisujesz godzine - napisz 'godz', 'godzina' lub 'godziny' a nasz program rozpozna ze chodzi Ci o godzine."
        <<" Data automatycznie zostanie ustawiona na dzisiaj.\n"
        <<"\t3. Podaj sam dzien i miesiac. Mozesz wpisac miesiac liczba, albo slownie, tzn. 'kwi', 'kwiecien' lub 'kwietnia'. Godzina pozostanie wtedy nieustalona!\n"
        <<"\t4. Wpisz 'dzisiaj' badz 'dzis' - data zostanie automatycznie ustawiona! Mozesz dodatkowo okreslic godzine.\n"<<endl;
}

void czyscBuff(){
    cin.clear();
    cin.ignore( numeric_limits <streamsize>::max(), '\n' );
}

void dodajDoListy ( const Data & dzis , Terminarz & mojTerm ){
    czyscBuff();
    string tresc_;
    string data_;
    cout<<"Podaj tresc Twojego zdarzenia:\n";
    getline( cin, tresc_ );
    cout<<"Podaj czas:\n";
    getline( cin, data_ );
    Zdarzenie dodawany( tresc_, data_, dzis );
    mojTerm.dodajZdarzenie( dodawany );
    cout<<"\tDodano zdarzenie."<<endl;
}

void zapiszDane ( Terminarz & mojTerm ){
    ofstream zapis ( "dane.txt", std::ios::trunc | std::ios::out );
    list<Zdarzenie>::iterator iter = mojTerm.poczatek();
    list<Zdarzenie>::iterator kontrolny = mojTerm.koniec();
    --kontrolny;
    for( ; iter != mojTerm.koniec(); ++iter ){
        zapis << *iter;
        if ( iter != kontrolny )
            zapis << endl;
    }
    zapis.close();
    zapis.clear();
}

void wczytajDane ( const Data & dzis, Terminarz & mojTerm ){
    ifstream odczyt ( "dane.txt" , std::ios::in );
    string liniaTresc;
    string liniaData;
    Zdarzenie tymcz;
    while ( !odczyt && !( odczyt.eof() ) ){
        getline ( odczyt, liniaTresc );
        getline ( odczyt, liniaData );
        tymcz = Zdarzenie( liniaTresc, liniaData, dzis );
        mojTerm.dodajZdarzenie( tymcz );
        liniaTresc.clear();
        liniaData.clear();
    }
    odczyt.close();
    odczyt.clear();
}

void wypiszListe ( Terminarz & mojTerm ){
    mojTerm.drukujListe();
}

void wypiszTeraz ( Terminarz & mojTerm, const Data & dat ){
    cout<<"Zdarzenia na biezaca godzine:\n"<<endl;
    mojTerm.drukujTeraz( dat );
}

void wypiszDzisiaj ( Terminarz & mojTerm, const Data & dat ){
    cout<<"Zdarzenia na dzisiaj:\n"<<endl;
    mojTerm.drukujDzisiaj( dat );
}

void wypiszTydzien ( Terminarz & mojTerm, const Data & dat, const struct tm * dzisiaj ){
    cout<<"Zdarzenia na biezacy tydzien:\n"<<endl;
    mojTerm.drukujTydzien( dat, dzisiaj );
}

void wypiszMiesiac ( Terminarz & mojTerm, const Data & dat ){
    cout<<"Zdarzenia na ten miesiac:\n"<<endl;
    mojTerm.drukujMiesiac( dat );
}

void wypiszRok ( Terminarz & mojTerm, const Data & dat ){
    cout<<"Zdarzenia na ten rok:\n"<<endl;
    mojTerm.drukujRok( dat );
}

void aktualizuj ( struct tm * aktCzas ){
    time_t akt;
    time ( & akt );
    aktCzas = localtime ( & akt );
}

void aktualizujObecnaDate ( Data & dzis, const struct tm * teraz ){
    dzis = Data( teraz );
}

void wypiszObecnaDate ( Data & dzis, struct tm * teraz ) {
    aktualizuj( teraz );
    aktualizujObecnaDate( dzis, teraz );
    cout<<dzis<<endl;
}

void wypisz ( Terminarz & mojTerm, const Data & dat, const struct tm * dzisiaj ){
    cout<<"Ktore ze zdarzen chcesz wypisac?\n";
    cout<<"\t1) Wszystkie\n\t2) Na obecna godzine\n\t3) Na dzisiaj\n\t4) Na biezacy tydzien\n\t5) Na biezacy miesiac\n\t6) Na biezacy rok\n\t7) Cofnij\n";
    int odpowiedz;
    cin>>odpowiedz;
    switch ( odpowiedz ){
        case 1:{
            wypiszListe( mojTerm );
            break;
        }
        case 2:{
            wypiszTeraz( mojTerm, dat );
            break;
        }
        case 3:{
            wypiszDzisiaj( mojTerm, dat );
            break;
        }
        case 4:{
            wypiszTydzien( mojTerm, dat, dzisiaj );
            break;
        }
        case 5:{
            wypiszMiesiac( mojTerm, dat );
            break;
        }
        case 6:{
            wypiszRok( mojTerm, dat );
            break;
        }
        case 7:
            break;
        default :
            break;
    }
}

void wypiszMenu (){
    cout<<endl<<"1) Dodaj nowe zdarzenie\n2) Usun zdarzenie\n3) Wypisz zdarzenia\n4) Wpisz ilosc wszystkich zdarzen\n"
        <<"5) Wypisz obecna date i czas\n6) Instrukcja uzytkowania\n7) Zapisz i wyjdz"<<endl;
}

void powitanie (){
    cout<<"\t\tWITAJ W APLIKACJI MOJ TERMINARZ!\n";
    cout<<endl<<"Powiedz mi, co chcialbys zrobic?:\n";
}

void usunZdarzenie ( Terminarz & mojTerm ){
    cout<<"Ktore ze zdarzen chcesz usunac? Podaj sama tresc:"<<endl;
    string usuwany;
    czyscBuff();
    getline( cin, usuwany );
    if ( mojTerm.usunZdarzenie( usuwany ) == true )
        cout<<"\n\tPomyslnie usunieto zdarzenie.\n";
    else
        cout<<"\n\tNie ma takiego zdarzenia!\n";
}
