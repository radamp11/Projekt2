#ifndef POWLOKA_H
#define POWLOKA_H
#include "terminarz.h"

void instrukcja ();

void czyscBuff();

void zapiszDane ( Terminarz & mojTerm );

void dodajDoListy ( const Data & dzis , Terminarz & mojTerm );

void wczytajDane ( const Data & dzis, Terminarz & mojTerm );

void wypiszListe ( Terminarz & mojTerm );

void wypiszTeraz ( Terminarz & mojTerm, const Data & dat );

void wypiszDzisiaj ( Terminarz & mojTerm, const Data & dat );

void wypiszTydzien ( Terminarz & mojTerm, const Data & dat, const struct tm * dzisiaj );

void wypiszMiesiac ( Terminarz & mojTerm, const Data & dat );

void wypiszRok ( Terminarz & mojTerm, const Data & dat );

void wypisz ( Terminarz & mojTerm, const Data & dat, const struct tm * dzisiaj );

void aktualizujObecnaDate ( Data & dzis, const struct tm * teraz );

void wypiszObecnaDate ( Data & dzis, struct tm * teraz );

void aktualizuj ( struct tm * aktCzas );

void wypiszMenu ();

void powitanie ();

void usunZdarzenie ( Terminarz & mojTerm );

#endif // POWLOKA_H
