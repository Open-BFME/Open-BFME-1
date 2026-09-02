// cl: /DNDEBUG /MD /EHsc

typedef int Int;

class InGameUIPrimary
{
public:
	virtual ~InGameUIPrimary();
	virtual void primaryAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class InGameUISecondary
{
public:
	virtual ~InGameUISecondary();
	virtual void secondaryAnchor();
};

class InGameUI : public InGameUIPrimary, public InGameUISecondary
{
public:
	virtual ~InGameUI();

private:
	unsigned char m_unmodelled_0C[ 0x13AC - 0x0C ];
};

class RefCounted
{
public:
	virtual void Delete_This();
	Int m_refCount;

	void Release_Ref()
	{
		if( --m_refCount == 0 )
			Delete_This();
	}
};

class W3DInGameUI : public InGameUI
{
public:
	virtual ~W3DInGameUI();

private:
	RefCounted *m_first[ 25 ];
	RefCounted *m_second[ 25 ];
	RefCounted *m_buildingPlacementAnchor;
	RefCounted *m_buildingPlacementArrow;
};

static void releaseRef( RefCounted *&p )
{
	if( p != 0 )
	{
		p->Release_Ref();
		p = 0;
	}
}

W3DInGameUI::~W3DInGameUI()
{
	for( Int i = 0; i < 25; ++i )
	{
		releaseRef( m_first[ i ] );
		releaseRef( m_second[ i ] );
	}

	releaseRef( m_buildingPlacementAnchor );
	releaseRef( m_buildingPlacementArrow );
}
