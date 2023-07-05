#include "helpers.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#if defined(_WIN32)
#if defined(_M_X64)
void* const DBG_PTR = (void* const)0xcccccccccccccccc;
#else
void* const DBG_PTR = (void* const)0xcccccccc;
#endif
#define WINassert(expr) assert(expr)
#else
// not _WIN32
#define WINassert(expr) ((void)0)
#endif

my_array my_array_init(){
	my_array array = { 0 };
	return array;
}


void my_array_free(my_array* pArray) {
	WINassert(pArray != DBG_PTR && pArray != NULL && "No my_array object allocated");
	WINassert(pArray->data != DBG_PTR && "array object has not been initialized: call 'array_uintmax_init()'");
	assert(pArray->amtElements <= pArray->maxCap && "array size > array capacity - impossible!");
	free(pArray->data);
	*pArray = my_array_init();
}


bool my_array_push_back(my_array* pArray, double value) {
	WINassert(pArray != DBG_PTR && pArray != NULL && "No my_array object allocated");
	WINassert(pArray->data != DBG_PTR && "array object has not been initialized: call 'array_uintmax_init()'");
	assert(pArray->amtElements <= pArray->maxCap && "array size > array capacity - impossible!");

	// Expand if necessary 
	if (pArray->amtElements == pArray->maxCap) {	// p->member   means 'member from pointer operator' (*p).member
		size_t newCapacity = (size_t)ceil(pArray->maxCap * 1.3);
		if (newCapacity == 0) {
			++newCapacity;
		}
		double* pNewBlock = realloc(pArray->data, newCapacity * sizeof(double));
		if (pNewBlock == NULL) {
			return false;
		}
		pArray->data = pNewBlock;
		pArray->maxCap = newCapacity;
	}

	// store
	pArray->data[pArray->amtElements++] = value;

	assert(pArray->amtElements <= pArray->maxCap && "array size > array capacity - impossible!");
	return true;
}