import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

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

		// Sorting the String ArrayList using shell sort
		ArrayList<HashMap<String, Integer>> sortedArray = shellSortInputArray(array);

		// Perform the search algorithm
		int hashMapPos = performInterpolationSearch(sortedArray, item, 0, (sortedArray.size() - 1));

		// Finding the original index of item
		int pos = sortedArray.get(hashMapPos).get(item);

		// Returning the position of the item in the original, unsorted array
		return pos;
		
	}

	/**
	 * Method to perform interpolation search using recursion
	 * @param sortedArray
	 * @param item
	 * @param low
	 * @param high
	 * @return Position of the item in the sorted array
	 */
	private static int performInterpolationSearch(ArrayList<HashMap<String, Integer>> sortedArray, String item, int low, int high) {

		int pos;

		if (low <= high && item.compareTo(stringAtIndex(sortedArray, low)) >= 0 && item.compareTo(stringAtIndex(sortedArray, high)) <= 0) {

			// Assuming uniform distribution
			pos = posFormula(sortedArray, item, low, high);

			// Found the item
			if (stringAtIndex(sortedArray, pos).equals(item)) {
				// Returning the position (within sortedArray)
				return pos;
			}

			// If our item is 'larger', we take the right sub-array
			if (stringAtIndex(sortedArray, pos).compareTo(item) < 0) {
				return performInterpolationSearch(sortedArray, item,pos + 1, high);
			}

			// If our item is 'smaller', we take the left sub-array
			if (stringAtIndex(sortedArray, pos).compareTo(item) > 0) {
				return performInterpolationSearch(sortedArray, item, low,pos - 1);
			}

		}

		// Returning -1 if the item is not found
		return -1;

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
	private static int posFormula(ArrayList<HashMap<String, Integer>> array, String item, int low, int high) {

		// Using the String compareTo() method
		// 	- It is comparison based on the unicode value of each character in the strings
		// 	- compareTo() returns 0 if the strings are equal
		// 	- It returns < 0 if the the string is less than the other string (and vice versa)
		return low + ((item.compareTo(stringAtIndex(array, low)) * (high - low))) / (stringAtIndex(array,high).compareTo(stringAtIndex(array,low)));

	}

	/**
	 * Method to get the key from the HashMap at a specific index in the ArrayList
	 * @param array
	 * @param index
	 * @return Name (String)
	 */
	private static String stringAtIndex(ArrayList<HashMap<String, Integer>> array, int index) {

		return array.get(index).keySet().toArray()[0].toString();

	}

	/**
	 * Utilising code from the previous question to sort the String ArrayList using shell sort
	 * 	- The only modification was to use the compareTo() method to compare the strings according to their unicode values
	 * @param array
	 * @return The sorted array
	 */
	private static ArrayList<HashMap<String, Integer>> shellSortInputArray(ArrayList<String> array) {

		// Populating the output ArrayList with HashMaps defining the strings with their respective original index positions (from the unsorted array)
		// This is so that we can return the position of item in the unsorted array after we have performed interpolation search on the sorted array
		ArrayList<HashMap<String, Integer>> output = populateArrayListHashMap(array);

		// ArrayList holding the pre-defined gaps for the search
		ArrayList<Integer> gaps = new ArrayList<>(Arrays.asList(511, 255, 127, 63, 31, 15, 7, 3, 1));

		// Looping through each gap
		for (Integer gap : gaps) {

			// Iterating through the array, started at index = gap
			for (int i = gap; i < output.size(); i += 1) {

				// Getting the value of the element currently at position i
				HashMap<String, Integer> temp = output.get(i);

				int j;
				// The expression "(stringAtIndex(output,j - gap)).compareTo(temp.keySet().toArray()[0].toString()) > 0" checks if the unicode values
				// Of the string stringAtIndex(output,j - gap) are greater than that of the string in temp.
				for (j = i; j >= gap && (stringAtIndex(output,j - gap)).compareTo(temp.keySet().toArray()[0].toString()) > 0; j -= gap) {

					// Updating the element at index = j to be the element at index = j - gap
					output.set(j, output.get(j - gap));

				}

				// Put the original element at index = i in its correct location
				output.set(j, temp);

			}

		}

		// Returning the sorted array
		return output;

	}

	/**
	 * Method to create an ArrayList of Hashmaps where there is one HashMap (containing the string and index position)
	 * for each element in the input array.
	 * @param array
	 * @return ArrayList of HashMaps
	 */
	private static ArrayList<HashMap<String, Integer>> populateArrayListHashMap(ArrayList<String> array) {

		ArrayList<HashMap<String, Integer>> output = new ArrayList<>();

		for (int i = 0; i < array.size(); i += 1) {

			HashMap<String, Integer> tempHashMap = new HashMap<>();
			tempHashMap.put(array.get(i), i);
			output.add(tempHashMap);

		}

		return output;

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
