#include <iostream>

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

// Enum für das Tempolimit
// INNERORTS = 50km/h
// LANDSTRASSE = 100km/h
// AUTOBAHN = keine Begrenzung
enum Tempolimit {
	INNERORTS,
	LANDSTRASSE,
	AUTOBAHN,
};

#endif
