#include "DividedDistrict.h"

namespace elc {

	DividedDistrict::DividedDistrict(string name, int serial, int repnum, int partyLen, int votes)
		: District(name, serial, repnum, partyLen, votes)
	{
	}	
	DividedDistrict::DividedDistrict(const DividedDistrict& d) : District(d)
	{
	}
	DividedDistrict::DividedDistrict(const District& d) : District(d)
	{
	}
	DividedDistrict::DividedDistrict(istream& in) : District(in)
	{
	}
	DividedDistrict::~DividedDistrict()
	{
	}

	void DividedDistrict::districtType() {
		std::cout << "| District type : Divided" << std::endl;
	}
	void DividedDistrict::load(istream& in)
	{
		District::load(in);
	}
	void DividedDistrict::save(ostream& out) const
	{
		District::save(out);
	}

	ostream& DividedDistrict::print(ostream& os) const
    {
	    District::print(os) ;
	    os << "\t Type: Divided" << endl;
	    return os;
    }

}