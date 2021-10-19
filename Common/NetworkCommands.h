#pragma once
#ifndef NETWORKCOMMANDS_H
#define NETWORKCOMMANDS_H

#include "Drawing.h"

#pragma region structures

// Enumeracija komandi klijenta (id-evi)
static enum command_ids
{
	SHUTDOWN = 0, // Gasenje
	REGISTER, // Registrovanje
	LOGIN, // Prijavljivanje
	NEW_SOLO_GAME, // Single player
	NEW_DUO_GAME, // Multiplayer
	NEW_MOVE, // Novi potez
	REGISTER_OK, // Uspesna registracija
	REGISTER_ERROR, // Greska prilikom registracije
	LOGIN_OK, //Uspesno prijavljivanje
	LOGIN_ERROR, //Greska prilikom prijavljivanja
	GAME_BEGIN, // Pocetak igre
	GAME_END, // Kraj igre
	MOVE, // Na potezu
	MOVE_HIT, // Pogodak
	MOVE_MISS, // Promasaj
	SECOND_PLAYER_MOVE, // Drugi igrac na potezu
	MOVE_TIMEOUT, // Timeout dok je drugi igrac na potezu
	GAME_OVER, // Kraj igre
	WINER, // Pobednik
	LOSER // Gubitnik
}CLIENT_COMMANDS;

// Jedan korisnik se sastoji od imena, prezimena, korisnickog imena i lozinke
typedef struct user_st
{
	char name[15];
	char surname[15];
	char username[15];
	char password[15];
}USER;

// Registrovanje - REGISTER i registrovani korisnik
typedef struct register_user_st
{
	char command_id;
	USER user;
}register_command;

// Prijavljivanje - LOGIN i korisnicko ime i lozinka pomocu kojeg se prijavljivanje izvrsava
typedef struct login_user_st
{
	char command_id;
	char uname[15];
	char pass[15];
}login_command;

// Pocetak igre - GAME_BEGIN, NEW_SOLO_GAME/NEW_DUO_GAME, retka matrica, velicina matrice
typedef struct start_game_st
{
	char command_id;
	char mode;
	FIELD sparse_matrix[17];	//broj ukupno polja x velicina FIELD-a
	int matrix_size;
}start_command;

// Odgovor servera - kod i greska
struct server_response
{
	int code;
	char error[30];
};

// Igrac - socket, korisnicko ime, svoji brodovi
typedef struct player_st
{
	SOCKET socket;
	char username[10];
	LIST *ships;
}player;

// Multiplayer - dva igraca
typedef struct duo_game_st
{
	player player_one;
	player player_two;
}duo_game;

// Potez, kod, move[0] - x osa, move[1] - y osa, move[2] - 0 ako je hit
typedef struct player_move_command
{
	int code;
	char move[3];
}move_command;

#pragma endregion


/*Slanje paketa iz manjih delova ako buffer nema dovoljno mesta
*
@param socket
@param message memorijska lokacija poruke
@param messageSize velicina poruke
@return 1 ako je poruka uspesno poslata i -1 ako je poslata poruka veca od prosledjene velicine
*/
int SendPacket(SOCKET socket, char * message, int messageSize);

/*Primanje paketa iz manjih delova ako buffer nema dovoljno mesta
*
@param socket
@param message memorijska lokacija poruke
@param messageSize velicina poruke
@return 1 ako je poruka uspesno poslata i -1 ako buffer nema dovoljno mesta da skladisti poruku
*/
int RecievePacket(SOCKET socket, char * recvBuffer, int length);

/*Validacija poteza igraca, case insensitive je i moze da handle-uje pogresan redosled, ali ne i pogresne karaktere i duze/krace poruke
*
@return true ako je validacija uspesna, u suprotnom vraca false
*/
bool validate_move(char move[]);

/*Thread za solo igru (server vs client)
*/
DWORD WINAPI solo_game_thread(LPVOID lpParam);

/*Thread za multiplayer (client vs client)
*/
DWORD WINAPI duo_game_thread(LPVOID lpParam);

/*Thread za test solo igre
*/
DWORD WINAPI solo_game_thread_test(LPVOID lpParam);

/*Inicijalizacija windows socket-a
	@return true ako je inicijalizacija uspesna, u suprotnom vraca false
*/
bool InitializeWindowsSockets();

/*Postavljanje socket-a u rezim osluskivanja
    @param listenSocket Pokazivac na listen socket koji ce biti set-ovan u rezim osluskivanja
	@return 1 ako je uspesno set-ovan na osluskivanje, odnosno -1 ako je doslo do greske
*/
int setToListenSocket(SOCKET *listenSocket);

/*Prihvatanje request-a novog klijenta na serveru
	@param listenSocket Pokazivac na listen socket koji prihvata klijenta
	@param clientSocket Pokazivac na klijentski socket koji se kaci na listen socket
	@return true ako je uspesno prihvacen klijent, odnosno false ako je doslo do greske prilikom prihvatanja request-a
*/
bool acceptNewClient(SOCKET *listenSocket, SOCKET *clientSocket);

/*Bind konkretnog port-a i bilo koje adrese na serverski socket
	@param listenSocket Pokazivac na listen socket na koga se bind-uje adresa i port
	@param SERVER_PORT Port koji se bind-uje na socket
	@return 1 ako je binding uspesan, odnosno -1 ako je doslo do greske prilikom binding-a
*/
int BindServerSocket(SOCKET *listenSocket, int SERVER_PORT);
#endif // /* NETWORKCOMMANDS_H */