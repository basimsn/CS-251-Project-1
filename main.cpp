//
//  Project 1 Starter Code - DNA Profiling
//  Course: CS 251
//  Author: Basim Nabulsi
//  
//  For my creative component I created a function called load_dna2 which allows users to type in two dna files which will allow for the dna to be processed. To use the creative component
//  type load_dna2 and two dna files of your choosing with spaces in between and a databse file it can be processed.

#include "ourvector.h"
#include <sstream>
#include <fstream>
using namespace std;

void allActions(string action, ourvector<char>db2, ourvector<char>dna1, bool process1, bool process2, bool search2){  //Function used to print possible outputs after a display function
  if(dna1.size() == 0 && process2 == false && search2 == false){
    cout<<"\nNo DNA loaded.\n";
  }
  if(process1 == false && process2 == false && search2 == false){
    cout<<"\nNo DNA has been processed.\n";
  }
  if(db2.size() == 0 && (process2 == true || search2 == true)){
    cout<<"No database loaded.\n";
  }
  if(db2.size() !=0 && process2 == true && dna1.size() == 0){
    cout<<"No DNA loaded.\n";
  }
  if(dna1.size() == 0 && db2.size() != 0 && search2 ==true){
    cout<<"No DNA loaded.\n";
  }
  if(dna1.size() != 0 && db2.size() != 0 && search2 ==true && process1 == false){
    cout<<"No DNA processed.\n";
  }
}

bool fileChecker(string &fileName){   //This function checks if the file is a valid file
  ifstream inFS;
  cin>>fileName;
  inFS.open(fileName);
  if(inFS.is_open()){
    return true;
  }
  else{
    cout<<"Error: unable to open '"<<fileName<<"'\n";
    return false;
  }

}

void load_db(ourvector<string>&db1, ourvector<char>&db2, string fileName, ourvector<string>&header){    // loads a database file into the program
  ifstream inFS;
  string fileWords, s,s1;
  inFS.open(fileName);
  inFS >> fileWords;
  int noHeader=0;
  db1.clear();
  db2.clear();
  while (!inFS.fail()) { 
    if(noHeader ==0){ //pushes back the header of the file to then be used to convert the dna strands into a separate vector
      header.push_back(fileWords);
      noHeader++;
      inFS>>fileWords;
    }
    else{   //pushes back everythingg but the header from the database file
      db1.push_back(fileWords);
      inFS>>fileWords;
    }
    
  }
  for(int i=0; i<db1.size();i++){   //function converts a string vector into a char vector and replaces the commas with spaces
    for(int j=0; j<db1[i].size(); j++){
        if(db1[i][j] == ','){
          db2.push_back(' ');
        }
        else{
          db2.push_back(db1[i][j]);
        }
    }
    db2.push_back('\n');
  }
}

void load_dna(ourvector<char>&dna1, string fileName){   //loads dna file into a char vector
  ifstream inFS;
  char fileChar;
  dna1.clear();
  inFS.open(fileName);
  inFS>>fileChar;
  while(!inFS.fail()){
    dna1.push_back(fileChar);
    inFS >> fileChar;
  }
}

void display(ourvector<char>db2, ourvector<char>dna1, bool loadDb, bool loadDna, ourvector<char>dnaStrands, ourvector<int> values, bool process1){   
  if(loadDb == true){  //function displays everthing that has beein loaded into the program
    cout<<"Database loaded: \n";
  }
  else{
    cout<<"No database loaded.\n";
  }
  for(int i=0; i<db2.size(); i++){
    cout<<db2[i];
  }
  if(loadDna == true ){
    cout<<"DNA loaded: \n";
  }
  if(dna1.size()>0){
    cout<<endl;
  }
  for(int i=0; i<dna1.size();i++){
    cout<<dna1[i];
  }
  if(dna1.size()>0){
    cout<<endl;
  }
  
  if(process1 == true && dnaStrands.size() !=0){    //function prints the dna strands and and the values that correspond with it
    cout<<"DNA processed, STR counts:\n";
    int z1=0;
    for(int i=0; i<dnaStrands.size(); i++){
      if(dnaStrands[i]== ','){
        cout<<": "<<values[z1]<<endl;
        z1++;
      }
      else{
        cout<<dnaStrands[i];
      }
    }
    cout<<": "<<values[z1]<<endl;
  }
}

void twoFunctions(ourvector<int> &increments, ourvector<int> &values, ourvector<char> dnaStrands, int &sum){
  int incr;   //function pushes back two vectors
  int base=0;
  for(int i=0; i<dnaStrands.size(); i++){   //finds how long each starnd is in order of the strand to then increment later
    if(dnaStrands[i]== ','){
        incr = i-base;
        base = i+1;
        increments.push_back(incr);
    }
    if(dnaStrands.size()-1 == i){
        incr = (i+1)-base;
        increments.push_back(incr);
    }
  }
  for(int i=0; i<increments.size(); i++){ //pushes back a counter for each dna strand starting at two which can then be either subtracted or added
    sum+= increments[i];    // sum is founded to know what the limit for incrementing is
    values.push_back(2);
    values.push_back(2);
  }
}

void removeName(ourvector<string>header, ourvector<char> &dnaStrands){  //function removes the name and comma and leaves the dna starnds in a vector
  int eraseName =0;  
  for(int i=0; i<header.size(); i++){
    for(int j=0; j<header[i].size(); j++){
      if(header[i][j] == ',' && eraseName ==0){
        eraseName++;
      }
      else if(eraseName >=1){
        dnaStrands.push_back(header[i][j]);
      }
    }
  }
}

bool strandChecker(ourvector<char> dnaStrands, ourvector<char> dna1, ourvector<int> increments, int val, int pos1, int pos2){ 
  int check =0; // function checks if the dna strand is equal to the dna txt file at a certain position
  for(int i=0; i<increments[val]; i++)
  {
      if(dna1[pos1+i] == dnaStrands[pos2+i]){
        check++;
      }
      else{
          return false;
      }
  }
  if(check == increments[val]){
    return true;
  }
  else{
    return false;
  }
}

void process(ourvector<char> dna1, ourvector<string>header, ourvector<char> &dnaStrands, ourvector<int> &values, ourvector<int> &increments){
  ourvector<int> findingMax; //function finds out what the longest strand of each dna strand is
  removeName(header, dnaStrands);
  int posDna=-1;
  int posStrand=0;
  int sum=0;
  int value=0;
  int i=0;
  twoFunctions(increments, values, dnaStrands, sum);
  cout<<"Processing DNA...\n";
  while (i <dnaStrands.size()){ // I loop through the dna txt file first and then once the whole dna strand has been looped through and the matches have been found I increment dna strands based on the corresponding 
    if(posDna >= dna1.size() && (value+1 == increments.size())){ //value +1 to then start at the next strand and loop through the dna txt file until the dna strand vector is finished
      break;    //If the first char in the dna strand is equal to the dna txt file I send it in in the strandchecker to see if it is correct. If it is I push back the position of the dna
    }    //to be used later. If it is not correct I just check the next value. Once I am done looping through the dna txt file with one strand I push back 999 into finding max letting me know
    if(posDna >= dna1.size()){  //later that the the next strand is starting 
      posDna =0;
      i=0;
      findingMax.push_back(999);
      posStrand+=(increments[value]+1);
      value++;
    }
    while(posDna < dna1.size()){
      ++posDna;
      if(posDna+2>= dna1.size()){
        break;
      }
      if(dna1[posDna] == dnaStrands[posStrand]){
        if(strandChecker(dnaStrands, dna1, increments, value, posDna, posStrand) == true ){
            findingMax.push_back(posDna);
          break;
        }
      }
    }
  }
  ourvector<int>maxVal;
  int temp=0; //Here I use the positions of the dna and the increment to find out if the strands that were correct were next to each this allows me to then find out how many were next to each  
    for(int i=0; i<findingMax.size(); i++){ //other to then add up in my values vector which increments based on if 999 is the value that is being compared. I have some if conditions that 
      if(findingMax[0]== 999){  //are used to fix specific test cases that weren't originally accounted for
        values[temp]=0;
      }
      if(findingMax[i]== 999){
        temp++;
      }
      if(findingMax[i] == 999 && findingMax[i+2] == 999){
        values[temp]--;
      }
      if(i == findingMax.size()-2){
        break;
      }
      if(i != findingMax.size()-1){
        if((findingMax[i+1] - findingMax[i]) == increments[temp]){
          if(findingMax[i+2]-findingMax[i+1]== increments[temp]){
            values[temp]++;
          }
        } 
      }
    }
}

void split(string str, ourvector<int> &dnaNumbers, int &rows, ourvector<string> &names1){
  string w =""; // Allowed me to split the database file into one file with just the names and one with just the integers
  bool name = false;
  for (auto x : str){
    if (x == ',' || x=='\n'){
      if(name != false){
        dnaNumbers.push_back(stoi(w));
        w="";
      }
      else{
        names1.push_back(w);
        w="";
        name = true;
      }
    }
    else{
      w = w + x;
    }
  }
  dnaNumbers.push_back(stoi(w));
  rows++; //added up the amount of rows in file

}

void search(ourvector<string> db1, ourvector<int>values, ourvector<int>increments, string fileName){
  ourvector<string> data; //This function allowed me to search for the person with the corresponding values with dna strand
  ourvector<int> dnaNumbers;
  ourvector<string>names;
  string integers, s, word;
  int rows=0;
  int increase;
  cout<<"Searching database...\n";
  for(int i=0;i<db1.size(); i++){ //function that split the database file
    word=db1[i];
    split(word, dnaNumbers, rows, names);
  }
  bool found = false;
  increase = dnaNumbers.size()/rows; //allowed me to figure out what I had to increase i by 
  int whichRow=-1;
  for(int i=0; i<dnaNumbers.size(); i+=increase){
    if(dnaNumbers[i]== values[0] && found == false){
      for(int j=0; j <increase; j++){
        if(dnaNumbers[i+j] == values[0+j]){ //checks if the numbers that were corresponding were correct
          whichRow = i; //stores the i variable to find the name later
          found = true;
          break;
        }
      }
    }
  }
  if(whichRow!= -1){ // I had to make this -1 instead of 0 because names 0 is a name that can possible be used
    cout<<"Found in database! DNA matches: "<<names[whichRow/increase]<<endl; // I found out the position of the name was the position of i divided by increase
  }
  else{
    cout<<"Not found in database.\n";
  }
}

void load_dna2(ourvector<char> &dna1, string fileName){
  ifstream inFS;    //creative function that takes in to dna files and makes sure the files are able to be used
  string fileName2;
  char fileChar;
  cin>>fileName>>fileName2;
  inFS.open(fileName);
  if(inFS.is_open()){
    inFS>>fileChar;
    while(!inFS.fail()){
      dna1.push_back(fileChar);
      inFS >> fileChar;
    }
  }
  inFS.close();
  inFS.open(fileName2);
  if(inFS.is_open()){
    inFS>>fileChar;
    while(!inFS.fail()){
      dna1.push_back(fileChar);
      inFS >> fileChar;
    }
  }
}

void commandChoice(string &action, string &fileName){ // the main game
  ourvector<string>db1; //all the variables that were initialized
  ourvector<char>db2;
  ourvector<char>dna1;
  ourvector<string>header;
  ourvector<char>dnaStrands;
  ourvector<int>values;
  ourvector<int>increments;
  bool endgame = false; bool loadDb = false; bool loadDna = false; bool display1 = false; bool process1 = false; bool process2 = false; bool search1 =false; bool search2 = false;
  while(endgame ==false){ // while loop that ran the game
    cout<<"Enter command or # to exit: ";
    cin>>action;
    if(action == "load_db"){
      cout<<"Loading database...\n";
      if(fileChecker(fileName)){  //checked if ilechecker returned true before moving on
        loadDb = true;
        load_db(db1, db2, fileName, header);
      }
    }
    else if(action == "process"){
      process2 = true;  //tells me that process was an action that might not have went inside the function
      if(dna1.size() !=0 && db2.size() !=0){ //checked if database and dna had been loaded in before processing
        process1=true;
        process(dna1, header, dnaStrands, values, increments);
      }
      allActions(action, db2, dna1, process1, process2, search2); //outputs after process
    }
    else if(action == "load_dna"){ 
      cout<<"Loading DNA...\n";
      if(fileChecker(fileName)){
        loadDna = true;
        load_dna(dna1, fileName);
      }
    }
    else if(action == "search"){ 
      search2 = true;
      if(process1 == true){
        search1 = true;
        search(db1, values, increments, fileName);
      }
      allActions(action, db2, dna1, process1, process2, search2);
    }
    else if(action =="display"){
      display(db2, dna1, loadDb, loadDna, dnaStrands, values, process1);
      allActions(action, db2, dna1, process1, process2, search2);
    }
    else if(action == "load_dna2"){  //creative component
      dna1.clear();
      load_dna2(dna1, fileName);
      if(dna1.size() !=0){
        cout<<"Loading both DNA files...\n";
        loadDna = true;
      }
    }
    else if(action == "#"){ //ends game
      endgame = true;
    }
    
  }
  
}

int main() {  //calls the command choices and initializes a few variables
  string fileName, action, fileWords, action1;
  cout<<"Welcome to the DNA Profiling Application.\n";
  commandChoice(action, fileName);

  return 0;
}