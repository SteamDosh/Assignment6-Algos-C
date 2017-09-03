#include "Functions.h"

string g_key;
string g_text;
const int g_primeInt = 257;

void SelectFile()
{
	cout << "\nEnter the name of the file (ie words.txt)" << endl;
	string input;
	cin >> input;

	ReadFile(input);
}

void ReadFile(string aFileName)
{
	ifstream fin(aFileName);

	if (!fin.good())
	{
		cerr << "Could not open data file!\n";
		return;
	}
	int step = 0;
	for (string word; fin >> word;)
	{
		if (g_text=="")g_text = word;
		else g_key = word;
	}

	fin.close();

	search(g_text, g_key);

	cout << "Finished loading file" << endl;
}

void search(string aText, string aKey)
{
	cout << "Text = " << aText << endl;
	cout << "Key = " << aKey << endl;

	uint64_t patternHash = 0;
	uint64_t textHash = 0;
	string outputString = "";

	//Create first hashes
	hashVal(patternHash,aKey,0);
	hashVal(textHash,aText,0);

	for (int i = 0; i <= aText.length() - aKey.length(); i++)
	{
		if (patternHash == textHash)				//Hashes match
		{
			int j = 0;
			for (j = 0; j < aKey.length(); j++)		//Mostly redundent Individual Checking 
			{
				if (aText[i + j] != aKey[j])
					break;
			}

			if (j == aKey.length())	outputString += " "+to_string(i)+",";	//add index to output String
		}

		if (i < aText.length() - aKey.length())
		{
			hashVal(textHash,aText,i);//New Hash value of i+1..keyLength
			
			if (textHash < 0) textHash = (textHash + g_primeInt);//Apparently we can get negative
		}	
	}

	if (outputString.size()>0) outputString.pop_back();	//remove excess ","
	cout << "Found pattern at index -" << outputString << "."<< endl;
}

void hashVal(int aVar, string aText,int aIndex)
{
	aVar = 0;
	for (int i = g_key.size()-1; i > 0; i--)
	{
		aVar += pow(g_primeInt, i) + aText[i + aIndex];
	}
}