#include "intDiv.h"
#include <string> // needed for << operator

/* ####### Implementation Invariant: #########
 * Private Storage:
 *   -internal state -> active and enabled by default(struct)
 *   -div value      -> can be set even after construction (0 by default)
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

intDiv& intDiv::operator++(){
  this->div++;
  return *this;
}

intDiv intDiv::operator++(int i){
  intDiv copy(*this);
  this->div++;
  return copy;
}

intDiv& intDiv::operator--(){
  this->div--;
  return *this;
}

intDiv intDiv::operator--(int i){
  intDiv copy(*this);
  this->div--;
  return copy;
}
int intDiv::operator[](int i)const {
	return this->div;
}

intDiv intDiv::operator+(const intDiv& rhs) const{ 
	intDiv local(rhs);
	local.div += this->div;
	return local;
}

intDiv intDiv::operator+(int increment) const{
	intDiv local(*this);
	local.div += increment;
	return local;
}

intDiv intDiv::operator*(const intDiv& rhs) const {
  intDiv local(*this);
  local.div *= rhs.div;
  return local;
}

int intDiv::operator*(const int value) const{
  if(value == 0) return ERROR_CODE_ONE;
  return this->div*value;
}

intDiv intDiv::operator/(const intDiv& rhs) const{
  intDiv local(*this);
  local.div /= rhs.div;
  return local;
}

int intDiv::operator%(const int value) const {
  if(value == 0) return ERROR_CODE_ONE;
  return this->div%value;
}

intDiv intDiv::operator%(const intDiv& rhs)const{
	intDiv local(*this);
	local.div %= rhs.div;
	return local;
}

bool intDiv::operator!=(const intDiv& other){
	return this->div != other.div;
}

intDiv intDiv::operator-(const intDiv& rhs){
	intDiv local(*this);
	if(local.div > rhs.div){
		local.div -= rhs.div;
	}else{
		local.div = 0;
	}
	return local;
}

intDiv& intDiv::operator-=(const intDiv& rhs){
	if(this->div < rhs.div){
		this->div = 0;
	}else{
		this->div -= rhs.div;
	}
	return *this;
}

intDiv& intDiv::operator+=(const intDiv& rhs){
	this->div += rhs.div;
	return *this;
}

intDiv& intDiv::operator*=(const intDiv& rhs){
	this->div *= rhs.div;
	return *this;
}

intDiv& intDiv::operator/=(const intDiv& rhs){
	this->div /= rhs.div;
	return *this;
}

intDiv& intDiv::operator%=(const intDiv& rhs){
	this->div %= rhs.div;
	return *this;
}

bool intDiv::operator>(const intDiv& rhs){
	return this->div > rhs.div;
}

bool intDiv::operator<(const intDiv& rhs){
	return this->div < rhs.div;
}

bool intDiv::operator>=(const intDiv& rhs){
	return this->div >= rhs.div;
}

bool intDiv::operator<=(const intDiv& rhs){
	return this->div <= rhs.div;
}

void intDiv::operator<<(std::ostream& out){
  std::string state;
  if(this->getActive() && !this->getDeactivated())
    state = "active";
  else
    state = "not active";
  out << "Div: {" << this->getDiv() << "} state: { "<< state << " } " << std::endl;
}
