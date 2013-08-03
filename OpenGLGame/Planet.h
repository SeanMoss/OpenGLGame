/*
 * This class is for planets. Actual, real size planets.
 * Includes: size, bounding sphere (surface and upper atmo), type
*/
#ifndef _PLANET_H_
#define _PLANET_H_

#include "SpaceObject.h"

enum PlanetType
{
	DESERT,
	DESERT_POPULATED,
	OCEAN,
	OCEAN_POPULATED,
	TERRAN,
	TERRAN_POPULATED,
	BARREN,
	BARREN_POPULATED
};

class Planet : public SpaceObject
{
private:
	PlanetType type;
};

#endif