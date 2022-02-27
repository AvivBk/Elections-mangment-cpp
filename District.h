#pragma once
#include "DynamicArray.h"
#include "StringBuffer.h"
#include "CitizenList.h"
#include <string>
/*
*Implementation of abstract class District
*This class manage information of District
*@param private : _name ( disctrict's name ) , _list ( Citizen in current district) , _partyArr ( Politicals Party array )
*@param private : _serial ( Serial ID ) , _RepNum ( amount of Representative ) , _votes ( amount of votes )
*/
namespace elc {
    class Citizen;
    class District {
    protected:
        string                  _name;
        CitizenList*            _list;
        DynamicArray<int>*      _partyArr;
        int                     _Serial;
        int                     _RepNum;
        int				        _votes = 0;

    public:
        /*District's Constructors
        *@param name , serial , repnum , partyLen
        *@returns the new District object
        */
        District(string name, int serial, int repnum, int partyLen, int votes);
        /*District's copy Constructor
        *@param other (District object)
        *@returns the new District object
        */
        District(const District&);
        /*District's Serialize Constructor
        *@param other (District object)
        *@returns the new District object
        */
        District(istream& in);
        /*District Destructor
        * This method manage to delete allocated memory and delete the object
        */
        virtual ~District();
		//------------------------------------Getters-------------------------------------//
        DynamicArray<int>::iterator getParty(void) const { return _partyArr->begin(); }
        string          getName             (void) const { return _name;  }
        const int       getSerial           (void) const { return _Serial; }
        const int       getRepNum           (void) const { return _RepNum; }
        const int       getVotes            (void) const { return _votes;  }
        int             getPartyArrLen      (void) const { return _partyArr->size(); }
        float           getPercentageVotes  (void) const;
        int             getSumOfVotes       (void) const;
		//---------------------------------------------------------------------------------//
        //This method Printing District's citizens list
        void printVaildList(void) const { _list->printList(); }
        //This method remove citizen from district's citizens list
        void removeCitizen(const Citizen& c) { _list->removeCitizen(c); }
        //This method add citizen to district's citizens list
        void addCitizen(const Citizen& c, bool allocated = false) { _list->addCitizen(c, allocated); }
        //This method addes vote of citizen
        bool addCount(Citizen& c, int party);
        /*This method add party to political party array
        *@return true for succees insert
        */
        bool addParty(void) { _partyArr->push_back(0); return true; }
		//Printing operator
		virtual void districtType() = 0;
        virtual void load(istream& in);
        virtual void save(ostream& out) const;

        friend ostream& operator<<(ostream& os, const District& d) {
            return d.print(os);
        }

        virtual ostream& print(ostream& os) const;
    };
}

