#include "CitizenList.h"
#include "District.h"
#include "Party.h"
#include <typeinfo>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace elc {
    CitizenList::CitizenList()
    {
    }

	CitizenList::CitizenList(const CitizenList& other)
	{
		list = other.list;
	}
    CitizenList::~CitizenList()
    {
        list.clear();
    }

    bool CitizenList::addCitizen(const Citizen& citizen, bool allocated)
    {
        try{
            getCitizenByID(citizen.getID());
            cout << "Citizen Already Exist" << endl;
            return false;
        }
        catch(invalid_argument& ex) {
            if (!allocated) {
                Citizen *c = nullptr;
                const Representative *rep = dynamic_cast<const Representative *>(&citizen);
                try {
                    if (rep != nullptr)
                        c = new Representative(citizen, rep->getParty(), rep->getDistrict());
                    else
                        c = new Citizen(citizen);
                }
                catch (bad_alloc &ex) {
                    cout << ex.what() << endl;
                    exit(1);
                }
                list.push_back(c);
            } else {
                list.push_back(const_cast<Citizen *>(&citizen));
            }
            return true;
        }
    }

    bool CitizenList::removeCitizen(const Citizen& citizen)
    {
        for(auto itr = list.begin(); itr != list.end(); ++itr) {
            if (**itr == citizen)
            {
                list.erase(itr);
                return true;
            }
        }
        return false;
    }

    //-------------------------Getters---------------------------------//

    Citizen& CitizenList::getCitizenByID(int id) const
    {
        for(Citizen* c : list){
            if (c->getID() == id)
                return *c;
        }
		throw invalid_argument("* Couldn't find the Citizen");
    }
    int CitizenList::getNum_Of_People_In_District(int district) const
    {
        int counter = 0;
        for(Citizen* c : list)
            if (c->getDistrictID() == district)
                counter++;

        return counter;
    }

    //-----------------------------------------------------------------//
	Citizen* CitizenList::makeCitizenRep(Representative& r)
	{
		Citizen* c;
		try{
			c = new Representative(r);
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
        for(auto itr = list.begin(); itr != list.end(); ++itr) {
            if (**itr == *c)
            {
                itr = list.erase(itr);
                list.insert(itr, c);
                return c;
            }
        }

        return nullptr;
	}

    void CitizenList::printList(void) const
    {
        int i = 1;
        cout << " --------------------------------------- " << endl;
        for(Citizen* c : list){
            cout << i++ << "." << *c << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    void CitizenList::printList(int num, int districtID) const
    {
        int i = 0;
        for(Citizen* c : list){
            cout << i++ << "." << *c << endl;
            cout << "----------------------------------------" << endl;
            --num;
            if(num == 1)
                break;
        }
    }	

    void CitizenList::save(ostream& out) const
    {
        int len = list.size();
        out.write(rcastcc(&len), sizeof(len));
        for (Citizen* c : list)
            CitizenLoader::save(c, out);
    }

    void CitizenList::load(istream& in)
    {
        int len = 0;
        in.read(rcastc(&len), sizeof(len));
        for (int i = 0; i < len; i++) {
			Citizen* c;
			try {
				c = CitizenLoader::load(in);
			}
			catch (invalid_argument& ex ){
				throw invalid_argument("Invalid Citizen data");
			}
           addCitizen(*c, true);
        }
    }

    void CitizenList::LinkDistrictByID(District* d)
    {
        for(Citizen* c : list){
            if(c->Citizen::getDistrictID() == d->getSerial()){
                c->Citizen::setDistrict(d);
                if(typeid(*c) == typeid(Representative))
                    c->setDistrict(d);
                d->addCitizen(*c, true);
            }
        }
    }

    void CitizenList::LinkPartyByID(Party *p)
    {
        for(Citizen* c : list){
            if(typeid(*c) == typeid(Representative))
            {
                Representative* r = dynamic_cast<Representative*>(c);
                if(r->getPartyID() == p->getSerial()){
                    r->setParty(p);
                    p->addCitizen(*r, true);
                }
            }
        }
    }

    const CitizenList& CitizenList::operator=(const CitizenList& other)
    {
        if(this != &other){
            list = other.list;
        }
        return *this;
    }

}