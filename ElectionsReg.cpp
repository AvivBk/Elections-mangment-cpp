#include "ElectionsReg.h"


namespace elc {
    ElectionsReg::ElectionsReg()
    {
    }
    ElectionsReg::ElectionsReg(istream& in) : Elections(in)
    {
    }
	ElectionsReg::~ElectionsReg()
	{
	}

    bool ElectionsReg::VoteResults(void) {
        cout << endl << "---------- Regular Elections ------------" << endl;
        cout << *getDate() << endl;
        
        return Elections::VoteResults();
    }

    void ElectionsReg::load(istream& in)
    {
        Elections::load(in);
    }
    void ElectionsReg::save(ostream& out) const
    {
        Elections::save(out);
    }
}