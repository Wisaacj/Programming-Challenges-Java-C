import java.io.*;
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

	/**
	 * Main method to control the redact process
	 * @param textFilename
	 * @param redactWordsFilename
	 */
	public static void redactWords(String textFilename, String redactWordsFilename){

		// Opening the two files and appending each line to an ArrayList of strings
		ArrayList<String> textFile = openFile(textFilename);
		ArrayList<String> redactFile = openFile(redactWordsFilename);

		// Splitting the lines in the redact file such that each word is on its own line
		redactFile = splitRedactFile(redactFile);
		// Removing all the 'redact' words from the text file (using the words given in the redact file)
		textFile = removeRedactWords(textFile, redactFile);
		// Removing all the proper nouns from the text file
        textFile = removeProperNouns(textFile);
        // This line is just for debugging
        printFile(textFile);

        // Output the results of all the parsing to a text file called 'result.txt'
        outputFile(textFile);

	}

	/**
	 * Method to remove all the specified words that need to be redacted from the text file
	 * @param file
	 * @param redactFile
	 * @return An ArrayList of strings with stars in place of the redacted words
	 */
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

	private static ArrayList<String> removeProperNouns(ArrayList<String> file) {

		ArrayList<String> output = new ArrayList<>();

		// Looping through each string in the ArrayList
		for (String s : file) {

			// Splitting each line into individual words
			String[] splits = s.split(" ");

			// Using StringBuilder so that we can concatenate the strings
            StringBuilder tempString = new StringBuilder();

            // Looping through each string in splits
            for (int i = 0; i < splits.length; i++) {

                // Checking if the word is a proper noun
                if (i != 0 && isNoun(splits[i], splits[i-1])) {

                    // Appending the 'starred' out word with a space after it if the word is a proper noun
                    tempString.append(convertToStars(splits[i])).append(" ");

                } else {

                    // Appending the original word with a space after it
                    tempString.append(splits[i]).append(" ");

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

	    // Integer variable to reduce the number of stars in the output string if there is any punctuation in word
	    int reduceLength = 0;

	    // Declaring a string variable to hold any punctuation which needs to be appended to the end of output
        String addPunctuation = "";

	    // Initialising a variable 'punctuation' to contain all the punctuation characters we will look out for
        String punctuation = ".,:;";

		// Using StringBuilder so that we can concatenate the stars
		StringBuilder output = new StringBuilder();

		// Checking if 'word' contains any punctuation
		for (int i = 0; i < word.length(); i++) {
            if (punctuation.contains(word.substring(i, i+1))) {
                // 'word' contains punctuation
                // Adding the punctuation to a temp String variable which will be used to append the punctuation to output
                addPunctuation = word.substring(i, i+1);
                // Incrementing the reduce length variable
                reduceLength += 1;
            }
        }

		// Appending (word.length() - reduceLength) number of "*"s to output
		output.append("*".repeat(word.length() - reduceLength));
		// Appending any punctuation which was previously included in 'word'
        output.append(addPunctuation);

		// Converting output to a string and returning it
		return output.toString();

	}

    /**
     * Method to check whether a word in a sentence is a proper noun
     * @param currWord
     * @param previousWord
     * @return Boolean variable to indicate whether the word is a proper noun or not
     */
	private static boolean isNoun(String currWord, String previousWord) {

	    boolean noun = false;

	    // Checking if currWord == null
        if (currWord.equals("")) {
            return false;
        }

	    // Checking if the first character is uppercase and the previous currWord's last character is not a full stop
	    if (Character.isUpperCase(currWord.charAt(0)) && !(previousWord.endsWith("."))) {

	        // Checking if the currWord is just one character long (i.e. currWord = "I")
            if (currWord.length() == 1) {
                return false;
            }

            for (int i = 1; i < currWord.length(); i++) {

                if (Character.isUpperCase(currWord.charAt(i))) {

                    return false;

                }

            }

            noun = true;

        }

	    return noun;

    }

	/**
	 * Method to check if the word needs to be redacted (using the redact file as guidlines0
	 * @param redactFile
	 * @param word
	 * @return Boolean saying whether or not the word needs to be redacted
	 */
	private static boolean redactable(ArrayList<String> redactFile, String word) {

        // Removing all the punctuation from the word
        word = word.replaceAll("\\p{Punct}", "");

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

		for (String s : file) {
			System.out.println(s);
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

	private static void outputFile(ArrayList<String> file) {

	    // Initialising a BufferedWriter variable
	    BufferedWriter bw = null;

	    try {

	        // Instantiating the BufferedWriter
	        bw = new BufferedWriter(new FileWriter("./result.txt"));

	        // Writing each line in 'file' to './result.txt'
	        for (String line : file) {

	            bw.write(line);
	            bw.newLine();

            }

        } catch (IOException e) {

	        e.printStackTrace();

        } finally {

	        try {

	            if (bw != null) {

	                bw.close();

                }

            } catch (IOException e) {

	            e.printStackTrace();

            }

        }

    }

	public static void main(String[] args) {
		String inputFile = "./warandpeace.txt";
		String redactFile = "./redact.txt";
		redactWords(inputFile, redactFile);
	}

}
