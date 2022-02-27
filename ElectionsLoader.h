#pragma once
#include "ElectionsReg.h"
#include "ElectionsSimple.h"

/*
*Implementation of ElectionsLoader
*This class manage Elections loader informations
*/


namespace elc {
	enum class ELECTIONS {
		REGULAR,
		SIMPLE
	};
	class ElectionsLoader
	{
	public:
		static Elections* load(istream& in);
		static void save(Elections* e, ostream& out);
	};
}


