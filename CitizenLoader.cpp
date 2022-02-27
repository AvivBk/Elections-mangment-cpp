#include "CitizenLoader.h"
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

namespace elc {
	Citizen* CitizenLoader::load(istream& in)
	{
		CITIZEN type;
		in.read(rcastc(&type), sizeof(type));

		switch (type)
		{
		case CITIZEN::Regular:
			try {
				return new Citizen(in);
				break;
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		case CITIZEN::Representative:
		    int did, pid;
            in.read(reinterpret_cast<char*>(&did), sizeof(did));
            in.read(reinterpret_cast<char*>(&pid), sizeof(pid));
			try{
				Representative* rp = new Representative(in);
				rp->setDistrictID(did);
				rp->setPartyID(pid);
				return rp;
				break;
			}
			//catch (invalid_argument& ex) {
			//	throw invalid_argument(ex);
			//	cout << " --------------------------------------- " << endl;
			//	cout <<					ex.what()					<< endl;
			//	cout << " --------------------------------------- " << endl;
			//}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
	}

	void CitizenLoader::save(Citizen* c,ostream& out)
	{
		CITIZEN type;
		Representative* r = dynamic_cast<Representative*>(c);
		if (r == nullptr) {
			type = CITIZEN::Regular;
			out.write(rcastcc(&type), sizeof(type));
			c->save(out);
		}
		else {
			type = CITIZEN::Representative;
			out.write(rcastcc(&type), sizeof(type));
			r->save(out);
		}
	}
}