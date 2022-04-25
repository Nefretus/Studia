#define _CRT_SECURE_NO_WARNINGS
#include "Bot.h"
#include"Kasyno.h"
#include<stdio.h>

const int ryzykujacy = 19;
const int normalny = 17;
const int zachowawczy = 15;

Bot::Bot() {
	int losujTypGracza = rand() % 2;
	if (losujTypGracza == 0) {
		odwaga = ryzykujacy;
	}
	else if (losujTypGracza == 1) {
		odwaga = normalny;
	}
	else {
		odwaga = zachowawczy;
	}
}

void Bot::podejmijDecyzje(Kasyno& _kasyno) {
	if (wartoscKart >= odwaga) {
		czySpasowal = true;
		return;
	}
	if(!czySpasowal) {
		wezKarte(_kasyno.dajKarte());
	}
}

void Bot::nadajNazwe(int _numerBota) {
	if (_numerBota == 0)
		strcpy(nazwa, "Bot1");
	else if (_numerBota == 1)
		strcpy(nazwa, "Bot2");
	else if (_numerBota == 2)
		strcpy(nazwa, "Bot3");
	else
		strcpy(nazwa, "Bot");
}