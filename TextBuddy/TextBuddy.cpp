// TextBuddy.cpp
// This class runs the whole application.

#include "stdafx.h"
#include "TextBuddy.h"
#include "TextFile.h"
using namespace std;

char TextBuddy::buffer[MAX];
string MESSAGE_PROMPT_COMMAND = "Command:";
string INPUT_ADD = "add";
string INPUT_DELETE = "delete";
string INPUT_CLEAR = "clear";
string INPUT_DISPLAY = "display";
string INPUT_SORT = "sort";
string INPUT_SEARCH = "search";
string INPUT_EXIT = "exit";
char *MESSAGE_CONTENT_ADDED = "added to %s: \"%s\"\n";
char *MESSAGE_CONTENT_DELETED = "deleted from %s: \"%s\"\n";
char *MESSAGE_CONTENT_CLEARED = "all content deleted from %s\n";

TextBuddy::TextBuddy(void) {
}

TextBuddy::~TextBuddy(void) {
}

// application initialisation
// -------------------------------------
void TextBuddy::initWithFileNamed(char* fileName) {
	_textFile.willBeNamed(fileName);
	
	promptUserCommand();
	executeCommand();
}

// general operations
// --------------------------------------
void TextBuddy::executeCommand()
// The file is saved (selectively) after each operation. This does not include when executing "display" and "exit" _command as nothing is touched.
// Option (a) is chosen over (c) to ensure security of saving work done immediately,
// to prevent loss of data half way through if not exited before anything happens,
// Option (a) is chosen over (b) as it is very difficult to implement periodic saving using C++.
// (a) makes a good enough alternative.
{
	while (_command != EXIT)
	{
		switch (_command) {
		case ADD:
			addNewInputToTextFile();
			break;
		case DELETE:
			removeRowFromTextFile();
			break;
		case CLEAR:
			clearTextFile();
			break;
		case DISPLAY:
			displayTextFile();
			break;
		case SORT:
			sortTextFile();
			break;
		case SEARCH:
			searchTextFile();
		default:
			break;
		}
		promptUserCommand();
	}
}

void TextBuddy::promptUserCommand() {
	string inputString;
	
	cout << MESSAGE_PROMPT_COMMAND;
	cin >> inputString;

	convert(inputString);
}

void TextBuddy::convert(string inputString) {
	if (inputString == INPUT_ADD) {
		_command = ADD;
	} else if (inputString == INPUT_DELETE) {
		_command = DELETE;
	} else if (inputString == INPUT_CLEAR) {
		_command = CLEAR;
	} else if (inputString == INPUT_DISPLAY) {
		_command = DISPLAY;
	} else if (inputString == INPUT_EXIT) {
		_command = EXIT;
	} else if (inputString == INPUT_SORT) {
		_command = SORT;
	} else if (inputString == INPUT_SEARCH) {
		_command = SEARCH;
	} else {
		_command = NONE;
	}
}

bool TextBuddy::isValid(int row) {
	bool isPositive = row > 0;
	bool isExistingRow = row <= _textFile.size();
	return isExistingRow && isPositive;
}

void TextBuddy::receiveInput(){
	// remove extra space
	getchar();
	getline(cin, _input);
}

// _command operations
// ------------------------------------
void TextBuddy::addNewInputToTextFile() {
	receiveInput();
	_textFile.addNew(_input);
	printMessageConfirmAdded();
}

void TextBuddy::removeRowFromTextFile(){
	cin >> _row;
	if (isValid(_row)) {
		string requestedString = _textFile.getTextAtRow(_row);

		_textFile.removeRow(_row);
		printMessageConfirmDeleted(requestedString);
	}
}

void TextBuddy::clearTextFile() {
	_textFile.clearText();
	printMessageConfirmCleared();
}

void TextBuddy::displayTextFile() 
{ 
	_textFile.display();			  
}

void TextBuddy::sortTextFile() {
	_textFile.sortRowsAlphabetically();
	_textFile.display();
}

void TextBuddy::searchTextFile() {
	receiveInput();
	_textFile.searchFor(_input);	
}

// confirmation messages
// -------------------------------
void TextBuddy::printMessageConfirmAdded() const {
	sprintf_s(buffer, MESSAGE_CONTENT_ADDED, _textFile.name().c_str(), _input.c_str());
	cout << (string)buffer;
}

void TextBuddy::printMessageConfirmDeleted(string requestedString) const {
	sprintf_s(buffer, MESSAGE_CONTENT_DELETED, _textFile.name().c_str(), requestedString.c_str());
	cout << (string)buffer;
}

void TextBuddy::printMessageConfirmCleared() const {
	sprintf_s(buffer, MESSAGE_CONTENT_CLEARED, _textFile.name().c_str());
	cout << (string)buffer;
}