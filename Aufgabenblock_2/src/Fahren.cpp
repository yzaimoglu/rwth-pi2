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

//	// Wenn das Überholverbot gilt
//	if(this->getWeg()->getUeberholverbot()) {
//		std::cout << "ÜBERHOLVERBOT" << std::endl;
//
//		// Fahrzeuge auf dem Weg
//		vertagt::VListe<std::unique_ptr<Fahrzeug>>* fahrzeugeOnWeg = this->getWeg()->getFahrzeuge();
//
//		int type = -1;
//		double toSet = -1;
//
//		// Iterieren über Fahrzeuge
//		for(auto& fahrzeugOnWeg : *fahrzeugeOnWeg) {
//			if(!((*fahrzeugOnWeg) == aFahrzeug)) {
//				double fahrzeugOnWegTeilstrecke = (*fahrzeugOnWeg).dGeschwindigkeit() * dZeitIntervall;
//				// Überprüfen ob Überholen stattfindet, wenn ja nicht überholen
//				std::cout << aFahrzeug.getName() + ":::: " << aFahrzeug.getAbschnittStrecke() + dTeilstrecke << std::endl;
//				std::cout << (*fahrzeugOnWeg).getName() + ":::: " << (*fahrzeugOnWeg).getAbschnittStrecke() + fahrzeugOnWegTeilstrecke<< std::endl;
//
//				// Überprüfen ob das Ende erreicht wird
//				if((*fahrzeugOnWeg).getAbschnittStrecke() + fahrzeugOnWegTeilstrecke >= p_pWeg->getLaenge()) {
//					type = 0;
//					toSet = p_pWeg->getLaenge() - aFahrzeug.getAbschnittStrecke();
//				} else if((*fahrzeugOnWeg).getAbschnittStrecke() + fahrzeugOnWegTeilstrecke >= aFahrzeug.getAbschnittStrecke() + dTeilstrecke) {
//					type = 1;
//					toSet = ((*fahrzeugOnWeg).getAbschnittStrecke() + fahrzeugOnWegTeilstrecke) * 0.99;
//				}
//			}
//		}
//
//		switch (type) {
//			case 0:
//				aFahrzeug.setAbschnittStrecke(toSet);
//				break;
//			case 1:
//				aFahrzeug.resetAbschnittStrecke();
//				aFahrzeug.setAbschnittStrecke(toSet);
//				break;
//			default:
//				break;
//		}
//	}

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

