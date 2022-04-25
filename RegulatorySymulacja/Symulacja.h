#pragma once
#include"Pomieszczenie.h"
#include"Grzejnik.h"
#include<vector>

class Regulator;
class Symulacja {
public:
	void iteracja(float uplywajacyCzas);
	void przebieg(int _ileIteracji, float _czas);
	void zapis(const char* _nazwa);
	void dodajRegulator(const char* _jakiRegulator, float _zadanaTemp);
	Symulacja(float wysokosc, float szerokosc, float glebokosc, float mocNominalna);
	~Symulacja();
	Symulacja(const Symulacja&) = delete;
	Symulacja& operator=(const Symulacja&) = delete;
private:
	Pomieszczenie pomieszczenie;
	Grzejnik grzejnik;
	Regulator *regulator;
	std::vector<float> dane, temperatura, czas, moc;
};
