#include <string>
#include <iostream>
#include <iomanip>
#include "Simulationsobjekt.h"

// Das statische Datenelement Max ID am Anfang auf 0 setzen
int Simulationsobjekt::p_iMaxID = 0;

// Konstruktor
Simulationsobjekt::Simulationsobjekt() : p_iID(++p_iMaxID) {
	std::cout << "(+) " << "Simulationsobjekt mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Konstruktor mit Namen
Simulationsobjekt::Simulationsobjekt(std::string sName) :
		p_sName(sName),
		p_iID(++p_iMaxID) {
	std::cout << "(+) " << "Simulationsobjekt mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Destruktor
Simulationsobjekt::~Simulationsobjekt() {
	std::cout << "Simulationsobjekt mit dem Namen '" << p_sName << "' und der ID " << p_iID << " gelöscht." << std::endl;
}

void Simulationsobjekt::vAusgeben() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << p_iID
			<< std::setw(10) << p_sName
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right);
}

// Definition der Memberfunktion vAusgeben()
void Simulationsobjekt::vAusgeben(std::ostream& o) const {
	o << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << p_iID
			<< std::setw(10) << p_sName
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right);
}

// Überladung des == Operators
bool Simulationsobjekt::operator==(const Simulationsobjekt& simulationsObjekt) {
	if(this->p_iID == simulationsObjekt.p_iID) {
		return true;
	} else {
		return false;
	}
}
