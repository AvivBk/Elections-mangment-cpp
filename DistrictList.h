#pragma once
#include "DistrictLoader.h"
#include <iterator>
#include <list>

/*
*Implementation of DistrictList
*This class manage DistrictList informations
*@param private : _len ( District list length) , _head ( Pointer to district list head) , _tail ( pointer to district list tail )
*/

namespace elc
{
    class DistrictList {
    private:
        std::list<District*> list;

    public:
        /*DistrictList Constructor
        *@return DistrictList new object
        */
        DistrictList();
		/*Copy Constructor 
		*@return DistrictList new object
		*/
		DistrictList(const DistrictList&);
        /*DistrictList destructor
        * This method manage to delete allocated memory and delete the object
        */
        ~DistrictList();
        /*Gets District by given id
        *@param id
        *@return District
        */
        District& getDistrictByID(int id) const;
        /*Gets list length
        *@return list length
        */
        int getLen(void) const { return list.size(); }
        /*Gets total votes
        *@return total votes
        */
        const int getTotalVotes(void) const;
        //This method add district to list
        bool addDistrict(const District&,int type, bool allocated = false);
        //This method add party to all district in list
        bool addPartyToAllDistricts(void);
        /*This method find District by given name
        *@param name
        *@return index of asked district
        */
        bool findDistrictByName(const char* name) const;
        //This method return the amount for total Representatives
        int totalRepresents(void) const;
        //This method printing districts list
        void printList(void) const;
		//This method save District List data to output file
        void save(ostream& out) const;
		//This method load District List data to input file
        void load(istream& in);

        const DistrictList& operator=(const DistrictList& other);

        std::list<District*>& getList(void) { return list; }
    };

}


