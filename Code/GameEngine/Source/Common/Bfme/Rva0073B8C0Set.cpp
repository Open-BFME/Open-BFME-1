// 24-byte setter, 15-byte subobject virtual tail-call, 72-byte reset, and 58-byte property setter

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	void appendIntegerArgument( int arg );
};

class GameMessageDispatcher
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual GameMessage *createMessage( int id );
};

extern GameMessageDispatcher *TheGameMessageDispatcher;

// The retail object at 0x012ED5C8 is the established GlobalData singleton;
// this TU-local view names only the +0x188 scalar read proven by 0x0073B9C0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char  m_pad00[ 0x188 ];
	float m_field188;
};

extern GlobalData *TheWritableGlobalData;

class SubObject0073B9A0
{
public:
	virtual void v0();
	virtual void handle();
};

class Rva0073B8C0
{
public:
	void set( int a, int b );
	void go();
	void reset();
	void setInt23BC( int arg );
	float scale( float arg );

	char              m_pad00[ 0x58 ];
	int               m_int58;
	int               m_int5C;
	int               m_field60;
	int               m_field64;
	int               m_int68;
	char              m_pad6C[ 0x170 ];
	char              m_byte1DC;
	char              m_pad1DD[ 0x27 ];
	char              m_byte204;
	char              m_pad205[ 0x23 ];
	char              m_byte228;
	char              m_pad229[ 0x53 ];
	char              m_byte27C;
	bool              m_flag27D;
	char              m_pad27E[ 0x20D6 ];
	int               m_int2354;
	char              m_pad2358[ 0x60 ];
	char              m_byte23B8;
	char              m_pad23B9[ 3 ];
	int               m_int23BC;
	char              m_pad23C0[ 0x20 ];
	float             m_float23E0;
	char              m_pad23E4[ 0x58 ];
	int               m_int243C;
	int               m_int2440;
	int               m_int2444;
	char              m_pad2448[ 0x70 ];
	SubObject0073B9A0 m_subObject;
};

void Rva0073B8C0::set( int a, int b )
{
	m_field60 = a;
	m_field64 = b;
	m_flag27D = true;
}

void Rva0073B8C0::go()
{
	m_subObject.handle();
}

void Rva0073B8C0::reset()
{
	m_int2354 = 0;
	m_byte1DC = 0;
	m_byte204 = 0;
	m_byte228 = 0;
	m_flag27D = 0;
	m_byte27C = 0;
	m_byte23B8 = 0;
	m_int243C = 0;
	m_int2440 = 0;
	m_int2444 = 0;
	m_int58 = 0;
	m_int5C = 0;
	m_int68 = 0;
}

void Rva0073B8C0::setInt23BC( int arg )
{
	if ( arg != m_int23BC )
	{
		if ( TheGameMessageDispatcher )
		{
			GameMessage *msg = TheGameMessageDispatcher->createMessage( 0x451 );
			msg->appendIntegerArgument( arg );
			return;
		}
		m_int23BC = arg;
	}
}

float Rva0073B8C0::scale( float arg )
{
	if ( TheWritableGlobalData->m_field188 > 1.0f )
		return arg / m_float23E0;
	return 1.0f;
}
