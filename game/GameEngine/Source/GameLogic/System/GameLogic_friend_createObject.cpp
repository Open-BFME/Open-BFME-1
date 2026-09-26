// The body at retail RVA 0x003830C0 creates an Object through GameLogic.
// ThingFactory::newObject calls this body through ILT 0x000168DD.
// Thirteen named callers identify ThingFactory::newObject.
// The retail newObj debug string identifies the same method.
// The allocator requests 0x3C4 bytes.
// The body calls the Object constructor at retail RVA 0x001D29A0.
// The constructor receives four caller arguments and a trailing literal 1.
typedef unsigned int UnsignedInt;

template <int N>
class BitFlags
{
public:
	UnsignedInt m_words[6];
};

typedef BitFlags<86> ObjectStatusMaskType;

class ThingTemplate;
class Team;

class Object
{
public:
	Object( const ThingTemplate *p1, const ObjectStatusMaskType &p2,
		Team *p3, UnsignedInt p4, int one );

private:
	char m_unmodelled[ 0x3C4 ];
};

class GameLogic
{
public:
	Object *friend_createObject( const ThingTemplate *,
		const ObjectStatusMaskType &, Team *, UnsignedInt );
};

// ?friend_createObject@GameLogic@@QAEPAVObject@@PBVThingTemplate@@ABV?$BitFlags@$0FG@@@PAVTeam@@I@Z
Object *GameLogic::friend_createObject( const ThingTemplate *p1,
	const ObjectStatusMaskType &p2, Team *p3, UnsignedInt p4 )
{
	return new Object( p1, p2, p3, p4, 1 );
}
