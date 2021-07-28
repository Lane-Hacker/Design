using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project5
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestConstructor()
        {
            uint a = 0, d = 10, skip=2;
            skipA test = new skipA(skip, a, d);
            skipA test2 = new skipA(skip);
        }

        [TestMethod]
        public void TestYield()
        {
            uint a = 0, d = 10, skip=2;
            skipA test = new skipA(skip, a, d);
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(60, test.yield());
            Assert.AreEqual(90, test.yield());
        }

        [TestMethod]
        public void TestModes()
        {
            uint a = 0, d = 10, skip=2;
            skipA test = new skipA(skip, a, d);
            test.retreat();
            Assert.AreEqual(0, test.yield());
            test.advance();
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(60, test.yield());
            Assert.AreEqual(90, test.yield());
            test.stay();
            Assert.AreEqual(90, test.yield());
            Assert.AreEqual(90, test.yield());
            test.retreat();
            Assert.AreEqual(60, test.yield());
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(0, test.yield());
            Assert.AreEqual(0, test.yield());
        }

        [TestMethod]
        public void TestNumGen()
        {
            uint a = 0, d = 10, skip=2;
            skipA test = new skipA(skip,a, d);
            Assert.AreEqual((int)0, (int)test.getNum());
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual((int)(5+5*skip), (int)test.getNum());
            test.stay();
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual((int)(5 + 5 * skip), (int)test.getNum());
            test.retreat();
            for (int i = 0; i < 5; i++)
            {
                test.yield();
            }
            Assert.AreEqual((int)(5 + 5 * skip), (int)test.getNum());
            test.advance();
            for (int i = 0; i < 10; i++)
            {
                test.yield();
            }
            Assert.AreEqual((int)(10 + 10 * skip), (int)test.getNum());
        }

        [TestMethod]
        public void TestInjection()
        {
            uint a = 0, d = 10, skip = 2;
            int[] forbidden = new int[5] { 10, 20, 40, 50, 60 };
            skipA test = new skipA(skip, a, d, 1, forbidden);
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(-1, test.yield());//60 is in forbidden set
            Assert.AreEqual(90, test.yield());
        }
    }
}
