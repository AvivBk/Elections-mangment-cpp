#pragma once

#include "District.h"

/*
*Implementation of Divided District
*This class manage Divided District informations
*This class inherited from District class
*/

namespace elc {

	class DividedDistrict : public District
	{
	public:
		/*DividedDistrict Constructor
		@param name , serial , representative number , party length , votes 
		*@return DividedDistrict new object
		*/
		DividedDistrict(string name, int serial, int repnum, int partyLen, int votes);
		/*DividedDistrict copy Constructor
		*@param other Divided District 
		@return DividedDistrict new object
		*/
		DividedDistrict(const DividedDistrict& d);
		/*DividedDistrict copy Constructor
		*@param other District
		@return DividedDistrict new object
		*/
		DividedDistrict(const District& d);
		/*DividedDistrict Constructor
		*@param input file 
		@return DividedDistrict new object
		*/
		DividedDistrict(istream& in);
		/* DividedDistrict Destructor
		*  This method manage to delete allocated memory and delete the object
		*/
		virtual ~DividedDistrict();
		//Printing District Type 
		void districtType();
		
		//This method load Divided District data to input file
		virtual void load(istream& in);
		//This method save Divided District data to output file
		virtual void save(ostream& out) const;

        virtual ostream& print(ostream& os) const override;
	};

}