#pragma once
#include "CitizenList.h"
#include <string>
/*
*Implementation of Party
*This class manage information of Party
*@param private : _name ( Party's name ) , _list ( Citizen in current Party) ,
*@param private : _Leader ( Party's leader ) , _Serial ( Party's ID )
*/
namespace elc {
    class Party
    {
    protected:
        string          _name;
        int             _Serial;
        Citizen*        _Leader;
        CitizenList*    _list;
    
    private:
        int             _LeaderID;
    public:
        //---------------------------------CTor & Dtor--------------------------------------------//
        /*Party's Constructor
        *@param name , serial , leader
        *@returns the new Party object
        */
        Party(string name, int serial, Citizen* leader);
        /*Party's copy Constructor
        *@param other (Party object)
        *@returns the new Party object
        */
        Party(const Party&);
        /*Party's Serialize Constructor
        *@param istream object
        *@returns the new Party object
        */
        Party(istream& in);
        /*Party Destructor
        * This method manage to delete allocated memory and delete the object
        */
        ~Party();
        //---------------------------------------------------------------------------------------//
        //------------------------------------Getters--------------------------------------------//
        const int   getPartyLen (void) const { return _list->getLength(); }
        string      getName     (void) const { return _name; }
        const int   getSerial   (void) const { return _Serial; }
        Citizen*    getLeader   (void) const { return _Leader; }
        int         getLeaderID (void) const { return _LeaderID; }
        int         getNumberOfRepFromDistrict(int districtID) const{ return _list->getNum_Of_People_In_District(districtID); }
        //---------------------------------------------------------------------------------------//
        //------------------------------------Setters--------------------------------------------//
        void        setLeader   (Citizen* c)    { _Leader = c; }
        void        setLeaderID (int id)        { _LeaderID = id; }
        //---------------------------------------------------------------------------------------//
        //Printing Party List of People.
        void        printVaildList(void) const  { _list->printList(); }
        //Printing The Winners
        void        printWinners(int num, int districtID) const    { _list->printList(num, districtID); }
        //This method add citizen to political party list
        void        addCitizen(const Citizen& c, bool allocated = false) { _list->addCitizen(c, allocated); }
		//This method removes citizen from the political party list
		void        removeCitizen(const Citizen& c) { _list->removeCitizen(c); }
		//Prining operator
        friend ostream& operator<<(ostream& os, const Party& p)
        {
            os << "ID: " << p.getSerial();
            os << "\t Name: " << p.getName();
            os << "\t Leader: " << p.getLeader()->getName() << endl;

            return os;
        }
		//This method load Divided Party data to input file
        virtual void load(istream& in);
		//This method save Divided Party data to output file
        virtual void save(ostream& out) const;

    };


}

