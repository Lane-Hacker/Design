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
  const int DEFAULT_RANGE_SIZE = 5;
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
  /* Constructors, deep copying supported
   */
  rangeDiv();
  rangeDiv(int size);
  rangeDiv(const rangeDiv& other);
  rangeDiv(rangeDiv&& other);
  rangeDiv& operator=(const rangeDiv& other);
  rangeDiv& operator=(rangeDiv&& other);

  /* Operator *
   * @Pre-Conditions: lhs and rhs are rangeDiv type, rhs can be integer literal
   * @Post-Condition: non destructive, truncated with smallest range size
   * @Return: copy of (*this) with all range values multiplied by rhs range values
   */
  rangeDiv operator*(rangeDiv& other);
  rangeDiv operator*(int val);

  /* Operator /
   * @Pre-Conditions: lhs is rangeDiv, rhs is integer
   * @Post-Conditions: non destructive
   * @Return: copy of *this with all range values divided by param value
   */
  rangeDiv operator/(int val);

  /* Operator %
   * @Pre-Conditions: lhs and rhs are rangeDiv type 
   * @Post-conditions: non destructive, truncates to smallest range size
   * @Return: Copy of *this with range values moduled
   */
  rangeDiv operator%(rangeDiv& other);
  
  /* Operator *=
   * @Pre-Conditions: lhs and rhs are rangeDiv typ
   * @Post-Conditions: destructive
   * @Return: *this with all range values multiplied by the factor sum(rhs_range)/sum(lhs_range)
   */
  rangeDiv& operator*=(const rangeDiv& other);

  /* Operator ++, --
   * @Pre-Conditions: none
   * @Post-Conditions: destructive, *this modified
   * @Return: copy of *this before of after modification to range values
   */
  rangeDiv& operator++();
  rangeDiv operator++(int i);
  rangeDiv& operator--();
  rangeDiv operator--(int i);

  /* Operator <<
   * @Pre-Conditions: none
   * @Post-Conditoins: value of *this streamed to outstream
   */
  void operator<<(std::ostream out){ this->printRange(out); }
  
/* Operator []
* @Pre-Condition: none
* @Post-Condition: non destructive
* @Return: copy of range value at specific index
*/
intDiv operator[](int index);

/* Operator +
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non destuctive, *this not-altered
* @Return: rangeDiv object, range of div values added (mixed sizes supported)
*/
rangeDiv operator+(rangeDiv& rhs);

/* Operator -
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non destuctive, *this not-altered
* @Return: rangeDiv object, range of div values subtracted (mixed sizes supported)
*/
rangeDiv operator-(rangeDiv& rhs);

/* Operator + (Integer Increment)
* @Pre-Condition: none
* @Post-Condition: non destructive
* @Return: rangeDiv copy with all this->range values incremented
*/
rangeDiv operator+(int increment);

/* Operator - (Integer Decrement)
* @Pre-Condition: none
* @Post-Condition: non destructive
* @Return: rangeDiv copy with all this->range values decremented
*/
rangeDiv operator-(int decrement);


/* Operator +=
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this, range values added
*/
rangeDiv& operator+=(rangeDiv& rhs);

/* Operator -=
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this, range values subtracted
*/
rangeDiv& operator-=(rangeDiv& rhs);

/* Operator !=
* @Pre-Condition: lhs and rhs are rangeDiv type with same range size
* @Post-Condition: none
* @Return: Boolean, checks if all range values match
*/
 bool operator!=(rangeDiv& other);

/* Operator /
* @Pre-Conditions: lhs and rhs are rangeDiv type
* @Post-Condtions: non destructive
* @Return: copy of *this with all range values divided by rhs range values
*/
rangeDiv operator/(rangeDiv& other);

/* Operator /=
* @Pre-Conditions: sum of rhs must not be zero
* @Post-Conditions: *this altered
* @Return: value of *this altered by adding sum(lhs)/sum(rhs) to each term in range
*/
rangeDiv& operator/=(const rangeDiv& other);

/* Operator %=
* @Pre-Conditions: none
* @Post-Conditions: *this altered
* @Return: *this altered by adding value of lhs%rhs to each term in range
*/
rangeDiv& operator%=(const rangeDiv& other);

/* Operator >
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non-destructive
* @Return: Boolean, true if sum(lhs)>sum(rhs)
*/
bool operator>(const rangeDiv& other);

/* Operator <
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non-destructive
* @Return: Boolean, true if sum(lhs)<sum(rhs)
*/
bool operator<(const rangeDiv& other);

/* Operator >=
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non-destructive
* @Return: Boolean, true if sum(lhs)>=sum(rhs)
*/
bool operator>=(const rangeDiv& other);

/* Operator <=
* @Pre-Condition: lhs and rhs are rangeDiv type
* @Post-Condition: non-destructive
* @Return: Boolean, true if sum(lhs)<=sum(rhs)
*/
bool operator<=(const rangeDiv& other);

/*Destructor 
 */ 
 ~rangeDiv();
 
 /* State change method: toggle()
  * @Pre-Conditions: none
  * @Post-Conditions: active becomes inactive and viceversa
  */
 void toggle();

 /* Get state method
  * @Pre-Conditions: none
  * @Post-Conditions: non destructive
  * @Return: true if *this is active
  */
 bool getActive();

 /* printRange function - output stream
   Same as operator <<
  */
 void printRange(std::ostream& out);

 /* Functionality:
  * TestOne ~ how many values are divisible by @param?
  * TestTwo ~ how many values are not divisible by @param?
  * TestThree ~ what is the max value of evenly divisible previous test values?
  */
  int testOne(int param);
  int testTwo(int param);
  int testThree();
};
#endif
