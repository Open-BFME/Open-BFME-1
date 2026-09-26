// cl: /DNDEBUG /MD

typedef int Int;

class Rva002BC4E0Sink
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

class Rva002BC4E0StateAction
{
public:
	void run( void *first, void *second );
	void prepare( void *first, void *second );
	void finish( void *second );

private:
	unsigned char m_unreconstructed00[ 0x30 ];
	Rva002BC4E0Sink *m_sink;
	unsigned char m_unreconstructed34[ 0x2f7 ];
	unsigned char m_disabled;
	unsigned char m_unreconstructed32c[ 0x134 ];
	Int m_actionStarted;
};

void Rva002BC4E0StateAction::run( void *first, void *second )
{
	if ( !m_disabled )
	{
		m_sink->beginAction();
		prepare( first, second );
		finish( second );
		m_sink->signalAction( 0x3fb );
		m_actionStarted = 1;
	}
}
