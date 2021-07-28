/* @Author: Patrick Manacorda
 * @Date: 10/14/2019
 * @See: Seattle University CPSC3200
 */


/*  ######### PROGRAM OVERVIEW #############
 * This automated program aims at demonstrating the functionality of both the intDiv class and the rangeDiv class
 * It follows these logical steps:
 *   1)It displays a menu asking which functionality wants to be tested
 *   2)It automates the creation of a random distribution of intDiv or rangeDiv objects 
 *   3)The objects are then initialized to random values (determined at runtime)
 *   4)The objects are processes for a random number of iterations (between MIN_NUM_ITERATIONS and MAX_NUM_ITERATIONS)
 *   5)In case of rangeDiv objects, explicit deep copy functionality is also automatically demonstrated
 *   6)Objects and state changes are displayed to screen
 */

#include "intDiv.h"
#include "rangeDiv.h"
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <list>
using namespace std;

void initialize_objects(list<unique_ptr<intDiv>>& list);
void initialize_objects(list<unique_ptr<rangeDiv>>& list);
void process_objects(list<unique_ptr<intDiv>>& list);
void process_objects(list<unique_ptr<rangeDiv>>& list);
void display_objects(list<unique_ptr<intDiv>>& list);
void display_objects(list<unique_ptr<rangeDiv>>& list);
void showoff_copy_functionality(list<unique_ptr<rangeDiv>>& list);
void pass_by_value(rangeDiv copy, list<unique_ptr<rangeDiv>>& list);
void clear_console(){ cout << "\033c" << endl;}
int menu();
void intDivTest();
void rangeDivTest();

const int MAX_NUM_OBJECTS = 5;
const int MIN_NUM_OBJECTS = 2;
const int MAX_DIV_VALUE = 100;
const int MAX_NUM_ITERATIONS = 5;
const int MIN_NUM_ITERATIONS = 3;

int main(){
  bool testing = true;
  srand(time(NULL));
  while(testing){
    switch(menu()){
    case 1:
      intDivTest();
      break;
    case 2:
      rangeDivTest();
      break;
    case 3:
      testing = false;
      break;
    }
  }
  return 0;
}

int menu(){
  clear_console();
  cout << "Select functionality to be tested. " << endl
       << "----------------------------------"  << endl
       << "(1) intDiv " << endl
       << "(2) rangeDiv " << endl
       << "(3) Quit Program " << endl
       << "----------------------------------" << endl
       << "INPUT: ";
  int input;
  cin >> input;
  while(input<1 || input > 3){
    cout << "INVALID INPUT. " << endl;
    cout << ">INPUT: ";
    cin >> input;
  }
  return input;
}

void intDivTest(){
  clear_console();
  cout << "Running IntDivTest... " << endl;
  list<unique_ptr<intDiv>> list;
  initialize_objects(list);
  display_objects(list);
  process_objects(list);
}

void initialize_objects(list<unique_ptr<intDiv>>& list){
  int number_of_objects = rand() % MAX_NUM_OBJECTS;
  if(number_of_objects < MIN_NUM_OBJECTS)
    number_of_objects = MIN_NUM_OBJECTS;
  for(int i=0; i<number_of_objects; i++){
    unique_ptr<intDiv> div(new intDiv(rand() % MAX_DIV_VALUE));
    list.push_back(move(div));
  }
}
void initialize_objects(list<unique_ptr<rangeDiv>>& list){
  int number_of_objects = rand() & MAX_NUM_OBJECTS;
  if(number_of_objects < MIN_NUM_OBJECTS)
    number_of_objects = MIN_NUM_OBJECTS;
  for(int i=0; i<number_of_objects; i++){
    unique_ptr<rangeDiv> rangediv(new rangeDiv(number_of_objects));
    list.push_back(move(rangediv));
  }
}
void process_objects(list<unique_ptr<intDiv>>& list){
  int number_of_iterations = rand()%MAX_NUM_ITERATIONS;
  if(number_of_iterations < MIN_NUM_ITERATIONS)
    number_of_iterations = MIN_NUM_ITERATIONS;
  for(int i=0; i<number_of_iterations; i++){
    int count = 1;
    for(unique_ptr<intDiv> &ptr : list){
      int test_value = rand() % MAX_DIV_VALUE;
      cout << "--> Object"<<count<<".test("<<test_value<<") = "<<ptr->test(test_value)<<endl;
      count++;
    }
    int revive_index = rand() % list.size();
    display_objects(list);
    cout << "--> Object"<<revive_index+1<<".revive() " << endl;
    int counter = 0;
    for(unique_ptr<intDiv> &ptr : list){
      if(counter == revive_index){
        ptr->revive();
        break;
      }
      else{
        counter++;
      }
    }
    display_objects(list);
    if((i+1)%2 == 0){
      int reset_index = rand() % list.size();
      counter = 0;
      for(unique_ptr<intDiv> &ptr : list){
        if(counter == reset_index){
          ptr->reset();
          break;
        }else{
          counter++;
        }
      }
      cout << "Object"<<reset_index+1<<".reset()" << endl;
      display_objects(list);
    }
    cout << "Press any key to go to next iteration...";
    if(i==0)
      cin.ignore();
    getchar();
  }
}

void process_objects(list<unique_ptr<rangeDiv>>& list){
  int number_of_iterations = rand() % MAX_NUM_ITERATIONS;
  if(number_of_iterations < MIN_NUM_ITERATIONS)
    number_of_iterations = MIN_NUM_ITERATIONS;
  for(int i=0; i<number_of_iterations; i++){
    int object_count = 1;
    for(unique_ptr<rangeDiv> const &ptr : list){
      int testVal = rand() % MAX_DIV_VALUE;
      cout << "Object" << object_count << ".testOne("<< testVal <<") = " << ptr->testOne(testVal) << endl;
      testVal = rand() % MAX_DIV_VALUE;
      cout << "Object" << object_count << ".testTwo("<< testVal <<") = " << ptr->testTwo(testVal) << endl;
      cout << "Object" << object_count << ".testThree() = " << ptr->testThree() << endl;
      object_count++;
    }
    if( (i+1)%2 == 0){
      int deactivate_index = rand() % list.size();
      int counter = 0;
      for(unique_ptr<rangeDiv> &ptr : list){
        if(counter == deactivate_index){
          cout << "Object" << counter+1 << ".toggle()" << endl;
          ptr->toggle();
          break;
        }else{
          counter++;
        }
      }
    }
    display_objects(list);
    cout << "Press any key to go to next iteration... "<<endl;
    if(i == 0)
      cin.ignore();
    getchar();
  }
  clear_console();
}
void display_objects(list<unique_ptr<intDiv>>& list){
  int count = 1;
  for(unique_ptr<intDiv> const &ptr : list){
    cout << "intDiv Object " << count << " : { div : " << ptr->getDiv()
         << " | active : " << ptr->getActive()
         << " | disabled : " << ptr->getDeactivated() << " } " << endl;
    count++;
  }
}

void display_objects(list<unique_ptr<rangeDiv>>& list){
  int count = 1;
  for(unique_ptr<rangeDiv> const &ptr : list){
    cout << "Range Object " << count << " : ";
    ptr->printRange(std::cout);
    count++;
  }
}

void rangeDivTest(){
  clear_console();
  cout << "Initializing rangeDiv test... " << endl;
  list<unique_ptr<rangeDiv>> list;
  initialize_objects(list);
  display_objects(list);
  process_objects(list);
  showoff_copy_functionality(list);
}


void showoff_copy_functionality(list<unique_ptr<rangeDiv>>& list){
  int rand_index = rand() % list.size();
  int counter = 0;
  for(unique_ptr<rangeDiv>& ptr : list){
    if(counter == rand_index){
      cout << "Copying Object"<<counter+1<< " !" << endl;
      ptr->printRange(std::cout);
      pass_by_value(*ptr, list);
      break;
    }else{
      counter++;
    }
  }
  cout << "Displaying new set of rangeDiv Objects: " << endl;
  display_objects(list);
  cout << "Press any key to go back to menu... " << endl;
  getchar();
}

void pass_by_value(rangeDiv copy, list<unique_ptr<rangeDiv>>& list){
  cout << "Copied object result: " << endl;
  copy.printRange(std::cout);
  cout << "Modifying state of copy object: Object" << list.size()+1 <<".toggle() " << endl;
  copy.toggle();
  cout << "Adding copied rangeDiv object to set.. " << endl;
  unique_ptr<rangeDiv> ptr(new rangeDiv(copy));
  list.push_back(move(ptr));
}


/* ###### IMPLEMENTATION INVARIANT #############
 * 1) Driver uses STL container list<T>
 * 2) Driver uses unique_ptr<T>
 * 3) Number of iterations and object initalization values are randomized
 *    -> Note: this is intentional design for a testing driver that runs automatically
 * 4) This driver is supposed to run on a console emulator
 */
