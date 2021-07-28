/*
* @Author: Patrick Manacorda
* @Date: October 14th 2019
*/

#include "intDiv.h"


/* ####### Implementation Invariant: #########
 * Private Storage:
 *   -internal state -> active and enabled by default
 *   -div value      -> cannot be set after construction (0 by default)
 *   -previous remainder -> Used to disable objects which return same test result twice in a row

 * Private utility function:
 *   -intDivState::activate(), deactivate(), enable(), disable()
 *      -> Used to toggle state of the intDiv object
 *
 */



void intDiv::intDivState::enable(){
  disabled = false;
}
void intDiv::intDivState::activate(){
  active = true;
}
void intDiv::intDivState::disable(){
  disabled = true;
}
void intDiv::intDivState::deactivate(){
  active = false;
}

intDiv::intDiv(unsigned int div_value){
  this->div = div_value;
  this->state.activate();
  this->state.enable();
  this->previous_remainder = DEFAULT_PREVIOUS_REMAINDER;
}

intDiv& intDiv::operator=(const intDiv& other){
  if(this != &other){
    this->div = other.div;
    this->state.active = other.state.active;
    this->state.disabled = other.state.disabled;
    this->previous_remainder = other.previous_remainder;
  }
  return *this;
}

intDiv::intDiv(const intDiv& other){
  *this = other;
}

unsigned int intDiv::getDiv(){
  return this->div;
}

bool intDiv::getActive(){
  return this->state.active;
}

bool intDiv::getDeactivated(){
  return this->state.disabled;
}

int intDiv::test(unsigned int denominator){
  if(denominator == 0)
    return ERROR_CODE_ONE;

  if(this->state.active){
    int remainder = this->div % denominator;

    if(remainder == this->previous_remainder)
      this->state.deactivate();
    else
      this->previous_remainder = static_cast<int>(remainder);

    return remainder;
  }else{
    return ERROR_CODE_TWO;
  }
}

void intDiv::revive(){
  if(this->state.active){
    this->state.deactivate();
    this->state.disable();
  }else if (!state.disabled)
    this->state.activate();
  else
    return;
}

void intDiv::reset(){
  this->state.activate();
  this->state.enable();
  this->previous_remainder = DEFAULT_PREVIOUS_REMAINDER;
}
