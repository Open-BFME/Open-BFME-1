// cl: /DNDEBUG /MD
//
// Retail 0x003EC070: the BFME member-ified cell callback used by
// moveAlliesAwayFromDestination.  The cell-space line walk passes the payload
// as this and (from,to,x,y) as its four stack arguments.

typedef int Int;
typedef bool Bool;
typedef int ObjectID;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum Relationship
{
	ALLIES = 2
};

class Object;

class BFMEActionObject
{
public:
	Bool testStatus( Int status ) const;

	char m_prefix[0x90];
	unsigned int m_status[1];
};

class BfmeHordeMember
{
public:
	Bool bfmeBlocksFormationRefresh( void );
};

class AICommandInterface
{
public:
	void aiMoveAwayFromUnit( Object *object, CommandSourceType commandSource );
};

class PathfindCellInfo
{
public:
	char m_prefix[0x18];
	ObjectID m_posUnit;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
};

class Object
{
public:
	Relationship getRelationship( const Object *other ) const;

	char m_prefix[0x74];
	ObjectID m_id;
	char m_gap78[0x204 - 0x78];
	BfmeHordeMember *m_ai;
	char m_gap208[0x214 - 0x208];
	Object *m_containedBy;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheBfmeGameLogic;

class MADStruct
{
public:
	Int cellCallback( PathfindCell *from, PathfindCell *to, Int to_x, Int to_y );

	Object *m_obj;
	ObjectID m_ignoreID;
};

Int MADStruct::cellCallback( PathfindCell *from, PathfindCell *to,
	Int to_x, Int to_y )
{
	PathfindCellInfo *info = to->m_info;
	if (info != 0)
	{
		ObjectID objectID = info->m_posUnit;
		if (objectID != 0)
		{
			register Object *obj = m_obj;
			if (objectID != obj->m_id && objectID != m_ignoreID)
			{
				Object *other = TheBfmeGameLogic->findObjectByID( objectID );
				if (other != 0 && obj->getRelationship( other ) == ALLIES)
				{
					if (((BFMEActionObject *)other)->testStatus( 0x25 ))
					{
						Object *contained = other->m_containedBy;
						if (contained != 0)
							other = contained;
					}
					if (other != 0)
					{
						if (other->m_ai != 0 &&
							!other->m_ai->bfmeBlocksFormationRefresh())
						{
							AICommandInterface *commands =
								(AICommandInterface *)((unsigned char *)other->m_ai + 0x20);
							commands->aiMoveAwayFromUnit( m_obj, CMD_FROM_AI );
						}
					}
				}
			}
		}
	}
	return 0;
}
