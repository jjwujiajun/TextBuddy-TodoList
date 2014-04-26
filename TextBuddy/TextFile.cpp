// TextFile.cpp
// This class contains all properties related to the handling of filestreams and the text vector data

#include "stdafx.h"
#include "TextFile.h"
using namespace std;

char TextFile::buffer[MAX];
char *MESSAGE_READY = "Welcome to TextBuddy. %s is ready for use.\n";
char *TEXT_LINE = "%d. %s\n";
char *TEXT_LINE_SELF_INDEX = "%s\n";

TextFile::TextFile(void) {
}

TextFile::~TextFile(void) {
}

// getters
// -----------------------------
string TextFile::name() const {
	return fileName;
}

string TextFile::getTextAtRow(int _row) const {
	return texts[_row - 1];
}

int TextFile::size() const {
	return texts.size();
}

vector<string> TextFile::getTexts() {
	return texts;
}

vector<string> TextFile::getPositiveSearch() {
	return listOfSearchPositives;
}

// vector<string> (texts) manipulation
// -----------------------------
void TextFile::addNew(string input) {
	texts.push_back(input);
	//appendLastRowToFile();
}

void TextFile::removeRow(int row) {
	vector<string>::iterator requestedRow = texts.begin();
	for (int i = 0; i < row - 1; ++i, ++requestedRow) {};

	texts.erase(requestedRow);
	saveTextToFile();
}

void TextFile::clearText() {
	texts.clear();
	saveTextToFile();
}

void TextFile::sortRowsAlphabetically() {
	sort(texts.begin(), texts.end());
}

void TextFile::searchFor(string input) {
	listOfSearchPositives.clear();

	for (int i = 1; i <= (int)texts.size(); ++i) {
		string textInThisRow = texts[i - 1];

		if (textDoesContainInput(textInThisRow, input)) {
			string textInThisRowWithIndex = to_string(i) + ". " + textInThisRow;
			listOfSearchPositives.push_back(textInThisRowWithIndex);
		}
	}
	displayBySelfIndexing(&listOfSearchPositives);
}

// fstream (file) manipulation
// ----------------------------
void TextFile::willBeNamed(char* inputFile)
{
	fileName = inputFile;
	clearText();
	announceTextFileReadyWithName(fileName);
}

void TextFile::saveTextToFile() {
	file.open(fileName, ios::trunc);

	for (int row = 1; row <= (int)texts.size(); ++row) {
		sprintf_s(buffer, TEXT_LINE, row, texts[row - 1].c_str());
		file << (string)buffer;
	}

	file.close();
}

void TextFile::appendLastRowToFile() {
	file.open(fileName, ios::app);

	int row = texts.size();
	sprintf_s(buffer, TEXT_LINE, row, texts[row - 1].c_str());
	file << (string)buffer;

	file.close();
}

void TextFile::display(){
	for (int row = 1; row <= (int)texts.size(); ++row) {
		sprintf_s(buffer, TEXT_LINE, row, texts[row - 1].c_str());
		cout << (string)buffer;
	}
}

void TextFile::displayBySelfIndexing(vector<string>* texts) {
	for (int row = 1; row <= (int)texts->size(); ++row) {
		sprintf_s(buffer, TEXT_LINE_SELF_INDEX, texts->at(row - 1).c_str());
		cout << (string)buffer;
	}
}

// confirm message
void TextFile::announceTextFileReadyWithName(string fileName) const {
	sprintf_s(buffer, MESSAGE_READY, fileName.c_str());
	cout << (string)buffer;
}

// Others
bool TextFile::textDoesContainInput(string text, string input) {
	int searchValue = text.find(input);
	if (searchValue < 0) {
			return false;
		}
	return true;
}