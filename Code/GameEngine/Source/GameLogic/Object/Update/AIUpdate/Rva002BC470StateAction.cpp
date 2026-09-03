// cl: /DNDEBUG /MD

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isMobile() const;
};

class Rva002BC470Sink
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void beginAction() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void signalAction( Int code ) = 0;
};

class Rva002BC470StateAction
{
public:
	void run( void *first, void *second );
	void prepare( void *first, void *second );
	void finish( void *second );

private:
	unsigned char m_unreconstructed00[ 0x08 ];
	Object *m_object;
	unsigned char m_unreconstructed0c[ 0x24 ];
	Rva002BC470Sink *m_sink;
	unsigned char m_unreconstructed34[ 0x42c ];
	Int m_actionStarted;
};

void Rva002BC470StateAction::run( void *first, void *second )
{
	if ( first && m_object->isMobile() )
	{
		m_sink->beginAction();
		prepare( first, second );
		finish( second );
		m_sink->signalAction( 0x3e9 );
		m_actionStarted = 1;
	}
}
