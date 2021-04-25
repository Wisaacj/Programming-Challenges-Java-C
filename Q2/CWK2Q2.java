import java.util.ArrayList;
import java.util.Arrays;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 2:
 *
 *  Implement interpolation search for a list of Strings in Java
 *  using the skeleton class provided. The method should return
 *  the position in the array if the string is present, or -1 if
 *  it is not present.
*/

public class CWK2Q2 {

	public static int interpolation_search(ArrayList<String> array, String item) {

		int pos = 0;

		ArrayList<String> sortedArray = shellSortInputArray(array);

		System.out.println(Arrays.toString(sortedArray.toArray()));

		return pos;
		
	}

	/**
	 * Utilising code from the previous question to sort the String ArrayList using shell sort
	 * 	- The only modification was to use the compareTo() method to compare the strings
	 * @param array
	 * @return The sorted array
	 */
	private static ArrayList<String> shellSortInputArray(ArrayList<String> array) {

		// ArrayList holding the pre-defined gaps for the search
		ArrayList<Integer> gaps = new ArrayList<>(Arrays.asList(511, 255, 127, 63, 31, 15, 7, 3, 1));

		// Looping through each gap
		for (Integer gap : gaps) {

			// Iterating through the array, started at index = gap
			for (int i = gap; i < array.size(); i += 1) {

				// Getting the value of the element currently at position i
				String temp = array.get(i);

				int j;
				// The expression "array.get(j - gap).compareTo(temp) > 0" checks if the unicode values
				// Of  the string array.get(j-gap) are greater than that of temp.
				for (j = i; j >= gap && array.get(j - gap).compareTo(temp) > 0; j -= gap) {

					// Updating the element at index = j to be the element at index = j - gap
					array.set(j, array.get(j - gap));

				}

				// Put the original element at index = i in its correct location
				array.set(j, temp);

			}

		}

		// Returning the sorted array
		return array;

	}

	/**
	 * Method to calculate the positional value of the item string being searched
	 * - Using the String compareTo() method
	 * - It is comparison based on the unicode value of each character in the strings
	 * - compareTo() returns 0 if the strings are equal
	 * - It returns < 0 if the the string is less than the other string (and vice versa)
	 * @param array
	 * @param item
	 * @param low
	 * @param high
	 * @return
	 */
	private static int posFormula(ArrayList<String> array, String item, int low, int high) {

		// Using the String compareTo() method
		// It is comparison based on the unicode value of each character in the strings
		// compareTo() returns 0 if the strings are equal
		// It returns < 0 if the the string is less than the other string (and vice versa)
		return low + (item.compareTo(array.get(low)) * (high - low)) / (array.get(high).compareTo(array.get(low)));

	}

	public static void main(String[] args) {
		ArrayList<String> testList = new ArrayList<String>();
		testList.add("Hello");
		testList.add("World");
		testList.add("How");
		testList.add("Are");
		testList.add("You");

		int result = interpolation_search(testList, "How");
		System.out.println("Result = " + result);
	}
}
