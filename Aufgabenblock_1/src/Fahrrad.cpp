#include <math.h>
#include <iomanip>
#include "Fahrrad.h"

// Standardkonstruktor
Fahrrad::Fahrrad() : Fahrzeug() {
	std::cout << "Das Fahrzeug ist ein Fahrrad." << std::endl;
}

// Konstruktor
Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit)
	: Fahrzeug(sName, dMaxGeschwindigkeit) {
	std::cout << "Das Fahrzeug ist ein Fahrrad." << std::endl;
}

// Destruktor
Fahrrad::~Fahrrad() {
	std::cout << "(-) " << "Das Fahrzeug ist ein Fahrrad." << std::endl;
}

// Definition der override Memberfunktion dGeschwindigkeit()
double Fahrrad::dGeschwindigkeit() {
	if(p_dMaxGeschwindigkeit < 12) {
		double dGeschwindigkeit = p_dMaxGeschwindigkeit;
		return dGeschwindigkeit;
	}

	// Anzahl der 20km Abschnitte
	int iAbschnitte = (int) (p_dGesamtStrecke / 20);

	// 10%ige Abnahme der Geschwindigkeit per 20km Abschnitt
	double dGeschwindigkeit = p_dMaxGeschwindigkeit * pow(1.0-0.1, iAbschnitte);

	// Minimalgeschwindigkeit soll 12km/h sein
	if(dGeschwindigkeit < 12) {
		dGeschwindigkeit = 12;
	}
	return dGeschwindigkeit;
}

// Definition der override Memberfunktion vAusgeben()
void Fahrrad::vAusgeben() {
	Fahrzeug::vAusgeben();
	std::cout << std::setw(30)
		<< 0
		<< std::setw(30)
		<< 0
		<< std::endl;
}

// Definition der override Memberfunktion vAusgeben()
void Fahrrad::vAusgeben(std::ostream& o) const {
	Fahrzeug::vAusgeben(o);
	o << std::setw(30)
		<< 0
		<< std::setw(30)
		<< 0
		<< std::endl;
}

// Definition der override Memberfunktion vSimulieren()
void Fahrrad::vSimulieren() {
	Fahrzeug::vSimulieren();
}
