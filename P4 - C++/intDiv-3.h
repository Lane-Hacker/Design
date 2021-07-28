/* @Author: Patrick Manacorda
 * @Date: 10/11/2019
 * @See: Seattle University CPSC 3200
 */

/*
  ######### Class Invariants: ################
  -Container stores unsigned integer
  -Container value can be initialized via constructor
  -Object can be revived if inactive via revive() method
  -Attempting to revive an active object will permanently disable the object
  -Object may be reset via the reset() method
  -Reset will also restore disabled objects

  ######## Interfact Invariants: ############
  -Constraints:
  1) Div value and test values must be zero or positive

  0Error handling:
  1) intDiv::test() will return error codes for invalid operations/parameters
  2) No exceptions are thrown for stable/hard-to-crash code

*/
#include <iostream> // needed for std::ostream
#ifndef INTDIV_H
#define INTDIV_H
class intDiv{
 private:
  const int ERROR_CODE_ONE = -1, ERROR_CODE_TWO = -2;
  const int DEFAULT_PREVIOUS_REMAINDER = -1;
  unsigned int div;
  int previous_remainder;
  /* State structure
   * -Holds active state
   * -Holds disabled state
   * -Has modifiers that are echoed in public functionality
   */
  struct intDivState{
    bool active;
    bool disabled;
    void enable();
    void disable();
    void activate();
    void deactivate();
  };
  intDivState state;

 public:
  
  /* Constructor, copy constructor and assignment operator
   */
  intDiv(unsigned int div_value = 0);
  intDiv(const intDiv& other);
  intDiv& operator=(const intDiv& other);

  /* operator++
     @Pre-condition: none
     @Post-condition: destructive, div value incremented
     @Return: value of *this before or after modification to div value
   */
  intDiv operator++(int i);
  intDiv& operator++();

  /* operator--
     @Pre-Coonditions: none
     @Post-conditions: destructive, div value decremented
     @Return: value of *this before or after modification to div value
   */
  intDiv operator--(int i);
  intDiv& operator--();
  
    /* Get Methods: intDiv::getDiv(), getActive(), getDeactivated()
   * @Pre-Conditions: none
   * @Post-Conditions: No state change
   * @Return: object state/value
   */
  unsigned int getDiv();
  bool getActive();
  bool getDeactivated();

  /* Test function: intDiv::test(<unsigned int>@param)
   * @Pre-Conditions: none
   * @Post-Conditions: Caller object might be disabled
   * @Return: remainder of integer division between this.$div and @param
   *        * Return ERROR_CODE_ONE for invalid @param
   *        * Return ERROR_CODE_TWO for invalid operation (object disabled/deactivated)
   */
  int test(unsigned int denominator);

  /* State-Change Method: intDiv::revive()
   * @Pre-Conditions: none
   * @Post-Conditions: Caller object's enabled value may be altered
   *      -Reviving an enabled object will cause it to be de-activated and disabled
   *      -If object is not enabled and it will be enabled unless object is deactivated
   */
  void revive();

  /* State-Change Method: intDiv::reset()
   * @Pre-Conditions: none
   * @Post-Conditions: Object is reset to default state
   */
  void reset();
  
/* Operator []
* @Pre-Conditions: none
* @Post-Conditions: none
* @Return: copy of div value
*/
int operator[](int i) const;

/* Operator +
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: const args, non destructive
* @Return: IntDiv object(div value is added up)
*/
intDiv operator+(const intDiv& rhs)const;

/* Operator + (integer increment)
* @Pre-Conditions: none 
* @Post-Conditions: div value incremented, non destructive
* @Return: copy of *this with div value incremented
*/
intDiv operator+(int increment) const;

/* Operator *
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: const args, non destructive
* @Return: IntDiv object(div value multiplied)
*/
 intDiv operator*(const intDiv& rhs) const;
 int operator*(const int value) const;
 
/* Operator /
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: const args, non destructive
* @Return: IntDiv object(div value divided)
*/
 intDiv operator/(const intDiv& rhs) const;

/* Operator %
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: const args, non destructive
* @Return: IntDiv object(div value moduled)
*/
 intDiv operator%(const intDiv& rhs) const;
 int operator%(int value) const;

/* Operator !=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: not destructive
* @Return: true if two objects have different div value
*/
bool operator!=(const intDiv& other);

/* Operator -
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: const args, non destructive
* @Return: IntDiv object(div value subtracted)
*/
intDiv operator-(const intDiv& rhs);

/* Operator -=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this pointer, div value subtracted, same as this = this - other;
*/
intDiv& operator-=(const intDiv& rhs);

/* Operator +=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this pointer, div value added, same as this = this + other;
*/
intDiv& operator+=(const intDiv& rhs);

/* Operator *=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this pointer, div value multiplied, same as this = this * other;
*/
intDiv& operator*=(const intDiv& rhs);

/* Operator /=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this pointer, div value divided, same as this = this / other;
*/
intDiv& operator/=(const intDiv& rhs);

/* Operator %=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: destructive, *this altered
* @Return: *this pointer, div value moduled, same as this = this % other;
*/
intDiv& operator%=(const intDiv& rhs);

/* Operator >
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: not destructive, *this not altered
* @Return: bool, true if this->div > param.div
*/
bool operator>(const intDiv& rhs);

/* Operator <
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: not destructive, *this not altered
* @Return: bool, true if this->div < param.div
*/
bool operator<(const intDiv& rhs);

/* Operator >=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: not destructive, *this not altered
* @Return: bool, true if this->div >= param.div
*/
bool operator>=(const intDiv& rhs);

/* Operator <=
* @Pre-Condition: lhs and rhs are intDiv type
* @Post-Condition: not destructive, *this not altered
* @Return: bool, true if this->div <= param.div
*/
bool operator<=(const intDiv& rhs);

/* Operator <<                                             \
 * @Pre-Conditions: none
 * @Post-Conditions: *this object outputted to ostream
 * @Return: void
 */
 void operator<<(std::ostream& out);
};
#endif
