// These payload helpers are the direct callees of the element-stride walks.
// Their destination null checks explain why the wrappers may pass an empty
// slot, while the fixed first store distinguishes construction from copying.

extern int R2Data010EC760;
extern int R2Data010EC764;
extern int R2Data010EC768;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

struct Elem32
{
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	int m_at14;
	int m_at18;
	char m_at1C;
	char m_pad1D[ 3 ];
};

void gen003A84E0( Elem32 * slot, const Elem32 * source )
{
	if ( slot == 0 )
		return;

	slot->m_at00 = &R2Data010EC764;
	slot->m_at04 = source->m_at04;
	slot->m_at08 = source->m_at08;
	slot->m_at0C = source->m_at0C;
	slot->m_at10 = source->m_at10;
	slot->m_at14 = source->m_at14;
	slot->m_at18 = source->m_at18;
	slot->m_at1C = source->m_at1C;
}

struct Elem16
{
	void * m_at00;
	int m_at04;
	void * m_at08;
	char m_at0C;
	char m_pad0D[ 3 ];
};

void gen003A85C0( Elem16 * slot, const Elem16 * source )
{
	if ( slot == 0 )
		return;

	slot->m_at00 = &R2Data010EC768;
	slot->m_at04 = source->m_at04;
	slot->m_at08 = source->m_at08;
	if ( slot->m_at08 != 0 )
		InterlockedIncrement( (long *)((char *)slot->m_at08 + 4) );
	slot->m_at0C = source->m_at0C;
}

struct Gen_t_003b4b60_p16cd
{
	void * m_at00;
	int m_at04;
	char m_at08;
	char m_pad09[ 3 ];
	int m_at0C;
};

namespace _STL
{
struct __false_type {};

template <class Input, class Output>
Output __uninitialized_copy( Input first, Input last, Output result, const __false_type & )
{
	for ( ; first != last; ++first, ++result )
	{
		if ( result != 0 )
		{
			result->m_at00 = &R2Data010EC760;
			result->m_at04 = first->m_at04;
			result->m_at08 = first->m_at08;
			result->m_at0C = first->m_at0C;
		}
	}
	return result;
}
}

template Gen_t_003b4b60_p16cd * _STL::__uninitialized_copy<const Gen_t_003b4b60_p16cd *, Gen_t_003b4b60_p16cd *>(
	const Gen_t_003b4b60_p16cd *, const Gen_t_003b4b60_p16cd *, Gen_t_003b4b60_p16cd *, const _STL::__false_type & );
