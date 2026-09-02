// cl: /DNDEBUG /MD
// Address-derived timed model-condition update at retail RVA 0x00216100.

class Object
{
public:
	void notifyModelConditionChanged();
	char m_unmodelled_000[ 0x114 ];
	unsigned int m_modelConditions;
};

struct GameLogicFrameSlice
{
	char m_unmodelled_000[ 0x3c ];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

class Rva00216100TimedCondition
{
public:
	int update00216100();
private:
	char m_unmodelled_000[ 0x14 ];
	unsigned int m_expirationFrame;
	char m_unmodelled_018[ 4 ];
	bool m_active;
};

int Rva00216100TimedCondition::update00216100()
{
	if( m_active )
	{
		if( m_expirationFrame < TheGameLogic->m_frame )
		{
			Object *object = *(Object **)( (char *)this - 8 );
			if( object->m_modelConditions & 0x100 )
			{
				object->m_modelConditions &= ~0x100;
				object->notifyModelConditionChanged();
			}
			m_active = false;
		}
		return 1;
	}
	return 0x3fffffff;
}
