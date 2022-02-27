#include "Citizen.h"
#include "District.h"

namespace elc {
	Citizen::Citizen(string name, District* district, int id, int bday, int districtid)
			: _name(name), _District(district), _ID(id), _BDay(bday), _DistrictID(districtid)
	{
		try {
			if (to_string(id).length() != 9) {
                _name.clear();
				throw invalid_argument("  Invalid ID input");
			}
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
	}

    Citizen::Citizen(const Citizen& c) :
		Citizen(c.getName(), c.Citizen::getDistrict(), c.getID(), c.getDate(), c.getDistrictID())
    {
    }
	Citizen::Citizen(istream& in) : Citizen("", nullptr, 999999999, 0, 0)
	{
		load(in);
	}

    Citizen::~Citizen()
    {
    }

	const Citizen& Citizen::operator=(const Citizen& other)
	{
		if (this != &other)
		{
			_name = other.getName();
			_District = other.getDistrict();
			_ID = other.getID();
			_BDay = other.getDate();
			_Voted = other.getVoted();
		}
		return *this;
	}

    bool Citizen::operator==(const Citizen& c) const
    {
        return (this->getID() == c.getID());
    }

    ostream& Citizen::print(ostream& os) const
    {
        os  << "\t   ID:" << this->getID() << endl;
        os  << "\t   Name: " << this->getName() << endl;
        os  << "\t   Birth Year: " << this->getDate() << endl;
        os  << "\t   District : " << this->getDistrict()->getName() << endl;
        os  << "\t   Not Representative" << endl;
        return os;
    }


	void Citizen::load(istream& in)
	{
        int len;

        in.read(rcastc(&len), sizeof(len));
		char* c;
		try{
			c = new char[len + 1];
		}catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
		in.read(rcastc(c), len);
		c[len] = '\0';
		_name = c;
		delete c;
		in.read(rcastc(&_DistrictID), sizeof(_DistrictID));
		in.read(rcastc(&_ID), sizeof(_ID));
		in.read(rcastc(&_BDay), sizeof(_BDay));
		in.read(rcastc(&_Voted), sizeof(_Voted));
	}

	void Citizen::save(ostream& out) const
	{
        int len = _name.size();
        out.write(rcastcc(&len), sizeof(len));
		const char* c = _name.c_str();
		out.write(rcastcc(c), len);
		out.write(rcastcc(&_DistrictID), sizeof(_DistrictID));
		out.write(rcastcc(&_ID), sizeof(_ID));
		out.write(rcastcc(&_BDay), sizeof(_BDay));
		out.write(rcastcc(&_Voted), sizeof(_Voted));
	}

}
