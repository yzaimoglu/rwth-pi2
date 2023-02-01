#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>

class Simulationsobjekt {
private:
	// Statische MaxID zum incrementen
	static int p_iMaxID;
public:
	// Standardkonstruktor und genutzer Konstruktor
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);

	// Standarddestruktor
	virtual ~Simulationsobjekt();

	// Simulationsmethode, pure virtuelle Methode
	virtual void vSimulieren() = 0;

	// Ausgabemethoden
	virtual void vAusgeben();
	virtual std::ostream& vAusgeben(std::ostream& os);

	// Getter ID
	const int getID() {
		return p_iID;
	}

	// Getter Name
	std::string getName() const {
		return p_sName;
	}

	// Getter Zeit
	double getZeit() {
		return p_dZeit;
	}

	// Verbieten des Copy-Konstruktors
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	// Überladen einiger Operatoren
	bool operator==(const Simulationsobjekt& simulationsObjekt);
// protected, da die Subklassen Zugriff haben sollen
protected:
	std::string p_sName;
	const int p_iID = 0;
	double p_dZeit = 0;
};

//std::ostream& operator<<(std::ostream& os, Simulationsobjekt& simulationsObjekt);

#endif
