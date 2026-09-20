// ?_M_insert_overflow@?$vector@UBfmeElemVKN@@V?$allocator@UBfmeElemVKN@@@_STL@@@_STL@@IAEXPAUBfmeElemVKN@@ABU3@ABU__false_type@2@I_N@Z
// partial score=0.11 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Retail 0x00143E50: _M_insert_overflow for vector<BfmeElemVKN> (0xEC-byte
// elements). Same growth/allocate shape as the landed twin
// Rva00745960VectorInsertOverflow.cpp, but the bulk copies go through the
// already-landed bfmeCopyInto_00134BB0/dup_0013d9f0 helper
// (Bfme5AllocateAndCopy.cpp) instead of an inline uninitialized_copy, and the
// single-element insert is a raw struct copy (POD, no constructor call).
// Callers: BfmeConv1405.cpp (bfmePushVKN) and
// ThingTemplate_parseWeaponTemplateSet_Thunk.cpp.

struct BfmeElemVKN
{
	char m_bytes[0xEC];
};

extern "C" BfmeElemVKN *__cdecl bfmeCopyInto_00134BB0(const BfmeElemVKN *first,
	const BfmeElemVKN *last, BfmeElemVKN *result, unsigned int *counter);

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void bfmeFreeNew(void *p);							// retail 0x00881EB0
void bfmeFreeNode(void *p, unsigned int bytes);	// retail 0x0082E5F0

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow( Type *position,
	const Type &value, const __false_type &, unsigned int fillLength, bool atEnd )
{
	vector<Type, Allocator> *self = this;
	unsigned int oldSize = ( unsigned int )( self->m_finish - self->m_start );
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if ( length != 0 )
	{
		unsigned int bytes = length * sizeof( Type );
		if ( bytes > 128 )
			newStart = ( Type * )bfmeNewAlloc( bytes );
		else
			newStart = ( Type * )bfmeAllocNode( bytes );
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = bfmeCopyInto_00134BB0( self->m_start, position, newStart, &fillLength );

	if ( fillLength == 1 )
	{
		*newFinish = value;
		++newFinish;
	}
	else
	{
		for ( unsigned int i = 0; i < fillLength; ++i )
			newFinish[ i ] = value;
		newFinish += fillLength;
	}

	if ( !atEnd )
	{
		Type *last = self->m_finish;
		newFinish = bfmeCopyInto_00134BB0( position, last, newFinish, &fillLength );
	}

	Type *oldStart = self->m_start;
	if ( oldStart != 0 )
	{
		unsigned int oldBytes = ( unsigned int )( self->m_end_of_storage - oldStart ) * sizeof( Type );
		if ( oldBytes > 128 )
			bfmeFreeNew( oldStart );
		else
			bfmeFreeNode( oldStart, oldBytes );
	}

	self->m_finish = newFinish;
	self->m_start = newStart;
	self->m_end_of_storage = newStart + length;
}
}

#pragma comment( linker, "/alternatename:?bfmeCopyInto_00134BB0@@YAPAUBfmeElemVKN@@PBU1@01PAI@Z=?b_00134bb0@@YAXXZ" )
#pragma comment( linker, "/alternatename:?bfmeNewAlloc@@YAPAXI@Z=??2@YAPAXI@Z" )
#pragma comment( linker, "/alternatename:?bfmeAllocNode@@YAPAXI@Z=?allocate@__new_alloc@_STL@@SAPAXI@Z" )
#pragma comment( linker, "/alternatename:?bfmeFreeNew@@YAXPAX@Z=??3@YAXPAX@Z" )
#pragma comment( linker, "/alternatename:?bfmeFreeNode@@YAXPAXI@Z=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z" )

template class _STL::vector<BfmeElemVKN, _STL::allocator<BfmeElemVKN> >;
