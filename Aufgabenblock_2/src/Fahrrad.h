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
	double dGeschwindigkeit() const override;

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	void vAusgeben() override;

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	virtual std::ostream& vAusgeben(std::ostream& o) override;

	// Funktion zum Simulieren
	void vSimulieren() override;

	// Funktion zum Zeichnen, geerbt von Fahrzeug
	virtual void vZeichnen(const Weg&) const override;

	// Destruktor
	~Fahrrad();
};

#endif
