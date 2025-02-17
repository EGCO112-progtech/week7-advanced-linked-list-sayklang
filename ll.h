#include <string.h>
// self-referential structure
struct Node {
   int id;
   char name[50];
   struct Node *nextPtr,*pPtr; // pointer to next node
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*



// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int id ,const char *name );
void printList( LLPtr currentPtr );
void printListR( LLPtr currentPtr );
void instructions( void );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int id ,const char *name)
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = id;
      strncpy(newPtr->name, name, sizeof(newPtr->name) - 1);  
      newPtr->name[sizeof(newPtr->name) - 1] = '\0'; 
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL;
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && id > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
      //   newPtr->pPtr= *bPtr;
       if(*sPtr)(*sPtr)->pPtr=newPtr;
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr = previousPtr;

         newPtr->nextPtr = currentPtr;
         if(currentPtr)currentPtr->pPtr=newPtr;
         
 
         
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", id );
   } // end else
} // end function insert







// delete a list element
int deletes( LLPtr *sPtr, int value )
{
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->id ) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else {
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != value ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         currentPtr=currentPtr->nextPtr;
         previousPtr->nextPtr = currentPtr;
         free( tempPtr );
         return value;
      } // end if
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList(LLPtr currentPtr) {
   if (isEmpty(currentPtr)) {
       puts("List is empty.\n");
   } else {
       puts("The list is:");
       while (currentPtr != NULL) {
           printf("ID: %d %s --> ", currentPtr->id, currentPtr->name);
           currentPtr = currentPtr->nextPtr;
       }
       printf("NULL\n");
   }
}

// Recursive function to print the list in reverse order
void printListR(LLPtr currentPtr) {
   if (isEmpty(currentPtr)) {
       return; // Base case: if the list is empty, stop recursion
   }

   // Recurse to the next node
   printListR(currentPtr->nextPtr);

   // After recursion, print the current node's data
   printf("ID: %d %s --> ", currentPtr->id, currentPtr->name);
}

// Function to print the list in reverse order, calling the recursive function
void printListReverse(LLPtr head) {
   if (isEmpty(head)) {
       puts("List is empty.\n");
       return;
   }
   printListR(head);
   printf("NULL");
}




void freeList(LLPtr *headPtr) {
   LLPtr currentPtr = *headPtr;
   while (currentPtr != NULL) {
       LLPtr temp = currentPtr;
       currentPtr = currentPtr->nextPtr;
       free(temp);  
   }
   *headPtr = NULL;  
}
