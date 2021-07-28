/* @Author: Patrick Manacorda
 * @Date: 11/29/2019
 * @File: Mangler
 */
using System;

/* ---- CLASS INVARIANTS -----
 * -Mangler encapsulates integer 'x'
 * -Mangler accepts value 'b' and returns:
 *   -(x + b) || (x - b) || (x*b) // Round robin style
 *   -Functionality provided by public int mangler::yield(int) method
 */

namespace Project5
{
    public class mangler : IManglerInterface
    {
        protected int x;
        protected int request_count;
        private uint state;

        public mangler(int x = 0)
        {
            this.x = x;
        }

        /* Function: yield(int value)
         * @Pre-Conditions: n/a
         * @Post-Conditions: const function, non destructive
         * @Return: integer value, see class invariants for details
         */
         virtual public int yield(int b)
        {
            request_count++;
            switch (state)
            {
                case 0:
                    state++;
                    return x + b;
                case 1:
                    state++;
                    return x - b;
                case 2:
                    state++;
                    return x * b;
                default:
                    state = 1;
                    return x + b;
            }
        }

        /* Reset x value
         * also resets state and request count
         */
        public void reset(int x = 0)
        {
            state = 0;
            this.x = x;
            request_count = 0;
        }
    }
}

/* --------Implementation Invariant:--------
 * Private Storage:
 *   -internal state -> mode may be ADVANCED, RETREAT or STUCK
 *   -Starting value x      -> can be reset via reset(int new_x) method
 *   
 * Dependencies: No dependencies of any sub-object. Functionality based on primitives.
 *
 */
