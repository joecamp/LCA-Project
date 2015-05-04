#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int size;
} arraylist;

void init(arraylist* myList);
void add(arraylist* myList, int value);
void del(arraylist* myList, int index);
int getSize(arraylist* myList);
void print(arraylist* myList);
int get(arraylist* myList, int index);

/*int main() {

    // Create and initialize an arraylist.
    arraylist mylist;
    init(&mylist);

    // Add 10 items and print the list after each add.
    int i;
    for (i=1; i<=10; i++) {
        add(&mylist, i);
        print(&mylist);
    }


    // Randomly select 10 indexes for deleting.
    for (i=0; i<10; i++) {

        // Note if the index is out of bounds, no change will be made.
        int val = rand()%10;
        printf("deleting index %d\n", val);
        del(&mylist, val);
        print(&mylist);
    }

    return 0;
}*/

// Given a pointer to an arraylist, this function initializes the list
// to be empty.
void init(arraylist* myList) {
    myList->array = NULL;
    myList->size = 0;
}

// This function adds value to the end of the arraylist pointed to by myList.
void add(arraylist* myList, int value) {

    // Add 1 to the size and reallocate memory.
    myList->size++;
    myList->array = realloc(myList->array, sizeof(int)*myList->size);

    // Now, add the value.
    myList->array[myList->size-1] = value;
}

// Deletes the contents stored in index, sliding over each element
// after it to the left, one slot.
void del(arraylist* myList, int index) {

    // Illegal index  - take no action
    if (index < 0 || index >= myList->size) return;

    // Just copy over everything one slot to the left,
    // starting at index.
    int i;
    for (i=index; i<myList->size-1; i++)
        myList->array[i] = myList->array[i+1];

    // Adjust size and reallocate.
    myList->size--;
    myList->array = realloc(myList->array, sizeof(int)*myList->size);
}

int getSize(arraylist* myList) {
    return myList->size;
}

// Print out the contents of the arraylist pointed to by myList, in
// order.
void print(arraylist* myList) {

    // Loop through each item and print.
    int i;
    for (i=0; i<myList->size; i++)
    printf("%d ", myList->array[i]);
    printf("\n");
}

int get(arraylist* myList, int index) {
    return myList->array[index];
}
