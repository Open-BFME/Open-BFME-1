// Team's MAKE_DLINK_HEAD(Object, TeamMemberList) list-owner pair, in BFME's
// object layout.
//
// WHAT THE BYTES SHOW.  0x001BD560 and 0x001BD5B0 are the two halves of the
// ZH MAKE_DLINK_HEAD macro, unchanged in shape:
//
//   prependTo: if (*head == o || o->prev || o->next) return;
//              o->next = *head; if (*head) (*head)->prev = o; *head = o;
//   removeFrom: if (*head == o || o->prev || o->next)
//                   o->dlink_removeFrom_TeamMemberList(head);
//
// and the tail call in the second one goes (through incremental-link thunk
// 0x0001330E) to 0x001BD490, which is itself the unmistakable
// dlink_removeFrom body: it unlinks through the same two fields, writes
// *pListHead when the prev link is null, and nulls both links.
//
// ONLY THREE CONSTANTS DIFFER from what the ZH headers compute:
//
//   Team::m_dlinkhead_TeamMemberList.m_head   +0x10 -> +0x0C
//   Object::m_dlink_TeamMemberList.m_prev     +0x1E8 -> +0x25C
//   Object::m_dlink_TeamMemberList.m_next     +0x1EC -> +0x260
//
// The Object pair is corroborated by adjacency: m_weaponSet is pinned at
// +0x264 by already-matched rows, and in the class the WeaponSet immediately
// follows the DLINK, so the DLINK's second word must end at 0x264.
//
// This lives in its own TU rather than in the bfmeobjectlayout shim because
// the shim's Object header cannot express the move (the members after the
// DLINK do not all shift by the same amount) and Weapon.cpp shares that shim.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void prependTo_TeamMemberList( Object* o );
	void removeFrom_TeamMemberList( Object* o );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// defined in retail at 0x001BD490; pinned in reverse/symbols.csv
	void dlink_removeFrom_TeamMemberList( Object** pListHead );
};

namespace
{
	struct W1TeamHeadView
	{
		unsigned char pad[0x0C];
		Object* head;
	};

	struct W1ObjectLinkView
	{
		unsigned char pad[0x25C];
		Object* prev;
		Object* next;
	};

	inline bool w1_dlink_isInList( Object* o, Object* const* pListHead )
	{
		W1ObjectLinkView* link = reinterpret_cast<W1ObjectLinkView*>( o );
		return *pListHead == o || link->prev || link->next;
	}

	inline void w1_dlink_prependTo( Object* o, Object** pListHead )
	{
		W1ObjectLinkView* link = reinterpret_cast<W1ObjectLinkView*>( o );
		link->next = *pListHead;
		if ( *pListHead )
			reinterpret_cast<W1ObjectLinkView*>( *pListHead )->prev = o;
		*pListHead = o;
	}
}

void Team::prependTo_TeamMemberList( Object* o )
{
	if ( !w1_dlink_isInList( o, &reinterpret_cast<W1TeamHeadView*>( this )->head ) )
		w1_dlink_prependTo( o, &reinterpret_cast<W1TeamHeadView*>( this )->head );
}

void Team::removeFrom_TeamMemberList( Object* o )
{
	Object** head = &reinterpret_cast<W1TeamHeadView*>( this )->head;
	W1ObjectLinkView* link = reinterpret_cast<W1ObjectLinkView*>( o );
	if ( *head == o || link->prev || link->next )
		o->dlink_removeFrom_TeamMemberList( head );
}
