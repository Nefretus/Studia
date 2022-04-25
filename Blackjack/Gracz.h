#pragma once
class Karta;
class Kasyno;
class Gracz {
public:
	Gracz();
	~Gracz();
	void wezKarte(Karta* _ptrKarta);
	void wypiszKarty();
	int ileKartMaGracz() { return ileKart; }
	int jakaWartoscKart() { return wartoscKart; }
	bool getCzyPas() { return czySpasowal; }
	char* getNazwa() { return nazwa; }
	Karta* getKarta(int _numerKarty);
	void podejmijDecyzje(Kasyno& _kasyno);
	void nadajNazwe();
protected:
	bool czySpasowal;
	int wartoscKart;
	char nazwa[20];
private:
	Karta* karty[10];
	int ileKart;
};