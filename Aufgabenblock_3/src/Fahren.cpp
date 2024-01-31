#include "Fahren.h"
#include "Verhalten.h"
#include "Streckenende.h"
#include "Parken.h"

Fahren::Fahren() {
}

Fahren::Fahren(Weg& weg) : Verhalten(weg) {
}

// Ermittlung wie lange das Fahrzeug innerhalb des Zeitintervalls noch fahren kann ohne Überschreitung des Wegendes
double Fahren::dStrecke(Fahrzeug& aFahrzeug, double dZeitIntervall) {
	// Berechnung der Teilstrecke
	double dTeilstrecke = aFahrzeug.dGeschwindigkeit() * dZeitIntervall;
	double virtuelleSchranke = p_pWeg->getVirtuelleSchranke();

	if((aFahrzeug.getAbschnittStrecke() - p_pWeg->getLaenge()) == 0) {
		// Throwen des Streckenendes, da das Streckenede erreicht wird
		throw new Streckenende(aFahrzeug, *p_pWeg);
	} else if (aFahrzeug.getAbschnittStrecke() + dTeilstrecke > virtuelleSchranke) {
		// Berechnung der überschrittenen Strecke
		double dUberschrriteneStrecke = aFahrzeug.getAbschnittStrecke() + dTeilstrecke - virtuelleSchranke;

		// Setzen der Abschnittstrecke
		aFahrzeug.setAbschnittStrecke(virtuelleSchranke - aFahrzeug.getAbschnittStrecke());
		if(p_pWeg->getUeberholverbot()) p_pWeg->setVirtuelleSchranke(aFahrzeug.getAbschnittStrecke());
		return dTeilstrecke-dUberschrriteneStrecke;
	}
	// Setzen der Abschnittstrecke
	aFahrzeug.setAbschnittStrecke(dTeilstrecke);
	if(p_pWeg->getUeberholverbot()) p_pWeg->setVirtuelleSchranke(aFahrzeug.getAbschnittStrecke());
	return dTeilstrecke;
}

Fahren::~Fahren() {
}

