#pragma once
#include "Elections.h"

/*
*Implementation of ElectionsSimple
*This class manage ElectionsSimple informations
*This class inherited from Elections class
*/

namespace elc {
	class ElectionsSimple : public Elections
	{
	public:
		/*ElectionsSimple Constructor
		*@return ElectionsSimple new object
		*/
		ElectionsSimple();
		/*ElectionsSimple Constructor from file input
		*@return ElectionsSimple new object
		*/
		ElectionsSimple(istream& in);
		/*ElectionsSimple destructor
		* This method manage to delete allocated memory and delete the object
		*/
		virtual ~ElectionsSimple();

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
