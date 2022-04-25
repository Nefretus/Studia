#pragma once
#include"Regulator.h"
class RegulatorPID: public Regulator {
public:
	RegulatorPID();
	void steruj(float _czas) override;
private:
	float kp, ki, kd, e_poprzednia;
};

