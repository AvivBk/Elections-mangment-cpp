#pragma once
#include "Party.h"
#include <iterator>
#include <list>

/*
*Implementation of PartyList
*This class manage CitizenList informations
*@param private : _len ( Party's list length) , _head ( Pointer to Party list head) , _tail ( pointer to Party list tail )
*/
namespace elc
{
    class PartyList {
    private:
        std::list<Party*> list;

    public:
        /*PartyList Constructor
        *@return PartyList new object
        */
        PartyList();
		/*PartyList copy Constructor
		*@return PartyList new object
		*/
		PartyList(const PartyList&);
        /*PartyList destructor
        * This method manage to delete allocated memory and delete the object
        */
        ~PartyList();
        /*Gets Politicals party list length
        *@return Politicals party list length
        */
        int getLen(void) const { return list.size(); }
        /*This method checks for minimum representatives
        *@param amount
        @return true for enought representatives  else false
        */
        bool enoughRepresents(int amount, int districtID)const;
        /*This method add given party to list
        *@param party object
        @return boolean value for success
        */
        bool addParty(const Party&, bool allocated = false);
		/*This method gets party by given ID
		*@Returns Party 
		*This method only been called after findPartyID Already called.
		*/
        Party& getPartyByID(int id) const;
		/*Printing the list 
		*/
        void printList(void) const;
		//This method save Party List data to output file
        void save(ostream& out) const;
		//This method load Party List data to input file
        void load(istream& in);

        const PartyList& operator=(const PartyList& other);

        std::list<Party*>& getList(void) { return list; }
    };
}


