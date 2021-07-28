using System;
using System.Collections.Generic;
using System.Text;

namespace Project5
{
    public class puzzler : mangler, IManglerInterface
    {
        private int c;
        public puzzler(int c = 0, int x = 0) : base(x) {
            this.c = c;
        }
        public override int yield(int b)
        {
            request_count++;
            if(request_count%c == 0)
                return 0;

            amplifier amp = new amplifier(x);
            return amp.yield(b);
        }
    }
}
