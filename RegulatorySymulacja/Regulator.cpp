#include "Regulator.h"
#include"Pomieszczenie.h"
#include"Grzejnik.h"
#include<iostream>

Regulator::Regulator() : grzejnik(nullptr), pomieszczenie(nullptr), zadanaTemperatura(0)
{}

void Regulator::dodajGrzenikIPomieszczenie(Pomieszczenie* _pom, Grzejnik* _grzej) {
	pomieszczenie = _pom;
	grzejnik = _grzej;
}

void Regulator::setTemperatura(float _temp) {
	zadanaTemperatura = _temp;
}