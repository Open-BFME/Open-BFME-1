class Gen_0064C330;
class Gen_0064C380;
class Gen_0064CAA0;
class Gen_0065DA70;
class Gen_0065DAC0;
class Gen_0065DCC0;
class Gen_0065DD10;
class Gen_006AB0B0;
class Gen_006AC5D0;
class BFMENetworkQueueItem;
class BFMENetworkQueueItem1;
class PeerRequest;
class PeerResponse;
class ThingRef;
struct Gen_t_00647b20_k4;
struct Gen_t_00647b20_p12cd;
struct Gen_t_004fc4b0_k4;
struct Gen_t_004fc4b0_p12cd;
struct Gen_t_0065aa20_k4;
struct Gen_t_0065aa20_p12cd;
struct Gen_t_0065aa80_k4;
struct Gen_t_0065aa80_p12cd;

namespace _STL
{
template <class T> class allocator;
template <class First, class Second> struct pair;
template <class T, class U> void _Construct(T *destination, const U &source);
template <class T, class Allocator>
class deque
{
protected:
    void _M_push_back_aux_v(const T &item);
    friend class ::Gen_0064C330;
    friend class ::Gen_0064C380;
    friend class ::Gen_0064CAA0;
    friend class ::Gen_0065DA70;
    friend class ::Gen_0065DAC0;
    friend class ::Gen_0065DCC0;
    friend class ::Gen_0065DD10;
    friend class ::Gen_006AB0B0;
    friend class ::Gen_006AC5D0;
};
}
typedef _STL::deque<BFMENetworkQueueItem, _STL::allocator<BFMENetworkQueueItem> > BFMENetworkQueueItemDeque;
typedef _STL::deque<BFMENetworkQueueItem1, _STL::allocator<BFMENetworkQueueItem1> > BFMENetworkQueueItem1Deque;
typedef _STL::deque<PeerRequest, _STL::allocator<PeerRequest> > PeerRequestDeque;
typedef _STL::deque<PeerResponse, _STL::allocator<PeerResponse> > PeerResponseDeque;
typedef _STL::deque<ThingRef, _STL::allocator<ThingRef> > ThingRefDeque;
void __cdecl gen_00698020(void **destination, void **source);

// Nine bounded appends.
//
// Each compares the cursor at +0x10 against the limit at +0x18 minus ONE
// ELEMENT, copies into the cursor and advances it when there is room, and
// hands the item to a grow routine when there is not.
//
// The subtraction is what gives the element width away -- 0x194, 0x1F0, 0x210,
// 0x330 and 4 across the nine -- because it is pointer arithmetic on the limit,
// not a byte constant the source spells out. The cursor is re-read after the
// copy call before being advanced, since the call could have moved it, and the
// two bodies with four-byte elements are five bytes shorter because both that
// subtraction and the advance fit in a byte displacement.


struct BfmeSlotA
{
	char m_bfmeBytes[0x194];
};

typedef _STL::pair<const Gen_t_00647b20_k4, Gen_t_00647b20_p12cd> BfmeSlotAPair;
__forceinline void bfmeCopySlotA(BfmeSlotA *dest, void *source)
{
    _STL::_Construct((BfmeSlotAPair *)dest, *(const BfmeSlotAPair *)source);
}

struct BfmeSlotB
{
	char m_bfmeBytes[0x330];
};

typedef _STL::pair<const Gen_t_004fc4b0_k4, Gen_t_004fc4b0_p12cd> BfmeSlotBPair;
__forceinline void bfmeCopySlotB(BfmeSlotB *dest, void *source)
{
    _STL::_Construct((BfmeSlotBPair *)dest, *(const BfmeSlotBPair *)source);
}

struct BfmeSlotC
{
	char m_bfmeBytes[0x210];
};

typedef _STL::pair<const Gen_t_0065aa20_k4, Gen_t_0065aa20_p12cd> BfmeSlotCPair;
__forceinline void bfmeCopySlotC(BfmeSlotC *dest, void *source)
{
    _STL::_Construct((BfmeSlotCPair *)dest, *(const BfmeSlotCPair *)source);
}

struct BfmeSlotD
{
	char m_bfmeBytes[0x1F0];
};

typedef _STL::pair<const Gen_t_0065aa80_k4, Gen_t_0065aa80_p12cd> BfmeSlotDPair;
__forceinline void bfmeCopySlotD(BfmeSlotD *dest, void *source)
{
    _STL::_Construct((BfmeSlotDPair *)dest, *(const BfmeSlotDPair *)source);
}

struct BfmeSlotE
{
	char m_bfmeBytes[0x4];
};

__forceinline void bfmeCopySlotE(BfmeSlotE *dest, void *source)
{
    gen_00698020((void **)dest, (void **)source);
}

class Gen_0064C330
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotA *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotA *m_bfmeEnd;					// +0x18
};

class Gen_0064C380
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotB *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotB *m_bfmeEnd;					// +0x18
};

class Gen_0064CAA0
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotA *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotA *m_bfmeEnd;					// +0x18
};

class Gen_0065DA70
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotC *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotC *m_bfmeEnd;					// +0x18
};

class Gen_0065DAC0
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotD *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotD *m_bfmeEnd;					// +0x18
};

class Gen_0065DCC0
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotC *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotC *m_bfmeEnd;					// +0x18
};

class Gen_0065DD10
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotD *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotD *m_bfmeEnd;					// +0x18
};

class Gen_006AB0B0
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotE *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotE *m_bfmeEnd;					// +0x18
};

class Gen_006AC5D0
{
public:
	void bfmePush(void *item);

private:

	char m_bfmeHead[0x10];
	BfmeSlotE *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotE *m_bfmeEnd;					// +0x18
};

// ?bfmePush@Gen_0064C330@@QAEXPAX@Z
void Gen_0064C330::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotA(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((PeerRequestDeque *)this)->_M_push_back_aux_v(*(const PeerRequest *)item);
	}
}

// ?bfmePush@Gen_0064C380@@QAEXPAX@Z
void Gen_0064C380::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotB(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((PeerResponseDeque *)this)->_M_push_back_aux_v(*(const PeerResponse *)item);
	}
}

// ?bfmePush@Gen_0064CAA0@@QAEXPAX@Z
void Gen_0064CAA0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotA(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((PeerRequestDeque *)this)->_M_push_back_aux_v(*(const PeerRequest *)item);
	}
}

// ?bfmePush@Gen_0065DA70@@QAEXPAX@Z
void Gen_0065DA70::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotC(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((BFMENetworkQueueItemDeque *)this)->_M_push_back_aux_v(*(const BFMENetworkQueueItem *)item);
	}
}

// ?bfmePush@Gen_0065DAC0@@QAEXPAX@Z
void Gen_0065DAC0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotD(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((BFMENetworkQueueItem1Deque *)this)->_M_push_back_aux_v(*(const BFMENetworkQueueItem1 *)item);
	}
}

// ?bfmePush@Gen_0065DCC0@@QAEXPAX@Z
void Gen_0065DCC0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotC(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((BFMENetworkQueueItemDeque *)this)->_M_push_back_aux_v(*(const BFMENetworkQueueItem *)item);
	}
}

// ?bfmePush@Gen_0065DD10@@QAEXPAX@Z
void Gen_0065DD10::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotD(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((BFMENetworkQueueItem1Deque *)this)->_M_push_back_aux_v(*(const BFMENetworkQueueItem1 *)item);
	}
}

// ?bfmePush@Gen_006AB0B0@@QAEXPAX@Z
void Gen_006AB0B0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotE(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((ThingRefDeque *)this)->_M_push_back_aux_v(*(const ThingRef *)item);
	}
}

// ?bfmePush@Gen_006AC5D0@@QAEXPAX@Z
void Gen_006AC5D0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotE(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		((ThingRefDeque *)this)->_M_push_back_aux_v(*(const ThingRef *)item);
	}
}
