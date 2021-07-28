/*
* @Author: Patrick Manacorda
* @Date: October 14th 2019
*/

#include "rangeDiv.h"
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


/* ##### Implementation Invariants: #######
 * -Private Storage:
 *   -Array of intDiv Objects   -> Holds the range of intDiv objects
 *   -Size of range             -> Must be specified in constructor, otherwise set to DEFAULT_RANGE
 *   -Array of number of evenly divisible tests -> parallel array to intDiv array, stores how many test values evenly divide that intDiv index
 *   -State  -> Object may be enabled or disabled

 * -Private Utility functions:
 *   -rangeDiv::State::activate(), deactivate() -> used to toggle object state
 *   -rangeDiv::countFunction(<int>@param) - returns number of range intDiv object that have no remainder when divided by @param
 *   -rangeDiv::getPrime() - return a prime number between 3 <smallest prime> and MAX_PRIME
 * Dependencies:
 *   -intDiv type dependency
 */

rangeDiv::rangeDiv(int size){
  if(size <= 0)
    throw std::invalid_argument("Size cannot be zero or negative");
  this->state.activate();
  this->range_size = size;
  this->range = new intDiv[size];
  this->parallel_even = new int[size];
  for(int i=0; i<size; i++){
    intDiv temp(this->getPrime());
    range[i] = temp;
    parallel_even[i] = 0;
  }
}

rangeDiv::rangeDiv(const rangeDiv& other){
  this->copyOther(other);
}

rangeDiv::rangeDiv(rangeDiv&& other){
  this->range = other.range;
  this->parallel_even = other.parallel_even;
  other.clear();
  this->range_size = other.range_size;
  this->state.active = other.state.active;
}

rangeDiv& rangeDiv::operator=(rangeDiv&& other){
  if(this != &other){
    this->clear();
    this->range = other.range;
    this->parallel_even = other.parallel_even;
    other.clear();
    this->state.active = other.state.active;
  }
  return *this;
}

void rangeDiv::clear(){
  delete[] this->range;
  delete[] this->parallel_even;
}

void rangeDiv::copyOther(const rangeDiv& other){
  this->range = new intDiv[other.range_size];
  this->parallel_even = new int[other.range_size];
  this->range_size = other.range_size;
  for(int i=0; i<range_size; i++){
    this->range[i] = other.range[i];
    this->parallel_even[i] = other.parallel_even[i];
  }
  this->state.active = other.state.active;
}
rangeDiv& rangeDiv::operator=(const rangeDiv& other){
  if(this != &other){
    this->clear();
    this->copyOther(other);
  }
  return *this;
}

bool rangeDiv::getActive(){
  return this->state.active;
}

void rangeDiv::printRange(std::ostream& out){
  out << "[Active: " << this->getActive() << " ";
  for(int i=0; i<range_size; i++){
    out << " { div: " << range[i].getDiv() << " } ";
    if(i+1 != range_size)
      out << " - ";
  }
  out << std::endl;

}
int rangeDiv::getPrime(){
  int guess;
  bool found = false;
  while(!found){
    guess = rand()%MAX_PRIME;
    found = true;
    while(guess < MIN_PRIME)
      guess++;
    for(int i=MIN_PRIME-1; i<=guess/2; i++){
      if(guess%i == 0){
        found = false;
        break;
      }
    }
  }
  return guess;
}

void rangeDiv::rangeDivState::activate(){
  active = true;
}
void rangeDiv::rangeDivState::deactivate(){
  active = false;
}

void rangeDiv::toggle(){
  if(this->getActive())
    this->state.deactivate();
  else
    this->state.activate();
}

int rangeDiv::countFunction(int param){
  if(param <= 0)
    return ERROR_CODE_ONE;
  else if(!getActive()){
    return ERROR_CODE_TWO;
  }
  int count = 0;
  for(int i=0; i<range_size; i++){
    // cout << "Object " << i+1 << " with div " << range[i].getDiv() << " % " << param << " = " << range[i].test(param) << endl;
    if(range[i].test(param) == 0){
      count++;
      parallel_even[i]++;
    }
  }
  return count;
}

int rangeDiv::testOne(int param){
  return countFunction(param);
}

int rangeDiv::testTwo(int param){
  if(getActive()){
    return range_size-countFunction(param);
  }else{
    return ERROR_CODE_TWO;
  }
}

int rangeDiv::testThree(){
  if(!getActive())
    return ERROR_CODE_TWO;
  
  int max_i = 0;
  for(int i=0; i<range_size; i++)
    if(parallel_even[i] > parallel_even[max_i])
      max_i = i;
  return parallel_even[max_i];
}

rangeDiv::~rangeDiv(){
  delete[] range;
  delete[] parallel_even;
}
