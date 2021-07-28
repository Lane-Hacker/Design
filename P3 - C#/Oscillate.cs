/*
 * @Author: Patrick Manacorda
 * @Date: October 2019
 * @See: Seattle University Fall Quarter 2019
 */

/* ----------- CLASS INVARIANT ---------------
 * 1) OscillateA object is a generator of arithmetic sequences derived from arithS base class.
 * 2) The value of the arithmetic sequence is returned by the public function OscillateA::yield();
 *      2b) Return values oscillate between positive and negative
 * 3) Generator initial value and common difference must be initialized during construction
 * 4) Forbidden set may be added via method injection or via constructor injection. Both supported.
 *     4b) Forbidden set injection is optional and generator works even without forbidden set injection.
 * 5) State of generator may be set to STUCK, ADVANCE or RETREAT via provided public functionality (of base arithS class).
 * 6) Values of the sequence which are in forbidden set will throw InvalidOperation exception
 * 7) Number of values generated may be returned by public functionality arithS::getNum().
 *     7b) The arithmetic sequence starts out with just the starting value, as the set grows, the number of values generated grows.
 *     7c) If in RETREAT mode or STUCK mode, no new values are generated.
 * 
 * -------------INTERFACE INVARIANTS------------------
 * -)Constraints:
 * 1) Generator mode may be modified via public functionality but no public getCurrentMode() function is provided.
 *     1b) Client must track state of the generator
 * 2) Starting value and common difference cannot be modified after construction. No public setter methods provided.
 * 
 * -)Error Handling
 * 1) yield() may throw exception of type <InvalidOperationException> if value generated is found to be in forbidden set
 */

using System;

namespace Project3
{
    public class OscillateA : arithS
    {
        private bool positive = true;
        public OscillateA(uint a=0, uint d=DEFAULT_COMMON_DIFFERENCE, int[] inject = null) : base(a, d, inject) { }

        /* Public yield() method.
        * @Return: value of the arithmetic sequence
        * @Pre-Conditions: None
        * @Post-Conditions: Value of arithmetic sequence is returned based on current mode
        *                   Values oscillate between positive and negative
        *                   Exception.InvalidOperationException may be thrown if value is found in forbidden set
        * @Dependencies: this.state.mode, this.preprocess(), this.positive
        */
        public override int yield()
        {
            num_queries++;
            uint current = n;
            preprocess();
            int return_val = 0;
            switch (positive)
            {
                case true:
                    return_val = getArith(current + state.getMode());
                    break;
                case false:
                    return_val = -getArith(current + state.getMode());
                    break;
            }
            positive = !positive;
            if (check_forbidden)
            {
                foreach (int i in forbidden)
                {
                    if (i == return_val)
                        throw new InvalidOperationException("Value in forbidden set!");
                }
            }
            return return_val;
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
 *   -Positive -> Keeps track of current return value sign. It oscillates between positive and negative.

 * Private utility function:
 *   -Preprocess() -> Updates values_generated and shift current n value for arithmetic sequence based on mode
 *   -getArith(long n) -> returns the value of the arithmetic sequence at position n
 *   
 * Dependencies: No dependencies of any sub-object. Functionality based on primitives.
 *
 */
