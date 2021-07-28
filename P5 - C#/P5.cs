/*
 * @Author: Patrick Manacorda
 * @Date: December 2019
 * @See: Seattle University Fall Quarter 2019
 */
using System;

/* -------- PROGRAM OVERVIEW -------------
 * This program aims at showing off the functionality of heterogeneous collections for polymorphic behaviour
 * 1) An array of parent (ArithMangler) type is generated with size between MIN_SIZE and MAX_SIZE (random at runtime)
 * 2) Each slot in array is initialized with a 1-to-1 mix-match between types: arithS, oscillateA, skipA and mangler, amplifier, puzzler). (random decision at runtime)
 * 3) Mode changes for each object are triggered
 * 4) Polymorphic yield(), yield(int) functionality for each ArithMangler object printed to screen
 * Note: Forbidden set injection and testing is performed in unit tests
 *       The possibility of injecting random forbidden sets to show off functionality and
 *       behaviour has been considered but rejected since the chance of randomly choosing values
 *       that are in the random arithmetic sequence is extremely unlikely (thus it would be pointless
 *       if the attempt is to show off functionality in a consistent manner).
 */

namespace Project5
{
    public class P5Driver
    {
        const int MAX_START = 100;
        const int MAX_DIFFERENCE = 20;
        const int MIN_DIFFERENCE = 2;
        const int MAX_SKIP = 10;
        const int MIN_SKIP = 1;
        const int MIN_SIZE = 3;
        const int MAX_SIZE = 5;
        const int NUM_MODES = 3;
        public static arithS getObjArithS()
        {
            Random rnd = new Random();
            int choice = rnd.Next(3);
            uint start = (uint)rnd.Next(MAX_START);
            uint difference = (uint)rnd.Next(MIN_DIFFERENCE, MAX_DIFFERENCE);
            switch (choice)
            {
                case 0:
                    Console.Write("Type: [ArtihS] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(start);
                    Console.Write(" ; Common Difference = ");
                    Console.WriteLine(difference);
                    return new arithS(start, difference);
                case 1:
                    Console.Write("Type: [OscillateA] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(start);
                    Console.Write(" ; Common Difference = ");
                    Console.WriteLine(difference);
                    return new OscillateA(start, difference);
                default:
                    Console.Write("Type: [SkipA] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(start);
                    Console.Write(" ; Common Difference = ");
                    Console.Write(difference);
                    uint skip = (uint)rnd.Next(MIN_SKIP, MAX_SKIP);
                    Console.Write(" ; Skip value: ");
                    Console.WriteLine(skip);
                    return new skipA(skip, start, difference);
            }
        }

        public static mangler getObjMangler()
        {
            Random rnd = new Random();
            int choice = rnd.Next(3);
            int x = rnd.Next(MAX_START);
            int c = rnd.Next(MIN_DIFFERENCE, MAX_DIFFERENCE);
            switch (choice)
            {
                case 0:
                    Console.Write("Type: [Mangler] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(x);
                    Console.WriteLine(" ;");
                    return new mangler(x);
                case 1:
                    Console.Write("Type: [Amplifier] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(x);
                    Console.WriteLine(" ;");
                    return new amplifier(x);
                default:
                    Console.Write("Type: [Puzzler] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(x);
                    Console.Write(" ; Value of c = ");
                    Console.WriteLine(c);
                    return new puzzler(c, x);
            }
        }

        public static void ChangeStates(ArithMangler[] array)
        {
            Random rnd = new Random();
            for (int i = 0; i < array.Length; i++)
            {
                int mode = rnd.Next(NUM_MODES);
                Console.Write("Object ");
                Console.Write(i + 1);
                switch (mode)
                {
                    case 0:
                        Console.WriteLine(" put in state: [ADVANCE]");
                        array[i].advance();
                        break;
                    case 1:
                        Console.WriteLine(" put in state: [STUCK]");
                        array[i].stay();
                        break;
                    default:
                        Console.WriteLine(" put in state: [RETREAT]");
                        array[i].retreat();
                        break;
                }
            }
        }

        public static void Main(string[] args)
        {
            Random rnd = new Random();
            int arr_size = rnd.Next(MIN_SIZE, MAX_SIZE);
            ArithMangler[] collection = new ArithMangler[arr_size];
            for (int i = 0; i < arr_size; i++)
            {
                if(i==0)
                    Console.WriteLine("########################");
                Console.Write("------Object ");
                Console.Write(i + 1);
                Console.WriteLine(" ------");
                collection[i] = new ArithMangler(getObjMangler(), getObjArithS());
                Console.WriteLine("########################");
            }
            for (int i=0; i<arr_size; i++)
            {
                for (int j = 0; j < NUM_MODES; j++)
                {
                    Console.Write("Object");
                    Console.Write(".yield() = ");
                    Console.WriteLine(collection[i].yield());

                    int b = rnd.Next(MIN_SIZE, MAX_START);
                    Console.Write("Object");
                    Console.Write(".yield(");
                    Console.Write(b);
                    Console.Write(")= ");
                    Console.WriteLine(collection[i].yield(b));
                }
                ChangeStates(collection);
            }
            Console.Write("Objects mode changes: ");
            Console.WriteLine(collection[0].modeChanges());
        }
        
    }
}
