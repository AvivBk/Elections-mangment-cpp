#include "ElectionsLoader.h"

#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

namespace elc {
	Elections* ElectionsLoader::load(istream& in)
	{
		ELECTIONS type;
		in.read(rcastc(&type), sizeof(type));

		switch (type)
		{
		case ELECTIONS::REGULAR:
			try {
				return new ElectionsReg(in);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		case ELECTIONS::SIMPLE:
			try {
				return new ElectionsSimple(in);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
	}
	void ElectionsLoader::save(Elections* e,ostream& out)
	{
		ELECTIONS type;
		ElectionsReg* r = dynamic_cast<ElectionsReg*>(e);
		if (r != nullptr) {
			type = ELECTIONS::REGULAR;
			out.write(rcastcc(&type), sizeof(type));
			r->save(out);
		}
		else {
			ElectionsSimple* r = dynamic_cast<ElectionsSimple*>(e);
			type = ELECTIONS::SIMPLE;
			out.write(rcastcc(&type), sizeof(type));
			r->save(out);
		}
	}
}
