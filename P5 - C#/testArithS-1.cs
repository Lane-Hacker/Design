using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Project5
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
        public void testReset()
        {
            uint a = 0, d = 10;
            arithS test = new arithS(a, d);
            test.yield(); //n= 2
            test.yield(); //n= 3
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(40, test.yield());
            test.reset();
            Assert.AreEqual(10, test.yield());
            test.stay();
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(10, test.yield());
            test.reset();
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(20, test.yield());
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
            Assert.AreEqual(4, test.modeChanges());
            test.reset();
            Assert.AreEqual(0, test.modeChanges());
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
            int[] inject_array = new int[5] { 3, 6, 27, 12, 33 };
            arithS test = new arithS(a, d, 10, null);
            Assert.AreEqual(3, test.yield());
            Assert.AreEqual(6, test.yield());
            test.inject(inject_array);
            Assert.AreEqual(9, test.yield());
            test.yield(); //values generated = 4
            for (int i = 0; i < 5; i++)
                test.yield(); //values generated = 9, n=27
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(-1, test.yield()); //Treshold reached, value in forbidden set
            Assert.AreEqual(36, test.yield()); //Still advancing, 33 not in forbidden set
            test.retreat();
            Assert.AreEqual(-1, test.yield()); //30 in forbidden set
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(-1, test.yield()); //27 in forbidden set
        }

        [TestMethod]
        public void TestMain()
        {
            P3.Main(null);
        }
    }
}
