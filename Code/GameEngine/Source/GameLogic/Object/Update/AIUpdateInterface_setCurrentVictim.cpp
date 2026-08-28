// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef int ObjectID;

class AIUpdateInterface;

class Object
{
public:
	ObjectID getID() const
	{
		return m_id;
	}

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

private:
	unsigned char m_unmodelled_00[ 0x74 ];
	ObjectID m_id;
	unsigned char m_unmodelled_78[ 0x204 - 0x78 ];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

#define AI_VIRTUAL_SLOT( PREFIX, SUFFIX ) virtual void slot_##PREFIX##SUFFIX();
#define AI_VIRTUAL_SLOT_TEN( PREFIX ) \
	AI_VIRTUAL_SLOT( PREFIX, 0 )       \
	AI_VIRTUAL_SLOT( PREFIX, 1 )       \
	AI_VIRTUAL_SLOT( PREFIX, 2 )       \
	AI_VIRTUAL_SLOT( PREFIX, 3 )       \
	AI_VIRTUAL_SLOT( PREFIX, 4 )       \
	AI_VIRTUAL_SLOT( PREFIX, 5 )       \
	AI_VIRTUAL_SLOT( PREFIX, 6 )       \
	AI_VIRTUAL_SLOT( PREFIX, 7 )       \
	AI_VIRTUAL_SLOT( PREFIX, 8 )       \
	AI_VIRTUAL_SLOT( PREFIX, 9 )

class AIUpdateInterface
{
public:
	AI_VIRTUAL_SLOT_TEN( 0 )
	AI_VIRTUAL_SLOT_TEN( 1 )
	AI_VIRTUAL_SLOT_TEN( 2 )
	AI_VIRTUAL_SLOT_TEN( 3 )
	AI_VIRTUAL_SLOT_TEN( 4 )
	AI_VIRTUAL_SLOT_TEN( 5 )
	AI_VIRTUAL_SLOT_TEN( 6 )
	AI_VIRTUAL_SLOT_TEN( 7 )
	AI_VIRTUAL_SLOT_TEN( 8 )
	AI_VIRTUAL_SLOT_TEN( 9 )
	AI_VIRTUAL_SLOT_TEN( 10 )
	AI_VIRTUAL_SLOT( 11, 0 )
	AI_VIRTUAL_SLOT( 11, 1 )
	AI_VIRTUAL_SLOT( 11, 2 )
	AI_VIRTUAL_SLOT( 11, 3 )
	AI_VIRTUAL_SLOT( 11, 4 )
	virtual void addTargeter( ObjectID id, Bool add );

	void setCurrentVictim( const Object *victim );

private:
	unsigned char m_unmodelled_04[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x40 - 0x0C ];
	ObjectID m_currentVictimID;
};

#undef AI_VIRTUAL_SLOT_TEN
#undef AI_VIRTUAL_SLOT

void AIUpdateInterface::setCurrentVictim( const Object *victim )
{
	if( victim == 0 )
	{
		if( m_currentVictimID != 0 )
		{
			Object *self = m_object;
			Object *target = TheGameLogic->findObjectByID( m_currentVictimID );
			if( self != 0 && target != 0 )
			{
				AIUpdateInterface *targetAI = target->getAI();
				if( targetAI != 0 )
					targetAI->addTargeter( self->getID(), false );
			}
		}

		m_currentVictimID = 0;
	}
	else
	{
		m_currentVictimID = victim->getID();
	}
}
