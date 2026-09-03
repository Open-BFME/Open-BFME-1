// cl: /DNDEBUG /MD /EHsc
// Constructor installing vtable 0x0109685C (same family as
// Rva00160BB0VptrZeroObject). Arg1 is an Object whose controlling player
// is stored at +8; arg2 is a flag at +0xC. Null object stores a null player.
// Virtual dtor on the head is what buys the constructor EH frame.

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04(0) {}
	virtual ~VptrZeroHead();
	unsigned int m_unmodelled_04;
};

VptrZeroHead::~VptrZeroHead()
{
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	class Player *getControllingPlayer(void) const;
};

class Rva001DCBB0Filter : public VptrZeroHead
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);

	class Player *m_player;
	unsigned char m_match;
};

Rva001DCBB0Filter::Rva001DCBB0Filter(Object *object, unsigned char match)
	: m_player(object ? object->getControllingPlayer() : 0), m_match(match)
{
}
