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

char** hash_map = 0x0;  // This is where you should store your names
int map_size = 0; // Used to store the current max size of the hash table
int no_items = 0; // Used to hold the number of items in the hash table
float load_factor; // Used to automatically resize the table

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

    if (hash_map == 0x0) {
        hash_map = (char**) malloc(new_size*sizeof(char*)); // Allocating memory for the hash_map
    } else {
        hash_map = (char**) realloc(hash_map, (new_size*sizeof(char*))); // Reallocating the hash_maps's memory to be of the new size
    }

    if (hash_map == 0x0) {
        // Memory allocation failed, cleanup process
        perror("Memory allocation failed, starting cleanup process...\n");
        for (int i = 0; i < map_size; i++) {
            free(hash_map[i]);
        }
        free(hash_map);
        return;
    }

    // Setting each item in the hash_map (that isn't already assigned) to be null
    if (map_size < new_size) {
        for (int i = map_size; i < new_size; i++) {
            hash_map[i] = 0x0;
        }
    }

    // The allocation was successful
    // Resetting the global integer 'map_size' to the new size
    map_size = new_size;

}

void assign_memory_for_bucket(int hash_value, int size_of_bucket) {

    if (hash_map[hash_value] == 0x0) {
        hash_map[hash_value] = (char*) malloc((size_of_bucket + 1)*sizeof(char));
    } else {
        hash_map[hash_value] = (char*) realloc(hash_map[hash_value], (size_of_bucket + 1)*sizeof(char));
    }

    if(hash_map[hash_value] == 0x0) {
        // Bucket memory allocation failed, cleanup process
        perror("Bucket memory allocation failed, starting cleanup process...\n");
        free(hash_map[hash_value]);
    }

}

int search_map(const char *name) {

    // Searching the map for the element 'name'
    for (int i = 0; i < map_size; i++) {
        char *temp = hash_map[i];

        if (temp == 0x0) {
            temp = "";
        }

        if (strcmp(temp, name) == 0) {
            return 1;
        }
    }

    // The element 'name' was not found in the map
    return 0;

}

// The parameter 'forward_check' allows for linear probing both 'forwards' and 'backwards' through the array
void assign_new_value(int hash_value, const char *name, int forward_check, int original_hash_value) {

    // Checking for collisions
    if (hash_map[hash_value] == 0x0 || !strcmp(hash_map[hash_value], "")) {

        // Assigning memory for bucket
        assign_memory_for_bucket(hash_value, strlen(name));

        strcpy(hash_map[hash_value], name); // Adding the string to the hash map at the index defined by hash_value
        no_items++; // As an item was successfully added to a bucket, the global integer variable no_items is incremented by one
        printf("Your key: %s has been successfully inserted into the hash table\n", name);

    } else {

        int duplicates = search_map(name);

        if (duplicates) {
            perror("Error: the key you wish to input already exists. Cancelling operation...\n");
            return;
        }

        // Conditional statement to allow for linear probing both backwards and forwards
        if (forward_check > 0) {
            hash_value = (original_hash_value + forward_check) % map_size;
            forward_check = -(forward_check + 1);
        } else {
            hash_value = (original_hash_value + forward_check) % map_size;
            forward_check = -(forward_check - 1);
        }

        // Checking for bugs where the hash_value is less than 0 (to stop index errors)
        if (hash_value < 0) {
            hash_value += map_size;
        }

        // Using recursion to implement the linear probing
        return assign_new_value(hash_value, name, forward_check, original_hash_value);

    }

}

void add_to_map(const char *name) {

    // Getting the hash value of the string
    int hash_value = hash_function(name);

    // Assigning a new value at the index given by the hash function
    // Using linear probing with an interval of 1 if there are collisions
    assign_new_value(hash_value, name, 1, hash_value);

    // Calculating the loading factor
    load_factor = (float) no_items / (float) map_size;

    // If the loading factor is above 0.7, the hash_map is automatically doubled in size
    if (load_factor > 0.7) {

        resize_map(2*map_size);

    }

}

int remove_from_map(const char *name) {

    // Searching the map for the element 'name'
    for (int i = 0; i < map_size; i++) {
        char *temp = hash_map[i];

        if (temp == 0x0) {
            temp = "";
        }

        if (strcmp(temp, name) == 0) {
            hash_map[i] = 0x0; // Resetting the element at index i to be null
            no_items--; // Decreasing the no_items by one
            return 1;
        }
    }

    return 0;

}

void print_map() {

    // Looping through all the elements in the hash map
    for (int i = 0; i < map_size; i++) {
        if (hash_map[i] != 0x0) { // Checking if the bucket at index i is empty or not
            printf("Element in bucket %d is %s\n", i , hash_map[i]);
        }
    }

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
