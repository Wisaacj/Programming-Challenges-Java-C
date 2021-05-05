/*
 ============================================================================
 Name        : CWK2Q5.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement an algorithm in C which given a file containing a block of text as
 input, redacts all words from a given set of “redactable” words (also from a
 file), and outputs the result to a file called “result.txt”. For example,
 given the block of text:
    The quick brown fox jumps over the lazy dog

 and the redactable set of words:
    the, jumps, lazy

 the output text in “result.txt” should be
    *** quick brown fox ***** over *** **** dog

 Note that the number of stars in the redacted text is the same as the number
 of letters in the word that has been redacted, and that capitalization is
 ignored. You should not use any of the string libraries to answer this
 question. You should also test your program using the example files
 provided.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

/* ~~~~~~~~~~~~ Global Variables ~~~~~~~~~~~~ */

char** redact_words_file;
char** input_words_file;
char** output_file;

int redact_no_lines;
int input_no_lines;

FILE *input, *redact, *result;

/* ~~~~~~~~~~~~ String Manipulation and Comparison Functions ~~~~~~~~~~~~ */

// Function to count the number of characters in a string
int string_length(const char *string) {

    int count = 0;
    while(string[count] != '\0') {
        count++;
    }
    return count;

}

// Function to copy a string from one char array to another
char *string_copy(char *destination, const char *source) {
    char *pointer = destination;

    while ((*pointer = *source) != '\0') {
        pointer++;
        source++;
    }

    return destination;

}

int split_string(char *string, char token) {

    static int start_index;

    if (start_index == 0x0) {
        start_index = 0;
    }

    for (int i = start_index; i < string_length(string); i++) {

        if (string[i] == token) {

            start_index = i+1;
            return i;

        }

    }

    return -1;

}

// Function to create a substring of a string and copy it to a destination variable
char *substring(char *dest, const char *source, int start, int end) {

    int i = 0;
    while (end - i > start) {

        // Using pointer arithmetic to copy the characters across one by one
        *dest = *(source + start);

        // Incrementing the char pointers by one
        dest++;
        source++;

        i++;

    }

    *dest = '\0';

    return dest;

}

// Function to check whether a character is in the alphabet (i.e. not a punctuation character)
int is_alpha(char letter) {

    return ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'));

}

// Function to convert strings to lowercase
char *to_lower(char *dest, const char*source) {

    for (int i = 0; i < string_length(source); i++) {

        if (source[i] >= 'A' && source[i] <= 'Z') {

            *(dest + i) = source[i] + 32;

        }

    }

    return dest;

}

// Function to compare two strings
int string_compare(const char *string1, const char *string2) {

    char *string1_lower;
    char *string2_lower;

    string_copy(string1_lower, string1);
    string_copy(string2_lower, string2);

    string1_lower = to_lower(string1_lower, string1);
    string2_lower = to_lower(string2_lower, string2);

    while (*string1_lower && *string1_lower == *string2_lower) {
        ++string1_lower;
        ++string2_lower;
    }

    return (int) (unsigned char) (*string1_lower) - (int) (unsigned char) (*string2_lower);

}

/* ~~~~~~~~~~~~ File Opening Functions ~~~~~~~~~~~~ */

// Function to open the redact words file and output it to an array of strings
int open_redact_words(const char *redact_words_filename) {

    // Setting up a count for the number of lines in the redact words file
    redact_no_lines = 0;

    // Initially allocating an arbitrary amount of memory for the redact words file
    redact_words_file = (char**) malloc(255*sizeof(char*));

    // Creating a buffer to hold each line from the file
    char buffer[1024];

    // Assigning the FILE pointer 'redact' to the file 'redact.txt'
    redact = fopen(redact_words_filename, "r");

    // If the file failed to open, return false
    if (redact == 0x0) {
        perror("Failed to open file...");
        return 0;
    }

    while(fgets(buffer, 1024, redact)) {


        redact_words_file[redact_no_lines] = (char *) malloc((string_length(buffer) + 1) * sizeof(char));
        string_copy(redact_words_file[redact_no_lines], buffer);
        printf("Line %d: %s with length %d\n", redact_no_lines, redact_words_file[redact_no_lines], string_length(buffer));
        redact_no_lines++;

        /* Use this section when you want to parse multiple words on each line
        int start_index = 0;

        for (int i = 0; i < 1024; i++) {

            if (buffer[i] == ' ' && in_alphabet(buffer[i+1]) {

                char *temp_word;
                substring(temp_word, buffer, start_index, i-1);
                printf("The current word is: %s\n", temp_word);
                start_index = i+1;

            }

        }
        */

    }

    fclose(redact);

    // Reallocating the memory for the redact_words_file variable to the correct size
    redact_words_file = (char**) realloc(redact_words_file, redact_no_lines*sizeof(char*));

    return 1;

}

int open_input_file(const char*text_filename) {

    // Setting up a count for the number of lines in the redact words file
    input_no_lines = 0;

    // Initially allocating an arbitrary amount of memory for the redact words file
    input_words_file = (char**) malloc(255*sizeof(char*));

    // Creating a buffer to hold each line from the file
    char buffer[2048];

    // Assigning the FILE pointer 'redact' to the file 'redact.txt'
    input = fopen(text_filename, "r");

    // If the file failed to open, return false
    if (input == 0x0) {
        perror("Failed to open file...");
        return 0;
    }

    while(fgets(buffer, 2048, input)) {

        input_words_file[input_no_lines] = (char*) malloc((string_length(buffer) + 1)*sizeof(char));
        string_copy(input_words_file[input_no_lines], buffer);
        printf("Line %d: %s with length %d\n", input_no_lines, input_words_file[input_no_lines], string_length(buffer));
        input_no_lines++;

    }

    fclose(input);

    // Reallocating the memory for the redact_words_file variable to the correct size
    input_words_file = (char**) realloc(input_words_file, input_no_lines*sizeof(char*));

    return 1;

}

/* ~~~~~~~~~~~~ Parsing Functions ~~~~~~~~~~~~ */

// Function to check whether the current word is in the redact words file
int in_redact_words(char *word) {

    for (int i = 0; i < redact_no_lines; i++) {

        // Need to convert the words to lower case
        if (string_compare(word, redact_words_file[i]) == 0) {

            return 1;

        }

    }

    return 0;

}

void parse_input_words() {

    for (int i = 0; i < input_no_lines; i++) {

        char *current_word;
        char *current_line = input_words_file[i];
        int index_of_last_word = 0;

        for (int j = 0; j < string_length(input_words_file[i]); j++) {

            if (input_words_file[i][j] == ' ' && is_alpha(input_words_file[i][j+1])) {


                substring(current_word, current_line, index_of_last_word, j-1);
                printf("Current word: %s", current_word);

            }

        }

    }

}

/* ~~~~~~~~~~~~ Main Functions ~~~~~~~~~~~~ */

void redact_words(const char *text_filename, const char *redact_words_filename){

    printf("---------------------------------------\n");
    printf("Reading from %s\n", text_filename);
    printf("Reading redact words from %s\n", redact_words_filename);
    printf("---------------------------------------\n");

    open_redact_words(redact_words_filename);
    open_input_file(text_filename);

    parse_input_words();

}

int main(int argc, char *argv[]) {
	const char *input_file = "C:\\Users\\Will\\Documents\\GitHub\\PoP-CW2-Programming-Challenges\\Q5\\debate.txt";
	const char *redact_file = "C:\\Users\\Will\\Documents\\GitHub\\PoP-CW2-Programming-Challenges\\Q5\\redact.txt";
	redact_words(input_file, redact_file);
	return EXIT_SUCCESS;
}
