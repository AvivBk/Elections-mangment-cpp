#pragma once
#include "CitizenList.h"
#include "DistrictList.h"
#include "PartyList.h"
#include "Date.h"
/*
*Implementation of 	class Elections
*This class manage information of Elections that used to allocate DynamicArray
*@param private : cList ( Citizen list ) , dList ( district list ) , pList ( Political party list ) , date ( Elections date)
*/
namespace elc
{
    class Elections
    {
    protected:
        Date*           date =nullptr;
        DistrictList*   dList;
        CitizenList*	cList;
        PartyList*		pList;

    public:
        /*Elections Constructor
        *@return Elections new object
        */
        Elections();
        /*Elections Serialize Constructor
        */
        Elections(istream& in);
        /*Elections destructor
        * This method manage to delete allocated memory and delete the object
        */
        virtual ~Elections();
        //-----------------------------Getters---------------------------//
        CitizenList*    getCList(void) const { return cList; }
        DistrictList*   getDList(void) const { return dList; }
        PartyList*      getPList(void) const { return pList; }
        Date*           getDate (void) const { return date ; }
        //---------------------------------------------------------------//
        /*Method calculate and printing the result of the elections
        *@Pure Abstract Function, Mandatory Implementaion for children
        */
		virtual bool VoteResults(void) = 0;
        /*Method checks if the elections ready to start
        *@retrun boolean as answer
        */
        bool checkValidility()const;
        /*Method links between citizen to distrcits
        *@After Loading from file.
        */
        void linkCitizensToDistricts(void);
        /*Method links between Representative Citizens to their parties
        *@After Loading from file.
        */
        void linkRepToParty(void);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		  //This method save Elections data to output file
          virtual void load(istream& in);
		  //This method save Elections data to input file
          virtual void save(ostream& out) const;
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    };
}

