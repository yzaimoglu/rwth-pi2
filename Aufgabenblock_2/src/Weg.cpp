#include <iostream>
#include <iomanip>
#include <string>
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Tempolimit.h"

Weg::Weg() :
	Simulationsobjekt(),
	p_dLaenge(15),
	p_eTempolimit(Tempolimit::AUTOBAHN) {

}

// Konstruktor
// 	sName : Name des Weges
//	dLaenge : Länge des Weges in km
//	eTempolimit : Typ der Straße für das Tempolimit (bsp. AUTOBAHN)
Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit) :
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit) {

}

// Destruktor
Weg::~Weg() {

}

// Kopfzeile
void Weg::vKopf() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << "ID"
			<< std::setw(10) << "Name"
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << "Laenge"
			<< std::setw(30) << "Fahrzeuge"
			<< std::endl
			<< std::setw(6+10+30*2)
			<< std::setfill('-')
			<< "-"
			<< std::setfill(' ')
			<< std::endl;
}

// Simuliert alle auf dem Weg befindlichen Fahrzeuge durch eine range-based loop
void Weg::vSimulieren() {
	for (auto const &fahrzeug : p_pFahrzeuge) {
		fahrzeug->vSimulieren();
	}
}

// Definition der Memberfunktion vAusgeben()
void Weg::vAusgeben() {
  Simulationsobjekt::vAusgeben();
  std::string fahrzeuge;
  int iterator = 0;
  if(p_pFahrzeuge.empty()) {
	  fahrzeuge = "( )";
	} else fahrzeuge = "(";
	for(auto fahrzeug = p_pFahrzeuge.cbegin(); fahrzeug != p_pFahrzeuge.cend(); fahrzeug++) {
		iterator++;
		std::string fahrzeug_name = fahrzeug->get()->getName();
		if(iterator == p_pFahrzeuge.size()) {
		  fahrzeuge += fahrzeug_name + ")";
		} else {
			fahrzeuge += fahrzeug_name + ",";
		}
	}
  std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
		    << std::setw(30) << p_dLaenge
		    << std::setw(30) << fahrzeuge;
}


// Definition der Memberfunktion vAusgeben() mit ostream
void Weg::vAusgeben(std::ostream& o) const {
  Simulationsobjekt::vAusgeben(o);
  std::string fahrzeuge;
  int iterator = 0;
  if(p_pFahrzeuge.empty()) {
	  fahrzeuge = "( )";
	} else fahrzeuge = "(";
	for(auto fahrzeug = p_pFahrzeuge.cbegin(); fahrzeug != p_pFahrzeuge.cend(); fahrzeug++) {
		iterator++;
		std::string fahrzeug_name = fahrzeug->get()->getName();
		if(iterator == p_pFahrzeuge.size()) {
		  fahrzeuge += fahrzeug_name + ")";
		} else {
			fahrzeuge += fahrzeug_name + ",";
		}
	}
    o << std::resetiosflags(std::ios::adjustfield)
      << std::setiosflags(std::ios::right)
      << std::setw(30) << p_dLaenge
      << std::setw(30) << fahrzeuge;
}



// Hinzufügen eines neuen Fahrzeugs in die Fahrzeugliste eines Weges
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
	fahrzeug->setAbschnittStrecke(0);
	fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fahrzeug));
}

// Überladung des << Operators
std::ostream& operator<<(std::ostream& o, const Weg& weg) {
	weg.vAusgeben(o);
	return o;
}

