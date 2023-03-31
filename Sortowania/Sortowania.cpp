#include <iostream>
#include <stdio.h>	
#include <stdlib.h> 
#include <time.h>
#include "Sort.h"


#define MAX 48
#define MAXTABPRINT 8
#define DEBUG

using namespace std;
void RandomTab ( int* pTab, int nSize );
void PrintTab ( int* pTab, int nSize );
int CreateTab ( int** pTab, int nSize );


typedef void( *sortFun )( int*, int ); 


int main( int argc, char* argv[] )
{

	if( argc != 2 ){
		printf("Usage %s <tab_size>\n", argv[0]);
		return -1;
	}

	
	const char* funName[] = { "InsertionSort", "SelectionSort", "BubbleSort", "MixSort", "HalfSort", "HeapSort", "QuickSort" };
	sortFun pSortTab[] = { InsertionSort, SelectionSort, BubbleSort, MixSort, HalfSort, HeapSort, QuickSort };


int nSize = atoi( argv[1] );


 int* pTab = NULL;

 if(!CreateTab(&pTab, nSize)) {
	 printf("ERROR: Createtab\n");
	 return -1;
 }


 int* pTabCopy = NULL;

 if( !CreateTab( &pTabCopy, nSize ) ){
	 printf( "ERROR: Createtab\n" );
	 return -1;
 }
 
 RandomTab( pTab, nSize );

 
 int  N = sizeof( funName ) / sizeof(const char*);
 

#ifdef DEBUG

 printf( " \n Tablica z losowymi elementami:\n" );
 PrintTab( pTab, ( nSize > MAX ) ? MAX : nSize );
 
#endif



 for( int i = 0; i < N; i++ ) {

	 memcpy( pTabCopy, pTab, nSize * sizeof( pTab ) );
	 clock_t start = clock(); 
	 pSortTab[i]( pTabCopy, nSize );
	
	 printf( "\n \n \n\nSortowanie za pomoca %s zajmuje: %.4f sekund\n", funName[i], ((double)clock() - start) / CLOCKS_PER_SEC );

#ifdef DEBUG

	 printf( "Posortowana tablica: \n" );
	 PrintTab( pTabCopy, nSize > MAX ? MAX : nSize );

#endif

 }
 free( pTabCopy );
 free( pTab );

 return 0;
}



int CreateTab(int** pTab, int nSize)
{
	*pTab = ( int* )calloc( nSize, sizeof( int ) );
	if( !*pTab ) return 0;
	return 1;
}
 


void RandomTab( int* pTab, int nSize )
{
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < nSize; i++ )          *pTab++ = rand() % nSize;	
}



void PrintTab( int* pTab, int nSize )
{
	for( int i = 0; i < nSize; i++ )  
	{
		printf( "%d\t", *pTab++ );
		if( ( i + 1 ) % MAXTABPRINT == 0 )   printf( "\n" );
	}
}


 




