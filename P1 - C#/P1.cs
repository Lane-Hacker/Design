/*
 * @Author: Patrick Manacorda
 * @Date: October 1st 2019
 * @Revision: 6.0
 */

/*
 *  @PROGRAM OVERVIEW:
 *  This program aims at demonstrating the functionality of the intDiv type.
 *  It tries to accomplish this by following these logical steps:
 *  -It creates between 2 and 5 intDiv objects (chosen randomly at runtime)
 *  -Initializes the intDiv objects with values between 1 and 100 (chosen randomly at runtime)
 *  -Iterates through the objects between 2 and 5 times (chosen randomly at runtime)
 *      -On every iteration every object is tested with a random value between 0 and it's div value
 *      -On every iteration one object is randomly chosen to be revived
 *      -Every two iterations one object is randomly chosen to be reset
 *  -Console output reports any changes in the objects states after every iteration
 *  
 *  @Error processing: None, Error values may be returned by the intDiv class methods (see intDiv.cs)
 *  @Environment assumptions: output tied to System.Console
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace ProjectOne
{
    public class driver
    {
        const int MIN_ARRAY_SIZE = 2;
        const int MAX_ARRAY_SIZE = 6;
        const int MAX_ITERATIONS = 5;
        const int MIN_ITERATIONS = 2;
        const int MAX_DIV_VALUE = 100;
        public static void main()
        {
            intDiv[] intDivArray = initialize_array();
            display_array(intDivArray);
            execute_operations(intDivArray);
        }

        private static intDiv[] initialize_array()
        {
            Console.WriteLine("Initializing random distribution of intDiv objects...");
            Random rand = new Random();
            int size_of_array = rand.Next(MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
            intDiv[] intDivArray = new intDiv[size_of_array];
            Console.Write("* Number of objects: ");
            Console.WriteLine(size_of_array);
            for(int i=0; i<size_of_array; i++){
                intDivArray[i] = new intDiv((uint)rand.Next(MAX_DIV_VALUE));
            }
            Console.WriteLine("----------------------");
            return intDivArray;
            
        }

        private static void display_array(intDiv[] array)
        {
            for (int i=0; i<array.Length; i++)
            {
                Console.Write("Obj");
                Console.Write(i + 1);
                Console.Write(" -- [div: ");
                Console.Write(array[i].getDiv());
                Console.Write("  /  active: ");
                if (array[i].getActive())
                    Console.Write("True ");
                else
                    Console.Write("False ");
                Console.Write("/  deactivated: ");
                if (array[i].getDeactivated())
                    Console.WriteLine("True]");
                else
                    Console.WriteLine("False]");
            }
            Console.WriteLine("----------------------");
        }

        private static void execute_operations(intDiv[] array)
        {
            Random rnd = new Random();
            int num_iterations = rnd.Next(MIN_ITERATIONS, MAX_ITERATIONS);
            for(int i=0; i<num_iterations; i++)
            {
                Console.Write("    ITERATION NUMBER ");
                Console.WriteLine(i + 1);
                for(int j=0; j<array.Length; j++)
                {
                    int denominator = rnd.Next(0, (int)array[j].getDiv());
                    Console.Write("Remainder of Obj");
                    Console.Write(j + 1);
                    Console.Write(" with div ");
                    Console.Write(array[j].getDiv());
                    Console.Write(" and denominator ");
                    Console.Write(denominator);
                    Console.Write(" is: ");
                    Console.WriteLine(array[j].test((uint)denominator));
                }
                int revive_indx = rnd.Next(0, array.Length);
                Console.Write("Attempting revive on Obj");
                Console.Write(revive_indx + 1);
                Console.Write(" with active state: ");
                Console.WriteLine(array[revive_indx].getActive());
                array[revive_indx].revive();
                if ((i + 1) % 2 == 0)
                {
                    int reset_indx = rnd.Next(0, array.Length);
                    Console.Write("Executing Reset on Obj");
                    Console.WriteLine(reset_indx + 1);
                    array[reset_indx].reset();
                }
                display_array(array);
            }
        }
    }
}

