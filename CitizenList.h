#pragma once
#include <list>
#include <iterator>
#include "CitizenLoader.h"

/*
*Implementation of CitizenList
*This class manage CitizenList informations
*@param private : STL list field.
*/

namespace elc {
    class CitizenList {
    private:
        std::list<Citizen*> list;

    public:
        /*CitizenList Constructor
        *@return CitizenList new object
        */
        CitizenList();
		/*CitizenList copy Constructor
		*@return CitizenList new object
		*/
		CitizenList(const CitizenList&);
		/*CitizenList destructor
        * This method manage to delete allocated memory and delete the object
        */
        ~CitizenList();
        /*Gets List length
        *@return the list length
        */
        int getLength(void) const { return list.size(); }
        /*Gets citizen by given ID
        *@return citizen
        */
        Citizen& getCitizenByID(int id) const;
        /*Method for calcultaing the number of citizens in list that restricted to certain district
        *@Returns The number of citizens restriced to district
        */
        int getNum_Of_People_In_District(int district) const;
        /*Method Linking All Citizens to their District after reading from file
        */
        void LinkDistrictByID(District* d);
        /*Method Linking All Citizens to their Party after reading from file
        */
        void LinkPartyByID(Party* p);
        /*This method Add mew citizen to citizens list
        *@param citizen
        *@return bool value for insert status
        */
        bool addCitizen(const Citizen&, bool allocated = false);
        /*This method remove citizen from citizens list
        *@param citizen
        *@return bool value for remove status
        */
        bool removeCitizen(const Citizen&);

        std::list<Citizen*>& getList(void) { return list; }

		//This method makes citizen as representative
		Citizen* makeCitizenRep(Representative& r);
        /*Printing citizen list without exeptions
        @return void
        */
        void printList(void) const;
        /*Printing an inserted amount of citizen From Certain District
        @return void
        */
        void printList(int num, int districtID) const;

        const CitizenList& operator=(const CitizenList& other);

		//This method save Citizen List data to output file
        void save(ostream& out) const;
		//This method load Citizen List data to input file
        void load(istream& in);
    };
}


