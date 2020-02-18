    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //                                                                                                                              //
  //    Program: This Program manages the inventory items of a book store, and invoices by adding/editing/deleting and viewing.   //
 //                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const string CSV_FILENAME = "MyStore-Inventory.csv"; // CSV file name created to hold data.
const int SLEEP_TIME = 500;                      // The amout of time in milliseconds programs wait before each function call.
const int ERROR_TIME = 4000;                     // The amout of time in milliseconds programs waits on some error messages.
const double TAX_PERCENTAGE = .0625;             // 6.25% TAX Percentage.

const string SCREEN_HEADER = "\n\t    M Y   C O N V I N I E N T   B O O K   S T O R E   M A N A G E M E N T   S Y S T E M"
                             "\n\t____________________________________________________________________________________________\n";


//======================================================= STRUCTURES =======================================================

// This structure has data for each inventory item.
struct InventoryData
{
	string itemNumber;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	char itemTaxable;
};

//////////////////////////////////////
                                   //
vector<InventoryData> theData;    //===================== ARRAY of struct type to populate with data from .csv file.
                                 //
//////////////////////////////////

//======================================================= FUNCTION PROTOTYPES =======================================================

// Fucntion prototype for MAIN MENU screen interface of program.
void mainScreen();

// Function prototype for Inventory Editor screen interface.
void inventoryEditorScreen();

// Function prototype definition will populate vector.
void populateVector();

// This function prototype definition will allow you to view items in the inventory.
void viewInventory();

// This function prototype defnition searches for an item by item number in the vector.
void searchInventory();

// This function prototype definition will allow us to add to the inventory.
void addToInventory();

// This function prototype definition will allow us to look for, then modify an element of the inventory.
void editInventoryItem();

// This function prototype definition will take the new input for editInventoryItem() (Takes a switch case option and index of item).
void editInventoryItemInput(int theOption, int index);

// This function prototype definition will allow the deletetion of an item form the file.
void deleteInventoryItem();

// This function prototype definition updates the file by overwriting it with the vector data when needed.
void updateFile();

// This function prototype definition allows the sale of an item, print the invoice on the screen then modifies the inventory to reflect sale.
void invoice();

// This Function prototype definition will allow us to turn a string into all uppercase.
string toupperAll(string theString);

//======================================================= MAIN FUNCTION =======================================================
int main()
{
	system("COLOR F2"); // Console color theme. 

	// Create file if it doesn't exist.
	ofstream theFile(CSV_FILENAME, ios::app);
	theFile.close();

	populateVector(); // Populate vector with data from existing file.

	mainScreen(); // Call to Main Menu interaface.

	system("PAUSE");
	return 0;
}

//======================================================= FUNCTION DEFINITIONS =======================================================

    ////////////////////////////////////////////////////////////////////////////////////
   //  Next 2 lines of codes when use clear and ignore gibberish before next input.  //
  //   cin.clear();                                                                 //
 //    cin.ignore(1000, '\n');                                                     //
////////////////////////////////////////////////////////////////////////////////////

// Function definition for MAIN MENU screen interface.
void mainScreen()
{
	int mainMenuOption; // This variable will hold the user chosen option from MAIN MENU.

	cout << SCREEN_HEADER;
	cout << "\n\t\tMAIN MENU:" << endl;
	cout << "\n\t\t   1  Invoice (Customer Receipt)" << endl;
	cout << "\t\t   2  Inventory Management (List/Add/Edit/Delete Items)" << endl;
	cout << "\t\t   3  Inventory Item Search" << endl;
	cout << "\t\t   4  Exit" << endl;
	
	// User input section.
	cout << "\n\t\t\t\t\tPlease Enter Required Option by Number: ";
	cin >> mainMenuOption;

	//  This while loop makes sure user enters a valid option that is not gibberish letter/s (only 1 to 4).
	while (cin.fail() || (mainMenuOption < 1 || mainMenuOption > 4))
	{
		cout << "\t\t\t\t\tPlease enter a valid option (1, 2, 3 or 4): ";
		// next 2 lines clear and ignore gibberish before next input.
		cin.clear();
		cin.ignore(1000, '\n');

		cin >> mainMenuOption;
	}
	cin.clear();
	cin.ignore(1000, '\n');

	// Switch case calls appropriate function for user option after clearing screen and waiting second/s.
	switch (mainMenuOption)
	{
	case 1: system("CLS");   cout << "\n\t\tLoading Invoice Screen...\n\n";   Sleep(SLEEP_TIME);   system("CLS");   invoice();   break;
	case 2: system("CLS");   cout << "\n\tLoading Inventory Editor...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();   break;
	case 3: system("CLS");   cout << "\n\t\tLoading Search Screen...\n\n";   Sleep(SLEEP_TIME);   system("CLS");   searchInventory();   break;
	case 4: system("CLS");   cout << "\n\tExiting Program...";   Sleep(SLEEP_TIME);   exit(0);   break;
	default: system("CLS"); cout << "\n\tInvalid Option\n\n"; break;
	}
}

// Function definition for inventory editor screen.
void inventoryEditorScreen()
{
	int userOption; // This variable will hold the user chosen option from Inventory Editor.

	cout << SCREEN_HEADER;
	cout << "\n\t\tInventory Editor:" << endl;
	cout << "\n\t\t   1  View Inventory List" << endl;
	cout << "\t\t   2  Add Inventory Items(s)" << endl;
	cout << "\t\t   3  Edit Enventory Item Detail" << endl;
	cout << "\t\t   4  Delete Inventory Item" << endl;
	cout << "\t\t   5  Return to Main Menu" << endl;

	// User input section.
	cout << "\n\t\t\t\t\tPlease Enter Required Option by Number: ";
	cin >> userOption;

	//  This while loop makes sure user enters a valid option that is not gibberish letter/s (only 1 to 5).
	while (cin.fail() || (userOption < 1 || userOption > 5))
	{
		cout << "\t\t\t\t\tPlease enter a valid option (1 to 5): ";
		// next 2 lines clear and ignore gibberish before next input.
		cin.clear();
		cin.ignore(1000, '\n');

		cin >> userOption;
	}
	cin.clear();
	cin.ignore(1000, '\n');

	// Switch case calls appropriate function for user option after clearing screen and waiting second/s.
	switch (userOption)
	{
	case 1: system("CLS");   cout << "\n\tLoading Inventory List...";   Sleep(SLEEP_TIME);   system("CLS");   viewInventory();   break;
	case 2: system("CLS");   cout << "\n\tLoading Adding Screen...";   Sleep(SLEEP_TIME);   system("CLS");   addToInventory();   break;
	case 3: system("CLS");   cout << "\n\t\tLoading Editing Screen...\n\n";   Sleep(SLEEP_TIME);   system("CLS");   editInventoryItem();   break;
	case 4: system("CLS");   cout << "\n\t\tLoading Deletation Screen...\n\n";   Sleep(SLEEP_TIME);   system("CLS");   deleteInventoryItem();   break;
	case 5: system("CLS");   cout << "\n\tLoading Main Menu...";   Sleep(SLEEP_TIME);   system("CLS");   mainScreen();   break;
	default: system("CLS"); cout << "\n\tInvalid Option\n\n"; break;
	}
}

// Function definition for populating vector.
void populateVector()
{
	string line;     // hold data line from file.
	int index = 0;   // Used for vector data index when populating inside while loop.
	
	theData.clear(); // Clear vector for new updated data.

	ifstream theFile(CSV_FILENAME);  // Open file for reading.

	// Make sure file is "available" or open then grab data as lines then split to seperate values to populate vector struct.
	if (theFile.is_open())
	{
		while (getline(theFile, line))
		{
			// Variables to hold data for vector of structure type.
			string itemNumber;
			string itemDescription;
			string itemQuantityStr;
			int itemQuantity;
			string itemPriceStr;
			double itemPrice;
			char itemTaxable;

			// This for loop breaks down the line into separate values after each comma.
			int delimeter = 0;
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',') { delimeter++; } // Counts how many comma we've encountered.

				if (delimeter == 0 && line[i] != ',') { itemNumber += line[i]; }
				if (delimeter == 1 && line[i] != ',') { itemDescription += line[i]; }
				if (delimeter == 2 && line[i] != ',') { itemQuantityStr += line[i]; }
				if (delimeter == 3 && line[i] != ',') { itemPriceStr += line[i]; }
				if (delimeter == 4 && line[i] != ',') { itemTaxable = line[i]; break; }
			}
			// Converting quantity and price into numbers.
			itemQuantity = stoi(itemQuantityStr);
			itemPrice = stod(itemPriceStr);
		
			//Add a new element to vector:
			theData.push_back(InventoryData());
			// Populating vector with data struct type.
			theData[index].itemNumber = itemNumber;
			theData[index].itemDescription = itemDescription;
			theData[index].itemQuantity = itemQuantity;
			theData[index].itemPrice = itemPrice;
			theData[index].itemTaxable = itemTaxable;

			index++;
		}
		theFile.close();
	}
	else
	{
		cout << "\n\n\t\t\t\t\t--- ERROR opening file ---";
		Sleep(ERROR_TIME);

		// Returns to Inventory Editor if opening file fails.
		system("CLS");   cout << "\n\tLoading Inventory Editor...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();
	}
}

// Function definition for viewing item list in enventory.
void viewInventory()
{
	cout << SCREEN_HEADER;
	cout << "\n\t\tInventory List:\n" << endl;

	// Formatted header for easy data reading when displayed.
	cout << "\n" << setw(30) << "P/N |" << setw(30) << "DESCRIPTION |" << setw(15) << "QUANTITY |" << setw(15) << "PRICE |" << setw(15) << "TAXABLE |" << endl;
	cout << setw(105) << right << "-----------------------------------------------------------------------------------------" << endl;

	// This for loop prints list of inventory item in vector.
	for (unsigned int i = 0; i < theData.size(); i++)
	{
		cout << setw(15) << i + 1 << "|" << setw(12) << theData[i].itemNumber
			                             << setw(30) << theData[i].itemDescription 
										 << setw(15) << theData[i].itemQuantity 
										 << setw(15) << theData[i].itemPrice 
										 << setw(15) << theData[i].itemTaxable << endl;
	}

	// If vector empty print no item found.
	if (theData.size() < 1) { cout << "\t\t   --- No Items Found ---\n"; }

	// Quit and return to enventory editor screen when user input 'Q' section.
	cout << "\n\n\n\t\t\t\t\tEnter 'Q' to Quit: ";
	while (true)
	{
		char quit;
		cin >> quit;
		if (toupper(quit) == 'Q') { break; }
	}
	cin.clear();
	cin.ignore(1000, '\n');

	// Returns to Inventory Editor if user quits or opening file fails.
	system("CLS");   cout << "\n\tLoading Inventory Editor...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();
}

// This function definition search through the inventory for an item by item number.
void searchInventory()
{
	string itemNumber; // Holds user input item to search for.
	int found = 0;     // Use to tell us if item searched is found.

	cout << SCREEN_HEADER;
	cout << "\n\t\tInventory Search:\n" << endl;

	while (true)
	{
		// User input (product number).
		cout << "\t\t   Enter Product Number (or 'Q' to Quit): ";
		getline(cin, itemNumber);
		// If itemNumber = Q, only Q with no extra characters including space char quit.
		if (toupper(itemNumber[0]) == 'Q' && itemNumber.length() == 1) break;

		// This for loop prints item of inventory vector.
		for (unsigned int i = 0; i < theData.size(); i++)
		{
			if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
			{
				cout << "\t\t             P/N: " << theData[i].itemNumber
				     << "\n\t\t     DESCRIPTION: " << theData[i].itemDescription
					 << "\n\t\t        QUANTITY: " << theData[i].itemQuantity
					 << "\n\t\t           PRICE: " << theData[i].itemPrice
					 << "\n\t\t         TAXABLE: " << theData[i].itemTaxable << endl << endl;
				found = 1;
			}
		}

		// If vector empty or nothing found print no item found.
		if (theData.size() < 1 || found == 0) { cout << "\t\t   --- No Items Found ---\n\n"; }
		found = 0;
	}

	// Returns to Main Menu if user quits.
	system("CLS");   cout << "\n\tLoading Main Menu...";   Sleep(SLEEP_TIME);   system("CLS");   mainScreen();
}

// Function definition for adding to inventory.
void addToInventory()
{
	// Variables to hold data for file.
	string itemNumber;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	char itemTaxable;

	cout << SCREEN_HEADER;
	cout << "\n\t\tAdd to Inventory:" << endl;

	// While user does not choose to quit keep asking for new item to add to inventory.
	while (true)
	{
		int itemAlreadyExist = 0;

		//_____________________________________________________________________________Item number input.
		cout << "\n\t\t     Enter Product Number (or 'Q' to Quit): ";
		getline(cin, itemNumber);
		// while loop makes sure user enters a  valid string (not empty or spaces)
		while (itemNumber.find_first_not_of(' ') == itemNumber.npos) 
		{
			cout << "\t\t     Enter Product Number (or 'Q' to Quit): ";
			getline(cin, itemNumber);
		}
		// If itemNumber = Q, only Q with no extra characters including space char quit.
		if (toupper(itemNumber[0]) == 'Q' && itemNumber.length() == 1) break;
		
		// This for loop checks if item is already in inventory.
		for (unsigned int i = 0; i < theData.size(); i++)
		{
			if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
			{
				cout << "\t\t     ***This item already exist.***\n";
				itemAlreadyExist = 1;
				break;
			}
		}

		if (itemAlreadyExist == 0)
		{
			//_____________________________________________________________________________Item description input.
			cout << "\t\t                    Enter Item Description: ";
			getline(cin, itemDescription);
			//_____________________________________________________________________________Item quantity input.
			cout << "\t\t                 Enter Item's New Quantity: ";
			cin >> itemQuantity;
			// This while loop makes sure user enters a valid option that is not gibberish letter/s or < 0.
			while (cin.fail() || itemQuantity < 0)
			{
				cout << "\t\t    Please Enter Quantity as a Number >= 0: ";
				cin.clear();
				cin.ignore(1000, '\n');

				cin >> itemQuantity;
			}
			//_____________________________________________________________________________Item cost input.
			cout << "\t\t                           Enter Item Cost: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> itemPrice;
			// This while loop makes sure user enters a valid option that is not gibberish letter/s < 0.
			while (cin.fail() || itemPrice < 0)
			{
				cout << "\t\t\tPlease Enter Cost as a Number >= 0: ";
				cin.clear();
				cin.ignore(1000, '\n');

				cin >> itemPrice;
			}
			//_____________________________________________________________________________Item is taxable? input.
			cout << "\t\t                     Is Item Taxable (Y/n)? ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> itemTaxable;
			itemTaxable = toupper(itemTaxable); // Make user input uppercase.

			//  This while loop makes sure user enters a valid option Y/n.
			while (itemTaxable != 'Y' && itemTaxable != 'N')
			{
				cout << "\t\t\t\t       Please Enter Y or N: ";
				cin.clear();
				cin.ignore(1000, '\n');

				cin >> itemTaxable;
				itemTaxable = toupper(itemTaxable);
			}
			cin.clear();
			cin.ignore(1000, '\n');

			// Writing new item to file, but 1st make sure file is open to be written to.
			ofstream theFile(CSV_FILENAME, ios::app);
			if (theFile.is_open())
			{
				theFile << itemNumber << "," << itemDescription << "," << itemQuantity << "," << itemPrice << "," << itemTaxable << "\n";
				theFile.close();

				populateVector(); // Update Vector data.

				cout << "\n\t\t\t\t\t*** Item Added Successfully! ***" << endl;
			}
			else
			{
				cout << "\n\t\t\t\t\t--- ERROR opening file ---";
				Sleep(ERROR_TIME);
			}
		}
	} // End while loop.

	// Returns to Inventory Editor if user quits.
	system("CLS");   cout << "\n\tLoading Inventory Editor...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();
}

// This function definition can allow us to look for, then modify items of the vector then updates the file data.
void editInventoryItem()
{
	// Holds data to put into vector.
	string itemNumber;

	int found = 0;     // Use to tell us if item searched is found.
	int userOption;

	cout << SCREEN_HEADER;
	cout << "\n\t\tEdit Inventory Item Detail:" << endl;

	while (true)
	{
		// User input (product number to look for).
		cout << "\n\t\t   Enter Product Number (or 'Q' to Quit): ";
		getline(cin, itemNumber);
		// If itemNumber = Q, only Q with no extra characters including space char quit.
		if (toupper(itemNumber[0]) == 'Q' && itemNumber.length() == 1) break;

		// This for loop prints, finds inventory item in vector and lets us edit it.
		for (unsigned int i = 0; i < theData.size(); i++)
		{
			if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
			{
				cout << "\t\t1             P/N: " << theData[i].itemNumber
					<< "\n\t\t2     DESCRIPTION: " << theData[i].itemDescription
					<< "\n\t\t3        QUANTITY: " << theData[i].itemQuantity
					<< "\n\t\t4           PRICE: " << theData[i].itemPrice
					<< "\n\t\t5         TAXABLE: " << theData[i].itemTaxable 
					<< "\n\t\t6 <-------[CANCEL] " << endl << endl;

				// User input section.
				cout << "\t\t\t\t\tPlease Choose an Option to Edit by Number: ";
				cin >> userOption; 

				//  This while loop makes sure user enters a valid option that is not gibberish letter/s (only 1 to 5).
				while (cin.fail() || (userOption < 1 || userOption > 6))
				{
					cout << "\t\t\t\t\tPlease enter a valid option (1 to 6): ";
					// next 2 lines clear and ignore gibberish before next input.
					cin.clear();
					cin.ignore(1000, '\n');

					cin >> userOption;
				}
				// Function takes new user edited input, then file updated.
				editInventoryItemInput(userOption, i);
				updateFile();
				cout << "\n\t\t------------------------------------------------------------------------------------";

				found = 1;
				break;
			}
		} // End of for loop

		// If vector empty or nothing found print no item found.
		if (theData.size() < 1 || found == 0) { cout << "\t\t   --- No Items Found ---\n\n"; }
		found = 0;
	} // End of outer while loop

	// Returns to Main Menu if user quits.
	system("CLS");   cout << "\n\tLoading Main Menu...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();
}

// This function definition deletes an item's record, then updates the file.
void deleteInventoryItem()
{
	string itemNumber;   // Holds user input item to search for.
	int found = 0;       // Use to tell us if item searched is found.
	char deleteYesOrNo;  // Use to hold user deletation confirmation option.

	cout << SCREEN_HEADER;
	cout << "\n\t\tDelete Enventory Item:" << endl;

	while (true)
	{
		// User input (product number).
		cout << "\n\t\t   Enter Product Number (or 'Q' to Quit): ";
		getline(cin, itemNumber);
		// If itemNumber = Q, only Q with no extra characters including space char quit.
		if (toupper(itemNumber[0]) == 'Q' && itemNumber.length() == 1) break;

		// This for loop deletes item from inventory vector, then overwrites the .csv file.
		for (unsigned int i = 0; i < theData.size(); i++)
		{
			if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
			{
				cout << "\t\t             P/N: " << theData[i].itemNumber
					<< "\n\t\t     DESCRIPTION: " << theData[i].itemDescription
					<< "\n\t\t        QUANTITY: " << theData[i].itemQuantity
					<< "\n\t\t           PRICE: " << theData[i].itemPrice
					<< "\n\t\t         TAXABLE: " << theData[i].itemTaxable << endl << endl;

				// Ask user if they really want to perform this action.
				cout << "\t\t   Are you sure you want to delete -[ " << toupperAll(itemNumber) << " ]- (Y/n)? ";
				cin >> deleteYesOrNo;
				deleteYesOrNo = toupper(deleteYesOrNo); // Make user input uppercase.

				//  This while loop makes sure user enters a valid option Y/n.
				while (deleteYesOrNo != 'Y' && deleteYesOrNo != 'N')
				{
					cout << "\t\t\t\t       Please Enter Y or N: ";
					cin.clear();
					cin.ignore(1000, '\n');

					cin >> deleteYesOrNo;
					deleteYesOrNo = toupper(deleteYesOrNo);
				}
				cin.clear(); 
				cin.ignore(1000, '\n');

				if (deleteYesOrNo == 'Y')
				{
					theData.erase(theData.begin() + i); // Erease array element.				
					updateFile();
				}

				found = 1;
				break;
			}
		}

		// If vector empty or nothing found print no item found.
		if (theData.size() < 1 || found == 0) { cout << "\t\t   --- No Items Found ---\n\n"; }
		found = 0;
	}

	// Returns to Main Menu if user quits.
	system("CLS");   cout << "\n\tLoading Main Menu...";   Sleep(SLEEP_TIME);   system("CLS");   inventoryEditorScreen();
}

// This function definition deals with taking user input to edit vector data (Takes the user option and item index).
void editInventoryItemInput(int theOption, int index)
{
	// Variables to get user input.
	string itemNumber;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	char itemTaxable;
	int itemAlreadyExist = 0;

	// Switch case that allow us to give elements in vector new edited values.
	switch (theOption)
	{
	case 1: //__________________________________________________________________Case 1
		cin.clear();
		cin.ignore(1000, '\n');
		do
		{
			itemAlreadyExist = 0;

			cout << "\n\t\t   Enter New Product Number: ";
			getline(cin, itemNumber);

			// while loop makes sure user enters a  valid string (not empty or spaces)
			while (itemNumber.find_first_not_of(' ') == itemNumber.npos)
			{
				cout << "\t\t   Enter New Product Number: ";
				getline(cin, itemNumber);
			}

			// This for loop checks if item is already in inventory.
			for (unsigned int i = 0; i < theData.size(); i++)
			{
				if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
				{
					cout << "\t\t   This item name already exist, try another name.\n";
					itemAlreadyExist = 1;
					break;
				}
			}
		} while (itemAlreadyExist == 1);
		theData[index].itemNumber = itemNumber; break;
	case 2: //__________________________________________________________________Case 2
		cout << "\n\t\t   Enter New Item Description: ";
		cin.clear();
		cin.ignore(1000, '\n');
		getline(cin, itemDescription);
		theData[index].itemDescription = itemDescription; break;
	case 3: //__________________________________________________________________Case 3
		cout << "\n\t\t   Enter Item's New Quantity as a Number: ";
		cin >> itemQuantity;
		// This while loop makes sure user enters a valid option that is not gibberish letter/s or < 0.
		while (cin.fail() || itemQuantity < 0)
		{
			cout << "\t\t  Please Enter Quantity as a Number >= 0: ";
			cin.clear();
			cin.ignore(1000, '\n');

			cin >> itemQuantity;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		theData[index].itemQuantity = itemQuantity; break;
	case 4: //__________________________________________________________________Case 4
		cout << "\n\t\t   Enter New Item Cost: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> itemPrice;
		// This while loop makes sure user enters a valid option that is not gibberish letter/s or < 0.
		while (cin.fail() || itemPrice < 0)
		{
			cout << "\t    Cost must be a Number >= 0: ";
			cin.clear();
			cin.ignore(1000, '\n');

			cin >> itemPrice;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		theData[index].itemPrice = itemPrice; break;
	case 5: //__________________________________________________________________Case 5
		cout << "\n\t\t   Is Item Taxable (Y/n)? ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> itemTaxable;
		itemTaxable = toupper(itemTaxable); // Make user input uppercase.

											//  This while loop makes sure user enters a valid option Y/n.
		while (itemTaxable != 'Y' && itemTaxable != 'N')
		{
			cout << "\t\t   Please Enter Y or N: ";
			cin.clear();
			cin.ignore(1000, '\n');

			cin >> itemTaxable;
			itemTaxable = toupper(itemTaxable);
		}
		cin.clear();
		cin.ignore(1000, '\n');
		theData[index].itemTaxable = itemTaxable; break;
	case 6: //__________________________________________________________________Case 6
		cin.clear();
		cin.ignore(1000, '\n');
		break; 
	default: system("CLS"); cout << "\n\tInvalid Option\n\n"; break;
	}
}

// This function updates the file to match the vector inventory items when call.
void updateFile()
{
	// Overwriting file with new data, but 1st make sure file is open to be written to.
	ofstream theFile(CSV_FILENAME);
	if (theFile.is_open())
	{
		for (unsigned int k = 0; k < theData.size(); k++)
		{
			// Writing array data to file
			theFile << theData[k].itemNumber << "," <<
				theData[k].itemDescription << "," <<
				theData[k].itemQuantity << "," <<
				theData[k].itemPrice << "," <<
				theData[k].itemTaxable << "\n";
		}
		theFile.close();

		populateVector(); // Update Vector data from file (not really needed, only for extra "consistency checks").

		cout << "\n\t\t\t\t\t*** Inventory Updated Successfully! ***" << endl;

	}
	else
	{
		cout << "\n\t\t\t\t\t--- ERROR opening file ---";
		Sleep(ERROR_TIME);
	}
}

// Function definition that allows sales of an item, prints invoice to the screen and modifies the inventory to reflect the sale.
void invoice()
{
	cout << SCREEN_HEADER;
	cout << "\n\t\tInvoice:" << endl;

	vector<InventoryData> invoiceData;
	string itemNumber;                                   // Holds user input item to search for.
	int found = 0;                                       // Use to tell us if item searched is found.
	int index = 0;                                       // This is to keep track of where to add element to local vector.
	double total = 0, taxAmount = 0, itemTotal = 0;      // Vars hold the total prices of the invoce amounts.

	while (true)
	{
		int inStock = 0;                                  // This var is used to tell us if something is not in stock.

		// User input (product number).
		cout << "\n\t\t   Enter Product Number (or 'Q' to Quit or P to Process Invoice): ";
		getline(cin, itemNumber);

		// If itemNumber = Q, only Q with no extra characters including space char quit and re-populate vector from file.
		if (toupper(itemNumber[0]) == 'Q' && itemNumber.length())
		{
			populateVector();
			break;
		}
		// If itemNumber = P, only P with no extra characters including space char quit and update file from vector data.
		if (toupper(itemNumber[0]) == 'P' && itemNumber.length() == 1)
		{
			cout << "\n\t\t\t\t\t*** I N V O I C E    P R O C E S S E D! ***" << endl;
			updateFile();
			Sleep(5000);
			break;
		}

		// This for loop prints inventory item in vector.
		for (unsigned int i = 0; i < theData.size(); i++)
		{
			if (toupperAll(theData[i].itemNumber) == toupperAll(itemNumber))
			{
				system("CLS");
				cout << SCREEN_HEADER;
				cout << "\n\t\tInvoice:" << endl;

				// Formatted header for easy data reading when displayed.
				cout << "\n" << setw(60) << "P/N |" << setw(15) << "PRICE |" << setw(15) << "TAX |" << endl;
				cout << setw(90) << right << "--------------------------------------------" << endl;

				if (theData[i].itemQuantity > 0)  // If item quantity is > 0, then add it, else it's considered as if not found.
				{
					//Add a new element to vector:
					invoiceData.push_back(InventoryData());
					// Adding invoice data to local vector (invoiceData).
					invoiceData[index].itemNumber = theData[i].itemNumber;
					invoiceData[index].itemQuantity = theData[i].itemQuantity;
					theData[i].itemQuantity -= 1; // Remove item from theData vector.
					invoiceData[index].itemPrice = theData[i].itemPrice;
					invoiceData[index].itemTaxable = theData[i].itemTaxable;

					index++;
					inStock = 1;
				}

				// Print new invoice vector data to screen.
				for (unsigned int j = 0; j < invoiceData.size(); j++)
				{
					// If item taxable calculate tax, else tax = 0;
					if (invoiceData[j].itemTaxable == 'Y') { taxAmount = (TAX_PERCENTAGE * invoiceData[j].itemPrice); }
					else taxAmount = 0;
					// Print invoice item to screen.
					cout << setw(45) << j + 1 << "|" << setw(12) << invoiceData[j].itemNumber
													 << setw(15) << invoiceData[j].itemPrice
													 << setw(15) << taxAmount << endl;

					itemTotal = taxAmount + invoiceData[j].itemPrice; // Calculate item total (tax + price).
				}
				// If an item is out of stock print message to screen.
				if (inStock == 0) { cout << "\n" << setw(58) << itemNumber << "  <----------No Longer in Stock\n"; }
				if (inStock != 0) { total += itemTotal; } // Calculate invoice total if a new found item added.
				cout << setw(90) << right << "____________________________________________" << endl;
				cout << setw(90) << right << "--------------------------------------------" << endl;
				cout << setw(60) << "TOTAL |" << setw(28) << total << endl;

				found = 1;
			}
		} // End of outer for loop.

		// If nothing found print no item found.
		if (found == 0) { cout << "\t\t   --- No Items Found ---\n"; }
		found = 0;
	} // End of while loop
	invoiceData.clear(); // Clear vector so it's ready for next invoice.

	// Returns to Main Menu if user quits.
	system("CLS");   cout << "\n\tLoading Main Menu...";   Sleep(SLEEP_TIME);   system("CLS");   mainScreen();
}

// Function definition that turn a string to all UPPERCASE for easier not case-sensitive comparing.
string toupperAll(string theString)
{
	string newString; // This variable will hold the new string all uppercase value.

	for (unsigned int i = 0; i < theString.length(); i++)
	{
		newString += toupper(theString[i]);
	}

	return newString;
}