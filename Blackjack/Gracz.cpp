#define _CRT_SECURE_NO_WARNINGS
#include "Gracz.h"
#include"Kasyno.h"
#include<iostream>
#include<stdio.h>
#include<iomanip>

Gracz::Gracz() : ileKart(0), wartoscKart(0), czySpasowal(false) {
	for (int i = 0; i < 10; i++) {
		karty[i] = nullptr;
	}
}

void Gracz::wypiszKarty() {
	for (int i = 0; i < ileKart; i++) {
		karty[i]->wypisz();
	}
}

void Gracz::wezKarte(Karta* _nowaKarta) {
	ileKart++;
	karty[ileKart - 1] = _nowaKarta;
	wartoscKart += _nowaKarta->getWartosc();
}

void Gracz::podejmijDecyzje(Kasyno& _kasyno) {
	if (wartoscKart >= 21) {
		czySpasowal = true;
	}
	if (!czySpasowal) {
		system("cls");
		std::cout << nazwa << " podejmi decyzje!\n" << "Aktualnie masz " << wartoscKart << " pkt\n";
		int decyzja;
		std::cout << "Pasujesz? (wprowadz liczbe)\n1.tak\n2.nie\n";
		while (1) {
			std::cin >> std::setw(1) >> decyzja;
			if (std::cin.fail()) {
				std::cout << "Zle dane, sprobuj jeszcze raz!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (decyzja != 1 && decyzja != 2) {
				std::cout << "Nie ma takiej opcji!\n";
			}
			else
				break;
		}
		if (decyzja == 1) {
			czySpasowal = true;
		}
		else {
			czySpasowal = false;
		}
		if (!czySpasowal) {
			wezKarte(_kasyno.dajKarte());
		}
	}
}

void Gracz::nadajNazwe() {
	char dane[20];
	std::cout << "Podaj imie gracza: \n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (1) {
		std::cin >> std::setw(20) >> dane;
		if (std::cin.fail()) {
			std::cout << "Zle dane, sprobuj jeszcze raz!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
	strcpy(nazwa, dane);
}

Karta* Gracz::getKarta(int _numerKarty) {
	if (_numerKarty < 0 || _numerKarty > ileKart)
		return nullptr;
	else
		return karty[_numerKarty];
}

Gracz::~Gracz() {

}