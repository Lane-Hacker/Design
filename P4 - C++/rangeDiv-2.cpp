#include "rangeDiv.h"
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <cassert>
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
rangeDiv::rangeDiv(){
  int size = DEFAULT_RANGE_SIZE;
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
  other.range = 0;
  other.parallel_even = 0;
  this->range_size = other.range_size;
  this->state.active = other.state.active;
}

rangeDiv& rangeDiv::operator=(rangeDiv&& other){
  if(this != &other){
    std::swap(this->range, other.range);
    std::swap(this->parallel_even, other.parallel_even);
    std::swap(this->state, other.state);
  }
  return *this;
}

intDiv rangeDiv::operator[](int index){
  assert(index >= 0);
  assert(index < range_size);
	return this->range[index];
}

rangeDiv rangeDiv::operator+(rangeDiv& rhs){
	if(this->range_size > rhs.range_size){
      rangeDiv local(*this);
		for(int i=0; i<rhs.range_size; i++)
			local[i] += rhs[i];
		return local;
	}else{
		rangeDiv local(rhs);
		for(int i=0; i<this->range_size; i++)
			local[i] += this->range[i];
		return local;
	}
}

rangeDiv rangeDiv::operator+(int increment){
	rangeDiv local(*this);
	for(int i=0; i<range_size; i++)
		range[i] += increment;
	return local;
}

rangeDiv rangeDiv::operator-(int decrement){
	rangeDiv local(*this);
	for(int i=0; i<range_size; i++)
		range[i] -= decrement;
	return local;
}

rangeDiv& rangeDiv::operator++(){
  for(int i=0; i<range_size; i++)
    this->range[i]++;
  return *this;
}
rangeDiv rangeDiv::operator++(int i){
  rangeDiv copy(*this);
  for(int i=0; i<range_size; i++)
    this->range[i]++;
  return copy;
}
rangeDiv& rangeDiv::operator--(){
  for(int i=0; i<range_size; i++)
    this->range[i]--;
  return *this;
  
}
rangeDiv rangeDiv::operator--(int i){
  rangeDiv copy(*this);
  for(int i=0; i<range_size; i++)
    this->range[i]--;
  return copy;
  
}


rangeDiv rangeDiv::operator-(rangeDiv& rhs){
	if(this->range_size > rhs.range_size){
		rangeDiv local(*this);
		for(int i=0; i<rhs.range_size; i++)
			local[i] -= rhs[i];
		return local;
	}else{
		rangeDiv local(*this);
		for(int i=0; i<this->range_size; i++)
			local[i] -= rhs[i];
		return local;
	}
}

rangeDiv rangeDiv::operator*(rangeDiv& rhs){
  if(this->range_size > rhs.range_size){
    rangeDiv local(*this);
    for(int i=0; i<rhs.range_size; i++)
      local[i] *= rhs[i];
    return local;
  }else{
    rangeDiv local(*this);
    for(int i=0; i<this->range_size; i++)
      local[i] *= rhs[i];
    return local;
  }
}

rangeDiv rangeDiv::operator/(rangeDiv& rhs){
  if(this->range_size > rhs.range_size){
    rangeDiv local(*this);
    for(int i=0; i<rhs.range_size; i++)
      local[i] /= rhs[i];
    return local;
  }else{
    rangeDiv local(*this);
    for(int i=0; i<this->range_size; i++)
      local[i] /= rhs[i];
    return local;
  }  
}

rangeDiv rangeDiv::operator*(int val){
  rangeDiv local(*this);
  for(int i=0; i<range_size; i++)
    local[i] *= val;
  return local;
}

rangeDiv rangeDiv::operator/(int val){
  rangeDiv local(*this);
  for(int i=0; i<range_size; i++)
    local[i] /= val;
  return local;
}

rangeDiv& rangeDiv::operator+=(rangeDiv& rhs){
	for(int i=0; (i<this->range_size) && (i<rhs.range_size); i++)
		this->range[i] += rhs[i];
	return *this;
}

rangeDiv& rangeDiv::operator-=(rangeDiv& rhs){
	for(int i=0; (i<this->range_size) && (i<rhs.range_size); i++)
		this->range[i] -= rhs[i];
	return *this;
}

bool rangeDiv::operator!=(rangeDiv& other){
	if(other.range_size != range_size)
		return true;
	for(int i=0; i<range_size; i++)
		if(range[i] != other[i])
			return true;
	return false;
}

rangeDiv rangeDiv::operator%(rangeDiv& other){
  rangeDiv temp(*this);
  for(int i=0; i<range_size && i<other.range_size; i++)
    temp[i] %= other[i];
  return temp;
}

rangeDiv& rangeDiv::operator*=(const rangeDiv& other){
  int sum_rhs = 0, sum_lhs = 0;
  for(int i=0; i<range_size; i++)
    sum_rhs += this->range[i][i];
  for(int i=0; i<other.range_size; i++)
    sum_lhs += other.range[i][i];
  for(int i=0; i<range_size; i++)
    range[i] *= (sum_lhs / sum_rhs);
  return *this;
  
}

rangeDiv& rangeDiv::operator/=(const rangeDiv& other){
  int sum_rhs = 0, sum_lhs = 0;
	for(int i=0; i<range_size; i++)
		sum_rhs += this->range[i][i];
	for(int i=0; i<other.range_size; i++)
		sum_lhs += other.range[i][i];
	for(int i=0; i<range_size; i++)
		range[i] /= (sum_lhs / sum_rhs);
	return *this;
}

bool rangeDiv::operator>(const rangeDiv& other){
	int sum_lhs = 0, sum_rhs = 0;
	for(int i=0; i<range_size; i++)
		sum_lhs += range[i][i];
	for(int i=0; i<other.range_size; i++)
		sum_rhs += range[i][i];
	if(sum_lhs > sum_rhs)
		return true;
	return false;
}

bool rangeDiv::operator<(const rangeDiv& other){
	int sum_lhs = 0, sum_rhs = 0;
	for(int i=0; i<range_size; i++)
		sum_lhs += range[i][i];
	for(int i=0; i<other.range_size; i++)
		sum_rhs += range[i][i];
	if(sum_lhs < sum_rhs)
		return true;
	return false;
}

bool rangeDiv::operator>=(const rangeDiv& other){
	int sum_lhs = 0, sum_rhs = 0;
	for(int i=0; i<range_size; i++)
		sum_lhs += range[i][i];
	for(int i=0; i<other.range_size; i++)
		sum_rhs += range[i][i];
	if(sum_lhs >= sum_rhs)
		return true;
	return false;
}

bool rangeDiv::operator<=(const rangeDiv& other){
	int sum_lhs = 0, sum_rhs = 0;
	for(int i=0; i<range_size; i++)
		sum_lhs += range[i][i];
	for(int i=0; i<other.range_size; i++)
		sum_rhs += range[i][i];
	if(sum_lhs <= sum_rhs)
		return true;
	return false;
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
    out << " {div: " << range[i].getDiv() << "} ";
    if(i+1 != range_size)
      out << "-";
  }
  out << "]";
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
