#include "Functions.h"

string g_key;
string g_text;
int g_currentHash = 1;	
const int g_primeInt = 101;

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
		if (step == 0)
		{
			step++;
			g_text = word;
		}
		else
		{
			g_key = word;
		}
	}

	fin.close();

	search(g_text, g_key);

	cout << "Finished loading file" << endl;
}

void search(string aText, string aKey)
{
	cout << aText << endl;
	cout << aKey << endl;

	for (int i = 0; i < aKey.length() - 1; i++)	//Idk what the fuck this is for
	{
		g_currentHash = (g_currentHash) % g_primeInt;
	}

	int patternHash = 0;
	int textHash = 0;

	//Create first hashes
	for (int i = 0; i < aKey.length(); i++)
	{
		patternHash = (patternHash + aKey[i]) % g_primeInt;
		textHash = (textHash + aText[i]) % g_primeInt;
	}

	for (int i = 0; i <= aText.length() - aKey.length(); i++)
	{
		if (patternHash == textHash)
		{
			int j = 0;
			for (j = 0; j < aKey.length(); j++)		//Individual Checking
			{
				if (aText[i + j] != aKey[j])
					break;
			}

			if (j == aKey.length())	cout << "Pattern found at index "<< i << endl;
		}

		if (i < aText.length() - aKey.length())
		{
			//New Hash value of i+1..keyLength
			textHash = ((textHash - aText[i] * g_currentHash) + aText[i + aKey.length()]) % g_primeInt;

			//Apparently we can get negatives
			if (textHash < 0) textHash = (textHash + g_primeInt);

		}
	}
}