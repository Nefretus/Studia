#include "Symulacja.h"
#include"Regulator.h"
#include"RegulatorBB.h"
#include"RegulatorPID.h"
#include<iostream>
#include<fstream>

Symulacja::Symulacja(float wysokosc, float szerokosc, float glebokosc, float mocNominalana) 
	: pomieszczenie(wysokosc, szerokosc, glebokosc) 
	, grzejnik(mocNominalana)
	, regulator(nullptr)
{
	grzejnik.setPoziomMocy(0);
	if (wysokosc <= 0 || szerokosc <= 0 || glebokosc <= 0 || mocNominalana <= 0) {
		throw "Symulacja dla podanych parametrow nie rozpocznie sie!\n";
	}
}

void Symulacja::dodajRegulator(const char* _jakiRegulator, float _zadanaTemperatura) {
	if (regulator) {
		delete regulator;
	}
	if (_jakiRegulator == "PID") {
		regulator = new RegulatorPID;
	}
	else
		regulator = new RegulatorBB;
	regulator->setTemperatura(_zadanaTemperatura);
	regulator->dodajGrzenikIPomieszczenie(&pomieszczenie, &grzejnik);
}

void Symulacja::iteracja(float _uplywajacyCzas) { 
	regulator->steruj(_uplywajacyCzas);
	pomieszczenie.dodajCieplo(grzejnik.emitowaneCieplo(_uplywajacyCzas));
	pomieszczenie.aktualizuj(_uplywajacyCzas);
}

void Symulacja::przebieg(int _liczbaIteracji, float _dt) {
	for (int i = 0; i < _liczbaIteracji; i++) {
		if (i == 0) {
			try {
				iteracja(_dt);
			}
			catch (int& e) {
				std::cout << "Regulator lub grzejnik nie zostal przypisany do regulatora!\n Symulacja nie zostala rozpoczeta!\n";
				return;
			}
		}
		else
			iteracja(_dt);
		std::cout << pomieszczenie.getTemperatura() << std::endl;
		temperatura.push_back(pomieszczenie.getTemperatura());
		czas.push_back(i * _dt);
		moc.push_back(grzejnik.getPoziomMocy());
	}
	zapis("wykres.csv");
	temperatura.clear();
	czas.clear();
	moc.clear();
}

void Symulacja::zapis(const char* _nazwa) {
	const char srednik = ';';
	std::locale pol("pl_PL");
	std::ofstream plik;
	plik.open(_nazwa, std::ifstream::out);
	if (plik.is_open()) {
		plik.imbue(pol);
		plik << "Temperatura;Czas;Moc\n";
		for (int i = 0; i < temperatura.size(); i++) {
			plik << temperatura.at(i) << srednik << czas.at(i) << srednik << moc.at(i);
			plik << std::endl;
		}
		plik.close();
	}
}

Symulacja::~Symulacja() {
	delete regulator;
}