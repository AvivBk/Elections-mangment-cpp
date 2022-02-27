#include "Party.h"

namespace elc
{
    Party::Party(string name, int serial, Citizen* leader)
            : _name(name), _list(new CitizenList()), _Serial(serial), _Leader(leader)
    {
		try{
			_list = new CitizenList();
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
        if (leader)
            _LeaderID = leader->getID();
        else
            _LeaderID = 0;
    }
    Party::Party(const Party& p) : Party(p.getName(), p.getSerial(), p.getLeader())
    {
    }
    Party::Party(istream& in) : Party("", 0, nullptr) {
        load(in);
    }
    Party::~Party()
    {
    }

	void Party::load(istream& in)
	{
		int len;

		in.read(rcastc(&len), sizeof(len));
		char * c;
		try{
		    c = new char[len + 1];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
        in.read(rcastc(c), len);
        c[len] = '\0';
        _name = c;
        delete c;
        in.read(reinterpret_cast<char*>(&_Serial), sizeof(_Serial));
        in.read(reinterpret_cast<char*>(&_LeaderID), sizeof(_LeaderID));
    }
    void Party::save(ostream& out) const
    {
        int len = _name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        const char* c = _name.c_str();
        out.write(reinterpret_cast<const char*>(c), len);
        out.write(reinterpret_cast<const char*>(&_Serial), sizeof(_Serial));
        out.write(reinterpret_cast<const char*>(&_LeaderID), sizeof(_LeaderID));
    }
}