x/* @Author: Patrick Manacorda
 * @Date: October 2019
 * @See: Seattle University Fall Quarter 2019
 */

 /* -------- PROGRAM OVERVIEW -------------
  * This program aims at showing off the functionality of heterogeneous collections for polymorphic behaviour
  * 1) An array of parent (base) type is generated with size between MIN_SIZE and MAX_SIZE (random at runtime)
  * 2) Each slot in array is initialized with one of three types: arithS, oscillateA, skipA. (random decision at runtime)
  * 3) Mode changes for each object are triggered
  * 4) The first N_TERMS of the sequence are printed to console
  * 5) Mode changes again
  * 6) Another N_TERMS of the sequence are printed to console
  * 7) Total number of queries is printed to screen
  * 
  * Note: Forbidden set injection and testing is performed in unit tests
  *       The possibility of injecting random forbidden sets to show off functionality and
  *       behaviour has been considered but rejected since the chance of randomly choosing values
  *       that are in the random arithmetic sequence is extremely unlikely (thus it would be pointless
  *       if the attempt is to show off functionality in a consistent manner).
  */


using System;
using System.Collections.Generic;
using System.Text;

namespace Project3
{
    public class P3
    {
        const int MAX_START = 100;
        const int MAX_DIFFERENCE = 20;
        const int MIN_DIFFERENCE = 2;
        const int NUM_MODES = 3;
        const int MAX_SKIP = 10;
        const int MIN_SKIP = 1;
        const int MAX_SIZE = 10;
        const int MIN_SIZE = 5;
        const int N_TERMS = 10;
        public static void Main(string[] args)
        {
            Random rnd = new Random();
            int size = rnd.Next(MIN_SIZE, MAX_SIZE);
            print_numQueries();
            arithS[] heterogenous = new arithS[size];
            GetObjects(heterogenous);
            print_numQueries();
            ChangeStates(heterogenous);
            print_numQueries();
            BasicYield(heterogenous);
            print_numQueries();
            ChangeStates(heterogenous);
            BasicYield(heterogenous);
            print_numQueries();
        }
        public static void print_numQueries()
        {
            Console.Write("Total number of queries: ");
            Console.WriteLine(arithS.num_queries);
        }

        public static void ChangeStates(arithS[] array)
        {
            Random rnd = new Random();
            for (int i=0; i<array.Length; i++)
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

        public static void BasicYield(arithS[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write("Object ");
                Console.Write(i + 1);
                Console.Write(" -> yield() = { ");
                for (int j = 0; j < N_TERMS; j++)
                {
                    int value = array[i].yield();
                    Console.Write(value);
                    if (j + 1 != N_TERMS)
                        Console.Write(" , ");
                    else
                        Console.WriteLine(" } ");
                }
            }
        }
        public static void GetObjects(arithS[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write("Generating object ");
                Console.Write(i + 1);
                Console.Write("...  ");
                array[i] = getObj();
            }
        }

        public static arithS getObj()
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
                    return new arithS(start,difference, null);
                case 1:
                    Console.Write("Type: [OscillateA] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(start);
                    Console.Write(" ; Common Difference = ");
                    Console.WriteLine(difference);
                    return new OscillateA(start, difference, null);
                default:
                    Console.Write("Type: [SkipA] ; ");
                    Console.Write("Starting value = ");
                    Console.Write(start);
                    Console.Write(" ; Common Difference = ");
                    Console.Write(difference);
                    uint skip = (uint)rnd.Next(MIN_SKIP, MAX_SKIP);
                    Console.Write(" ; Skip value: ");
                    Console.WriteLine(skip);
                    return new skipA(skip,start,difference, null);
            }
        }
    }
}
