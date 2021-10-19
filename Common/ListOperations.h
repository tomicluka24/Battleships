#pragma once
#ifndef LISTOPERATIONS_H
#define LISTOPERATIONS_H
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>

// Polje - red, kolona i stanje (pogodak/promasaj)
typedef struct field_st
{
	int row;
	int column;
	int state;
}FIELD;

// Lista polja - polje i pokazivac na sledece polje
typedef struct list_el
{
	FIELD value;
	struct list_el* next;
}LIST;

/*Otvaranje fajla sa validirajucom dozvolom za citanje i/ili pisanje
@param  file_name  naziv fajla iz kog se cita/u koji se pise
@param  mode  mode citanja ili pisanja
@param  err  broj koji opisuje gresku
*/
FILE *safe_fopen(const char file_name[], const char mode[], int err);

/*Ucitavanje liste iz .txt fajla
@param file_name naziv fajla iz kog se ucitava lista
@return lista ucitana iz .txt fajl-a sa random rasporedjenim poljima
*/
LIST* load_battlefield(char *file_name);

/*Cuvanje elemenata u listu koje korisnik unosi manuelno, kada ne izabere random generisanje
*
*param head pokazivac na pocetak liste u koju se upisuju uneti elementi
*/
void save_battlefield(LIST *head);

/*Generisanje random pozicija brodova koji su ucitani iz .txt fajla
*return lista koja je ucitana iz .txt fajla sa random poljima
*/
LIST* get_random_battlefield();

/**
*Racunanje velicine prosledjene liste
* @param  head  pokazivac na pocetak liste
* @return      the size of the list
*/
int GetSize(LIST *head);

/*
*Dodavanje novog elementa na kraj liste
* @param  head  pokazivac na pokazivac na pocetak liste
* @param  newValue polje koje se dodaje
*/
void PushBack(LIST **head, FIELD newValue);

/*
*Dodavanje novog elementa na pocetak liste
* @param  head  pokazivac na pokazivac na pocetak liste
* @param  newValue polje koje se dodaje
*/
void PushFront(LIST **head, FIELD newValue);

/*Brisanje svih elemenata liste
* @param  head  pokazivac na pokazivac na pocetak liste
*/
void ClearList(LIST **head);

/*Ispis svih elemenata liste
* @param  head  pokazivac na pocetak liste
*/
void PrintList(LIST * head);

/*Cuvanje liste u red
*@param  list lista
*@return red u koji smestamo elemente liste
*/
FIELD* list_to_array(LIST* list);

/*Trazenje vrednosti elementa koji je na prosledjenoj poziciji
*@param  head lista
*@param  index  pozicija elementa u listi ciju vrednost zelimo 
*@return vrednost polja koji se nalazi na prosledjenoj pozici u prosledjenoj listi
*/
FIELD GetNth(struct list_el* head, int index);

/*Trazenje vrednosti elementa koji je na prosledjenoj poziciji
*@param  head pokazivac na pocetak liste
*@param  rowKey  red u tabeli (listi) u kom se nalazi element kog trazimo 
*@param columnKey kolona u tabeli (listi) u kojoj se nalazi element kog trazimo
*@return vrednost elementa koji je na prosledjenoj poziciji
*/
int searchValue(LIST *head, int rowKey, int columnKey);

/*Brisanje poslednjeg elementa u listi
*@param  head  pokazivac na pokazivac na pocetak liste
*@return polje koje je izbrisano
*/
FIELD Pop(LIST **head);

/*Brisanje prvog elementa u listi 
*@param  head  pokazivac na pokazivac na pocetak liste
*/
void DeleteFirstElement(LIST **head);

/*Brisanje poslednjeg elementa u listi
*@param  head  pokazivac na pocetak liste
*/
void RemoveLast(LIST *head);

/*Brisanje elementa liste koji je na prosledjenoj poziciji
*@param  head  pokazivac na pokazivac na pocetak liste
*@param  n  poziicija elementa za brisanje
*@return polje iz tabele (element iz liste) koje je izbrisano
*/
FIELD RemoveByIndex(LIST ** head, int n);

/*Pretraga elementa na prosledjenoj poziciji u listi, ako je pronadjen, menjanje njegovog stanja iz 0 u 1
U suprotnom se kreira novo polje sa stanjem -1 na prosledjenoj poziciji
*@param  head pokazivac na pokazivac na pocetak liste
*@param  row red u tabeli u kom se nalazi trazeni element
*@param  column kolona u tabeli u kojoj se nalazi trazeni element
*/
void shootField(LIST **head, int row, int column);

/*Cuvanje niza u listu
*@param  array niz
*@return lista u koju su smesteni elementi iz prosledjenog niza
*/
LIST* arrayToList(FIELD* array, int array_size);

/*Menjanje stanja polja sa prosledjenom pozicijom na 1, koristi se kad neko pogodi ili promasi protivnikovo polje
*@param  head pokazivac na pokazivac na pocetak liste
*@param  rowKey red u tabeli u kojoj se nalazi polje
*@param  columnKey kolona u tabeli u kojoj se nalazi polje
*/
void changeState(LIST **head, int rowKey, int columnKey);

// stress
/*Generisanje random matrice (samo za testiranje)
@return Lista
*/
LIST* get_random_battlefield_test();

#endif /* LISTOPERATIONS_H */