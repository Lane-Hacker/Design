/* @Author: Patrick Manacorda
 * @Date: 10/11/2019
 * @See: Seattle University CPSC 3200
 */

/*
  ######### Class Invariants: ################
  -Container stores unsigned integer
  -Container value can be initialized via constructor
  -Copying is supported
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
#ifndef INTDIV_H
#define INTDIV_H
class intDiv{
 private:
  const int ERROR_CODE_ONE = -1, ERROR_CODE_TWO = -2;
  const int DEFAULT_PREVIOUS_REMAINDER = -1;
  unsigned int div;
  int previous_remainder;
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
  intDiv(unsigned int div_value = 0);
  intDiv(const intDiv& other);
  intDiv& operator=(const intDiv& other);

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
  
};
#endif
