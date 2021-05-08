/*
 ============================================================================
 Name        : CWK2Q7.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement a Columnar Transposition Cipher in C to encrypt a message of any
 length. A Columnar Transposition Cipher is transposition cipher that follows
 a simple rule for mixing up the characters in the plaintext to form the
 ciphertext.

 As an example, to encrypt the message ATTACKATDAWN with the keyword KEYS,
 we first write out our message as shown below,
    K	E	Y	S
    A	T	T	A
    C	K	A	T
    D	A	W	N

 Note: if the message to encode does not fit into the grid, you should pad
 the message with x's or random characters for example, ATTACKNOW with the
 keyword KEYS might look like below,
    K	E	Y	S
    A	T	T	A
    C	K	N	O
    W	X	X	X

 Once you have constructed your table, the columns are now reordered such
 that the letters in the keyword are ordered alphabetically,
    E	K	S	Y
    T	A	A	T
    K	C	T	A
    A	D	N	W

 The ciphertext is now read off along the columns, so in our example above,
 the ciphertext is TAATKCTAADNW.

 You should demonstrate your implementation by encrypting the file in the
 folder Q7 using the keyword - LOVELACE.

 ============================================================================
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Integer variable to hold the number of rows in the 2d array
int no_rows;

char *open_input_file(const char*text_filename) {

    // Declaring the file pointer
    FILE *input;

    // Initialising a variable to hold the total number of letters in the input_letters char array
    int no_letters = 0;

    // Initialising a variable 'input_letters_size' which holds the current size of the input_letters array
    int input_letters_size = 2048;

    // Initially allocating an arbitrary amount of memory for the redact words file
    char* input_letters = (char*) malloc(input_letters_size*sizeof(char));

    // Assigning the FILE pointer
    input = fopen(text_filename, "r");

    // If the file failed to open, return false
    if (input == 0x0) {
        perror("Failed to open file...");
        return NULL;
    }

    // Running the loop until we reach the end of the file
    do {

        char curr_char = fgetc(input);

        // Checking for the end of the file
        if (feof(input)) {
            break;
        }

        // Removing the spaces, newline characters, and punctuation from the char array
        if (curr_char == ' ' || curr_char == '\n' || isalpha(curr_char) == 0) {
            continue;
        }

        input_letters[no_letters] = curr_char;

        // Resizing the char array if the total number of letters is getting close to using up all of the (currently) allocated memory
        if (((float) no_letters / (float) input_letters_size) > 0.8) {
            input_letters_size *= 2;
            input_letters = (char*) realloc(input_letters, input_letters_size*sizeof(char));
        }

        no_letters++;

    } while(1);

    fclose(input);

    // Reallocating the memory for the redact_words_file variable to the correct size
    input_letters = (char*) realloc(input_letters, no_letters*sizeof(char));

    return input_letters;

}

char **form_2d_array(char *all_letters, const char *key) {

    int key_length = strlen(key);
    no_rows = (int) ((double) (strlen(all_letters) + key_length) / (double) key_length) + 1;

    // Assigning memory for the 2d char array
    char **char_array = (char**) malloc(sizeof(char*)*no_rows);

    // Assigning memory for each row
    for (int i = 0; i < no_rows; i++) {
        // (key_length + 1) is used so that there is space for the null terminator also
        char_array[i] = (char*) malloc(sizeof(char)*(key_length+1));
    }

    strcpy(char_array[0], key);

    int count = 0;
    for (int i = 1; i < no_rows; i++) {
        int internal_count = 0; // Resetting internal_count to allow for placeholder values to be inputted into rows which aren't full
        for (int j = 0; j < key_length; j++) {
            // If there is still space in the 2d array after all the characters from 'all_letters' have been inserted, add placeholder characters
            if (count >= strlen(all_letters)) {
                char_array[i][j] = '5';
                continue;
            }

            char_array[i][j] = all_letters[count];
            internal_count++;
            count++;
        }
        // Adding the null terminator to the end of each row
        char_array[i][key_length] = '\0';
    }

    return char_array;

}

void print_2d_array(char **array) {

    // Looping through each row in the array and printing out the corresponding string
    for (int i = 0; i < no_rows; i++) {
        printf("Count %d: %s\n", i, array[i]);
    }

}

int *sort_key_alphabetically(const char* key) {

    // Defining an array to keep track of how the indexes change whilst the key is being sorted alphabetically
    int length_of_key = strlen(key);
    int *index_array = (int*) malloc(sizeof(int)*length_of_key);
    for (int i = 0; i < length_of_key; i++) {
        index_array[i] = i;
    }

    // Defining an array to hold the sorted key
    char *sorted_key = (char*) malloc(sizeof(char)*length_of_key+1);
    sorted_key[length_of_key] = '\0';

    /* Bubble sort the characters in 'key' */
    // Algorithm found on: https://stackoverflow.com/questions/9809839/bubble-sort-a-character-array-in-alphabetic-order-in-c
    // Initialise the sorted_key array to hold pointers to each element in key
    for (int i = 0; i < length_of_key; i++) {
        sorted_key[i] = key[i];
    }

    // Declaring temp variables which will be used during the swaps in bubble sort
    char temp_char;
    int temp_int;

    // Sort the array using bubble sort
    for (int i = 0; i < length_of_key; i++) {
        for (int j = 0; j < length_of_key-1; j++) {
            if (sorted_key[j] > sorted_key[j+1]) {
                temp_char = sorted_key[j];
                temp_int = index_array[j];

                sorted_key[j] = sorted_key[j+1];
                index_array[j] = index_array[j+1];

                sorted_key[j+1] = temp_char;
                index_array[j+1] = temp_int;
            }
        }
    }

    printf("Sorted key: %s\n", sorted_key);

    // Printing the index array after being sorted
    for (int i = 0; i < length_of_key; i++) {
        printf("%d ", index_array[i]);
    }

    printf("\n");

    // Freeing the memory used by 'sorted_array'
    free(sorted_key);

    return index_array;

}

char *get_cipher_string(char **array, int no_characters, int key_length, const int *sorted_key_index_array) {

    char *output = (char*) malloc(sizeof(char)*(no_characters+1));

    int count = 0;
    for (int i = 1; i < no_rows; i++) {
        for (int j = 0; j < key_length; j++) {
            output[count] = array[i][sorted_key_index_array[j]];
            count++;
        }
    }

    return output;

}

void encrypt_columnar(const char *message_filename, const char *key, char **result){

    // Getting the data from the input data file
    char *all_letters = open_input_file(message_filename);
    // Putting the data in a 2d array format
    char **letters_array = form_2d_array(all_letters, key);
    // Printing the 2d array
    print_2d_array(letters_array);
    // Getting the indexes of the characters in the sorted key
    int *sorted_key_indexes = sort_key_alphabetically(key);
    // Getting the encrypted string
    char *encrypted_string = get_cipher_string(letters_array, strlen(all_letters), strlen(key), sorted_key_indexes);
    // Setting result equal to the encrypted string
    *result = encrypted_string;

    // Freeing the memory being used by 'all_letters'
    free(all_letters);
    // Freeing the memory being used by 'letters_array'
    free(letters_array);
    // Freeing the memory being used by 'sorted_key_indexes'
    free(sorted_key_indexes);

}

int main(int argc, char *argv[]) {
	const char *example_message = "./text.txt";
	const char *example_key = "LOVELACE";
	char *encrypted_message = NULL;
	encrypt_columnar(example_message, example_key, &encrypted_message);
	printf("Encrypted message = %s\n", encrypted_message);
	// insert more code here :-)

	// Outputting the encrypted message
	FILE *output;
	output = fopen("./output.txt", "w");

	fprintf(output, "%s", encrypted_message);
	fflush(output);
	fclose(output);

	// Freeing the memory used by 'encrypted_message'
	// free(encrypted_message);

	return EXIT_SUCCESS;
}