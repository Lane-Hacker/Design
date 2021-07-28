using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace Project5
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestConstructor()
        {
            uint a = 0, d = 10;
            OscillateA test = new OscillateA(a, d);
            OscillateA test2 = new OscillateA();
        }

        [TestMethod]
        public void TestYield()
        {
            uint a = 0, d = 10;
            OscillateA test = new OscillateA(a, d);
            Assert.AreEqual(+10, test.yield());
            Assert.AreEqual(-20, test.yield());
            Assert.AreEqual(+30, test.yield());
            Assert.AreEqual(-40, test.yield());
        }

        [TestMethod]
        public void TestModes()
        {
            uint a = 0, d = 10;
            OscillateA test = new OscillateA(a, d);
            test.retreat();
            Assert.AreEqual(0, test.yield());
            test.advance();
            Assert.AreEqual(-10, test.yield());
            Assert.AreEqual(20, test.yield());
            Assert.AreEqual(-30, test.yield());
            test.stay();
            Assert.AreEqual(30, test.yield());
            Assert.AreEqual(-30, test.yield());
            test.retreat();
            Assert.AreEqual(20, test.yield());
            Assert.AreEqual(-10, test.yield());
            Assert.AreEqual(0, test.yield());
            Assert.AreEqual(0, test.yield());
        }

        [TestMethod]
        public void TestNumGen()
        {
            uint a = 0, d = 10;
            OscillateA test = new OscillateA(a, d);
            Assert.AreEqual(0, (int)test.getNum());
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual(5, (int)test.getNum());
            test.stay();
            for (int i = 0; i < 5; i++)
                test.yield();
            Assert.AreEqual(5, (int)test.getNum());
            test.retreat();
            for (int i = 0; i < 5; i++)
            {
                test.yield();
            }
            Assert.AreEqual(5, (int)test.getNum());
            test.advance();
            for (int i = 0; i < 10; i++)
            {
                test.yield();
            }
            Assert.AreEqual(10, (int)test.getNum());
        }

        [TestMethod]
        public void TestInjection()
        {
            uint a = 0, d = 10;
            OscillateA test = new OscillateA(a, d);
            Assert.AreEqual(10, test.yield());
            Assert.AreEqual(-20, test.yield());
            Assert.AreEqual(30, test.yield());
            int[] injection = new int[5]{40, -50, -60, 70, 80};
            test.inject(injection);
            Assert.AreEqual(-40, test.yield());
            Assert.AreEqual(50, test.yield());
            try { test.yield(); }
            catch(Exception ex)
            {
                if (ex is InvalidOperationException)
                { }
                else
                    Assert.Fail();
            }
        }
    }
}
