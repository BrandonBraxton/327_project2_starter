/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: Brandon Braxton
 */

//============================================================================
//	 add necessary includes here
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
using namespace std;
using namespace constants;
//============================================================================

//============================================================================
//	stuff you will need

//============================================================================
/**
 * define a structure to track words and number of times they occur
*/

struct p2{
	string word;

	int numOcc;

	//string upper;
	//entry occ[];
};

/**
 * add a global array of entry structs (global to this file)
 */
p2 *wArray = new p2[MAX_WORDS];

/**
 * add variable to keep track of next available slot in array
 */
int nxt = 0;

// look in utilities.h for useful functions, particularly strip_unwanted_chars!

/**
 * how many unique words are in array
 */
int getArraySize(){

	return nxt;
}

/**
 * get data at a particular location
 */
std::string getArrayWordAt(int i){

	return wArray[i].word;
}

/**
 * get data at a particular location
 */
int getArrayWord_NumbOccur_At(int i){

	return wArray[i].numOcc;

}
/**
 * clear contents of array
 */
void clearArray(){

	for(int i = 0; i < getArraySize(); i++){

		wArray[i].word = ""; // clears words
		wArray[i].numOcc = 0; // clears numOcc

	}

	nxt = 0; // clears next element
}


/**
 * loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise
 */
bool processFile(std::fstream &myfstream){

	if (myfstream.is_open()){

		string aLine;

		while (!myfstream.eof()){
			getline(myfstream, aLine); //reads on line at a time
			processLine(aLine); //process line
		}

		return true;

	}

	return false;
}

/**
 * take 1 line and extract all the tokens from it
 * feed each token to processToken for recording
*/
void processLine(std::string &myString){

	stringstream ss(myString);
	string tmpTok;
	strip_unwanted_chars(tmpTok); // trying to fix CRLF

	while(getline(ss,tmpTok,CHAR_TO_SEARCH_FOR)){
		processToken(tmpTok);
	}
}

/*
 *Keep track of how many times each token seen*
 */
void processToken(std::string &token){

	strip_unwanted_chars(token);

	if (token == ""){
		return;
	}
	if (token == "\n"){
		return;
	}

	if (token == "\r"){

		return;
	}

		string tmp = token;
		toUpper(tmp);
		//tmp.toUpper();

		bool exist = false; //checking element exists in array are equal

		for (int i = 0; i < getArraySize(); i++){

			string tmp2 = wArray[i].word;

			toUpper(tmp2);

			if (tmp == tmp2){
				wArray[i].numOcc++;
				exist = true;
			}
		}

		if (!exist){
				wArray[nxt].word = token;
				wArray[nxt].numOcc++;
				nxt++;
			}
		}

/*
 * if you are debugging the file must be in the project parent directory
 * in this case Project2 with the .project and .cProject files
*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){

	myfile.open(myFileName,mode);

	if (myfile.is_open()){
		return true;
	}

	return false;

}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){

	if (myfile.is_open()){
		myfile.close();
	}
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){

	ofstream test;

	test.open(outputfilename);

	if (!test.is_open()){
		return FAIL_FILE_DID_NOT_OPEN;
	}

	if (getArraySize() == 0){
		return FAIL_NO_ARRAY_DATA;
	}

	else{
		for(int i = 0; i < getArraySize();i++){
			test << wArray[i].word << " " << wArray[i].numOcc << endl;
		}
	}

	return SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){

	switch(so){

	case NUMBER_OCCURRENCES:
		break;

	case NONE:
		break;
	case ASCENDING:

	for (int i = 0; i < getArraySize(); i++){

		for (int j = 0; j < getArraySize()-1; j++){

			string tmp1 = wArray[j].word;

			string tmp2 = wArray[j++].word;

			toUpper(tmp1);
			toUpper(tmp2);

			if (tmp1 > tmp2){
				//swap items
				swap(wArray[j], wArray[j+1]);
			}
		}
	}
		break;
	case DESCENDING:
		break;
	}
}
