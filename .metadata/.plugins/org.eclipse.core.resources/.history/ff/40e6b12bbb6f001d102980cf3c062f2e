#pragma once
#include <limits>
#include "Fahrzeug.h"

#ifndef PKW_H_
#define PKW_H_

class PKW : public Fahrzeug {
private:
	// Verbrauch l/100km
	double p_dVerbrauch = 0.0;

	// Tankvolumen des PKWS
	double p_dTankvolumen = 55.0;

	// Tankinhalt des PKWs
	// initial die Hälfte des Tankvolumens
	double p_dTankinhalt = p_dTankvolumen / 2;
public:
	// Standardkonstruktor
	PKW();

	// Konstruktor mit dem Namen
	PKW(std::string sName);

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	PKW(std::string sName, double dMaxGeschwindigkeit);

	// Konstruktor mit dem Namen, der maximalen Geschwindigkeit, dem Verbrauch und dem Tankvolumen
	PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55.0);

	// Funktion zum Tanken
	// Standardwert so, dass der Tank vollgetankt wird
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

	// Funktion zum Simulieren
	virtual void vSimulieren() override;

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	virtual void vAusgeben() override;

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	virtual void vAusgeben(std::ostream& o) const override;

	// Destruktor
	virtual ~PKW();
};

#endif
