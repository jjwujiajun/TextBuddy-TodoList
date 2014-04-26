/*	TextFile.h
 *	This class contains all properties and methods related to the handling of file streams and the vector data
 *	The purpose of this class is to group all background operations in one class to declutter TextBuddy class.
 *	It also better define the user input text file as an object.

 *	For technical understanding of the class structure:
 *	1) TextFile
 *			Every user specified .txt file will be classified under one TextFile instance.
 *			Therefore there can be many TextFiles.
 *	2) file
 *			Can be treated as the actual .txt file, as the .txt file is made a file stream here.
 *			It is here that actual operations on the .txt file is made.
 *	3) fileName
 *			The identity of the .txt file. This is the place where the name of the manupulated .txt file is stored.
 *			It will not be changed after being named.
 *	4) texts
 *			The content manager of the TextFile.
 *			Operations to be done on a TextFile will be sort out here before being transferred to the file.
 
 *	Things to note:
 *	1) For this CE1, we assume only one TextFile. So it is conveniently made a TextBuddy property.
 *
 *	Coded by: Wu Jiajun (A0100705Y)
 */ 

#include "stdafx.h"
#define MAX 250
using namespace std;

#pragma once

class TextFile
{
private:
	ofstream file;			// Input file by user
	string fileName;		// Name of input file by user
	vector<string> texts;	// A container to temporary store all items. To be manipulated by other functions
	vector<string> listOfSearchPositives;

public:

	static char buffer[MAX];

	TextFile(void);
	~TextFile(void);

	// getters
	// -----------------------------
	//	Name of file
	string name() const;
	//	Get text at specified row 
	string getTextAtRow(int row) const;
	//	Size of textFile
	int size() const;
	vector<string> getTexts();
	vector<string> getPositiveSearch();

	// vector<string> (texts) manipulation
	// -----------------------------
	//	Add new input
	//	adds a new roll of text below the existing text file.
	void addNew(string input);
	//	Remove a row
	void removeRow(int row);
	//	Clears textFile of any information.
	void clearText();
	void sortRowsAlphabetically();
	void searchFor(string input);

	// fstream (file) manipulation
	// ----------------------------
	//	Will be Named
	//	Prepares the TextFile by naming the file and	wiping clean the file content.
	void willBeNamed(char* inputFile);
	//	Save text to file
	//	After user has given their inputs, information is not transferred to the file yet.
	//	This step is required to save the information on the vector<string> (texts) to the fstream (file).
	//	eg.	texts.clear();
	//		saveTexttoFile();
	void saveTextToFile();
	//	Append last row to file
	//	If the information to be saved is just to append one new line to the pre-existing file,
	//	then this function can be called instead of saveTextToFile to reduce inefficient process
	//	eg.	text.push_back(string);
	//		appendLastRowToFile();
	void appendLastRowToFile();
	//	Displays all content on texts
	void display();
	void displayBySelfIndexing(vector<string>* texts);

	// confirm message
	void announceTextFileReadyWithName(string fileName) const;

	// others
	//	Covert searchValue to boolean
	bool textDoesContainInput(string text, string input);
};

