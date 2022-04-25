#pragma once
#include"Karta.h"
class Gracz;
class Bot;
class Kasyno {
public:
	Kasyno(const Kasyno&) = delete;
	Kasyno& operator=(const Kasyno&) = delete;
	Kasyno();
	~Kasyno();
	Karta* dajKarte();
	void graj();
	int wprowadzDane();
private:
	void zapiszDoPliku();
	void tasuj();
	int ktoWygral();
	void rozdajDwieKarty();
	void dodajGraczy();
	void dodajBoty();
	bool wszyscyGraczePas();
	void pokazStanPoRozgrywce();
	void zwolnijPamiec();
	int znajdzMaxPktGraczy();
	int znajdzMaxPktBotow();
	Gracz *gracze;
	Bot *boty;
	Karta talia[52];
	int liczbaGraczy;
	int liczbaBotow;
};