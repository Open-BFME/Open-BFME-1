// cl: /MD -Iinputs/reference/shims/gamespy /DNDEBUG
/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from inputs/reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */
/* 
 *
 * File: hashtable.c
 * ---------------
 *	David Wright
 *	10/8/98
 *
 * See hashtable.h for function comments
 * Implmentation is straight-forward, using a fixed dynamically allocated
 * array for the buckets, and a DArray for each individual bucket
 */

#include <stdlib.h>
#include <string.h>
#include "darray.h"
#include "hashtable.h"

#ifdef _MFC_MEM_DEBUG
#define _CRTDBG_MAP_ALLOC 1
#include <crtdbg.h>
#endif


#ifdef _NO_NOPORT_H_
	#define gsimalloc malloc
	#define gsifree free
	#define gsirealloc realloc
	#include <assert.h>
#else
	#include "nonport.h" //for gsimalloc/realloc/free/assert
#endif


struct HashImplementation 
{
	DArray *buckets;
	int nbuckets;
	TableElementFreeFn freefn;
	TableHashFn hashfn;
	TableCompareFn compfn;
};

HashTable TableNew(int elemSize, int nBuckets, 
                   TableHashFn hashFn, TableCompareFn compFn, 
 					 TableElementFreeFn freeFn)
{
	return TableNew2(elemSize, nBuckets, 4, hashFn, compFn, freeFn);
}
// TableNew2 present-unmatched
HashTable TableNew2(int elemSize, int nBuckets, int nChains,
                   TableHashFn hashFn, TableCompareFn compFn, 
 					 TableElementFreeFn freeFn)
{
	HashTable table;
	int i;

	assert(hashFn);
	assert(compFn);
	assert(elemSize);
	assert(nBuckets);

	table = (HashTable)gsimalloc(sizeof(struct HashImplementation));
	assert(table);
	
	table->buckets = (DArray *)gsimalloc(nBuckets * sizeof(DArray));
	assert(table->buckets);
	for (i = 0; i < nBuckets; i++) //ArrayNew will assert if allocation fails
		table->buckets[i] = ArrayNew(elemSize, nChains, freeFn);
	table->nbuckets = nBuckets;
	table->freefn = freeFn;
	table->compfn = compFn;
	table->hashfn = hashFn;

	return table;
}


// TableFree present-unmatched
void TableFree(HashTable table)
{
	int i;
	
	assert(table);

	if (NULL == table )
		return;
	
	for (i = 0 ; i < table->nbuckets ; i++)
		ArrayFree(table->buckets[i]);
	gsifree(table->buckets);
	gsifree(table);
}


// TableCount present-unmatched
int TableCount(HashTable table)
{
	int i, count = 0;
	
	assert(table);

	if (NULL == table )
		return count;

	for (i = 0 ; i < table->nbuckets ; i++)
		count += ArrayLength(table->buckets[i]);
	
	return count;
}


// TableEnter present-unmatched
void TableEnter(HashTable table, const void *newElem)
{
	int hash, itempos;
	
	assert(table);

	if (NULL == table )
		return;

	hash = table->hashfn(newElem, table->nbuckets);
	itempos = ArraySearch(table->buckets[hash], newElem, table->compfn, 0,0);
	if (itempos == NOT_FOUND)
		ArrayAppend(table->buckets[hash], newElem);
	else
		ArrayReplaceAt(table->buckets[hash], newElem, itempos);
}

// TableRemove present-unmatched
int TableRemove(HashTable table, const void *delElem)
{
	int hash, itempos;
	
	assert(table);

	if (NULL == table )
		return 0;

	hash = table->hashfn(delElem, table->nbuckets);
	itempos = ArraySearch(table->buckets[hash], delElem, table->compfn, 0,0);
	if (itempos == NOT_FOUND)
		return 0;
	else
		ArrayDeleteAt(table->buckets[hash], itempos);
	return 1;
}

// TableLookup present-unmatched
void *TableLookup(HashTable table, const void *elemKey)
{
	int hash, itempos;
	
	assert(table);

	if (NULL == table )
		return NULL;

	hash = table->hashfn(elemKey, table->nbuckets);
	itempos = ArraySearch(table->buckets[hash], elemKey, table->compfn, 0,
						  0);
	if (itempos == NOT_FOUND)
		return NULL;
	else
		return ArrayNth(table->buckets[hash], itempos);
}


// TableMap present-unmatched
void TableMap(HashTable table, TableMapFn fn, void *clientData)
{
	int i;
	
	assert(table);
	assert(fn);

	if (NULL == table || NULL == fn)
		return;
	
	for (i = 0 ; i < table->nbuckets ; i++)
		ArrayMap(table->buckets[i], fn, clientData);
	
}

// TableMapSafe absent-from-retail
void TableMapSafe(HashTable table, TableMapFn fn, void *clientData)
{
	int i;
	
	assert(fn);
	
	for (i = 0 ; i < table->nbuckets ; i++)
		ArrayMapBackwards(table->buckets[i], fn, clientData);
	
}

// TableMap2 absent-from-retail
void * TableMap2(HashTable table, TableMapFn2 fn, void *clientData)
{
	int i;
	void * pcurr;
	
	assert(fn);
	
	for (i = 0 ; i < table->nbuckets ; i++)
	{
		pcurr = ArrayMap2(table->buckets[i], fn, clientData);
		if(pcurr)
			return pcurr;
	}

	return NULL;
}

// TableMapSafe2 present-unmatched
void * TableMapSafe2(HashTable table, TableMapFn2 fn, void *clientData)
{
	int i;
	void * pcurr;
	
	assert(fn);
	
	for (i = 0 ; i < table->nbuckets ; i++)
	{
		pcurr = ArrayMapBackwards2(table->buckets[i], fn, clientData);
		if(pcurr)
			return pcurr;
	}

	return NULL;
}

void TableClear(HashTable table)
{
	int i;

	for (i = 0 ; i < table->nbuckets ; i++)
		ArrayClear(table->buckets[i]);
}
