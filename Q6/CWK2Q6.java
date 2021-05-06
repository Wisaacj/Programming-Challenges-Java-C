import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 6:
 *
 *  Implement in Java a similar algorithm to that in Q5, i.e. given a
 *  block of text your algorithm should be able to redact words from
 *  a given set and outputs the result to a file called â€œresult.txtâ€�.
 *  However, in this implementation of the algorithm all
 *  redactable words will be proper nouns (i.e. a name used for an
 *  individual person, place, or organisation, spelled with an initial
 *  capital letter) and your algorithm should take into account that
 *  the list of redactable words might not be complete. For example,
 *  given the block of text:
 *      It was in July, 1805, and the speaker was the well-known Anna
 *      Pavlovna Scherer, maid of honor and favorite of the Empress
 *      Marya Fedorovna. With these words she greeted Prince Vasili
 *      Kuragin, a man of high rank and importance, who was the first
 *      to arrive at her reception. Anna Pavlovna had had a cough for
 *      some days. She was, as she said, suffering from la grippe;
 *      grippe being then a new word in St. Petersburg, used only by
 *      the elite.
 *
 *  and the redactable set of words
 *      Anna Pavlovna Scherer, St. Petersburg, Marya Fedorovna
 *
 *  the output text should be
 *      It was in ****, 1805, and the speaker was the well-known ****
 *      ******** *******, maid of honor and favorite of the *******
 *      ***** *********. With these words she greeted ****** ******
 *      *******, a man of high rank and importance, who was the first
 *      to arrive at her reception. **** ******** had had a cough for
 *      some days. She was, as she said, suffering from la grippe;
 *      grippe being then a new word in *** **********, used only by
 *      the elite.
 *
 *  You should test your program using the example files provided.
*/

public class CWK2Q6 {

	public static void redactWords(String textFilename, String redactWordsFilename){

		// Opening the two files and appending each line to an ArrayList of strings
		ArrayList<String> textFile = openFile(textFilename);
		ArrayList<String> redactFile = openFile(redactWordsFilename);

		// Splitting the lines in the redact file such that each word is on its own line
		redactFile = splitRedactFile(redactFile);

		// Removing all the 'redact' words from the text file (using the words given in the redact file)
		textFile = removeRedactWords(textFile, redactFile);
		// This line is just for debugging
		printFile(textFile);
		
	}

	private static ArrayList<String> removeRedactWords(ArrayList<String> file, ArrayList<String> redactFile) {

		ArrayList<String> output = new ArrayList<>();

		// Looping through each string in the ArrayList
		for (String s : file) {

			// Splitting each line into individual words
			String[] splits = s.split(" ");

			// Using StringBuilder so that we can concatenate the strings
			StringBuilder tempString = new StringBuilder();

			// Looping through each word in splits
			for (String str : splits) {

				// Checking if the word needs to be redacted
				if (redactable(redactFile, str)) {

					// Appending the 'starred' out word with a space after it
					tempString.append(convertToStars(str)).append(" ");

				} else {

					// Appending the original word with a space after it
					tempString.append(str).append(" ");

				}

			}

			// Adding the line to the output ArrayList
			output.add(tempString.toString());

		}

		return output;

	}

	/**
	 * Method to convert a word into the same sized string, but with stars replacing the letters
	 * @param word
	 * @return A string with a number of stars in it equal to the length of the input word
	 */
	private static String convertToStars(String word) {

		// Using StringBuilder so that we can concatenate the stars
		StringBuilder output = new StringBuilder();

		// Looping for the length of the string and appending the corresponding number of "*"s to output
		output.append("*".repeat(word.length()));

		// Converting output to a string and returning it
		return output.toString();

	}

	/**
	 * Method to check if the word needs to be redacted (using the redact file as guidlines0
	 * @param redactFile
	 * @param word
	 * @return Boolean saying whether or not the word needs to be redacted
	 */
	private static Boolean redactable(ArrayList<String> redactFile, String word) {

		// Looping through all the words in the redact file
		for (String redactWord : redactFile) {

			// If the variable 'word' is a word that needs to be redacted (using words from the file 'redactFile'), return true
			if (redactWord.equals(word)) {

				return true;

			}

		}

		// The word does not need to be redacted
		return false;

	}

	/**
	 * Method to print out the elements of an ArrayList
	 * @param file
	 */
	private static void printFile(ArrayList<String> file) {

		/*
		for (String s : file) {
			System.out.println(s);
		}
		*/

		for (int i = 0; i < 500; i++) {

			System.out.println(file.get(i));

		}

	}

	/**
	 * Method to split the lines in the redact file such that each word is on its own line
	 * @param file
	 * @return An ArrayList of strings with each line containing only one word
	 */
	private static ArrayList<String> splitRedactFile(ArrayList<String> file) {

		ArrayList<String> output = new ArrayList<>();

		for (String s : file) {

			String[] splits = s.split(" ");

			output.addAll(Arrays.asList(splits));

		}

		return output;

	}

	/**
	 * Method to open a file with a given filename
	 * @param filename
	 * @return An ArrayList of strings containing each line of the input file as a string
	 */
	private static ArrayList<String> openFile(String filename) {

		// Instantiating an ArrayList of strings to hold the output
		ArrayList<String> output = new ArrayList<>();

		// Declaring a temp variable 'line' to hold the contents of each line
		String line;
		// Declaring the buffered reader
		BufferedReader br = null;

		try {

			// Instantiating the BufferedReader with the file path (filename)
			br = new BufferedReader(new FileReader(filename));
			// Looping through the file until there are no more lines
			while ((line = br.readLine()) != null) {
				output.add(line); // Adding each line to the output ArrayList
			}

		} catch (FileNotFoundException e) {

			System.err.println("Error: file not found.");

		} catch (IOException e) {

			e.printStackTrace();

		} finally {

			try {

				// Checking if the BufferedReader was successfully instantiated previously
				if (br != null) {
					br.close(); // Closing the BufferedReader
				}

			} catch (IOException e) {

				e.printStackTrace();

			}

		}

		// Returning the file as an ArrayList of strings
		return output;

	}

	public static void main(String[] args) {
		String inputFile = "./warandpeace.txt";
		String redactFile = "./redact.txt";
		redactWords(inputFile, redactFile);
	}

}
