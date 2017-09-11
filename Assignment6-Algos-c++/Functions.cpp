//ca797 - Christopher Aldous
//##########################

#include "Functions.h"
#define fuckthepolice unsigned long long int 
string g_key;
string g_text;
const int g_primeInt = 101;
const int g_modInt = 257;
int g_totalChecks = 0;

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


	for (string word; fin >> word;)
	{
		if (g_text == "")g_text = word;
		else g_key = word;
	}

	fin.close();

	search(g_text, g_key);

	cout << "Finished loading file" << endl;
}

void search(string aText, string aKey)
{
	cout << "Text = " << aText << endl;
	cout << "Key = " << aKey << " " << g_key << endl;

	uint64_t patternHash = 0;
	uint64_t textHash = 0;
	string outputString = "";

	//Create first hashes 
	int count = 0;
	for (int i = g_key.size(); i > 0; i--)
	{
		patternHash += (uint64_t)(aKey[count] * pow(g_primeInt, i - 1));
		textHash += (uint64_t)(aText[count] * pow(g_primeInt, i - 1));
		count++;
	}
	patternHash = modVal(patternHash);

	cout << "key Modulo=" << patternHash << endl;

	for (int i = 0; i <= aText.length() - aKey.length(); i++)
	{
		if (patternHash == modVal(textHash))				//Hashes match
		{
			g_totalChecks++;
			int j =	0;
			for (j = 0; j < aKey.length(); j++)		//Mostly redundent Individual Checking 
			{
				if (aText[i + j] != aKey[j])
					break;
			}

			if (j == aKey.length())	outputString += " " + to_string(i) + ",";	//add index to output String
		}	

		if (i < aText.length() - aKey.length())
		{
			textHash = hashVal(textHash, i);	//New Hash value of i+1..keyLength
		}
	}

	if (outputString.size()>0) outputString.pop_back();	//remove excess ","
	cout << "Found pattern at index -" << outputString << "." << endl;
	cout << "Performed " << g_totalChecks << " brute force checks." << endl;
}

uint64_t hashVal(uint64_t aVar, int aIndex)
{
	aVar -= pow(g_primeInt, 4) * g_text[aIndex];	//remove previous Character
	aVar *= g_primeInt;								//Times by our prime
	aVar += g_text[aIndex + g_key.size()];			//Add new character

	return aVar;
}


uint64_t modVal(uint64_t aVar) 
{
	return aVar %= g_modInt; 
}