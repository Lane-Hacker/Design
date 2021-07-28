/*
 * @Author: Patrick Manacorda
 * @Date: October 2019
 * @See: Seattle University Fall Quarter 2019
 */

/* ----------- CLASS INVARIANT ---------------
 * 1) SkipA object is a generator of arithmetic sequences derived from arithS base class.
 * 2) The value of the arithmetic sequence is returned by the public function skipA::yield();
 *      2b) A number of intermediate values (defined by this.skipVal, must be defined during construction) is skipped (still generated).
 * 3) Generator initial value, common difference and skip value must be initialized during construction
 * 4) Forbidden set may be added via method injection or via constructor injection. Both supported.
 *     4b) Forbidden set injection is optional and generator works even without forbidden set injection.
 * 5) State of generator may be set to STUCK, ADVANCE or RETREAT via provided public functionality (of base arithS class).
 * 6) Return value for values of the sequence that are in forbidden set is set as ERROR_CODE_I
 * 7) Number of values generated may be returned by public functionality arithS::getNum().
 *     7b) The arithmetic sequence starts out with just the starting value, as the set grows, the number of values generated grows.
 *     7c) If in RETREAT mode or STUCK mode, no new values are generated.
 *     7d) Intermediate values that are skipped are still generated.
 * 
 * -------------INTERFACE INVARIANTS------------------
 * -)Constraints:
 * 1) Generator mode may be modified via public functionality but no public getCurrentMode() function is provided.
 *     1b) Client must track state of the generator
 * 2) Starting value, common difference and skip value cannot be modified after construction. No public setter methods provided.
 * 
 * -)Error Handling
 * 1) yield() may return <int>ERROR_CODE_I if value generated is found to be in forbidden set
 *     1b) value of ERROR_CODE_I is not ambiguous since it cannot be returned during normal operations.
 */

using System;
namespace Project5
{
    public class skipA : arithS, IArithSInterface
    {
        private readonly uint skipVal;
        private const int DEFAULT_SKIP = 5;
        public skipA(uint skipVal=DEFAULT_SKIP, uint a=0, uint d=DEFAULT_COMMON_DIFFERENCE, uint treshold = DEFAULT_TRESHOLD, int[] inject = null) : base(a,d, treshold, inject){
            this.skipVal = skipVal;
        }

        /* Private utility function: preprocess()
         * @Return: void
         * @Pre-Conditions: none
         * @Post-Conditions: value of this.n (current position in arithmetic sequence) is updated based on current mode.
         *                   Value of this.values_generated is also updated.
         *    @Example: Given sequence {10 <n=1> ,20 <n=2> ,30 <n=3> ,40,50..} , position n=2 (value=20) and state ADVANCE, new value of n= 2 + 1 = 3  
         *              If values up to n=5 (value=50) had already been calculated previously, values_generated is not advanced.
         */
        private new void preprocess()
        {
            if (this.state.getMode() == (int)arithsMode.ADVANCE)
            {
                n+=(uint)skipVal+1;
                if (n > curr_max_n)
                {
                    values_generated+=n-curr_max_n;
                    curr_max_n = n;
                }
            }
            else if (this.state.getMode() == (int)arithsMode.RETREAT)
            {
                if (n > skipVal+1)
                    n-=(uint)skipVal+1;
            }
        }

        /* Public yield() method.
        * @Return: value of the arithmetic sequence
        * @Pre-Conditions: None
        * @Post-Conditions: Value of arithmetic sequence is returned based on current mode
        *                   An intermediate number of values (this.skipVal) are skipped
        *                   ERROR_CODE_I may be returned if value is found in forbidden set
        * @Dependencies: this.state.mode, this.preprocess(). this.skipVal
        */
        public override int yield()
        {
            num_queries++;
            int current = (int)n;
            this.preprocess();
            int value = 0;
            switch (this.state.getMode()) {
                case (int)arithsMode.ADVANCE:
                    value = getArith(current + this.state.getMode() + skipVal);
                    break;
                case (int)arithsMode.STUCK:
                    value = getArith(current);
                    break;
                case (int)arithsMode.RETREAT:
                    if (current - (skipVal + 1) > 0)
                        value = getArith(current + this.state.getMode() - skipVal);
                    else
                        value = getArith(1);
                    break;
            }
            if (valid(value))
                return value;
            return ERROR_CODE_I;
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
 *   -SkipVal     -> Number of intermediate values that are skipped. Must be initialized during construction (5 by default)
 * Private utility function:
 *   -Preprocess() -> Updates values_generated and shift current n value for arithmetic sequence based on mode
 *   -getArith(long n) -> returns the value of the arithmetic sequence at position n
 *   
 * Dependencies: No dependencies of any sub-object. Functionality based on primitives.
 *
 */
