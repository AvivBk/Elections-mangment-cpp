#include "Representative.h"
#include "District.h"
#include "Party.h"

namespace elc {
    Representative::Representative(const Citizen& c, Party* party, District * district)
		: Citizen(c), _party(party), _district(district)
    {
    }
    Representative::Representative(const Representative& rep) 
		: Citizen(rep), _party(rep.getParty()), _district(rep.getDistrict())
    {
        _districtID = rep.getDistrictID();
        _partyID = rep.getPartyID();
    }

	Representative::Representative(istream& in) : Citizen(in), _party(nullptr), _district(nullptr)
	{
	}

	const Representative& Representative::operator=(const Representative& other)
	{
		if (this != &other)
		{
			Citizen::operator=(other);
			_party = other.getParty();
			_district = other.getDistrict();
		}
		return *this;
	}

	void Representative::save(ostream& out) const
	{
        out.write(rcastcc(&_districtID), sizeof(_districtID));
        out.write(rcastcc(&_partyID), sizeof(_partyID));
		Citizen::save(out);
	}
	void Representative::load(istream& in)
	{
        in.read(rcastc(&_districtID), sizeof(_districtID));
        in.read(rcastc(&_partyID), sizeof(_partyID));
		Citizen::load(in);
	}

	ostream& Representative::print(ostream& os) const
    {
        os  << "\t   ID:" << Citizen::getID() << endl;
        os  << "\t   Name: " << Citizen::getName() << endl;
        os  << "\t   Birth Year: " << Citizen::getDate() << endl;
        os  << "\t   District : " << Citizen::getDistrict()->getName() << endl;
        os  << "\t   Representative: " << getParty()->getName() << endl;
        return os;
    }

}