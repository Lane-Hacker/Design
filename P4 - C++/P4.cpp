/* @Author: Patrick Manacorda
 * @Date: Nov 13th 2019
 * @See: Seattle University Fall Quarter
 */
/*########### PROGRAM OVERVIEW ##############
 * This drivers aims at demonstrating the different functionality
 * of the intDiv and rangeDiv type operators.
 * STEP 1) Select which type should be tested
 * STEP 2) Random distribution of desired type is generated & intialized
 * STEP 3) Several operations are printed to screen to showcase functionality
 * Note: not ALL implemented operators are used to showcase functionality
 *
 *
 * Assumptions: none, div and range values are random at runtime
 */

#include "intDiv.h"
#include "rangeDiv.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAX_OBJECTS = 5;
const int MAX_DIV = 99;
const int MAX_RANGE = 5;
const int MAX_LEN = 5;
int menu();
void test_intDiv();
void test_rangeDiv();
void div_mathematical(intDiv* utility, int size);
void range_mathematical(rangeDiv* utility, int size);
void printDiv(intDiv* utility, int size);
void printRange(rangeDiv* utility, int size);

int main(){
  srand(time(NULL));
  bool done = false;
  do{
    switch(menu()){
    case 1:
      test_intDiv();
      break;
    case 2:
      test_rangeDiv();
      break;
    default:
      done = true;
      break;
    }
  }while(!done);
}

int menu(){
  cout << "Please select which type should be tested. " <<endl;
  cout << "------------------------------------------" <<endl;
  cout << "1. intDiv " << endl;
  cout << "2. rangeDiv " << endl;
  cout << "other. Quit " << endl;
  cout << "------------------------------------------" << endl;
  int a; cin >> a; return a;
}

void test_intDiv(){
  int num = rand()%MAX_OBJECTS+1;
  if(num==1) num=2;
  intDiv* utility = new intDiv[num];
  for(int i=0; i<num; i++){
    unsigned int value = rand()%MAX_DIV + 1;
    utility[i] = intDiv(value);
  }
  printDiv(utility, num);
  div_mathematical(utility, num);
  delete[] utility;
}

void test_rangeDiv(){
  int num = rand()%MAX_OBJECTS+1;
  if(num==1) num=2;
  rangeDiv* utility = new rangeDiv[num];
  for(int i=0; i<num; i++){
    int value = rand()%MAX_LEN + 1;
    if(value <= 1) value = MAX_LEN;
    rangeDiv other(value);
    utility[i] = other;
  }
  printRange(utility, num);
  range_mathematical(utility, num);
  delete[] utility;
}                                               \

void div_mathematical(intDiv* utility, int size){
  for(int i=0; i<size-1; i++){
    cout << "DIV " << i+1 << " + " << "DIV " << i+2 << " = ";
    intDiv temp = utility[i]+utility[i+1];
    temp.operator<<(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "DIV " << i+1 << " - " << "DIV " << i+2 << " = ";
    intDiv temp = utility[i]-utility[i+1];
    temp.operator<<(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "DIV " << i+1 << " * " << "DIV " << i+2 << " = ";
    intDiv temp = utility[i]*utility[i+1];
    temp.operator<<(cout);
  }
  for(int i=0; i<size-1; i++){
   cout << "DIV " << i+1 << " / " << "DIV " << i+2 << " = ";
    intDiv temp = utility[i]/utility[i+1];
    temp.operator<<(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "DIV " << i+1 << " % " << "DIV " << i+2 << " = ";
    intDiv temp = utility[i]%utility[i+1];
    temp.operator<<(cout);
  }
  for(int i=0; i<size; i++){
    cout << "DIV " << i+1 << "++ = ";
    utility[i]++;
    utility[i].operator<<(cout);
  }
  for(int i=0; i<size; i++){
    cout << "DIV " << i+1 << "-- = ";
    utility[i]--;
    utility[i].operator<<(cout);
  }
  
  
}
void range_mathematical(rangeDiv* utility, int size){
  for(int i=0; i<size-1; i++){
    cout << "RANGE " << i+1 << " + " << "RANGE " << i+2 << " = ";
    rangeDiv temp = utility[i]+utility[i+1];
    temp.printRange(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "RANGE " << i+1 << " - " << "RANGE " << i+2 << " = ";
    rangeDiv temp = utility[i]-utility[i+1];
    temp.printRange(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "RANGE " << i+1 << " * RANGE " << i+2 << " = ";
    rangeDiv temp = utility[i]*utility[i+1];
    temp.printRange(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "RANGE " << i+1 << " / RANGE " << i+2 << " = ";
    rangeDiv temp = utility[i]/utility[i+1];
    temp.printRange(cout);
  }
  for(int i=0; i<size-1; i++){
    cout << "RANGE " << i+1 << " % RANGE " << i+2 << " = ";
    rangeDiv temp = utility[i]%utility[i+1];
    temp.printRange(cout);
  }
  for(int i=0; i<size; i++){
    cout << "RANGE " << i+1 << "++ = ";
    utility[i]++;
    utility[i].printRange(cout);
  }
  for(int i=0; i<size; i++){
    cout << "RANGE " << i+1 << "-- = ";
    utility[i]--;
    utility[i].printRange(cout);
  }
  
}
void printDiv(intDiv* utility, int size){
  for(int i=0; i<size; i++){
    cout << "Div " << i+1 << " : ";
    utility[i].operator<<(cout);
  }
}
void printRange(rangeDiv* utility, int size){
  for(int i=0; i<size; i++){
    cout << "Range " << i+1 << " : ";
    utility[i].printRange(cout);
  }
}
