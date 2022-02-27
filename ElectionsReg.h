#pragma once
#include "Elections.h"

/*
*Implementation of Regular elections
*This class manage Regular elections informations
*This class inherited from Elections class
*/
namespace elc {
	class ElectionsReg : public Elections
	{
	public:
		/*ElectionsReg Constructor
		*@return ElectionsReg new object
		*/
		ElectionsReg();
		/*ElectionsReg Constructor from file input
		*@return ElectionsReg new object
		*/
		ElectionsReg(istream& in);
		/*ElectionsSimple destructor
		* This method manage to delete allocated memory and delete the object
		*/
		virtual ~ElectionsReg();
	
		/*Method calculate and printing the result of the elections
		*@Function inheritated
		*/
		virtual bool VoteResults(void);

		/*Loading data from input file
		@param input file with elections data
		*/
		virtual void load(istream& in);
		/*Saving data to output file
		@param output file with elections data
		*/
		virtual void save(ostream& out) const;

	};
}