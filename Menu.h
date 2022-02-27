#pragma once
#include "ElectionsLoader.h"
#include <string>
/*
*Implementation of Menu class
*This class manage menu informations
*@param private : e ( Elections ) , simpleElcFlag ( Simple election flag) , resFlag ( Result flag) , loadedFlag ( loaded flag)
*/

namespace elc {
	class Menu
	{
	private:
		Elections* e;
		bool simpleElcFlag;
		bool resFlag;
		bool loadedFlag;

	public:
		/*Menu Constructor
		*@param other ( election ) , loaded 
		*@return Menu new object
		*/
		Menu(Elections* other, bool loaded);
		/* Menu Destructor
		*  This method manage to delete allocated memory and delete the object
		*/
		~Menu();
        //This is the Management menu
		virtual void MainMenu(void);
		//This method set citizen as political party representative
		void MakeRepMenu(void);
		//This method create new citizen by given information
		void CitizenMenu(void);
		//This method create new district by given information
		virtual void DistirctMenu(void);
		//This method create new political party by given information
		void PartyMenu(void);
		//This method manage the votes
		void VoteMenu(void);
	};
}
