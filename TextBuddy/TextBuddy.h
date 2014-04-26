/* TextBuddy.h
 * This class runs an application that manipulates information in a .txt file.
 * The user must execute the programme along with a .txt filename in a single line using the command prompt.
 * The indicated .txt file will then be created if it does not already exist, and will be manipulated.
 * The product .txt file will be saved in the same folder as the TextBuddy execution file.

 * There are 5 commands that user can initiate to manipulate the text file.
 * 1) add (string)
 *			Adds a line of text to the end of the file.
 *			It will be pre-fixed with a row number for easy reference.
 *			Format: "add (string)", where (string) is any line of text the user wants to input.
 * 2) delete (int)
 *			Deletes a line of text in the file.
 *			Lines of texts below the deleted line will move up to take up the empty space of the deleted line.
 *			Note: if requested row is not found in text, it is invalid. TextBuddy will not do anything to text, and re-prompt for command.
 *			Format: "delete (int)", where int is the row number of the line user wants  to delete.
 * 3) display
 *			Displays content in the text file as it is.
 *			Format: "display".
 * 4) clear
 *			Clears the content in the text file.
 *			.txt file will become empty.
 *			Format: "clear".
 * 5) sort
 *			Sorts the rows in the textFile in alphanumeric order.
 *			Format: "sort".
 * 6) search (string)
 *			Searches the entire textFile for rows that contain the input string.
 *			Results are displayed in order, with their original indexes for easy reference for other uses.
 *			Format: "search (string)", where (string) is any line of text you want to search.
 * 7) exit
 *			Exits the TextBuddy application.

 * Things to Note:
 * 1) If user input an invalid command, nothing will be done by the application. User will be re-prompted.
 * 2) The text file will be saved after user has initiated every command.
 * 3) If the file name specified by user is already in the folder when the app is executed, the file will be cleared.
 * 4) For CE1, we assume there is only one user input .txt file. Therefore there will only be one TextFile instance.
 *	  It is conveniently made a TextBuddy Property.

 * Coded by: Wu Jiajun (A0100705Y)
 */ 

#include "stdafx.h"
#include "TextFile.h"

class TextBuddy {
public:

	typedef enum {ADD, DELETE, CLEAR, DISPLAY, EXIT, SORT, SEARCH, NONE} Command;

	TextBuddy(void);
	~TextBuddy(void);
	
	// application initialisation
	// ----------------------------
	// starts the application after receiving a file name given by user
	void initWithFileNamed(char* inputFile);
	
	// general operations
	// ----------------------------
	//	Prompt User Command
	//	If command is not "add", "delete", "clear", "display" or "exit", command will be made "none".
	//	App will only quit when user commands an "exit".
	void promptUserCommand();
	//	Execute Command
	//	Function will performed a command according to requested command.
	//	Function will automatically re-prompt user for command after finish executing actions.
	void executeCommand();
	//	Convert string type input to enum type command, for use in other general operations.
	//	It ensures only allowed inputs will become legit commands for other functions to understand.
	void convert(string inputString);
	void receiveInput();
	//	Check row is valid
	bool isValid(int row);

	// command operations
	// -------------------------
	//	Add new input to textFile
	//	Takes in a user input and save to text file
	//	Confirm to user that their request has been successfully executed
	void addNewInputToTextFile();
	//	Remove a row from textFile
	//	Takes in a requested row (indicate by its pre-fixed number) to be deleted from the file.
	//	eg. "1. some texts" ----> row 1
	//	If requested row is valid, confirms to user operation is successful
	//	If requested row is invalid, does not confirm anything
	void removeRowFromTextFile();
	void displayTextFile();
	void clearTextFile();
	void sortTextFile();
	void searchTextFile();

	// confirmation messages
	// -------------------------------
	void printMessageConfirmAdded() const;
	void printMessageConfirmDeleted(string requestedItem) const;
	void printMessageConfirmCleared() const;
	
	static char buffer[MAX];
	
private:
	TextFile _textFile;
	Command _command;
	string _input;
	int _row;
};