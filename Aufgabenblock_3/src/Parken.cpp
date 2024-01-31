#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

extern double dGlobaleZeit;

Parken::Parken() {
}

Parken::Parken(Weg& weg, double dStartzeitpunkt) :
		Verhalten(weg),
		p_dStartzeitpunkt(dStartzeitpunkt)
{}

// Ermittlung wie lange das Fahrzeug innerhalb des Zeitintervalls noch fahren kann ohne Überschreitung des Wegendes
double Parken::dStrecke(Fahrzeug& aFahrzeug, double dStartzeitpunkt) {
	if(dGlobaleZeit >= p_dStartzeitpunkt) {
		throw new Losfahren(aFahrzeug, *p_pWeg);
	}
	return 0.0;
}

Parken::~Parken() {
}

