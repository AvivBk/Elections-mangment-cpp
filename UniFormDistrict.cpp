#include "UniFormDistrict.h"

namespace elc {
	UniFormDistrict::UniFormDistrict(string name, int serial, int repnum, int partyLen, int votes)
		:District(name, serial, repnum , partyLen, votes)
	{
	}
	UniFormDistrict::UniFormDistrict(const UniFormDistrict& d) : District(d)
	{
	}
	UniFormDistrict::UniFormDistrict(const District& d) : District(d)
	{
	}
	UniFormDistrict::UniFormDistrict(istream& in) : District(in)
	{
	}

	UniFormDistrict::~UniFormDistrict()
	{
	}

	void UniFormDistrict::districtType() {
		std::cout << "| District type : Uniform" << endl;
	}

	void UniFormDistrict::load(istream& in)
	{
		District::load(in);
	}
	void UniFormDistrict::save(ostream& out) const
	{
		District::save(out);
	}

    ostream& UniFormDistrict::print(ostream& os) const
    {
        District::print(os) ;
        os << "\t Type: United" << endl;
        return os;
    }

}