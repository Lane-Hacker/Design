using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project5
{
    [TestClass]
    public class UnitTest2
    {
        [TestMethod]
        public void TestAmplifier()
        {
            int x = 5;
            amplifier test = new amplifier(x);
            int even = 10;
            int odd = 11;
            for (int i = 0; i < 5; i++)
            {
                Assert.AreEqual(x * odd, test.yield(odd));
                Assert.AreEqual(x * (even + 1), test.yield(even));
            }

        }
    }
}