#pragma once
#include "District.h"

/*
*Implementation of Divided District
*This class manage Divided District informations
*This class inherited from District class
*/

namespace elc {
	class UniFormDistrict : public District
	{
	public:
		/*UniFormDistrict Constructor
		@param name , serial , representative number , party length , votes
		*@return UniFormDistrict new object
		*/
		UniFormDistrict(string name, int serial, int repnum, int partyLen, int votes);
		/*UniFormDistrict copy Constructor
		*@param other Uniform District
		@return UniFormDistrict new object
		*/
		UniFormDistrict(const UniFormDistrict& d);
		/*UniFormDistrict copy Constructor
		*@param other  District
		@return UniFormDistrict new object
		*/
		UniFormDistrict(const District& d);
		/*UniFormDistrict  Constructor
		*@param input file
		@return UniFormDistrict new object
		*/
		UniFormDistrict(istream& in);
		/* DividedDistrict Destructor
		*  This method manage to delete allocated memory and delete the object
		*/
		virtual ~UniFormDistrict();
		//Printing District Type
		void districtType();

		//This method load UniFormDistrict data to input file
		virtual void load(istream& in);
		//This method save UniFormDistrict data to output file
		virtual void save(ostream& out) const;

        virtual ostream& print(ostream& os) const override;
	};

}