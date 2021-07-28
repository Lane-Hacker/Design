/*
 *  @Author: Patrick Manacorda
 *  @Date: September 29 - 2019
 *  @Revision: 6.0
 */

/*
 *  ############ CLASS INVARIANTS ############
 *  
 *   -Container stores unsigned integer
 *   -Container value must be initialized during object construction
 *   -Container value can be tested via the public test() method
 *   -Container can be revived if inactive via the revive() method
 *      -Attempting to revive active object will deactivate and disable it
 *   -Container can be reset to initial state via the reset() method
 *      -Reset will restore even disabled objects
 *   
 *  ############ INTERFACE INVARIANTS ############
 *  
 *   -Constraints:
 *       -Div values and test parameters must be zero or positive
 *          
 *   -Error handling
*        -intDiv::test() will return appropriate error codes for invalid operations/parameters
*        -No exceptions are thrown
*           -Why? -> Stable, hard to crash code, recovery
 */

using System;

namespace ProjectOne
{
    public class intDiv
    {
        private const int ERROR_CODE_ONE = -1;
        private const int ERROR_CODE_TWO = -2;
        private const int DEFAULT_PREV_REMAINDER = -1;

        private uint div = 0;
        private bool enabled = true;
        private bool deactivated = false;
        private int previous_remainder = DEFAULT_PREV_REMAINDER;
     

        public intDiv(uint div_value = 0){
            this.div = div_value;
            return;
        }

        /*
         *  Get Methods
         *  @Pre-Conditions: None
         *  @Post-Conditions: No state change
         */
        public uint getDiv(){ return this.div; }
        public bool getActive(){ return this.enabled;}
        public bool getDeactivated(){ return this.deactivated; }

        /* Function intDiv::test(denominator) 
         *   @Param: <uint>denominator, the value for which the test will be performed
         *   @Return: Remainder of integer division between this.$div and $denominator
         *            *Return -1 for invalid denominator (0)
         *            *Return -2 if caller object is disabled
         *   @Pre-Conditions: N/A
         *   @Post-Conditions: Caller object might be disabled
         */
        public int test(uint denominator){
            if (denominator == 0)
                return ERROR_CODE_ONE;

            if (this.enabled){
                uint remainder = div % denominator;
                if (remainder == this.previous_remainder)
                    this.enabled = false;
                else
                    this.previous_remainder = (int)remainder;
                return (int)remainder;
            }else{
                return ERROR_CODE_TWO;
            }
        }

        /*
         *  Function intDiv::revive()
         *    @Pre-Conditions: None
         *    @Post-Conditions: Caller object is re-activated
         *                      *No state change if caller object is disabled
         */
        public void revive(){
            if (this.enabled){
                this.deactivated = true;
                this.enabled = false;
            }else if(!this.deactivated)
                this.enabled = true;
            return;
        }

        /* Function intDiv::reset()
         *   @Pre-Conditions: None
         *   @Post-Conditions: Caller object is active and has div value of 0 (default)
         */
        public void reset(){
            this.div = 0;
            this.enabled = true;
            this.deactivated = false;
            this.previous_remainder = DEFAULT_PREV_REMAINDER;
            return;
        }
    }
}

/*
 * ############ IMPLEMENTATION INVARIANT ############
 * 
 *  -intDiv Object private storage:
 *      -internal state         -> active and enabled by default
 *      -div value              -> must be initialized via constructor or 0 by default
 *      -previous test results  -> Used to permanently disable objects which return the same intDiv::test() result twice
 *      
 *      
 *  -Private utility functions: None
 * 
 *  -Dependencies: None
 */
