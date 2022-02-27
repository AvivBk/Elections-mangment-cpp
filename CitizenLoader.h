#pragma once
#include "Representative.h"

/*
*Implementation of CitizenLoader
*This class manage Citizen loader informations
*/

namespace elc {
	enum class CITIZEN {
		Regular,
		Representative
	};
	class CitizenLoader
	{
	public:
		static Citizen* load(istream& in);
		static void save(Citizen* c, ostream& out);
	};
}

