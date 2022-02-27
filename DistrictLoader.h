#pragma once
#include "UniFormDistrict.h"
#include "DividedDistrict.h"

/*
*Implementation of DistrictLoader
*This class manage Distrcit loader informations
*/

namespace elc {
	enum class DISTRICT {
		UNIFORM,
		DEVIDED
	};
	class DistrictLoader
	{
	public:
		static District* load(istream& in);
		static void save(District* c, ostream& out);
	};
}


