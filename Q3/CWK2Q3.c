/*
 ============================================================================
 Name        : CWK2Q3.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own Hash Table in C for storing and searching names, i.e. char
 arrays. In the event of collisions, you should use linear probing with an
 interval of 1. The hash function should be the sum of the ASCII values of the
 string modulo the size of the underlying data structure. Your Hash Table
 implementation should have the following interface:
	int hash_function(const char *key)
	void resize_map(int new_size)
	void add_to_map(const char *name)
	int remove_from_map(const char *name)
	int search_map(const char *name)
	void print_map()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** hash_map;  // This is where you should store your names
int map_size;
int no_items = 0; // Used to hold the number of items in the hash map
float load_factor; // Used to automatically resize the map

int hash_function(const char *key) {

    int hash_total = 0;

    // Looping through each character in the string
    for (int i = 0; i < strlen(key); i++) {
        hash_total += key[i]; // Summing the ASCII values of each character in the string
    }

    // Finding the value of hash_total modulus the size of the underlying data structure
    int hash_value = hash_total % map_size;

    return hash_value;

}

void resize_map(int new_size) {

    // Resetting the global integer 'map_size' to the new size
    map_size = new_size;
    // Reallocating the hash_maps's memory to be of the new size
    hash_map = (char**) realloc(hash_map, sizeof(char) * new_size);

}

// The parameter 'forward_check' allows for linear probing both 'forwards' and 'backwards' through the array
void assign_new_value(int hash_value, const char *name, int forward_check) {

    // Checking for collisions
    if (hash_map[hash_value] == NULL) {

        hash_map[hash_value] = name; // Adding the string to the hash map at the index defined by hash_value
        no_items++; // As an item was successfully added to a bucket, the global integer variable no_items is incremented by one

    } else {

        // Conditional statement to allow for linear probing both backwards and forwards
        if (forward_check && ++hash_value < map_size) {
            forward_check = 0;
        } else if (!forward_check && --hash_value >= 0) {
            forward_check = 1;
        }

        // Using recursion to implement the linear probing
        return assign_new_value(hash_value, name, forward_check);

    }

}

void add_to_map(const char *name) {

    // Getting the hash value of the string
    int hash_value = hash_function(name);

    // Assigning a new value at the index given by the hash function
    // Using linear probing with an interval of 1 if there are collisions
    assign_new_value(hash_value, name, 1);

    // Calculating the loading factor
    load_factor = (float) no_items / (float) map_size;

    // If the loading factor is above 0.7, the hash_map is automatically doubled in size
    if (load_factor > 0.7) {

        resize_map(2*map_size);

    }

}

int remove_from_map(const char *name) {

}

int search_map(const char *name) {

}

void print_map() {

}

int main(int argc, char *argv[]) {
	char *stringOne = "#Hello world";
	char *stringTwo = "How are you?";
	char *stringThree = "Be the best you...!!";
	char *stringFour = "Be kind to yourself";
	char *stringFive = "Principles of Programming 2";

	resize_map(6);
	add_to_map(stringOne);
	add_to_map(stringTwo);
	add_to_map(stringOne);
	add_to_map(stringThree);
	add_to_map(stringFour);
	add_to_map(stringFive);
	print_map();

	int ret = search_map(stringOne);
	if(ret)
		printf("Found %s!\n", stringOne);

	remove_from_map(stringThree);

	ret = search_map(stringFive);
	if(ret)
		printf("Found %s!\n", stringFive);
	print_map();

	add_to_map(stringThree);
	print_map();

	return EXIT_SUCCESS;
}
