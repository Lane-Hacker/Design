using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project3
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestConstructor()
        {
            uint a = 0, d = 10;
            arithS test = new arithS(a, d);
        }

        [TestMethod]
        public void TestYield()
        {
            uint a = 0, d = 10;
            arithS test = new arithS(a, d);
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(20, test.yield());
            Assert.AreEqual(30, test.yield());
        }

        [TestMethod]
        public void TestModes()
        {
            uint a = 0, d = 10;
            arithS test = new arithS(a, d);
            test.retreat();
            Assert.AreEqual(0, test.yield());
            test.advance();
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(20, test.yield());
            Assert.AreEqual(30, test.yield());
            test.stay();
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(30, test.yield());
            test.retreat();
            Assert.AreEqual(20, test.yield());
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(0, test.yield());
            Assert.AreEqual(0, test.yield());
        }

        [TestMethod]
        public void TestNumGen()
        {
            uint a = 0, d = 10;
            arithS test = new arithS(a, d);
            Assert.AreEqual(0, (int)test.getNum());
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual(5, (int)test.getNum());
            test.stay();
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual(5, (int)test.getNum());
            test.retreat();
            for(int i=0; i<5; i++)
            {
                test.yield();
            }
            Assert.AreEqual(5, (int)test.getNum());
            test.advance();
            for(int i=0; i<10; i++)
            {
                test.yield();
            }
            Assert.AreEqual(10, (int)test.getNum());
        }

        [TestMethod]
        public void TestInjection()
        {
            uint a = 0, d = 3;
            int[] inject_array = new int[5] { 3, 6, 8, 12, 15 };
            arithS test = new arithS(a, d);
            Assert.AreEqual(3, test.yield());
            Assert.AreEqual(6, test.yield());
            test.inject(inject_array);
            Assert.AreEqual(9, test.yield());
            Assert.AreEqual(-1, test.yield());
            Assert.AreEqual(-1, test.yield());
            Assert.AreEqual(18, test.yield());
            test.retreat();
            Assert.AreEqual(-1, test.yield());
            Assert.AreEqual(-1, test.yield());
            Assert.AreEqual(9, test.yield());
        }

        [TestMethod]
        public void TestMain()
        {
            P3.Main(null);
        }
    }
}
