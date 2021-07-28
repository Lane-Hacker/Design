/* @Author: Patrick Manacorda
 * @Date: October 1st 2019
 * @Revision: 6.0
 */

using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.IO;

namespace ProjectOne
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void Constructor()
        {
            intDiv obj = new intDiv(10);
            Assert.AreEqual(obj.getActive(), true);
            Assert.AreEqual(obj.getDeactivated(), false);
            Assert.AreEqual(obj.getDiv(), (uint)10);
        }
        
        [TestMethod]
        public void Divide()
        {
            intDiv obj = new intDiv(10);
            Assert.AreEqual(0, obj.test(5));
            Assert.AreEqual(1, obj.test(3));
            Assert.AreEqual(3, obj.test(7));
            Assert.AreEqual(10, obj.test(11));
        }

        [TestMethod]
        public void Deactivate_n_Revive()
        {
            intDiv obj = new intDiv(20);
            Assert.AreEqual(true, obj.getActive());
            obj.test(8);
            Assert.AreEqual(true, obj.getActive());
            obj.test(8);
            Assert.AreEqual(false, obj.getActive());
            obj.revive();
            Assert.AreEqual(true, obj.getActive());
        }

        [TestMethod]
        public void Revive_ActiveObj()
        {
            intDiv obj = new intDiv();
            Assert.AreEqual((uint)0, obj.getDiv());
            Assert.AreEqual(true, obj.getActive());
            obj.revive();
            Assert.AreEqual(true, obj.getDeactivated());
        }

        [TestMethod]
        public void Deactivate_n_Reset()
        {
            intDiv obj = new intDiv(10);
            obj.test(2);
            obj.test(2);
            Assert.AreEqual(false, obj.getActive());
            obj.revive();
            Assert.AreEqual(true, obj.getActive());
            Assert.AreEqual(false, obj.getDeactivated());
            obj.revive();
            Assert.AreEqual(true, obj.getDeactivated());
            obj.reset();
            Assert.AreEqual(true, obj.getActive());
            Assert.AreEqual(false, obj.getDeactivated());
        }

        [TestMethod]
        public void mainDriver()
        {
            driver.main();
        }
    }
}
