using System;
using System.Collections.Generic;
using System.Text;

namespace Project5
{
    public class amplifier : mangler, IManglerInterface
    {
        public amplifier(int x = 0) : base(x) { }
        public override int yield(int b)
        {
            request_count++;
            if(b%2 == 1)
            {
                return x * b;
            }
            return x * (b + 1);
        }
    }
}
