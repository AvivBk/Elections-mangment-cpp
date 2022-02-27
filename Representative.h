#pragma once
/*
*Implementation of Representative
*This class manage information of Citizen that defined as a Representative
*@param private : _rep_id ( Representative ) , _party_id ( Political Party ID ) , _district ( District ID )
*/
#include "Citizen.h"
namespace elc {
    class Party;
    class District;
    class Representative : public Citizen {
    protected:
        Party*		_party;
        District*   _district;
    private:
        int         _partyID;
        int         _districtID;
    public:

        /*Constructor of Representative class
        *@param repid ,partyid , district
        *@return the new Representative object
        */
        Representative(const Citizen& c, Party* partyid, District* district);
        /*Copy Constructor of Representative class
        * using Constructor method
        *@param other
        *@return the new Representative object
        */
        Representative(const Representative&);
		/*Constructor of Representative class
		*@param input file (in ) 
		*@return the new Representative object
		*/
        Representative(istream& in);
        
		//--------------------Getters-------------------
		/*
        *Gets Political Party ID
        *@return the Political Party ID
        */
		virtual Party* getParty(void) const { return _party; }
        /*
        *Gets District ID
        *@return the District ID
		*@function overrides getDistrict from citizen
        */
		virtual District* getDistrict(void) const { return _district; }

		
		int getDistrictID(void) const { return _districtID; }
        int getPartyID(void) const { return _partyID; }
		
		//--------------------Setters-------------------
		//This method sets Distrcit ID 
		virtual void setParty(Party* p) { _party = p; }
        void setDistrictID(int id) { _districtID = id; }
		//This method sets Party ID 
        void setPartyID(int id) { _partyID = id; }
		// virtual method , setDistrict by following district input
        virtual void setDistrict(District* d) { _district = d; }

		const Representative& operator=(const Representative& other);

		bool operator==(const Representative& other){
		    return Citizen::operator==(other);
		}

		virtual ostream& print(ostream& os) const override;

		//This method save Representative data to output file
        virtual void save(ostream& out) const;
		//This method load Representative data to input file
        virtual void load(istream& in);
    };
}


