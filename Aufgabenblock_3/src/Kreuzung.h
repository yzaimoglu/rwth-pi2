#pragma once
#include <memory>
#include <list>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Weg.h"

#ifndef SRC_KREUZUNG_H_
#define SRC_KREUZUNG_H_

class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
private:
	std::list<std::shared_ptr<Weg>> p_pWege;

	double p_dTankstelle;
public:
	Kreuzung();
	Kreuzung(std::string sName, double dTankstelle = 0);

	// statische Methode zum Verbinden von zwei Wegen
	static void vVerbinde(std::string sNameHinweg, std::string sNameRueckweg,
							double dWegLaenge, std::weak_ptr<Kreuzung> pStartKreuzung,
							const std::weak_ptr<Kreuzung> pZielKreuzung, Tempolimit eTempolimit = Tempolimit::AUTOBAHN,
							bool bUeberholverbot = true);
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
	Weg& pZufaelligerWeg(Weg& weg);

	virtual void vAusgeben() const;
	std::ostream& vAusgeben(std::ostream& os) const;
	std::istream& vEinlesen(std::istream&);

	virtual ~Kreuzung();
};

std::ostream& operator<<(std::ostream& os, const Kreuzung& kreuzung);

#endif /* SRC_KREUZUNG_H_ */
