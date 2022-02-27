#include "DistrictLoader.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

namespace elc {
	District* DistrictLoader::load(istream& in) {
		DISTRICT type;
		in.read(rcastc(&type), sizeof(type));
		switch (type)
		{
		case DISTRICT::DEVIDED:
			try {
				return new DividedDistrict(in);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		case DISTRICT::UNIFORM:
			try{
				return new UniFormDistrict(in);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
	}
	void DistrictLoader::save(District* d, ostream& out)
	{
		DISTRICT type;
		DividedDistrict* r = dynamic_cast<DividedDistrict*>(d);
		if (r != nullptr) {
			type = DISTRICT::DEVIDED;
			out.write(rcastcc(&type), sizeof(type));
			r->save(out);
		}
		else {
			UniFormDistrict* r = dynamic_cast<UniFormDistrict*>(d);
			type = DISTRICT::UNIFORM;
			out.write(rcastcc(&type), sizeof(type));
			r->save(out);
		}
	}
}