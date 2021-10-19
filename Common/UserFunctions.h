#pragma once
#ifndef USERFUNCTIONS_H
#define USERFUNCTIONS_H

#include "NetworkCommands.h"

#define FILE_NAME "Users.txt"

/*Cuvanje (upis) korisnika u .txt fajl
	@param user korisnik kog upisujemo
*/
void save_user(USER user);

/*Validacija korisnika
	@param user korisnik cije podatke validiramo
*/
bool validate_user(USER user);

/*Registracija korisnika
	@param user korisnik koji se registruje
*/
bool register_user(USER user);

/*Prijavljivanje korisnika
	@param uname korisnicko ime korisnika prilikom prijavljivanja
	@param pass  lozinka korisnika prilikom prijavljivanja
*/
bool login_user(char* uname, char* pass);

#endif /* USERFUNCTIONS_H */