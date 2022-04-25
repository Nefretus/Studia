#include "RegulatorPID.h"
#include"Pomieszczenie.h"
#include"Grzejnik.h"
#include<iostream>

const float MAX_MOC = 1.0;

RegulatorPID::RegulatorPID() : kp(4.0f), ki(0.02f), kd(0.1f), e_poprzednia(0)
{}

void RegulatorPID::steruj(float _czas) {
	if (pomieszczenie == nullptr || grzejnik == nullptr) {
		throw - 1;
	}
	float uchyb, Up, Ui, Ud, e_calka = 0, de = 0;
	uchyb = getZadanaTemperatura() - pomieszczenie->getTemperatura();
	Up = kp * uchyb;
	e_calka += uchyb * _czas;
	Ui = ki * e_calka;
	if (e_poprzednia)
		de = (uchyb - e_poprzednia) / _czas;
	Ud = kd * de;
	float sygnalSterujacy = Up + Ui + Ud;
	if (sygnalSterujacy >= 1.0) {
		grzejnik->setPoziomMocy(MAX_MOC);
	}
	else if (sygnalSterujacy < 0) {
		grzejnik->setPoziomMocy(NULL);
	}
	else {
		grzejnik->setPoziomMocy(sygnalSterujacy);
	}
}
