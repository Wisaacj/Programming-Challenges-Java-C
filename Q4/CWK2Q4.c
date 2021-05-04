/*
 ============================================================================
 Name        : CWK2Q4.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own XOR Linked List (https://en.wikipedia.org/wiki/XOR_linked_list)
 in C capable of storing names. Your implementation should have the following
 functions:
    void insert_string(const char* newObj)
	int insert_before(const char* before, const char* newObj)
	int insert_after(const char* after, const char* newObj)
	void remove_string(char* result)
	int remove_after(const char *after, char *result)
	int remove_before(const char *before, char *result)
    void print_list()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct linked_list_node {
    char *name;
    struct linked_list_node *npx; // npx means the bitwise XOR of the next and previous pointers (address)
} linked_list_node;

// Defining some global variables to hold the head and tail of the linked list
linked_list_node *head;
linked_list_node *tail; // May not need this variable

struct linked_list_node *xor_node(char *name) {
    struct linked_list_node *new;
    new = (struct linked_list_node *) malloc(sizeof(struct linked_list_node));

    // Checking to see if the memory was successfully allocated
    if (new == 0x0) {
        return new;
    }

    new->name = name;
    // Initialising the npx address pointer to be null
    new->npx = 0x0;

    return new;
}

// Defining a function to calculate the bitwise XOR npx address for the current node
linked_list_node *calc_xor(linked_list_node *before, linked_list_node *after) {

    return (linked_list_node*) ((uintptr_t) before ^ (uintptr_t) after);

}

void insert_string(const char* newObj) {

    // Using '<' rather than '<=' to account for the fact that strlen() doesn't count the null character
    if (strlen(newObj) < 64) {
        struct linked_list_node *new_node = xor_node(newObj); // Creating a new node

        if (head == 0x0) {
            // Setting the head, tail, and new_node to all have the same pointer when the first node is added to the linked list
            head = tail = new_node;
        } else {
            // Inserting an item at the front of the linked list
            new_node->npx = calc_xor(0x0, head);
            head->npx = calc_xor(new_node, calc_xor(0x0, head->npx));
            head = new_node;
        }
    } else {
        perror("Error: String object is too long.\n");
        perror("Strings should be less than 64 characters in length\n");
    }
	
}


int insert_before(const char* before, const char* newObj) {

    if (strlen(newObj) >= 64) {
        perror("Error: String object is too long.\n");
        perror("Strings should be less than 64 characters in length\n");
        return 0;
    }

    linked_list_node *curr = head;
    linked_list_node *prev = 0x0, *next;

    // Looping through the linked list until we get to 'before'
    while (strcmp(curr->name, before) != 0) {
        next = calc_xor(prev, curr->npx);
        prev = curr;
        curr = next;

        if (curr == 0x0) {
            return 0; // Return false if the string 'before' is not in the linked_list
        }

    }

    // Creating a new node to be inserted into the list
    struct linked_list_node *new_node = xor_node(newObj);

    linked_list_node *prev_prev;

    if (prev != 0x0) {
        // Getting the 'prev-prev' node
        prev_prev = calc_xor(curr, prev->npx);

        // Getting the 'next' node
        next = calc_xor(prev, curr->npx);
        // Setting the new node's pointer address 'npx' to be the bitwise XOR of the previous and current node (i.e., it slots in-between them)
        new_node->npx = calc_xor(prev, curr);
        // Updating the previous node's link
        prev->npx = calc_xor(prev_prev, new_node);
        // Updating the current node's link
        curr->npx = calc_xor(new_node, next);
    } else {
        // Inserting an item at the front of the linked list
        new_node->npx = calc_xor(0x0, head);
        head->npx = calc_xor(new_node, calc_xor(0x0, head->npx));
        head = new_node;
    }

    return 1;
	
}


int insert_after(const char* after, const char* newObj) {

    if (strlen(newObj) >= 64) {
        perror("Error: String object is too long.\n");
        perror("Strings should be less than 64 characters in length\n");
        return 0;
    }

    linked_list_node *curr = head;
    linked_list_node *prev = 0x0, *next;

    while (strcmp(curr->name, after) != 0) {
        next = calc_xor(prev, curr->npx);
        prev = curr;
        curr = next;

        if (curr == 0x0) {
            return 0; // Return false if the string 'after' is not in the linked_list
        }

    }

    // Creating a new node to be inserted into the list
    struct linked_list_node *new_node = xor_node(newObj);

    // Getting the next node in the linked list
    next = calc_xor(prev, curr->npx);

    linked_list_node *next_next;

    if (next != 0x0) {
        // Getting the 'next-next' node in the linked list
        next_next = calc_xor(curr, next->npx);
    }

    // Setting the new node's pointer to be the bitwise XOR of the current and next node
    new_node->npx = calc_xor(curr, next);
    // Updating the current node's link
    curr->npx = calc_xor(prev, new_node);

    if (next != 0x0) {
        // Updating the next node's link
        next->npx = calc_xor(new_node, next_next);
    }

    return 1;
	
}


int remove_string(char* result){

    // Checking that the head exists
    if (head == 0x0) {
        return 0;
    }

    // Getting the name from the head and filling the result buffer with it
    strcpy(result, head->name);

    // Calculating the address of the item after the head
    linked_list_node *next_after_head = calc_xor(0x0, head->npx);

    if (next_after_head != 0x0) {

        linked_list_node *next_next = calc_xor(head, next_after_head->npx);
        // Calculating the new address of the new head
        next_after_head->npx = calc_xor(0x0, next_next);
        // Freeing the memory currently occupied by the linked list node to be removed
        free(head);
        // Resetting the head to the node now at the first position in the linked list
        head = next_after_head;

    } else {

        // This is branch is called if the head is the only node in the linked_list
        free(head);
        head = 0x0;

    }

    // Returning true after a successful removal
    return 1;
	
}


int remove_after(const char *after, char *result){

    linked_list_node *curr = head;
    linked_list_node *prev = 0x0, *next;

    // Checking to make sure the head is not null
    if (curr == 0x0) {
        return 0;
    }

    while (strcmp(curr->name, after) != 0) {
        next = calc_xor(prev, curr->npx);
        prev = curr;
        curr = next;

        if (curr == 0x0) {
            return 0; // Returning false if the string 'after' is not in the linked list
        }

    }

    // Calculating the address of the node after curr
    linked_list_node *removal_node = calc_xor(prev, curr->npx);

    // Checking to see if we have reached the end of the linked list
    if (removal_node == 0x0) {
        return 0;
    }

    // Getting the name from the node and filling the result buffer with it
    strcpy(result, removal_node->name);

    // Calculating the address of the node after removal_node
    next = calc_xor(curr, removal_node->npx);

    // If next is not null, update the pointer address 'npx' of next
    if (next != 0x0) {
        next->npx = calc_xor(curr, calc_xor(removal_node, next->npx));
    }

    // Updating the address of curr
    curr->npx = calc_xor(prev, next);

    // Freeing up the memory previously used by the removal_node
    free(removal_node);

    // Returning true after a successful removal
	return 1;

}


int remove_before(const char *before, char *result) {

    linked_list_node *curr = head;
    linked_list_node *prev = 0x0, *next;

    // Checking to make sure the head is not null
    if (curr == 0x0) {
        return 0;
    }

    while (strcmp(curr->name, before) != 0) {
        next = calc_xor(prev, curr->npx);
        prev = curr;
        curr = next;

        if (curr == 0x0) {
            return 0; // Returning false if the string 'before' is not in the linked list
        }

    }

    // Setting the address of the removal_node
    linked_list_node *removal_node = prev;

    // Checking to see if the removal node exists
    if (removal_node == 0x0) {
        return 0;
    }

    // Getting the name from the node and filling the result buffer with it
    strcpy(result, removal_node->name);

    // Calculating the address of the node before removal_node
    prev = calc_xor(curr, removal_node->npx);

    // If prev is not null, update the pointer address 'npx' of prev
    if (prev != 0x0) {
        prev->npx = calc_xor(calc_xor(removal_node, prev->npx), curr);
    }

    // Updating the address of curr
    curr->npx = calc_xor(prev, calc_xor(removal_node, curr->npx));

    // Freeing up the memory previously used by removal_node
    free(removal_node);

    // Returning true after a successful removal
    return 1;
	
}

void print_list() {

    linked_list_node *curr = head;
    linked_list_node *prev = 0x0, *next;

    printf("--------------------------\n");

    while (curr != 0x0) {
        printf("Item: %s\n", curr->name);
        next = calc_xor(prev, curr->npx);
        prev = curr;
        curr = next;
    }

    printf("--------------------------\n");
	
}

int main(int argc, char *argv[]) {
	insert_string("Alpha");
	insert_string("Bravo");
	insert_string("Charlie");
	insert_after("Bravo", "Delta");
	insert_before("Alpha", "Echo");

	print_list(); // Charlie -> Bravo -> Delta -> Echo -> Alpha

    char result[10];
    int ret;

	ret = remove_after("Delta",result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_before("Bravo", result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_string(result);
	if(ret)
		printf("Removed: %s\n", result);
		
	print_list();
}
