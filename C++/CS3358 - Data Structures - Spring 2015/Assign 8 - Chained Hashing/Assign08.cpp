// File: Assign08.cpp
//       A simple interactive test program that looks up a state abbreviation
//       from a table containing the abbreviations of the 50 U.S. states.

#include <iostream>
#include <algorithm>
#include <string>
#include "StrTab.h"
using namespace std;

string getLine(const string& prompt = "");
// Reads a line of text from cin and returns that line as a string.
// The newline character that terminates the input is not stored as
// part of the return value. If supplied, the optional prompt string
// is printed before reading the value.

void getLine(const string& prompt, string& out);
// Overloaded version of getLine that accepts a prompt and fills a
// given output (reference) string variable with its result.

void loadStateTab(StrTab& stateTab);
// Initializes the table so that it contains the two-letter abbreviations
// for the 50 states.

int main()
{
   StrTab stateTab;
   loadStateTab(stateTab);
   while (true)
   {
      string code = getLine("Enter 2-letter state code (0-letter to quit): ");
      if (code == "") break;
      if (code.length() > 2 ) code.erase(2, string::npos);
      transform(code.begin(), code.end(), code.begin(), ::toupper);
      string name = stateTab.get(code);
      if (name == "")
         cout << code << " is not a valid abbreviation" << endl;
      else
         cout << code << " = " << stateTab.get(code) << endl;
   }
   return 0;
}

string getLine(const string& prompt)
{
    string line;
    getLine(prompt, line);
    return line;
}

void getLine(const string& prompt, string& out)
{
    string promptCopy = prompt;
    if (!promptCopy.empty() && !isspace(promptCopy[promptCopy.length() - 1]))
       promptCopy += ' ';
    cout << promptCopy;
    getline(cin, out);
}

void loadStateTab(StrTab& table)
{
   table.put("AK", "Alaska");
   table.put("AL", "Alabama");
   table.put("AR", "Arkansas");
   table.put("AZ", "Arizona");
   table.put("CA", "California");
   table.put("CO", "Colorado");
   table.put("CT", "Connecticut");
   table.put("DE", "Delaware");
   table.put("FL", "Florida");
   table.put("GA", "Georgia");
   table.put("HI", "Hawaii");
   table.put("IA", "Iowa");
   table.put("ID", "Idaho");
   table.put("IL", "Illinois");
   table.put("IN", "Indiana");
   table.put("KS", "Kansas");
   table.put("KY", "Kentucky");
   table.put("LA", "Louisiana");
   table.put("MA", "Massachusetts");
   table.put("MD", "Maryland");
   table.put("ME", "Maine");
   table.put("MI", "Michigan");
   table.put("MN", "Minnesota");
   table.put("MO", "Missouri");
   table.put("MS", "Mississippi");
   table.put("MT", "Montana");
   table.put("NC", "North Carolina");
   table.put("ND", "North Dakota");
   table.put("NE", "Nebraska");
   table.put("NH", "New Hampshire");
   table.put("NJ", "New Jersey");
   table.put("NM", "New Mexico");
   table.put("NV", "Nevada");
   table.put("NY", "New York");
   table.put("OH", "Ohio");
   table.put("OK", "Oklahoma");
   table.put("OR", "Oregon");
   table.put("PA", "Pennsylvania");
   table.put("RI", "Rhode Island");
   table.put("SC", "South Carolina");
   table.put("SD", "South Dakota");
   table.put("TN", "Tennessee");
   table.put("TX", "Texas");
   table.put("UT", "Utah");
   table.put("VA", "Virginia");
   table.put("VT", "Vermont");
   table.put("WA", "Washington");
   table.put("WI", "Wisconsin");
   table.put("WV", "West Virginia");
   table.put("WY", "Wyoming");
}
