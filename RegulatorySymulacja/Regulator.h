#pragma once
class Pomieszczenie;
class Grzejnik;
class Regulator { 
public:
	Regulator();
	virtual void steruj(float _czas) = 0;
	void setTemperatura(float _temp = 20);
	void dodajGrzenikIPomieszczenie(Pomieszczenie*, Grzejnik*);
	float getZadanaTemperatura() { return zadanaTemperatura; }
protected:
	Grzejnik* grzejnik;
	Pomieszczenie* pomieszczenie;
private:
	float zadanaTemperatura;
};
