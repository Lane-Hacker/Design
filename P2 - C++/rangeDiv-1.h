/* @Author: Patrick Manacorda
 * @Date: 10/11/2019
 * @See: Seattle University CPSC 3200
 */

/* ###### Class Invariants: #######
 * -Container stores a range of intDiv objects
 *    -> Dependency on intDiv type
 * -Each rangeDiv object may be active or inactive
 * -Functionality is provided via three test functions:
 *    -> testOne(@param) returns number of intDiv objects that return no remainder when tested with @param
 *    -> testTwo(@param) returns number of intDiv objects that return remainder when tested with @param
 *    -> testThree() returns maximum number of evenly divisible intDiv objects when divided by previous test values
 *
 *  -Printing to ostream supported via the rangeDiv::print_range(ostream&) method
 *
 * ###### Interface Invariants: #######
 * -Constrains:
 * 1) test values must be zero or positive
 *
 * -Error Handling:
 * 1) test functions will return ERROR_CODE values for invalid @parameters or illegal operations
 * 2) Constructor will throw exception if size of range is zero or negative
 * 3) No other exceptions thrown -> stable/hard to crash code
 */
#ifndef RANGEDIV_H
#define RANGEDIV_H
#include "intDiv.h"
#include <iostream> //needed to define std::ostream

class rangeDiv{
 private:
  intDiv* range;
  const int DEFAULT_RANGE_SIZE = 10;
  const int ERROR_CODE_ONE = -1;
  const int ERROR_CODE_TWO = -2;
  int range_size;
  int* parallel_even;
  struct rangeDivState{
    bool active;
    void activate();
    void deactivate();
  };
  rangeDivState state;
  const int MAX_PRIME = 100;
  const int MIN_PRIME = 3;
  int getPrime();
  int countFunction(int param);
  void clear();
  void copyOther(const rangeDiv& other);
  
 public:
  rangeDiv(int size = 0);
  rangeDiv(const rangeDiv& other);
  rangeDiv(rangeDiv&& other);
  rangeDiv& operator=(const rangeDiv& other);
  rangeDiv& operator=(rangeDiv&& other);
  ~rangeDiv();
  void toggle();
  bool getActive();
  void printRange(std::ostream& out);
  int testOne(int param);
  int testTwo(int param);
  int testThree();
};
#endif
