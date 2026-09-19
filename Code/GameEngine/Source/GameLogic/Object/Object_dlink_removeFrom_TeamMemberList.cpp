// BFME's Object TeamMemberList dlink removal helper, retail 0x001BD490.
//
// The Team wrapper's only tail call reaches this body, and the retail layout
// is independently anchored by the adjacent exact Team wrapper and the
// Object weapon-set field at +0x264: prev/next are +0x25C/+0x260.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void dlink_removeFrom_TeamMemberList( Object** pListHead );
};

struct W1ObjectTeamLinkView
{
	unsigned char pad[0x25C];
	Object* prev;
	Object* next;
};

void Object::dlink_removeFrom_TeamMemberList( Object** pListHead )
{
	W1ObjectTeamLinkView* link = reinterpret_cast<W1ObjectTeamLinkView*>( this );
	if ( link->next )
		reinterpret_cast<W1ObjectTeamLinkView*>( link->next )->prev = link->prev;

	if ( link->prev )
		reinterpret_cast<W1ObjectTeamLinkView*>( link->prev )->next = link->next;
	else
		*pListHead = link->next;

	link->prev = 0;
	link->next = 0;
}
