/***************************************************************************************************
*                                                                                                  *
*      This program tests the Single Linked List and is heavily based on a test by Jerry Cain      *
*                                                                                                  *
***************************************************************************************************/

#include "linkedList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void freeInt(void* v1) {
	free((int*)v1);
}

void freeChr(void* v1) {
	free((char*)v1);
}

void freeStr(void* v1) {
	free(*(char**)v1);
}


int intCmp(const void* v1,const void* v2) {
	return *(int*)v1 - *(int*)v2;
}

int chrCmp(const void* v1,const void* v2) {
	return *(char*)v1 - *(char*)v2;
}

int strCmp(const void* v1,const void* v2) {
	return strcmp(*(char**)v1,*(char**)v2);
}

void printInt(void* elm,void* fp) {
	fprintf((FILE*)fp,"%i ",*(int*)elm);
	fflush((FILE*)fp);
}


void printChr(void* elm,void* file) {
	fprintf((FILE*)file,"%c",*(char*)elm);
	fflush((FILE*)file);
}

void printStr(void* elm,void* file) {
	fprintf((FILE*)file,"%s  ",*(char**)elm);
	fflush((FILE*)file);
}


static void InsertAlphabet(list* l) {
	char* tmp;

	for(char letter = 'A'; letter <= 'Z'; letter++) {
		tmp = malloc(sizeof(char*));
		*tmp = letter;
		ListInsert(l,tmp);
	}
	printf("After inserting Alphabet (ListInsert): \t\t\t\t\t\t\t  ");
	ListMap(l,printChr,stdout);

	printf("\n");
}

static void InsertNumbers(list* l) {
	int* tmp;

	for(int number = '0'; number <= '9'; number++) {
		tmp = malloc(sizeof(int));
		*tmp = number;
		ListInsert_front(l,tmp);
	}
	printf("After inserting some numbers in the same List (ListInsert_front): \t\t");
	ListMap(l,printChr,stdout);

	printf("\n");
}

static void TestCharSort(list* l) {
	ListSort(l,intCmp);

	printf("List after Sorting (ListSort): \t\t\t\t\t\t\t");
	ListMap(l,printChr,stdout);
	printf("\n");
}


static void LowerLetters(list* l) {

	for(int i=0; i< ListLength(l); i+=2) {
		char *elm;
		ListReturnNth(l,(void*)&elm,i);
		*elm = tolower(*elm);
	}

	printf("After lowering ever 2nd letter (ReturnNth): \t\t\t\t\t");
	ListMap(l,printChr,stdout);
	printf("\n");

}

void TestInsertDelete(list* l) {

	for (int i=3; i < ListLength(l); i+=4) {
	  char* ch = malloc(sizeof(int));
	  *ch ='-';
		ListInsertNth(l,ch,i);
  }

	printf("After inserting dashes (ListInsertNth): \t\t\t     ");
	ListMap(l,printChr,stdout);
	printf("\n");

	for (int i=3; i < ListLength(l); i+=3) {
		ListRemoveNth(l,NULL,i);
  }

	printf("After deleting dashes (ListRemoveNth): \t\t\t\t\t\t");
	ListMap(l,printChr,stdout);
	printf("\n");

	for (int i=0; i<3; i++) {
	char* chf =  malloc(sizeof(char));
	char* chb =  malloc(sizeof(char));

	*chf ='*';
	*chb ='!';

  ListInsert(l,chb);
	ListInsert_front(l,chf);

}

  printf("After Inserting at both ends (ListInsert_front & ListInsert):  \t\t     ");
  ListMap(l,printChr,stdout);
  printf("\n");

	void* resFront[3];
	void* resBack[3];

	for (int i=0; i<3; i++) {
	ListRemove(l,(resFront+i));
	ListRemove_back(l,(resBack+i));
	}

  fprintf(stdout,"\nRemoving both, but saving the result (ListRemove & ListRemove_back): \t\t");
  ListMap(l,printChr,stdout);
  printf("\n");
	for(int i=0; i<3; i++) {
		fprintf(stdout,"resFront[%i]: %c, resBack[%i]: %c\t",i,*(char*)resFront[i],i,*(char*)resBack[i]);
	}
  fprintf(stdout,"\nWe took ownership back, we need to free the items (free):\n");
	for(int i=0; i<3; i++) {
		free(resFront[i]);
		free(resBack[i]);
	}
	for(int i=0; i<3; i++) {
		fprintf(stdout,"resFront[%i]: %c, resBack[%i]: %c\t",i,*(char*)resFront[i],i,*(char*)resBack[i]);
	}
  fprintf(stdout,"\nAnd, they're gone.\n\n");
}

static void TestFindAndRemove(list* l) {
	fprintf(stdout,"Let's search for H (ListFind): \t...\t");
	int pos = ListFind(l,"H",chrCmp,0);
	assert (pos != -1);
	fprintf(stdout,"Found at Position %i\n",pos);
	fprintf(stdout,"Let's search for @ (ListFind): \t...\t");
	pos = ListFind(l,"@",chrCmp,0);
	assert (pos == -1);
	fprintf(stdout,"Result: %i",pos);
	fprintf(stdout,", because it's not in there\n");

	char* chInsert1 = malloc(sizeof(char));
	char* chInsert2 = malloc(sizeof(char));
	*chInsert1 = '@';
	*chInsert2 = '@';

	ListInsertNth(l,chInsert1,11);
	ListInsertNth(l,chInsert2,13);

	fprintf(stdout,"Insert some @ at position 11 and 13 (ListInsertNth) \t\t\t      ");
	ListMap(l,printChr,stdout);

	fprintf(stdout,"\nLet's search for @ (ListFind) from position  0:  ...  ");
	int pos1 = ListFind(l,"@",chrCmp,0);
	assert (pos1 != -1);
	fprintf(stdout,"Found at Position %i\n",pos1);
	fprintf(stdout,"Let's search for @ (ListFind) from position 11:  ...  ");
	int pos2 = ListFind(l,"@",chrCmp,12);
	assert (pos2 != -1);
	fprintf(stdout,"Found at Position %i\n",pos2);

	fprintf(stdout,"\nRemove from the middle, position 18-22 and keep the result (ListRemoveNth):   ");
	ListMap(l,printChr,stdout);
	printf("\n");

	void* resMiddle[5];
	for (int i=0; i<4; i++) {
		ListRemoveNth(l,(resMiddle+i),18);
	}

	for (int i=0; i<4; i++) {
		fprintf(stdout,"resMiddle[%i]: %c, ",i,*(char*)resMiddle[i]);
	}
	fprintf(stdout,"\nThe Linked List now looks like this: \t\t\t\t\t\t");
	ListMap(l,printChr,stdout);
	printf("\n");
	fprintf(stdout,"We took ownership of the elments back, we need to free them again ... ");
	for (int i=0; i<4; i++) {
		free(resMiddle[i]);
	}
	fprintf(stdout,"Done!\n\n");
}

static void TestDispose(list* l) {
	fprintf(stdout,"Returning the Element B (12): (ListReturnNth) ... ");
	void* finalRemoval = malloc(sizeof(void*));
	ListReturnNth(l,&finalRemoval,12);
	fprintf(stdout,"Taken out: %s \n",(char*)finalRemoval);
	fprintf(stdout,"The element is still in the list we just got a pointer to it. ");
	fprintf(stdout,"Disposing the Linked List (LinkDispose): ...");
	ListDispose(l);
	fprintf(stdout,"Done!\n");
  fprintf(stdout,"The free function also removed the element    ... Taken out: %s\n", (char*)finalRemoval);
	printf("\n");

}


static void SimpleTest() {

	fprintf(stdout,"\n-----------------------------------------Creating a Sinlge Linked List for Chars-----------------------------------------\n");
	fprintf(stdout,"-----------------------------------------Testing every functionality implemented-----------------------------------------\n\n");

	list alphabet = ListInit(freeChr);

	InsertAlphabet(&alphabet);
	InsertNumbers(&alphabet);
	TestCharSort(&alphabet);
	LowerLetters(&alphabet);
	TestInsertDelete(&alphabet);
	TestFindAndRemove(&alphabet);
	TestDispose(&alphabet);
}

static void TestStringList() {
	
	fprintf(stdout,"\n-----------------------------------------Creating a Sinlge Linked List for Strings---------------------------------------\n\n");

	list stringList = ListInit(freeStr);

	void* names[] = {strdup("Bob Dylan"), strdup("Shawn Clovin"), strdup("Linda Perry"), strdup("Neil Young"), strdup("Towns van Zandt"), strdup("Bradley Nowell"), strdup("Tom Petty") };

	for( int i =0; i<7; i++) {
		ListInsert(&stringList,&names[i]);
	}

		fprintf(stdout,"\nLinked List filled with Strings:\n");
	  ListMap(&stringList,printStr,stdout);

	  ListSort(&stringList,strCmp);

		fprintf(stdout,"\n\nLinked List sorted:\n");
	  ListMap(&stringList,printStr,stdout);

		fprintf(stdout,"\n\nRegaining control of the first element (ListRemove): ");

		void* keep = malloc(sizeof(void));
    ListRemove(&stringList,&keep);

		fprintf(stdout,"\t %s \nList now looks like this: \n\n",*(char**)keep);

	  ListMap(&stringList,printStr,stdout);

		fprintf(stdout,"\n\nPrinting names[%i] before freeing: %s ... ",6,(char*)names[6]);

		ListDispose(&stringList);
		
		fprintf(stdout,"Linked List Disposed ... ");
		fprintf(stdout,"Printing names[%i] after freeing: %s\n",6,(char*)names[6]);
		fprintf(stdout,"We still have: \t %s \t",*(char**)keep);
		fprintf(stdout,"Freeing the strdup memory with free(*(char**)keep)\n");
		free(*(char**)keep);
} 

static void InsertPermutationOfNumber(list* l, long n, long d) {
	fprintf(stdout,"Generating one permutation of all numbers between [0,%ld) \n",d-1);

	for(long k=0; k<d; k++) {
	   long* residue = malloc(sizeof(long));
		 *residue = (long) (((long long)k * (long long)n) % d);
		 ListInsert(l,residue);
	}	
}

static void FindANumber(list* l,int* toFind) {
	int position;
	
  fprintf(stdout, "Looking for number %i in the list\n",*toFind);
	fflush(stdout);

	position = ListFind(l,toFind,intCmp,0);

  fprintf(stdout, "Found! It's at position %i\n",position);
	fflush(stdout);

}

static void TestSort(list* l) {
	fprintf(stdout, "Starting sorting the list with %i elements",ListLength(l));
	fflush(stdout);
	ListSort(l,intCmp);
	fprintf(stdout, "\n[Done!]\n");

	fprintf(stdout, "Checking if it's indeed sorted:\n");
	long* embeddedLong = malloc(sizeof(long));
	for (int residue =0; residue < ListLength(l); residue++) {
		ListReturnNth(l,(void*)&embeddedLong,residue);
		ListReturnNth(l,(void*)&embeddedLong,residue);
		assert( *embeddedLong == residue);
	}
	fprintf(stdout, "Yes, it is!\n");
}

static void TestDelete(list* l) {
	long* largestOriginalNumber = malloc(sizeof(long));
	fprintf(stdout, "Removing every Node by repeatedlly removing the 100th-to-last Node \n");
	fflush(stdout);
  ListReturnNth(l,(void*)&largestOriginalNumber,ListLength(l)-1);
	int k =0;
	while (ListLength(l) >= 20) {
		k++;
		ListRemoveNth(l,NULL,ListLength(l)-100);
//		if ( k % 1000 == 0 ) { printf("%i \n"); }
	}
	fprintf(stdout, "The last 100 elments in the list are:\n");
	fflush(stdout);

	ListMap(l,printInt,stdout);

  fprintf(stdout, "\nRemoving the final 20:\n");
	fflush(stdout);

	int* justRemoved =malloc(sizeof(int));
	while(ListLength(l) >0) { ListRemoveNth(l,(void*)&justRemoved,ListLength(l)-1);
  fprintf(stdout, "Removing: %i\n",*justRemoved);
	fflush(stdout);
	}

}

static void TestingALargeLinkedList() {

	fprintf(stdout,"\n-----------------------------------Performance Test for very large Single Linked Lists-----------------------------------\n\n");
  static const long kLargePrime =100391;
	static const long kEvenLargerPrime =201577;

  int* toFind = malloc(sizeof(int));
	*toFind = 711;

	list numbers = ListInit(freeInt);
	InsertPermutationOfNumber(&numbers,kLargePrime,kEvenLargerPrime);
  FindANumber(&numbers,toFind);
	TestSort(&numbers);
	TestDelete(&numbers);

	ListDispose(&numbers);
}

int main() {

	system("clear");

	SimpleTest();
	TestingALargeLinkedList();
  TestStringList();

		
}
