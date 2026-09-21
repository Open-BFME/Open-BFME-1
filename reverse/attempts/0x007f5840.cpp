// ?handleQueueReply@Rva007F5840Owner@@QAEXPAVRva007E8810Message@@PAVBfmeOwnerYA@@@Z
// partial score=0.25 date=2026-09-21
// cl: /GS
// 0x007F5840: FESL game-browser queue-status reply handler.
//
// The on-stack Rva007F5120Queue temporary (ctor at 0x007F5120, matched in
// V2FeslAriesRecords.cpp), the message error accessors pinned at
// 0x007E88A0/0x007E88B0 (?hasError@Rva007E8810Message@@QAE_NXZ /
// ?getError@Rva007E8810Message@@QAEHXZ), and the listener member at +0x1c
// match the neighboring recovered gamebrowser reply handlers at 0x007F5720
// and 0x007F5D10 (Rva007F5720GameBrowserLogin.cpp / Rva007F5D10GameBrowser.cpp)
// exactly in shape. No caller, string, or vtable install proves the owning
// class or method name here, so the remaining names are address-derived; the
// result-holder type keeps the BfmeOwnerYA name already established by
// BfmeConv1857.cpp (its ::bfmeParseYA is called directly below).

class Rva007E8810Message
{
public:
	bool hasError( void );
	int getError( void );
};

class Rva007F5120Queue
{
public:
	Rva007F5120Queue( Rva007E8810Message *msg );

	char m_pad000[ 8 ];
	char m_reason[ 0x100 ];
	int m_qpos;
	int m_qlen;
};

class BfmeOwnerYA
{
public:
	void bfmeParseYA( const char *text );

	char m_pad000[ 8 ];
	int m_status;
	int m_qlen;
	int m_qpos;
	unsigned char m_flag014;
};

class Rva007F5840Listener
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void onQueueStatus( BfmeOwnerYA *result, int zero );
};

class Rva007F5840Owner
{
public:
	void handleQueueReply( Rva007E8810Message *msg, BfmeOwnerYA *result );

private:
	char m_pad000[ 0x1c ];
	Rva007F5840Listener *m_listener;
	char m_pad020[ 0x16 ];
	unsigned char m_flag036;
};

void Rva007F5840Owner::handleQueueReply( Rva007E8810Message *msg, BfmeOwnerYA *result )
{
	Rva007F5120Queue q( msg );
	int code = 0;

	if( msg->hasError() )
	{
		code = msg->getError();
		if( code == 0x71756575 )
		{
			result->m_status = 0;
			result->bfmeParseYA( q.m_reason );
		}
		else
		{
			result->m_qpos = q.m_qpos;
			result->m_qlen = q.m_qlen;
			result->m_status = 3;
		}
	}
	else if( result->m_flag014 )
	{
		m_flag036 = 0;
		m_listener->onQueueStatus( result, code );
	}
}
