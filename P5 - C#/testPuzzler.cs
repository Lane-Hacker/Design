using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project5
{
    [TestClass]
    public class UnitTest3
    {
        [TestMethod]
        public void TestPuzzler()
        {
            int x = 5;
            int c = 10;
            puzzler test = new puzzler(c, x);
            int even = 10;
            int odd = 11;
            for (int i = 0; i < 5; i++)
            {
                Assert.AreEqual(x * (even + 1), test.yield(even));
                if (i == 4)
                    Assert.AreEqual(0, test.yield(odd));
                else
                    Assert.AreEqual(x * odd, test.yield(odd));
            }
        }
    }
}