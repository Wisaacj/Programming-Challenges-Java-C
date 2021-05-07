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

// Function to create a substring of a string and copy it to a destination variable
char* substring(const char *src, int start, int end)
{
    // Get the length of the destination string
    int len = end - start;

    // Allocate (len + 1) chars for destination string (including the null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    // Extracts characters between start and end index from source string and copy them into the destination string
    for (int i = start; i < end && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }

    // Add a null termination to the end of the string
    *dest = '\0';

    return dest - len;
}

// Function to check whether a character is in the alphabet (i.e. not a punctuation character)
int is_alpha(char letter) {

    return ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'));

}

// Function to convert strings to lowercase --- Currently not working
char *to_lower(const char *source) {

    char *dest = (char*) malloc(sizeof(char)*string_length(source+1));

    int i = 0;
    while (source[i] != '\0') {
        if (source[i] >= 'A' && source[i] <= 'Z') {
            *(dest + i) = *(source + i) + 32;
        }
        i++;
    }

    return dest;

}

// Function to compare two strings
int string_compare(char *string1, char *string2) {

    while (*string1 == *string2) {
        if (*string1 == '\0' || *string2 == '\n')
            break;

        string1++;
        string2++;
    }

    if (*string1 == '\0' && *string2 == '\n') {
        return 0;
    }
    else {
        return -1;
    }

}

// Function to covert a word to stars
char *convert_to_stars(char *word) {

    char *output = (char*) malloc(string_length(word+1)*sizeof(char));

    for (int i = 0; i < string_length(word); i++) {

        output[i] = '*';

    }

    output[string_length(word)] = '\0';

    return output;

}

// Function to remove a character from a string
void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';

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

        int index_of_last_word = 0;

        // If a line contains multiple redact words, split it into multiple lines
        for (int i = 0; i < 1024; i++) {

            if (buffer[i] == '\0') {
                redact_words_file[redact_no_lines] = (char *) malloc((string_length(buffer) + 1) * sizeof(char));
                string_copy(redact_words_file[redact_no_lines], substring(buffer, index_of_last_word, i));
                printf("Found new redact word: %s\n", redact_words_file[redact_no_lines]);
                redact_no_lines++;
                break;
            }

            if (buffer[i] == ' ') {

                redact_words_file[redact_no_lines] = (char *) malloc((string_length(buffer) + 1) * sizeof(char));
                string_copy(redact_words_file[redact_no_lines], substring(buffer, index_of_last_word, i));
                printf("Found new redact word: %s\n", redact_words_file[redact_no_lines]);
                redact_no_lines++;
                index_of_last_word = i+1;

            }

        }

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
        input_no_lines++;

    }

    fclose(input);

    // Reallocating the memory for the redact_words_file variable to the correct size
    input_words_file = (char**) realloc(input_words_file, input_no_lines*sizeof(char*));

    return 1;

}

/* ~~~~~~~~~~~~ Parsing and File Output Functions ~~~~~~~~~~~~ */

int add_word_to_file(char *word, int line_no) {

    result = fopen("./result.txt", "r+");

    // If the file failed to open, return false
    if (result == 0x0) {
        perror("Failed to open file...");
        return 0;
    }

    fseek(result, 0, SEEK_END);

    fprintf(result, "%s ", word);
    fflush(result);
    fclose(result);

    return 1;

}

// Function to check whether the current word is in the redact words file
int in_redact_words(char *word) {

    char *word_copy = (char*) malloc(sizeof(char)*(string_length(word)+1));

    string_copy(word_copy, word);

    // Removing punctuation from current word_copy
    for (int i = 0; i < string_length(word_copy); i++){
        if (is_alpha(word_copy[i]) == 0) {
            removeChar(word_copy, word_copy[i]);
        }
    }

    for (int i = 0; i < redact_no_lines; i++) {
        if (string_compare(word_copy, redact_words_file[i]) == 0) {
            return 1;
        }
    }

    // free(word_copy);

    return 0;

}

// Main parsing function
void parse_input_words() {

    // Looping through all the words in the input words file
    for (int i = 0; i < input_no_lines; i++) {

        char *current_line = input_words_file[i];
        int index_of_last_word = 0;

        // Looping through the line
        for (int j = 0; j < string_length(input_words_file[i]); j++) {

            // Checking to see if the word has ended
            if (input_words_file[i][j] == ' ') {

                // Setting current_word equal the word just detected
                char *current_word = substring(current_line, index_of_last_word, j);

                if (in_redact_words(current_word)) {
                    // Add '*'s of length string_length(current_word) to the output file
                    printf("Current word: STARS\n");
                    add_word_to_file(convert_to_stars(current_word), i);
                } else {
                    // Add the original word to the output file
                    printf("Current word: %s\n", current_word);
                    add_word_to_file(current_word, i);
                }

                // Freeing up the memory currently being used by current_word
                free(current_word);

                // Updating index_of_last_word so that the index is now at the start of the next word
                index_of_last_word = j+1;

            }

        }

        // Add a new line character to the file at the end of the sentence
        add_word_to_file("\n", i);

    }

}

/* ~~~~~~~~~~~~ Main Functions ~~~~~~~~~~~~ */

void redact_words(const char *text_filename, const char *redact_words_filename) {

    printf("---------------------------------------\n");
    printf("Reading from %s\n", text_filename);
    printf("Reading redact words from %s\n", redact_words_filename);
    printf("---------------------------------------\n");

    open_redact_words(redact_words_filename);
    open_input_file(text_filename);

    parse_input_words();

}

int main(int argc, char *argv[]) {
	const char *input_file = "./debate.txt";
	const char *redact_file = "./redact.txt";
	redact_words(input_file, redact_file);
	return EXIT_SUCCESS;
}
