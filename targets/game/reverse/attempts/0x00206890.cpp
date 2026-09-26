// ?d_00206890@@YAXXZ
// partial score=0.82 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

typedef int ObjectID;

class Object;

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheBfmeGameLogic;

class Object
{
};

class Overridable
{
public:
	Overridable *getFinalOverride();

	char m_unmodelled[ 0xd8 ];
	unsigned int m_flags;
};

class BfmeSiegeDockEntry
{
public:
	char m_unmodelled_00[ 4 ];
	void *m_at04;
	char m_unmodelled[ 0x18 ];
	unsigned int m_at20;
};

class BfmeOuterCFD
{
public:
	void bfmeTwoCFD();
};

class __declspec( novtable ) Rva00206890SiegeDockingInterface
{
public:
	virtual bool query( ObjectID id );

private:
	BfmeSiegeDockEntry **m_start;
	BfmeSiegeDockEntry **m_finish;
};

// ?query@Rva00206890SiegeDockingInterface@@QAE_NH@Z
bool Rva00206890SiegeDockingInterface::query( ObjectID id )
{
	Object *object = TheBfmeGameLogic->findObjectByID( id );
	if( object == 0 )
		return false;

	((BfmeOuterCFD *)((char *)this - 0x20))->bfmeTwoCFD();

	unsigned int count = (unsigned int)( m_finish - m_start );
	if( count == 0 )
		return false;

	BfmeSiegeDockEntry **it = m_start;
	unsigned int i = 0;
	while( i < count )
	{
		BfmeSiegeDockEntry *entry = *it;
		if( entry->m_at20 != 0 )
			return true;

		Object *templateObject = *(Object **)((char *)object + 4);
		if( templateObject != 0 )
		{
			Overridable *overrideObject = *(Overridable **)((char *)templateObject + 4);
			if( overrideObject != 0 )
			{
				if( ( overrideObject->getFinalOverride()->m_flags & 0x400 ) == 0
					&& entry->m_at04 != 0 )
					return true;
			}
		}

		++i;
		++it;
	}

	return false;
}
