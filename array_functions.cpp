/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

#include "array_functions.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "utilities.h"
//============================================================================

//============================================================================
//	stuff you will need
using namespace std;
using namespace constants;
//============================================================================
//TODO define a structure to track words and number of times they occur
typedef struct Entry
{
        string word;
        int number_of_occurences;
        Entry(string wo = "", int occ = 0)
        {
            word = wo;
            number_of_occurences = occ;
        }
}
Entry;

//TODO add a global array of entry structs (global to this file)
struct Entry myEntryArray[MAX_WORDS];

//TODO add variable to keep track of next available slot in array
int next_available_slot = 0;

//TODO define all functions in header file

void clearArray(){

    for (int i = 0; i < getArraySize(); i++){
        myEntryArray[i].word = "";
        myEntryArray[i].number_of_occurences = 0;
    }
    next_available_slot = 0;
}

int getArraySize(){
    return next_available_slot;
}


std::string getArrayWordAt(int i){
    return myEntryArray[i].word;
}

int getArrayWord_NumbOccur_At(int i){
    return myEntryArray[i].number_of_occurences;
}


bool processFile(std::fstream &myfstream){

    if (myfstream.is_open()){
        string line;

        while (!myfstream.eof()){
            getline(myfstream, line);
            processLine(line);
        }
        closeFile(myfstream);
        return true;
    }
    else
    {
        return false;
    }
}

void extractTokensFromLine(std::string &myString){

    stringstream ss(myString);
    string temp_token;
    while (getline(ss, temp_token, CHAR_TO_SEARCH_FOR)){
        processToken(temp_token);
    }
}

void printArray(){
    cout << next_available_slot << endl;
}


void processLine(std::string &myString){
    extractTokensFromLine(myString);
}

void processToken(std::string &token){

    if (strip_unwanted_chars(token)){
        string temp = token;

        toUpper(temp);
        bool is_in_array = false;

        for (int i = 0; i < getArraySize(); i++){

        	string test_two = myEntryArray[i].word;
            toUpper(test_two);

            if (temp == test_two){
                myEntryArray[i].number_of_occurences++;
                is_in_array = true;
            }
        }
        if (!is_in_array){
            myEntryArray[next_available_slot].word = token;
            myEntryArray[next_available_slot].number_of_occurences++;
            next_available_slot++;
        }
    }
}


bool openFile(std::fstream &myfile, const std::string &myFileName, std::ios_base::openmode mode){
    myfile.open(myFileName.c_str(), mode);
    return myfile.is_open();
}


void closeFile(std::fstream &myfile){
    if (myfile.is_open()){
        myfile.close();
    }
}


int writeArraytoFile(const std::string &outputfilename){

	if (getArraySize() == 0){
        return FAIL_NO_ARRAY_DATA;
    }

    fstream tst;
    tst.open(outputfilename.c_str(), ios::out);
    if (!tst.is_open()){

        return FAIL_FILE_DID_NOT_OPEN;
    }
    else {
        for (int i = 0; i < getArraySize(); i++){
            tst << myEntryArray[i].word << " " << myEntryArray[i].number_of_occurences << endl;
        }

        tst.close();
        return SUCCESS;
    }
}

void sortArray(constants::sortOrder so){
    switch (so)
    {
    case NONE:
        break;
    case ASCENDING:
        for (int i = 0; i < getArraySize(); i++){
            for (int j = 1; j < getArraySize() - i; j++){

                string temp = myEntryArray[j].word;
                toUpper(temp);
                string second_temp = myEntryArray[j - 1].word;
                toUpper(second_temp);

                if (second_temp > temp){
                    swap(myEntryArray[j - 1], myEntryArray[j]);
                }
            }
        }
        break;
    case DESCENDING:
        break;

    case NUMBER_OCCURRENCES:
        break;
    }
}
