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

void encrypt_columnar(const char *message_filename, const char *key, char **result){

    // Getting the data from the input data file
    char *all_letters = open_input_file(message_filename);

    printf("%s\n", all_letters);

    // Freeing the memory being used by 'all_letters'
    free(all_letters);

}

int main(int argc, char *argv[]) {
	const char *example_message = "../text.txt";
	const char *example_key = "LOVELACE";
	char *encrypted_message = NULL;
	encrypt_columnar(example_message, example_key, &encrypted_message);
	printf("Encrypted message = %s\n", encrypted_message);
	// insert more code here :-)
	return EXIT_SUCCESS;
}
