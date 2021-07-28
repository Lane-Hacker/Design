using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project5
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMangler()
        {
            int x = 5;
            int b = 3;
            mangler test = new mangler(x);
            mangler test2 = new mangler();
            for (int i = 0; i < 20; i++)
            {
                Assert.AreEqual(x + b, test.yield(b));
                Assert.AreEqual(x - b, test.yield(b));
                Assert.AreEqual(b, test2.yield(b));
                Assert.AreEqual(-b, test2.yield(b));
                Assert.AreEqual(0, test2.yield(b));
                Assert.AreEqual(x * b, test.yield(b));
            }
            int x2 = 10;
            for (int i = 0; i < 10; i++)
            {
                test.reset(x2);
                test2.reset(x);
                Assert.AreEqual(x2 + b, test.yield(b));
                Assert.AreEqual(x2 - b, test.yield(b));
                Assert.AreEqual(x + b, test2.yield(b));
                Assert.AreEqual(x - b, test2.yield(b));
            }

        }
    }
}
