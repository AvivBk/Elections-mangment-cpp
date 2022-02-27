#include "District.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elc {
    District::District(string name, int serial, int repnum, int partyLen, int votes)
            : _name(name), _Serial(serial), _RepNum(repnum), _votes(votes) {
        try {
            _list = new CitizenList();
            _partyArr = new DynamicArray<int>();
        }
        catch (bad_alloc &ex) {
            cout << ex.what() << endl;
            exit(1);
        }
    }

    District::District(const District &d) : District(d.getName(), d.getSerial(), d.getRepNum(), d._partyArr->size(),
                                                     d.getVotes()) {
        _partyArr = d._partyArr;
    }

    District::District(istream &in) : District("", 0, 0, 0, 0) {
        load(in);
    }

    District::~District() {
    }

    bool District::addCount(Citizen &c, int party) {
        if (c.getVoted())
            return false;

        c.setVoted(true);
        ++_votes;
        _partyArr->byIndex(party)++;
    }

    float District::getPercentageVotes(void) const {
        return (((float) _votes / _list->getLength()) * 100);
    }

    int District::getSumOfVotes(void) const {
        int sum = 0;
        for (auto itr = _partyArr->begin(); itr != _partyArr->end(); ++itr)
            sum += *itr;
        return sum;
    }

    void District::load(istream &in) {
        int len;

        in.read(rcastc(&len), sizeof(len));
        char *c = new char[len + 1];
        in.read(rcastc(c), len);
        c[len] = '\0';
        _name = c;
        delete c;

        in.read(rcastc(&len), sizeof(len));
        for (int i = 0; i < len; i++) {
            int temp;
            in.read(rcastc(&temp), sizeof(temp));
            _partyArr->push_back(temp);
        }


        in.read(rcastc(&_Serial), sizeof(_Serial));
        in.read(rcastc(&_RepNum), sizeof(_RepNum));
        in.read(rcastc(&_votes), sizeof(_votes));
    }

    void District::save(ostream &out) const {
        int len = _name.size();
        out.write(rcastcc(&len), sizeof(len));
        const char *c = _name.c_str();
        out.write(rcastcc(c), len);

        len = _partyArr->size();
        out.write(rcastcc(&len), sizeof(len));
        for (auto itr = _partyArr->begin(); itr != _partyArr->end(); ++itr) {
            int temp = *itr;
            out.write(rcastcc(&temp), sizeof(temp));
        }
        out.write(rcastcc(&_Serial), sizeof(_Serial));
        out.write(rcastcc(&_RepNum), sizeof(_RepNum));
        out.write(rcastcc(&_votes), sizeof(_votes));
    }

    ostream& District::print(ostream &os) const {
        os << " Serial: " << getSerial() << "\t Name: " << getName() << "\t Rep: " << getRepNum();
        return os;
    }
}