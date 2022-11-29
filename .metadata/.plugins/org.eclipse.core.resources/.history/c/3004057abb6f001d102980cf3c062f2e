#pragma once
#include "Fahrzeug.h"

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

class Fahrrad : public Fahrzeug {
public:
	// Standardkonstruktor
	Fahrrad();

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrrad(std::string sName, double dMaxGeschwindigkeit);

	// Funktion für die aktuelle Geschwindigkeit
	virtual double dGeschwindigkeit() override;

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	virtual void vAusgeben() override;

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	virtual void vAusgeben(std::ostream& o) const override;

	// Funktion zum Simulieren
	virtual void vSimulieren() override;

	// Destruktor
	virtual ~Fahrrad();
};

#endif
