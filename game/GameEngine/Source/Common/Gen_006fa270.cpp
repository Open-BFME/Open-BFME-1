// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: the two anonymous retail bodies at 0x006FA270 (177B) and
// 0x006FA420 (85B), converted from the game/gen_asm naked dumps to real C++.
//
// The targets/game/reverse/symbols.csv pins that name these
// as the STLport AsciiString copy/destroy shims ARE WRONG, and this conversion is the disproof.  Both bodies stride the
// range by TWELVE bytes (0x006FA270 divides last-first by 12 via the
// 0x2AAAAAAB magic multiply; 0x006FA420 does `add eax,0Ch`), and AsciiString
// is FOUR bytes -- one AsciiStringData*.  The earlier verdict ("intrusive-list
// or hashtable node splice code, not a linear array copy") had the right
// observation and the wrong conclusion: these ARE _STL::__copy and
// _STL::__destroy_aux over a linear array, and the splice code is the ELEMENT's
// operator= and destructor being inlined into the loop body.
//
// The AsciiString attribution came in through ICF.  vector<T>::erase / clear /
// __copy_ptrs / __destroy / _Destroy carry NO stride arithmetic -- they only
// forward pointers -- so those bodies are byte-identical for every element type
// and fold together; the surviving name is whichever instantiation the pinner
// reached first.  Only __copy and __destroy_aux, which inline the element's
// own operator= and ~T(), keep the element's fingerprint, and this one's is a
// 12-byte intrusive doubly-linked list node, not a string.
//
// The element is UNIDENTIFIABLE from this image, not merely unidentified: the
// only paths in are through ILT thunks (0x00042EA6, 0x00014AA1, 0x0002FD8D,
// 0x00001CDF) that nothing in the image references.  The names below are
// address-derived on purpose; they disclaim identity rather than assert one.
//
// Recovered element ABI: 12 bytes { owner*, prev*, next* }, owner keeps the
// list head at owner+0x98 and the tail at owner+0x9C.

struct GenNode_006fa270;

struct GenOwner_006fa270
{
	char m_pad[0x98];
	GenNode_006fa270 *m_head;	// owner + 0x98
	GenNode_006fa270 *m_tail;	// owner + 0x9C
};

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;	// +0
	GenNode_006fa270 *m_prev;	// +4
	GenNode_006fa270 *m_next;	// +8

	void unlink(void)
	{
		if (m_owner != 0)
		{
			if (m_prev != 0)
				m_prev->m_next = m_next;
			else
				m_owner->m_head = m_next;

			if (m_next != 0)
				m_next->m_prev = m_prev;
			else
				m_owner->m_tail = m_prev;

			m_prev = 0;
			m_next = 0;
		}
	}

	void setOwner(GenOwner_006fa270 *owner)
	{
		m_owner = owner;
		if (owner != 0)
		{
			m_prev = owner->m_tail;
			m_next = 0;
			owner->m_tail = this;
			if (m_prev != 0)
				m_prev->m_next = this;
			else
				m_owner->m_head = this;
		}
	}

	~GenNode_006fa270(void) { unlink(); }

	GenNode_006fa270 &operator=(const GenNode_006fa270 &o)
	{
		if (this != &o)
		{
			unlink();
			setOwner(o.m_owner);
		}
		return *this;
	}
};

GenNode_006fa270 *gen_copy_006fa270(GenNode_006fa270 *first, GenNode_006fa270 *last, GenNode_006fa270 *result)
{
	for (int n = last - first; n > 0; --n)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

void gen_destroy_006fa420(GenNode_006fa270 *first, GenNode_006fa270 *last)
{
	for (; first != last; ++first)
		first->~GenNode_006fa270();
}
