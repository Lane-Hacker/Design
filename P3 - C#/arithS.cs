/*
 * @Author: Patrick Manacorda
 * @Date: October 2019
 * @See: Seattle University Fall Quarter 2019
 */

 /* ----------- CLASS INVARIANT ---------------
  * 1) ArithS object is a generator of arithmetic sequences
  * 2) The value of the arithmetic sequence is returned by the public function arithS::yield();
  * 3) Generator initial value and common difference must be initialized during construction
  * 4) Forbidden set may be added via method injection or via constructor injection. Both supported.
  *     4b) Forbidden set injection is optional and generator works even without forbidden set injection.
  * 5) State of generator may be set to STUCK, ADVANCE or RETREAT via provided public functionality.
  * 6) Return value for values of the sequence that are in forbidden set is set as ERROR_CODE_I
  * 7) Number of values generated may be returned by public functionality arithS::getNum().
  *     7b) The arithmetic sequence starts out with just the starting value, as the set grows, the number of values generated grows.
  *     7c) If in RETREAT mode or STUCK mode, no new values are generated.
  * 8) Copy constructor is declared
  * -------------INTERFACE INVARIANTS------------------
  * -)Constraints:
  * 1) Generator mode may be modified via public functionality but no public getCurrentMode() function is provided.
  *     1b) Client must track state of the generator
  * 2) Starting value and common difference cannot be modified after construction. No public setter methods provided.
  * 
  * -)Error Handling
  * 1) yield() may return <int>ERROR_CODE_I if value generated is found to be in forbidden set
  *     1b) value of ERROR_CODE_I is not ambiguous since it cannot be returned during normal operations.
  */


using System;

namespace Project3
{
    public class arithS
    {
        protected const int ERROR_CODE_I = -1;
        protected const int DEFAULT_COMMON_DIFFERENCE = 10;
        protected uint n = 1;
        protected bool check_forbidden = false;
        protected uint values_generated = 0;
        protected uint curr_max_n = 1;
        protected int[] forbidden;
        public static uint num_queries = 0;
        protected readonly uint a,d;
        protected enum arithsMode
        {
            RETREAT = -1,
            STUCK = 0,
            ADVANCE = +1
        }
        protected struct arithsState
        {
            private int mode;
            public void advance() { this.mode = (int)arithsMode.ADVANCE; }
            public void retreat() { this.mode = (int)arithsMode.RETREAT; }
            public void stay() { this.mode = (int)arithsMode.STUCK; }
            public int getMode() { return this.mode; }
        }
        protected arithsState state;
    
        /*  Protected utility function: getArith(long @param1)
         *  @Return: value of arithmetic sequence at position @param1
         *           returns starting term of the sequence if @param1 is out of range
         *  @Pre-Conditions: none
         *  @Post-Conditions: no state change
         */
        protected int getArith(long n)
        {
            int return_val;
            if (n <= 0)
                return_val = (int)a;
            else 
                return_val = (int)(this.a + this.d * (n - 1));
            return return_val;
        }

        /* Protected utility function: preprocess()
         * @Return: void
         * @Pre-Conditions: none
         * @Post-Conditions: value of this.n (current position in arithmetic sequence) is updated based on current mode.
         *                   Value of this.values_generated is also updated.
         *    @Example: Given sequence {10 <n=1> ,20 <n=2> ,30 <n=3> ,40,50..} , position n=2 (value=20) and state ADVANCE, new value of n= 2 + 1 = 3  
         *              If values up to n=5 (value=50) had already been calculated previously, values_generated is not advanced.
         */
        protected void preprocess()
        {
            if (this.state.getMode() == (int)arithsMode.ADVANCE)
            {
                n++;
                if (n > curr_max_n)
                {
                    values_generated++;
                    curr_max_n = n;
                }
            }
            else if (this.state.getMode() == (int)arithsMode.RETREAT)
            {
                if (n > 1)
                    n--;
            }
        }

        /* Copy Constructor
         *  Pre-Conditions: none
         *  Post-Conditions: this.Obj has the same state/properties of other.Obj
         */
        public arithS(arithS other)
        {
            this.n = other.n;
            this.a = other.a;
            this.d = other.d;
            this.state = other.state;
            this.values_generated = other.values_generated;
            this.curr_max_n = other.curr_max_n;
            this.check_forbidden = other.check_forbidden;
            if (check_forbidden)
            {
                this.forbidden = new int[other.forbidden.Length];
                for (int i = 0; i < other.forbidden.Length; i++)
                    this.forbidden[i] = other.forbidden[i];
            }
        }



       /* Public yield() method.
        * @Return: value of the arithmetic sequence
        * @Pre-Conditions: None
        * @Post-Conditions: Value of arithmetic sequence is returned based on current mode
        *                   ERROR_CODE_I may be returned if value is found in forbidden set
        * @Dependencies: this.state.mode, this.preprocess()
        */
         public virtual int yield()
        {
            num_queries++;
            uint current = n;
            preprocess();
            int value = this.getArith(current + this.state.getMode());
            if (check_forbidden)
            {
                foreach (int i in forbidden)
                {
                    if (i == value)
                        return ERROR_CODE_I;
                }
            }
            return value;
        }

        /* Public utility function getNum()
         * @Return: number of values internally generated
         * @Pre-Conditions: none
         * @Post-Conditions: no state change
         *     @Note: Returns a new reference to protected member this.values_generated so no violation of encapsulation
         */
        public ref uint getNum()
        {
            return ref values_generated;
        }

        /* Constructor
         * @Pre-Conditions: none
         * @Post-Conditions: object is set to ADVANCE mode by default
         */
        public arithS(uint start=0, uint difference=DEFAULT_COMMON_DIFFERENCE, int[] inject = null)
        {
            this.state.advance();
            this.a = start;
            this.d = difference;
            this.n = 1;
            if (inject != null)
            {
                this.check_forbidden = true;
                this.forbidden = new int[inject.Length];
                for(int i=0; i<forbidden.Length; i++)
                {
                    forbidden[i] = inject[i];
                }
            }else{
                this.check_forbidden = false;
            }
        }


        /* Method injection utility inject(int[] @param1)
         * @Param: the forbidden set you want to inject into the generator
         * @Pre-Condition: none
         * @Post-Conditions: Values of arithS.yield() will be checked against values contained in @param1
         */
        public void inject(int[] injection)
        {
            this.check_forbidden = true;
            this.forbidden = new int[injection.Length];
            for (int i = 0; i < injection.Length; i++)
                this.forbidden[i] = injection[i];
        }

        /* State changing methods
         * @Pre-Conditions: none
         * @Post-Conditions: State is set to ADVANCE, RETREAT or STUCK.
         */
        public void advance()
        {
            this.state.advance();
        }
        public void retreat()
        {
            this.state.retreat();
        }
        public void stay()
        {
            this.state.stay();
        }
    }
}


/* --------Implementation Invariant:--------
 * Private Storage:
 *   -internal state -> mode may be ADVANCED, RETREAT or STUCK
 *   -Starting value      -> cannot be set after construction (0 by default)
 *   -Common difference term -> cannot be set after construction (10 by default)
 *   -Forbidden set -> Optional, may be injected via constructor injection or via method injection
 *   -values_generated -> Keeps track of how many new values of the sequence are generated
 *   -curr_max_n  -> Keeps track of what is the biggest term of the sequence which has been calculated
 *                   Values of n which are less or equal than curr_max_n will not increment values_generated
 *   -Check_forbidden -> Indicates whether or not forbidden set has been injected

 * Private utility function:
 *   -Preprocess() -> Updates values_generated and shift current n value for arithmetic sequence based on mode
 *   -getArith(long n) -> returns the value of the arithmetic sequence at position n
 *   
 * Dependencies: No dependencies of any sub-object. Functionality based on primitives.
 *
 */
