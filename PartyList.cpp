#include "PartyList.h"

namespace elc {
    PartyList::PartyList()
    {
    }

	PartyList::PartyList(const PartyList& other)
	{
		list = other.list;
	}
    PartyList::~PartyList()
    {
        list.clear();
    }
    bool PartyList::addParty(const Party& party, bool allocated)
    {
        if (!allocated) {
			try{
				Party* p = new Party(party);
				p->setLeaderID(party.getLeaderID());
				list.push_back(p);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
        }
        else {
            list.push_back(const_cast<Party*>(&party));
        }
        return true;
    }
    Party& PartyList::getPartyByID(int id) const
    {
        for(Party* p : list)
            if (p->getSerial() == id)
                return *p;

        throw invalid_argument("Couldn't find party");
    }
    void PartyList::printList(void) const
    {
        cout << " --------------------------------------- " << endl;

        for(Party* p : list){
            cout << *p;
            p->printVaildList();
        }
    }

    bool PartyList::enoughRepresents(int amount, int districtID)const {
        for(Party* p : list)
            if(p->getNumberOfRepFromDistrict(districtID) < amount)
                return false;

        return true;
    }

    void PartyList::save(ostream& out) const
    {
        int len = list.size();
        out.write(rcastcc(&len), sizeof(len));
        for(Party* p : list)
            p->save(out);

    }
    void PartyList::load(istream& in)
    {
        int len = 0;
        in.read(rcastc(&len), sizeof(len));
        for (int i = 0; i < len; i++) {
            Party p(in);
            addParty(p);
        }
    }

    const PartyList& PartyList::operator=(const PartyList& other)
    {
        if(this != &other)
            list = other.list;
        return *this;
    }
}