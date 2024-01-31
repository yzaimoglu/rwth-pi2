#pragma once
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include "Kreuzung.h"

#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_

using namespace std;
class Kreuzung;

class Simulation {
public:
	void vSimulieren(double, double);
	void vEinlesen(std::istream& is, bool bMitGrafik = false);
	std::map<std::string, std::shared_ptr<Kreuzung>> mKreuzungen;
};

#endif /* SRC_SIMULATION_H_ */
