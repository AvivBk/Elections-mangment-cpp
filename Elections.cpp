#include "Elections.h"

namespace elc {
    Elections::Elections()
    {
		try {
			cList = new CitizenList();
			dList = new DistrictList();
			pList = new PartyList();
			date = new Date();
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
    }

    Elections::Elections(istream& in) : Elections()
    {
        load(in);
    }

    Elections::~Elections()
    {
        cList->~CitizenList();
        dList->~DistrictList();
        pList->~PartyList();
        delete date;
    }

    bool Elections::checkValidility(void) const {
        int amountRep = dList->totalRepresents();
        int totalVotes = dList->getTotalVotes();

        //IF there is not parties.
        if (pList->getLen() < 1) {
			throw invalid_argument("*  No Party have been signed up ");
            //cout << "---------------------------------------- " << endl;
            //cout << "*  No Party have been signed up " << endl;
            //cout << "---------------------------------------- " << endl;
            return false;
        }

        //IF there is enough Representative
		for (int i = 0; i < dList->getLen(); i++)
		{
			if (pList->enoughRepresents(dList->getDistrictByID(i+1).getRepNum(), i+1) == false) {
				throw invalid_argument("*  Not enough Representative ");
				//cout << "---------------------------------------- " << endl;
				//cout << "*  Not enough Representative " << endl;
				//cout << "---------------------------------------- " << endl;
				return false;
			}
		}

        //IF there is no Districts
        if (dList->getLen() < 1 && cList->getLength() < 1) {
			throw invalid_argument("* No District have been signed up in the state *");
			//cout << "---------------------------------------- " << endl;
   //         cout << "* No District have been signed up in the state *" << endl;
			//cout << "---------------------------------------- " << endl;
            return false;
        }

        //If not one have been voted yed
        if (totalVotes == 0) {
			throw invalid_argument("*  No Votes have been recorded ");
            //cout << "---------------------------------------- " << endl;
            //cout << "*  No Votes have been recorded " << endl;
            //cout << "---------------------------------------- " << endl;
            return false;
        }

        //IF everything is ok
        return true;
    }

    bool Elections::VoteResults(void) {
        //IF We can start the vote count
		try{
			checkValidility();

			//Initiallizing Array Votes
			int dLen = dList->getLen();
			int pLen = pList->getLen();
			int* electionsWinner;
			int* totalVotes;
			int* totalRepresentatives;
			try {
				electionsWinner = new int[pLen];
				totalVotes = new int[pLen];
				totalRepresentatives = new int[pLen];
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
			//Initiallizing Array to Zero
			for (int i = 0; i < pLen; i++) {
				electionsWinner[i] = 0;
				totalVotes[i] = 0;
				totalRepresentatives[i] = 0;
			}

			//Calculating the results for each District.
			for (int i = 0; i < dLen; i++)
			{
				//Allocating and Reffering.
				District& d = dList->getDistrictByID(i + 1);
				float* BucketScore;
				float* BucketPrecentage;
				try {
					BucketScore = new float[pLen];
					BucketPrecentage = new float[pLen];
				}
				catch (bad_alloc& ex) {
					cout << ex.what() << endl;
					exit(1);
				}
				DynamicArray<int>::iterator VotesArray = d.getParty();

				int sumOfVotes = d.getSumOfVotes();

				// Variable for calculating the gap in the votes.
				int a = 0;
				// Variables for Maximum finder
				float max1 = 0.0;
				int maxIndex = -1;

				bool UniformFlag = true;

				const UniFormDistrict* p = dynamic_cast<const UniFormDistrict*>(&d);
				if (p == nullptr) {
					UniformFlag = false;
				}

				// Calulcating for every party the amount of rep she got in district.
				for (int j = 0; j < pLen; j++) {
					if (sumOfVotes == 0) {
						a = d.getRepNum();
						maxIndex = 0;
						BucketPrecentage[j] = 0.0;
						BucketScore[j] = 0.0;
					}
					else {
						BucketPrecentage[j] = (float)(((float)(*VotesArray) / sumOfVotes) * 100.0);
						BucketScore[j] = (float)(((float)(*VotesArray) / sumOfVotes) * d.getRepNum());
						totalVotes[j] += (*VotesArray);
						if (BucketScore[j] > max1) {
							max1 = BucketScore[j];
							maxIndex = j;
						}
						a += (int)BucketScore[j];
					}
					VotesArray++;
				}
				//        electionsWinner[maxIndex] += d.getRepNum();

						// Rounding up the highest shaerit in order the count correcly the rep number.
				for (a; a < d.getRepNum(); a++) {
					float max = BucketScore[0] - (int)BucketScore[0];
					int idx = 0;
					for (int k = 1; k < pLen; k++) {
						if (max < (BucketScore[k] - (int)BucketScore[k])) {
							max = (BucketScore[k] - (int)BucketScore[k]);
							idx = k;
						}
					}
					BucketScore[idx] = (int)BucketScore[idx] + 1;
				}

				// case for uniform district 
				if (UniformFlag == true)
					electionsWinner[maxIndex] += d.getRepNum();
				// case for divided district 
				else {
					for (int k = 0; k < pLen; k++)
						electionsWinner[k] += BucketScore[k];
				}

				for (int k = 0; k < pLen; k++) {
					totalRepresentatives[k] += BucketScore[k];
				}

				cout << "---------------------------------------- " << endl;
				cout << "*  District: " << d.getName() << " Provides: " << d.getRepNum() << endl;

				// IF no one voted in this district
				if (maxIndex == -1)
				{
					cout << "*  In this District no one voted yet" << endl;
					cout << "---------------------------------------- " << endl;
				}
				//There is someone who voted
				else {
					cout << "---------------------------------------- " << endl;
					cout << "*  Winner : ** " << pList->getPartyByID(maxIndex + 1).getLeader()->getName() << " **" << endl;
					VotesArray = d.getParty();
					for (int pp = 0; pp < pLen; pp++) {
						cout << "*  Party: " << pList->getPartyByID(pp + 1).getName() << ", With " << *VotesArray << " votes" << endl;
						cout << "*  Which are: " << BucketPrecentage[pp] << "% " << endl;
						cout << "*  The Party List: " << endl;
						pList->getPartyByID(pp + 1).printWinners(BucketScore[pp], i + 1);
						cout << "---------------------------------------- " << endl;
						VotesArray++;
					}
				}
				cout << "Percentage of voting in the district: " << d.getPercentageVotes() << '%' << endl;
				delete[] BucketScore;
				delete[] BucketPrecentage;
			}

			//Finding the index for winning party
			int winnerInd = 0;
			int maxWinner = electionsWinner[0];
			for (int i = 0; i < pLen; i++) {
				if (electionsWinner[i] > maxWinner) {
					maxWinner = electionsWinner[i];
					winnerInd = i;
				}
			}

			cout << "---------------------------------------- " << endl;
			cout << "*  The Elections Winner is --> " << pList->getPartyByID(winnerInd + 1).getLeader()->getName() << endl;
			cout << "*  With " << electionsWinner[winnerInd] << "  Electors " << endl;
			cout << "---------------------------------------- " << endl;

			delete[] electionsWinner;
			delete[] totalVotes;
			delete[] totalRepresentatives;

			system("pause");
			return true;
		}
		catch (invalid_argument& ex) {
			cout << "---------------------------------------- " << endl;
			cout << ex.what() << endl;
			cout << "---------------------------------------- " << endl;
			cout << "* The result cannot be displayed " << endl;
			cout << "---------------------------------------- " << endl;
			system("pause");
			return false;
		}
    }

    //-----------------------------------Serialize Elections-------------------------------------//
    void Elections::load(istream& in)
    {
        date->load(in);
        dList->load(in);
        cList->load(in);
        pList->load(in);
        linkCitizensToDistricts();
        linkRepToParty();
    }
    void Elections::save(ostream& out) const
    {
        date->save(out);
        dList->save(out);
        cList->save(out);
        pList->save(out);
    }
    void Elections::linkCitizensToDistricts(void)
    {
        for (int i = 0; i < dList->getLen(); i++)
        {
            District* d = &dList->getDistrictByID(i + 1);
            cList->LinkDistrictByID(d);
        }
    }
    void Elections::linkRepToParty()
    {
        for(int i = 0; i < pList->getLen(); i++)
        {
            Party* p = &pList->getPartyByID(i+1);
            p->setLeader(&cList->getCitizenByID(p->getLeaderID()));
            cList->LinkPartyByID(p);
        }
    }
    //-------------------------------------------------------------------------------------------//
}
