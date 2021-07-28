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
 * 9) Object may be reset, returning to start of sequence, in ADVANCE mode, with query count and values generated reset to 0
 * 10) Yield() value checked against forbidden set if and only if forbidden set injected and number of values generated exceeds treshold
 *     10a) treshold value may be set during construction or via public set_treshold(uint) method
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
using System.Collections.Generic;
using System.Text;

namespace Project5
{
    public class ArithMangler : IArithSInterface, IManglerInterface
    {
        uint member;
        mangler Mangler;
        arithS ArithS;
        public ArithMangler(mangler Mang, arithS Arith)
        {
            Mangler = Mang;
            ArithS = Arith;
        }
        
        //Refer to ArithS.cs method description for following methods:
        public int yield()
        {
            return ArithS.yield();
        }
        public ref uint getNum()
        {
            return ref ArithS.getNum();
        }
        public void inject(int[] injection)
        {
            ArithS.inject(injection);
        }
        public void advance() { ArithS.advance(); }
        public void retreat() { ArithS.retreat(); }
        public void stay() { ArithS.stay(); }
        public int modeChanges()
        {
            return ArithS.modeChanges();
        }
        public void set_treshold(uint val)
        {
            ArithS.set_treshold(val);  
        }
        public void reset() {
            ArithS.reset();
        }

        //Refer to Mangler.cs for method description:
        public int yield(int b)
        {
            return Mangler.yield(b);
        }
        public void reset(int x) {
            Mangler.reset(x);
        }
    }
}
