// cl: /DNDEBUG /MD
//
// Retail 0x00809690: BfmeSubSKA::bfmeTestSKA.  Walks the pointer array at +8
// (count at +4) for an element whose dword at +0x10 equals the argument, then
// runs that element's destructor and sized delete (0x38) and nulls the slot.

// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies
// call (store the base vtable 0x01129358 into *this, then ret).  It is defined
// under this name in game/gen_small/fun_005.cpp, so every call site spells it
// through this neutral declaration rather than a member of the local view.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeSub1045
{
public:
	int m_gap00;
	int m_gap04;
	int m_gap08;
	int m_gap0c;
	int m_id;
};

// The sized release this body calls is retail 0x007F0170, defined as the
// class operator delete ? 3Gen007F0170@@SAXPAX@Z
// (game/GameEngine/Source/Common/S3AllocatorOperatorNewDelete.cpp).  Retail
// pushes the size as well, so the call goes through that definition with a
// two-argument pointer type.
class Gen007F0170
{
public:
	static void operator delete(void *block);
};

typedef void (__cdecl *Gen007F0170SizedFree)(void *block, unsigned int size);

class BfmeSubSKA
{
public:
	char bfmeTestSKA( int id );

	int m_gap00;
	int m_count;
	BfmeSub1045 **m_array;
};

char BfmeSubSKA::bfmeTestSKA( int id )
{
	BfmeSub1045 *elem;
	BfmeSub1045 **slot;
	int i;
	int n;

	n = m_count;
	i = 0;
	if ( n > 0 )
	{
		slot = m_array;
		do
		{
			elem = *slot;
			if ( elem != 0 )
			{
				if ( elem->m_id == id )
				{
					reinterpret_cast< Gen_007e86c0 * >( elem )->m();
					((Gen007F0170SizedFree)&Gen007F0170::operator delete)( elem, 0x38 );
					m_array[ i ] = 0;
					return 1;
				}
			}
			++i;
			++slot;
		} while ( i < n );
	}
	return 0;
}
