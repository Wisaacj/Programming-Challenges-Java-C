import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.math.BigDecimal;
import java.math.RoundingMode;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 1:
 *
 *  Implement the Shellsort algorithm (https://en.wikipedia.org/wiki/Shellsort) 
 *  for an array of up to 1000 signed doubles in Java. Your solution must use 
 *  concrete gaps of [1, 3, 7, 15, 31, 63, 127, 255, 511]. Your solution must 
 *  print the (partially) sorted array after each gap on a new line in the form:
 *      [a0, a1, a2, a3, ..., an]
 *  Where an is the nth element in the (partially) sorted array (please note 
 *  the space after the commas), and each element should be formatted to 2 
 *  decimal places (e.g. 1.00).
 *
*/

public class CWK2Q1 {

	/**
	 * Method to perform shell sort search
	 * @param array
	 */
	public static void shell_sort(ArrayList<Double> array) {

		// Perform check that the array contains <= 1000 elements
		if (isValidArray(array)) {

			// ArrayList holding the pre-defined gaps for the search
			ArrayList<Integer> gaps = new ArrayList<>(Arrays.asList(511, 255, 127, 63, 31, 15, 7, 3, 1));

			// Looping through each gap
			for (Integer gap : gaps) {

				// Iterating through the array, started at index = gap
				for (int i = gap; i < array.size(); i += 1) {

					// Getting the value of the element currently at position i
					double temp = array.get(i);

					int j;
					for (j = i; j >= gap && array.get(j - gap) > temp; j -= gap) {

						// Updating the element at index = j to be the element at index = j - gap
						array.set(j, array.get(j - gap));

					}

					// Put the original element at index = i in its correct location
					array.set(j, temp);

				}

				// Printing out the partially (or fully) sorted ArrayList
				printArray(array);

			}

		} else {

			System.out.println("Err: Array is too large... must contain <= 1000 elements");

		}
		
	}

	/**
	 * Method to check whether the input ArrayList is valid
	 * @param array
	 * @return Boolean to indicate whether the ArrayList is valid or not
	 */
	private static Boolean isValidArray(ArrayList<Double> array) {

		return array.size() <= 1000;

	}

	/**
	 * Method to print out the ArrayList in the specified format (to 2 d.p.)
	 * @param array
	 */
	private static void printArray(ArrayList<Double> array) {

		System.out.print("[");

		for (int i = 0; i < array.size(); i += 1) {

			if (i == array.size() -1) {
				System.out.printf("%.2f", array.get(i));
			} else {
				System.out.print(String.format("%.2f", array.get(i)) + ", ");
			}


		}

		System.out.print("]\n");

	}

	public static void main(String[] args) {
		ArrayList<Double> testList = new ArrayList<Double>();
		testList.add(3.4);
		testList.add(6.55);
		testList.add(-12.2);
		testList.add(1.73);
		testList.add(140.98);
		testList.add(-4.18);
		testList.add(52.87);
		testList.add(99.14);
		testList.add(73.202);
		testList.add(-23.6);
		
		shell_sort(testList);
	}
}
