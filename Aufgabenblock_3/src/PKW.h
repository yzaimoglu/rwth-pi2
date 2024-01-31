#pragma once
#include <limits>
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Weg.h"

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
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

	// Geschwindigkeitsimplementierung für das PKW
	// Wenn die Maximalgeschwindigkeit höher ist als das Tempolimit, dann wird das Tempolimit eingehalten
	double dGeschwindigkeit() const override {
		if(p_pVerhalten->getWeg()->getTempolimit() <= p_dMaxGeschwindigkeit) {
			return p_pVerhalten->getWeg()->getTempolimit();
		}
		return p_dMaxGeschwindigkeit;
	};

	// Gibt das Tankvolumen des PKWs zurück
	double getTankvolumen() {
		return p_dTankvolumen;
	}

	// Funktion zum Simulieren
	void vSimulieren() override;

	// Funktion zum Zeichnen, geerbt von Fahrzeug
	virtual void vZeichnen(const Weg&) const override;

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	void vAusgeben() const override;

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	std::ostream& vAusgeben(std::ostream& o) const override;
	std::istream& vEinlesen(std::istream& is);

	// Destruktor
	~PKW();
};

std::ostream& operator<<(std::ostream& os, const PKW& pkw);

#endif
