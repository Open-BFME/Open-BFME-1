// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::pair<const Int, GameSpyGroupRoom>::~pair, retail
// 0x00631920, 77 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The pair's first is an Int, so the whole body is the second member's
// compiler-generated destructor inlined: it destroys two strings in reverse
// declaration order and nothing else. The unwind object is registered as
// pair+4 -- the GameSpyGroupRoom itself -- and the state counts 0 then -1
// across the two members.
//
// Which string is which comes from the two releaseBuffer bodies: the member at
// GameSpyGroupRoom+4 releases through 0x008881D0, the wide one, and the member
// at +0 through 0x00887940, the narrow one. Reverse order puts the wide member
// first, which is why the higher address is destroyed first.

typedef int Int;

template <class T>
class StringBase
{
public:
	~StringBase(void) { releaseBuffer(); }

private:
	void releaseBuffer(void);				// D: 0x00887940  G: 0x008881D0

	T *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyGroupRoom
{
public:
	StringBase<char> m_bfmeNarrow;				// +0x00
	StringBase<unsigned short> m_bfmeWide;			// +0x04
	unsigned char m_bfmeTail[0x18];
};

namespace _STL
{

template <class T1, class T2>
class pair
{
public:
	T1 first;
	T2 second;
};

}

// The explicit instantiation alone does not emit the implicit destructor, so
// it is reached through a call.
void BfmeGameSpyGroupRoomPairDestroyAnchor(_STL::pair<const Int, GameSpyGroupRoom> *entry)
{
	entry->~pair();
}
