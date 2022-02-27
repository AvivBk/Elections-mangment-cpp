#pragma once
#include "StringBuffer.h"
#include <string>
/*
*Implementation of Citizen
*This class manage Citizen informations
*@param private : _name ( Citizen's name ) , _rep ( Citizen's Representative informations )
*@param private : _District ( Pointer to District relevant ) , _ID (Citizen's ID ) , _BDay( Citizen's Birthday ) , _vote ( vote status )
*/
namespace elc
{
    class District;
    class Citizen
    {
    protected:
        string      	_name;
        District*		_District;
        int				_ID;
        int				_BDay;
        bool			_Voted = false;
    private:
        int             _DistrictID;
    public:
        //-------------------------------------- Constructors --------------------------------------//
        /*Citizen's Constructor
        *@parma name , rep , district, id , bday
        *@return New Citizen's object
        */
        Citizen(string name, District* district, int id, int bday, int districtid);
        /*Citizen's copy Constructor
        *@param other Citizen
        @return new Citizen Object
        */
        Citizen(const Citizen&);
        /*Serialization Citizen
        *@param istream
        *@return new Citizen Object
        */
        Citizen(istream& in);
        /*Citizen's Destructor
        *This method manage to delete Citizen object
        */
        virtual ~Citizen();
        /*Gets Citizen's name
        *@return the citizen's name
        */
        //-------------------------------------------------------------------------------------------//
        //----------------------------------------- Getters -----------------------------------------//
        virtual string getName(void) const { return _name; }
        /*Gets Citizen's ID
        *@return the citizen's ID
        */
        virtual int getID(void) const { return _ID; }
        /*Gets Citizen's Birthday
        *@return the citizen's Birthday
        */
        int getDate(void) const { return _BDay; }
        /*Gets Citizen's district
        *@return the citizen's District
        */
        virtual District* getDistrict(void) const { return _District; }
        /*Gets Citizen's vote status
        *@return the citizen's vote status
        */
        bool getVoted(void) const { return _Voted; }
        /*Set citizen's vote status
        *@param bool(b)
        *@return The citizen's new status
        */
        bool setVoted(bool b) { _Voted = b; return true; }

        int getDistrictID(void) const { return _DistrictID; }
        //-------------------------------------------------------------------------------------------//
        //----------------------------------------- Setters -----------------------------------------//
        /*Set citizen's district
        *@param District(d)
        */
        virtual void setDistrict(District* d) { _District = d; }
        //-------------------------------------------------------------------------------------------//
		//---------------------------------------- Operators ----------------------------------------//
		//Printing operator
        friend ostream& operator<<(ostream& os, const Citizen& c) {
            return c.print(os);
        }

        virtual ostream& print(ostream& os) const;
		//Operator=
		const Citizen& operator=(const Citizen&);

        //Operator==
        bool operator==(const Citizen& c) const;

        //-------------------------------------------------------------------------------------------//

        virtual void load(istream& in);
        virtual void save(ostream& out) const;
    };

}

