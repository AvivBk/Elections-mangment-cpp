#include "Menu.h"

namespace elc {

    class Print {
    public:
        template <class T>
        void operator()(const T& t) const {
            cout << t << endl;
        }
    };

    template <class T, class Func>
    void applyAll(T& ds, const Func& func)
    {
        int i = 1;
        cout << " --------------------------------------- " << endl;
        for (auto itr = ds.begin(); itr != ds.end(); ++itr) {
                cout << i++ << ". ";
                func(**itr);
                cout << "----------------------------------------" << endl;
            }
    }

	enum class MENU {
		DISTRICT = 1,
		CITIZEN,
		PARTY,
		MAKEREP,
		PRINTC,
		PRINTP,
		PRINTD,
		VOTE,
		RESULTS,
		EXIT
	};

    Menu::Menu(Elections* other, bool loaded) : e(other), simpleElcFlag(false), resFlag(false), loadedFlag(loaded)
    {
        ElectionsSimple* ptr = dynamic_cast<ElectionsSimple*>(e);
        if (!loaded) {
            if (ptr) {
                while (true) {
                    cout << " ---------------------------------------- " << endl;
                    cout << " - Please Enter amount of Represenative -" << endl;
                    cout << " ---------------------------------------- " << endl;
                    int rep;
                    cin >> rep;

                    if (rep < 1)
                        cout << " ---- NonPositive Number Recored, please try again ----" << endl;
                    else {
                        e->getDList()->addDistrict(DividedDistrict("A", 1, rep, e->getPList()->getLen(), 0), 0);
                        simpleElcFlag = true;
                        break;
                    }
                }
            }
        }
        else {
            cout << " ---------------------------------------- " << endl;
            cout << " -  Elections have Loaded Successfully  - " << endl;
            cout << "     Day:  " << e->getDate()->getDay() << "  Month:  " << e->getDate()->getMonth()
                << "  Year:  " << e->getDate()->getYear() << "    " << endl;;
            cout << " ---------------------------------------- " << endl;
            if (ptr)
                simpleElcFlag = true;
        }
        MainMenu();
    }
    Menu::~Menu() {
        delete e;
    }

	void Menu::MainMenu(void)
	{
        if (loadedFlag == false) {
            while(true)
            {
                int day, month, year;
                cout << " --------------------------------------- " << endl;
                cout << " -        Enter Date (dd/mm/yy)        -" << endl;
                cout << " --------------------------------------- " << endl;
                cout << " Day: ";
                cin >> day;
                cout << " Month: ";
                cin >> month;
                cout << " Year: ";
                cin >> year;
                try {
                    e->getDate()->setDate(day, month, year);
                    break;
                }
                catch (invalid_argument &ex) {
                    cout << "BAD DATE U FCKING MORON" << endl;
                }
            }
        }
		int input;

		while (true) {
			cout << " --------------------------------------- " << endl;
			cout << "| Elections Main Menu:                  |" << endl;
			cout << "| 1. Add District                       |" << endl;
			cout << "| 2. Add Citizen                        |" << endl;
			cout << "| 3. Add Party                          |" << endl;
			cout << "| 4. Make Citizen a Representative      |" << endl;
			cout << "| 5. Print Citizen's List               |" << endl;
			cout << "| 6. Print Party's List                 |" << endl;
			cout << "| 7. Print District's List              |" << endl;
			cout << "| 8. Vote                               |" << endl;
			cout << "| 9. Show Results                       |" << endl;
			cout << "| 10. Exit                              |" << endl;
            if (resFlag == true)
            {
                cout << "| 11. Save Elections                    |" << endl;
                cout << "| 12. Load Elections                    |" << endl;
            }
			cout << " --------------------------------------- " << endl;

			cout << " Choice: ";
			cin >> input;

			MENU CHOICE = MENU(input);
			if (CHOICE == MENU::DISTRICT) {
				if (simpleElcFlag == true)
				{
					cout << " --------------------------------------- " << endl;
					cout << " -       Simple Elections Mode.        -" << endl;
					cout << " --------------------------------------- " << endl;
				}
                else
                    DistirctMenu();
			}
			else if (CHOICE == MENU::CITIZEN) {
				CitizenMenu();
			}
			else if (CHOICE == MENU::PARTY) {
				PartyMenu();
			}
			else if (CHOICE == MENU::MAKEREP) {
				MakeRepMenu();
			}
			else if (CHOICE == MENU::PRINTC) {
			    applyAll(e->getCList()->getList(), Print());
				system("pause");
			}
			else if (CHOICE == MENU::PRINTP) {
                applyAll(e->getPList()->getList(), Print());
				system("pause");
			}
			else if (CHOICE == MENU::PRINTD) {
                applyAll(e->getDList()->getList(), Print());
				system("pause");
			}
			else if (CHOICE == MENU::VOTE) {
				VoteMenu();
			}
			else if (CHOICE == MENU::RESULTS) {
                if (e->VoteResults())
                    resFlag = true;
			}
			else if (CHOICE == MENU::EXIT) {
				break;
			}
            else if (resFlag == true && input == 11)
            {
                cout << " - Enter file's Name: ";
                string name;
                cin >> name;

				try {
					ofstream outfile(name, ios::binary | ios::trunc);
					ElectionsLoader::save(e, outfile);
					outfile.close();
				}
				catch (const ifstream::failure& e) {
					cout << "Error outfile" << endl;
					exit(-1);
				}
            }
			else if (resFlag == true && input == 12)
            {
                cout << " -  Enter file name: ";
                string name;
                cin >> name;

                ifstream infile(name, ios::binary);
                if (!infile) {
                    cout << "Error infile" << endl;
                    exit(-1);
                }
                delete e;
                Elections* es = ElectionsLoader::load(infile);
                e = es;
                if(dynamic_cast<ElectionsReg*>(es))
                    simpleElcFlag = false;
                else
                    simpleElcFlag = true;
                cout << " ---------------------------------------- " << endl;
                cout << " -  Elections have Loaded Successfully  - " << endl;
                cout << "     Day:  " << e->getDate()->getDay() << "  Month:  " << e->getDate()->getMonth()
                    << "  Year:  " << e->getDate()->getYear() << "    " << endl;;
                cout << " ---------------------------------------- " << endl;
            }
			else {
				cout << " --------------------------------------- " << endl;
				cout << " -  Invaild input, Please try Again    - " << endl;
				cout << " --------------------------------------- " << endl;
			}
		}
	}
    void Menu::MakeRepMenu(void)
    {
        int tempID;

        while (true) {
            cout << "---------------------------------------- " << endl;
            cout << "-  Please Enter ID of Disired Citizen: - " << endl;
            cout << "-             0 to Exit                - " << endl;
            cout << "---------------------------------------- " << endl;
            cin >> tempID;

            //Exit
            if (tempID == 0)
                break;

            CitizenList* _cList = e->getCList();
            DistrictList* _dList = e->getDList();
            PartyList* _pList = e->getPList();

            //If Citizen have been founded
            try {
                _cList->getCitizenByID(tempID);
            }
            catch (invalid_argument& ex) {
                cout << "---------------------------------------- " << endl;
                cout << "* " << "Cannot find ID " << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
                break;
            }
            Citizen &c1 = _cList->getCitizenByID(tempID);
            Representative* rep = dynamic_cast<Representative*>(&c1);

            //IF he is not representative already
            if (!rep) {

                cout << "---------------------------------------- " << endl;
                cout << "*  Make " << c1.getName() << " Representative " << endl;
                cout << "*  Please Enter Party & District ID :" << endl;
                cout << "---------------------------------------- " << endl;

                int temParty, temDistrict;
                cin >> temParty >> temDistrict;

                if (simpleElcFlag == true)
                    temDistrict = 1;

                try {
                    _pList->getPartyByID(temParty);
                    _dList->getDistrictByID(temDistrict);
                }
                catch(int x) {
                    cout << "---------------------------------------- " << endl;
                    cout << "-     Party or District not found;     -" << endl;
                    cout << "---------------------------------------- " << endl;
                    system("pause");
                    break;
                }
                //Setting Citizen's rep class, sending pointer to district
                Representative r(c1, &_pList->getPartyByID(temParty), &_dList->getDistrictByID(temDistrict));
                r.setPartyID(temParty);
                r.setDistrictID(temDistrict);

                //Adding Citizen to Party's list
                _cList->makeCitizenRep(r);
                _pList->getPartyByID(temParty).addCitizen(r);

                //OK msg.
                cout << "---------------------------------------- " << endl;
                cout << "* " << r.getName() << " Set Successfully as a Rep;" << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
                break;
            }
            //ERROR msg.
            else {
                cout << "---------------------------------------- " << endl;
                cout << "* " << rep->getName() << " is already a Representative in party: " << rep->getParty()->getSerial() << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
            }
        }
    }
    void Menu::CitizenMenu(void)
    {
        while (true) {

            cout << "---------------------------------------- " << endl;
            cout << "-  Provide Name (up tp 100 characters) -" << endl;
            cout << "---------------------------------------- " << endl;
            string name;
            cin >> name;

            cout << "---------------------------------------- " << endl;
            cout << "-     Provide ID, Bday & District      -" << endl;
            cout << "---------------------------------------- " << endl;
            int iD, bDay, district;
            cin >> iD >> bDay >> district;

            if ( e->getDate()->getYear() - bDay < 18) {
                cout << "---------------------------------------- " << endl;
                cout << "*  Citizen age under 18: "				 << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
                break;
            }

            if (simpleElcFlag == true)
                district = 1;

            CitizenList* _cList = e->getCList();
            DistrictList* _dList = e->getDList();

            District* d;
            try{
                d = &_dList->getDistrictByID(district);
            }
            catch (invalid_argument& ex) {
                cout << "---------------------------------------- " << endl;
                cout << "*  District: " << district << " Not Found" << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
                break;
            }

			try{
				// Local initilization for citizen, will be allocated later in ctor;
				Citizen c(name, d, iD, bDay, district);

				// citizen added Successfully Print indication.
				if (_cList->addCitizen(c)) {
					cout << "---------------------------------------- " << endl;
					cout << "*  " << c.getName() << " Added Successfully" << endl;
					cout << "---------------------------------------- " << endl;

					//Add Citizen to vaild to vote citizen's list in district
					d->addCitizen(c);
					system("pause");
					break;
				}
			}
            // print ERROR msg.
			catch (invalid_argument& ex) {
				cout << "---------------------------------------- " << endl;
				cout << "*  ID: " << iD << ex.what() << endl;
				cout << "---------------------------------------- " << endl;
				system("pause");
				break;
			}
        }
    }
    void Menu::DistirctMenu(void)
    {
		//Local pointers for a better working flow with the lists
		PartyList* _pList = e->getPList();
		DistrictList* _dList = e->getDList();

		//Menu Loop
        while (true) {
            cout << " ----------------------------------------- " << endl;
            cout << " -   Enter Name (up tp 100 characters)   - " << endl;
            cout << " ----------------------------------------- " << endl;
            string name;
            cin >> name;

            cout << "----------------------------------------- " << endl;
            cout << "-     Provide amount Repersentative     - " << endl;
            cout << "----------------------------------------- " << endl;

            int repNum;
            cin >> repNum;

			if (repNum < 1)
			{
				cout << " --------------------------------------- " << endl;
				cout << " -  Invaild input, Please try Again    - " << endl;
				cout << " --------------------------------------- " << endl;
			}
			else {
				int dType;
				cout << "----------------------------------------- " << endl;
				cout << "-  Is the District Unified  ( 1 / 0 )   - " << endl;
				cout << "----------------------------------------- " << endl;
				cin >> dType;

				//Adding the District and Printing Success MSG.
				try {
				    if(dType == 1)
                        _dList->addDistrict(UniFormDistrict(name, _dList->getLen()+1, repNum, _pList->getLen(), 0), dType);
				    else
                        _dList->addDistrict(DividedDistrict(name, _dList->getLen()+1, repNum, _pList->getLen(), 0), dType);
					cout << "----------------------------------------- " << endl;
					cout << "*  " << _dList->getDistrictByID(_dList->getLen()).getName() << " Added Successfully" << endl;
					cout << "*  Generated Serial Number : " << _dList->getLen() << endl;
					cout << "----------------------------------------- " << endl;

					system("pause");
					break;
				}
				catch (invalid_argument& ex) {
					cout << "----------------------------------------- " << endl;
					cout << "*  Name : " << _dList->getDistrictByID(_dList->getLen()).getName() << ex.what() << endl;
					cout << "----------------------------------------- " << endl;

					system("pause");
					break;
				}
			}	
        }
    }
    void Menu::PartyMenu(void)
    {
        while (true) {
            cout << "---------------------------------------- " << endl;
            cout << "- Enter Party's Name: (100 characters) -" << endl;
            cout << "---------------------------------------- " << endl;
            string name;
            int id;

            cin >> name;
            cout << "---------------------------------------- " << endl;
            cout << "-     Enter Leader's ID (vaild one)    -" << endl;
            cout << "---------------------------------------- " << endl;
            cin >> id;

            CitizenList* _cList = e->getCList();
            DistrictList* _dList = e->getDList();
            PartyList* _pList = e->getPList();

            Citizen* c;
            try{
                c = &_cList->getCitizenByID(id);
            }
            catch (invalid_argument& ex) {
                cout << "---------------------------------------- " << endl;
                cout <<			"* Couldn't find the leader"	    << endl;
                cout << "---------------------------------------- " << endl;

                system("pause");
                break;
            }

            Representative* rep = dynamic_cast<Representative*>(c);

            //Checking if Leader is already assigned to another party.
            if (rep != nullptr) {
                cout << "---------------------------------------- " << endl;
                cout << "* " << rep->getName() << " is Already Representative" << endl << endl;
                cout << "---------------------------------------- " << endl;
                system("pause");
                break;
            }

            //Local party, for later CopyConstructor
            Party p(name, _pList->getLen() + 1, c);

            //Adding local party to the list
            if (_pList->addParty(p)) {
                //Upgrading citizen to rep & adding the rep to the party
                // nullptr for Leader -------------------------------------------- Function maybe ??
                Representative r(*c, &_pList->getPartyByID(_pList->getLen()), nullptr);
                r.setPartyID(_pList->getLen());
                r.setDistrictID(0);
                _pList->getPartyByID(_pList->getLen()).setLeader(_cList->makeCitizenRep(r));

                //Updating all districts partyArr field.
                _dList->addPartyToAllDistricts();

                //Printing Success
                cout << "---------------------------------------- " << endl;
                cout << "*  " << p.getName() << " - Have been added Successfully." << endl;
                cout << "*  Generated Serial Number: " << _pList->getLen() << endl;
                cout << "---------------------------------------- " << endl;

                system("pause");
                break;
            }

        }
    }
    void Menu::VoteMenu(void)
    {
        while (true)
        {
            cout << "---------------------------------------- " << endl;
            cout << "-Enter Voter's ID & Party's ID (0.Exit)-" << endl;
            cout << "---------------------------------------- " << endl;
            int id, partyid;
            cin >> id >> partyid;

            //Break the vote
            if (id == 0)
                break;

            CitizenList* _cList = e->getCList();
            DistrictList* _dList = e->getDList();
            PartyList* _pList = e->getPList();

            try {
                _cList->getCitizenByID(id);
                _pList->getPartyByID(partyid);

                Citizen& c = _cList->getCitizenByID(id);

                //If he didnt voted already.
                if (!c.getVoted()) {
                    //Add vote in the district's VotesArray.
                    _dList->getDistrictByID(c.Citizen::getDistrict()->getSerial()).addCount(c, partyid - 1);

                    cout << "---------------------------------------- " << endl;
                    cout << "*  " << c.getName() << " Voted Successfully" << endl;
                    cout << "---------------------------------------- " << endl;
                    system("pause");
                    break;
                }
                //Else Print Error msg.
                else {
                    cout << "---------------------------------------- " << endl;
                    cout << "*  " << c.getName() << " Already voted" << endl;
                    cout << "---------------------------------------- " << endl;
                }
            }

            catch(invalid_argument& ex) {
                cout << "---------------------------------------- " << endl;
                cout << "*  Something went wrong" << endl;
                cout << "*	Cannot find citizen or party." << endl;
                cout << "*  Please enter correctly" << endl;
                cout << "---------------------------------------- " << endl;
            }
        }
    }

}
