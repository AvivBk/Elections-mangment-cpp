#include "ElectionsSimple.h"

namespace elc {
	ElectionsSimple::ElectionsSimple()
	{	
	}

    ElectionsSimple::ElectionsSimple(istream& in) : Elections(in)
    {
    }

	ElectionsSimple::~ElectionsSimple()
	{
	}

    bool ElectionsSimple::VoteResults(void){
        cout << endl << "------------ Elections Simple -------------" << endl;
        cout << *getDate() << endl;

        return Elections::VoteResults();      
    }

    void ElectionsSimple::load(istream& in)
    {
        Elections::load(in);
    }
    void ElectionsSimple::save(ostream& out) const
    {
        Elections::save(out);
    }
}
