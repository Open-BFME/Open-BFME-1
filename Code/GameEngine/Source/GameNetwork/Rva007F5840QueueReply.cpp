// cl: /O2 /GS
// 0x007F5840: FESL queue-status reply handler.
//
// The on-stack Rva007F5120Queue temporary (ctor at 0x007F5120, matched in
// V2FeslAriesRecords.cpp), the message error accessors pinned at
// 0x007E88A0/0x007E88B0 and the listener member at +0x1c follow the
// neighbouring game-browser reply handlers at 0x007F5720 and 0x007F5D10.
// The 'queu' error code (0x71756575) copies the queue position/length into
// the result; any other error forwards the reason text to
// BfmeOwnerYA::bfmeParseYA (0x007F5560, BfmeConv1857.cpp). No caller, string
// or vtable install proves the owner class or method name, so both stay
// address-derived.

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
	virtual void onQueueStatus( BfmeOwnerYA *result, int error );
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
	int error = 0;

	if( msg->hasError() )
	{
		error = msg->getError();
		if( error == 0x71756575 )
		{
			error = 0;
			result->m_qpos = q.m_qpos;
			result->m_qlen = q.m_qlen;
			result->m_status = 3;
		}
		else
		{
			result->m_status = 0;
			result->bfmeParseYA( q.m_reason );
		}
	}
	else if( result->m_flag014 )
	{
		m_flag036 = 0;
	}

	m_listener->onQueueStatus( result, error );
}
