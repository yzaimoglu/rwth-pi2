#include "Verhalten.h"

// Standardkonstruktor
Verhalten::Verhalten() {
}

// Konstruktor mit Weg
Verhalten::Verhalten(Weg& weg)
	: p_pWeg(&weg){
}

// Ermittlung wie lange das Fahrzeug innerhalb des Zeitintervalls noch fahren kann ohne Überschreitung des Wegendes
double Verhalten::dStrecke(Fahrzeug& aFahrzeug, double dZeitIntervall) {
	std::cout << "wird ausgeführt" << std::endl;
	// Teilstrecke
	double dTeilstrecke = aFahrzeug.dGeschwindigkeit() * dZeitIntervall;

	std::cout << dTeilstrecke << std::endl;

	// Überprüfen ob die gefahrene Strecke die Länge überschreitet und setzen der Abschnittstrecke
	if (aFahrzeug.getAbschnittStrecke() + dTeilstrecke > p_pWeg->getLaenge()) {
		std::cout << "Ende des Weges erreicht." << std::endl;
		double dUberschrriteneStrecke = aFahrzeug.getAbschnittStrecke() + dTeilstrecke - p_pWeg->getLaenge();
		aFahrzeug.setAbschnittStrecke(dTeilstrecke-dUberschrriteneStrecke);
		return dTeilstrecke-dUberschrriteneStrecke;
	}
	std::cout << "Weiter" << std::endl;
	aFahrzeug.setAbschnittStrecke(dTeilstrecke);
	return dTeilstrecke;
}

// Destruktor
Verhalten::~Verhalten() {
}

