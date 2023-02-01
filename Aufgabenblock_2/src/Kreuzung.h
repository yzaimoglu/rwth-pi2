#pragma once
#include <memory>
#include <list>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Weg.h"

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
private:
	// shared_ptr, da ein Weg an mehreren Kreuzungen sein kann
	std::list<std::shared_ptr<Weg>> p_pWege;
	// Tankstellenkapazität
	double p_dTankstelle;
public:
	// Standardkonstruktor & Konstruktor mit Parametern
	Kreuzung();
	Kreuzung(std::string sName, double dTankstelle = 0);

	// Statische Methode zum Verbinden von zwei Wegen
	static void vVerbinde(std::string sNameHinweg, std::string sNameRuckweg,
			double dWegLaenge, std::weak_ptr<Kreuzung> pStartKreuzung,
			const std::weak_ptr<Kreuzung> pZielKreuzung, Tempolimit eTempolimit = Tempolimit::AUTOBAHN, bool bUeberholverbot = true);

	// Tanken eines Fahrzeugs an einer Kreuzung
	void vTanken(Fahrzeug&);

	// Annahme eines Fahrzeugs durch die Kreuzung
	void vAnnahme(std::unique_ptr<Fahrzeug>, double dZeit);

	// Simulation des Simulationsobjekts Kreuzung
	void vSimulieren();

	// Tankstellenkapazität erhalten
	double getTankstelle() {
		return p_dTankstelle;
	}

	// Tankstellenkapazität abziehen
	void setTankstelle(double dTanke) {
		p_dTankstelle -= dTanke;
		if(p_dTankstelle < 0) {
			p_dTankstelle = 0;
		}
	}

	// Returned alle Wege
	std::list<std::shared_ptr<Weg>> getWege() {
		return p_pWege;
	}

	// Aussuchen eines zufälligen Weges
	Weg& pZufaelligerWeg(Weg& weg) {
		Weg& rueckweg = weg.getRueckweg();

		// Wenn es nur einen Weg gibt, dann wird der Rückweg genommen (Sackgasse)
		if(p_pWege.size() == 1) {
			return rueckweg;
		}

		// Zufallsgenerator
		int r = (rand() % p_pWege.size());

		// Iterieren durch die Wege und auswählen eines Weges
		std::list<std::shared_ptr<Weg>>::iterator it = p_pWege.begin();
		for(int i = 0; i < r; i++) it++;

		// Wenn der zufällige Weg dem Rückweg des Weges entspricht, dann wird erneut ein zufälliger Weg ausgesucht
		if((*it).get() == &rueckweg) {
			return pZufaelligerWeg(weg);
		}

		// Den zufälligen Weg zurückgeben
		return *(*it);
	}

	virtual ~Kreuzung();
};

#endif
