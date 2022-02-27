#include "Menu.h"
using namespace elc;

int main(void) {
    cout << " --------------------------------------- " << endl;
    cout << " -               Welcome               - " << endl;
    cout << " --------------------------------------- " << endl;
    cout << " -  Choose: 1.New round 2.Load round   - " << endl;

    int temp1;
    cin >> temp1;

    if (temp1 == 2)
    {
        cout << " -  Enter file name: ";
        string name;
        cin >> name;

        ifstream infile(name, ios::binary);
        if (!infile) {
            cout << "Error infile" << endl;
            exit(-1);
        }
        Elections* e = ElectionsLoader::load(infile);
        Menu m(e, true);
    }
    else {
        cout << " --------------------------------------- " << endl;
        cout << " -      Welcome to Elections 2020      - " << endl;
        cout << " -        Choose Elections Type        - " << endl;
        cout << " -      Normal/Simple   ( 1 / 2 )      - " << endl;
        cout << " --------------------------------------- " << endl;

        int temp;
        cin >> temp;

		try{
			if (temp == 2)
			{
				ElectionsSimple* e = new ElectionsSimple();
				Menu m(e, false);
			}
			else {
				ElectionsReg* e = new ElectionsReg();
				Menu m(e, false);
			}
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
    } 
    cout << " -             GoodBye :)              - " << endl;
    cout << " --------------------------------------- " << endl;
    return 1;
}

