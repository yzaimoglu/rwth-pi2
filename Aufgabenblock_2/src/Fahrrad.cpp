#include <math.h>
#include <iomanip>
#include "Fahrrad.h"
#include "SimuClient.h"

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
double Fahrrad::dGeschwindigkeit() const {
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
	Simulationsobjekt::vAusgeben();
	Fahrzeug::vAusgeben();
	std::cout << std::setw(30)
		<< 0
		<< std::setw(30)
		<< 0
		<< std::endl;
}

// Definition der override Memberfunktion vAusgeben()
std::ostream& Fahrrad::vAusgeben(std::ostream& o) {
	Simulationsobjekt::vAusgeben(o);
	Fahrzeug::vAusgeben(o);
	o << std::setw(30)
		<< 0
		<< std::setw(30)
		<< 0
		<< std::endl;
	return o;
}

// Zeichnen des Fahrrads im Simuserver
void Fahrrad::vZeichnen(const Weg& weg) const {
	// Finden der relativen Position & Zeichnen des Fahrrads
	double relPos = p_dAbschnittStrecke / weg.getLaenge();
	bZeichneFahrrad(p_sName, weg.getName(), relPos, dGeschwindigkeit());
}

// Definition der override Memberfunktion vSimulieren()
void Fahrrad::vSimulieren() {
	Fahrzeug::vSimulieren();
}
