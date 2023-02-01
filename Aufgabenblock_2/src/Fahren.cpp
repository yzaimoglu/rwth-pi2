#include "Fahren.h"
#include "Verhalten.h"
#include "Streckenende.h"

Fahren::Fahren() {
}

Fahren::Fahren(Weg& weg) : Verhalten(weg) {
}

// Ermittlung wie lange das Fahrzeug innerhalb des Zeitintervalls noch fahren kann ohne Überschreitung des Wegendes
double Fahren::dStrecke(Fahrzeug& aFahrzeug, double dZeitIntervall) {
	// Berechnung der Teilstrecke
	double dTeilstrecke = aFahrzeug.dGeschwindigkeit() * dZeitIntervall;

	// Überprüfen ob die gefahrene Strecke die Länge überschreitet und setzen der Abschnittstrecke
	if((aFahrzeug.getAbschnittStrecke() - p_pWeg->getLaenge()) == 0) {
		// Throwen des Streckenendes, da das Streckenede erreicht wird
		throw new Streckenende(aFahrzeug, *p_pWeg);
	} else if (aFahrzeug.getAbschnittStrecke() + dTeilstrecke > p_pWeg->getLaenge()) {
		// Berechnung der überschrittenen Strecke
		double dUberschrriteneStrecke = aFahrzeug.getAbschnittStrecke() + dTeilstrecke - p_pWeg->getLaenge();

		// Setzen der Abschnittstrecke
		aFahrzeug.setAbschnittStrecke(p_pWeg->getLaenge() - aFahrzeug.getAbschnittStrecke());
		return dTeilstrecke-dUberschrriteneStrecke;
	}
	// Setzen der Abschnittstrecke
	aFahrzeug.setAbschnittStrecke(dTeilstrecke);
	return dTeilstrecke;
}

Fahren::~Fahren() {
}

