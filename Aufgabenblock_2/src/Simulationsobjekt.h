#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>

class Simulationsobjekt {
private:
	static int p_iMaxID;
public:
	// Konstruktoren
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);

	// Destruktoren
	virtual ~Simulationsobjekt();

	// Simulationsmethode
	virtual void vSimulieren() = 0;

	// Ausgabemethode
	virtual void vAusgeben();
	virtual void vAusgeben(std::ostream& os) const;

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
protected:
	std::string p_sName;
	const int p_iID = 0;
	double p_dZeit = 0;
};

//std::ostream& operator<<(std::ostream& os, Simulationsobjekt& simulationsObjekt);

#endif
