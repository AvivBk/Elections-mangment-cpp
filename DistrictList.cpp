#include "DistrictList.h"

namespace elc {
    DistrictList::DistrictList()
    {
    }

	DistrictList::DistrictList(const DistrictList& other)
	{
		list = other.list;
	}

    DistrictList::~DistrictList()
    {
        list.clear();
    }

    bool DistrictList::addDistrict(const District& district,int type, bool allocated)
    {
        const char* n = district.getName().c_str();
		if (findDistrictByName(n)) {
			throw invalid_argument(" Already taken");
		}
		District *d = nullptr;

        if(!allocated){
			try{
				if (type == 1) {
					d = new UniFormDistrict(district);
				}
				else {
					d = new DividedDistrict(district);
				}
			}
			catch (bad_alloc& ex) {
				cout << ex.what();
				exit(0);
			}
            list.push_back(d);
        }
        else{
            list.push_back(const_cast<District*>(&district));
        }
        return true;
    }

    District& DistrictList::getDistrictByID(int id) const
    {
        for(District* d : list)
            if(d->getSerial() == id)
                return *d;
        throw invalid_argument("BAD");
    }
    void DistrictList::printList(void) const
    {
        cout << "-------------------------------------------------------------------" << endl;

        for(District* d : list){
            cout << *d;
            cout << "-------------------------------------------------------------------" << endl;
        }
    }
    bool DistrictList::addPartyToAllDistricts(void)
    {
        for(District* d : list)
            d->addParty();

        return true;
    }
    int DistrictList::totalRepresents(void) const {
        int sum = 0;

        for(District* d : list)
            sum += d->getRepNum();

        return sum;
    }
    const int  DistrictList::getTotalVotes(void) const
    {
        int sum = 0;

        for(District* d : list)
            sum += d->getVotes();

        return sum;
    }
    void DistrictList::save(ostream& out) const
    {
        int len = list.size();
        out.write(rcastcc(&len), sizeof(len));

        for(District* d : list)
            DistrictLoader::save(d, out);
    }
    void DistrictList::load(istream& in)
    {
        int len = 0;
        in.read(rcastc(&len), sizeof(len));
        for (int i = 0; i < len; i++) {
            District* d = DistrictLoader::load(in);
            if(dynamic_cast<UniFormDistrict*>(d))
                addDistrict(*d, 1);
            else
                addDistrict(*d, 0);
        }
    }


	bool DistrictList::findDistrictByName(const char* name) const
	{
        for (District* d : list)
            if (d->getName() == name)
                return true;

        return false;
	}

    const DistrictList& DistrictList::operator=(const DistrictList& other)
    {
        if(this != &other)
            list = other.list;

        return *this;
    }
}