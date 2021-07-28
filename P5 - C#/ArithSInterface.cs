using System;
using System.Collections.Generic;
using System.Text;

namespace Project5
{
    public interface IArithSInterface
    {
        int yield();
        ref uint getNum();
        void inject(int[] injection);
        void advance();
        void retreat();
        void stay();
        int modeChanges();
        void set_treshold(uint val);
        void reset();
    }
}
