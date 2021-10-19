#pragma once
#ifndef USERMENU_H
#define USERMENU_H

#include "UserFunctions.h"

/*Popunjavanje prilikom registracije
	@param socket 
	@return true ako je uspesno registrovanje, false ako je neuspesno
*/
bool new_user(SOCKET socket);

/*Popunjavanje prilikom prijavljivanja
	@param socket 
	@return true ako je uspesno prijavljivanje, false ako je neuspesno
*/
bool log_in(SOCKET socket);

/*Korisnicki meni prilikom pokretanja konzolne aplikacije
	@param socket 
*/
int user_menu(SOCKET socket);

/*Smestanje jednog broda
	@param head pokazivac na pokazivac na pocetak liste koju menjamo
	@param length broda
	@param begin lokacija pocetka broda
	@param end lokacija kraja broda
*/
bool place_one_battleship(LIST **head, int length, char begin[], char end[]);

/*Korisnicki meni koji se prikazuje nakon prijavljivanja/registrovanja
	@param socket
*/
int game_menu(SOCKET socket);

/*Smestanje svih brodova
	@param head pokazivac na pokazivac na pocetak liste koju menjamo
*/
void place_battleships(LIST **head);

/*Igranje igre
	@param socket
	@param head pokazivac na pokazivac na pocetak liste koju menjamo
    @param mode single player/multiplayer
*/
bool play_game(SOCKET socket, LIST **head, int mode);

/*Automatsko igranje igre
	@param socket
	@param head pokazivac na pokazivac na pocetak liste koju menjamo
	@param mode single player
*/
// stress
bool play_game_automatic(SOCKET socket, LIST **head, int mode);

#endif /* USERMENU_H */