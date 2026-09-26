// EA FESL client SDK ("jabba") -- Aries browser reply handlers.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; see that file's head
// comment for how the span was identified.
//
// WHAT THE BYTES SHOW.  Three tiny __thiscall accessors on the message object
// pin down its error word at +0x24:
//     0x007E88A0   mov edx,[ecx+0x24] ; xor eax,eax ; test edx,edx ; setne al
//     0x007E88B0   mov eax,[ecx+0x24] ; ret
//     0x007E88C0   mov [ecx+0x24],arg ; ret 4
// and 0x007E88C0 is the same body the request builders call to store -113 on a
// bad owner type, so +0x24 really is an error code: a predicate, a getter and a
// setter over one field.  The ledger reaches 0x007E88A0 under the ICF-fold name
// ?valid@W3DVideoBuffer@@UAE_NXZ; that is an unrelated body folded onto these
// five bytes, not evidence about this object, so this file pins its own names.
//
// Every row here dispatches through the pointer at +0x1C of the browser object
// into a vtable, so that pointer is a LISTENER and the slot INDEX is evidence
// (0x0C, 0x10, 0x48, 0x4C -> slots 3, 4, 18, 19).  Nothing names the listener
// interface, so its other slots are placeholders and exist only to number the
// ones that are used.
//
// The two count handlers end in `mov [esp+4],eax ; jmp [edx+slot]`, MSVC's tail
// call for a void function whose last statement is a one-argument __thiscall
// virtual call -- so the notification really is the last thing each does.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the browser, the listener, or
// any method.  The key spellings "NUM-REGIONS" and "NUM-LOBBIES" are pushed
// literals and are real; the C++ names are address-derived.

class Rva007E8810Message
{
public:
	bool hasError( void );                                            // 0x007E88A0
	int getError( void );                                             // 0x007E88B0
	int getInt( const char *key, int defaultValue );                  // 0x007E8900

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007F6BA0
{
public:
	void clear();                                                     // 0x007F6BA0
	void *m_array;
	int m_count;
};

class Rva007F6C60
{
public:
	void clear();                                                     // 0x007F6C60
	void *m_array;
	int m_count;
};

class Rva007F77B0Block : public Rva007F6BA0
{
public:
	void allocate( int count );                                       // 0x007F77B0
};

class Rva007F7810Block : public Rva007F6C60
{
public:
	void allocate( int count );                                       // 0x007F7810
};

class Rva007F7980Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void onRegionCountDone( int status );                     // slot 3
	virtual void onLobbyCountDone( int status );                      // slot 4
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void onSlot18( int status );                              // slot 18
	virtual void onSlot19( int status );                              // slot 19
};

class Rva007F7980Browser
{
public:
	void onRegionCount( Rva007E8810Message *msg );
	void onLobbyCount( Rva007E8810Message *msg );

	void *m_vptr;
	char m_head[ 0x18 ];
	Rva007F7980Listener *m_listener;
	char m_pad[ 0x18 ];
	Rva007F77B0Block m_regions;
	int m_regionIndex;
	int m_regionTxn;
	Rva007F7810Block m_lobbies;
	int m_lobbyIndex;
	int m_lobbyTxn;
};

void Rva007F7980Browser::onRegionCount( Rva007E8810Message *msg )
{
	if( msg->hasError() )
	{
		int status = msg->getError();
		m_listener->onRegionCountDone( status );
		return;
	}

	int count = msg->getInt( "NUM-REGIONS", 0 );
	if( count != 0 )
	{
		m_regions.allocate( count );
		m_regionIndex = 0;
		m_regionTxn = msg->m_txn;
		return;
	}
	m_listener->onRegionCountDone( 0 );
}

void Rva007F7980Browser::onLobbyCount( Rva007E8810Message *msg )
{
	if( msg->hasError() )
	{
		int status = msg->getError();
		m_listener->onLobbyCountDone( status );
		return;
	}

	int count = msg->getInt( "NUM-LOBBIES", 0 );
	if( count != 0 )
	{
		m_lobbies.allocate( count );
		m_lobbyIndex = 0;
		m_lobbyTxn = msg->m_txn;
		return;
	}
	m_listener->onLobbyCountDone( 0 );
}

void Rva007F5AC0( Rva007E8810Message *msg, Rva007F7980Browser *browser )
{
	if( msg->hasError() )
	{
		int status = msg->getError();
		browser->m_listener->onSlot19( status );
	}
	else
	{
		browser->m_listener->onSlot19( 0 );
	}
}

void Rva007F5B40( Rva007E8810Message *msg, Rva007F7980Browser *browser )
{
	if( msg->hasError() )
	{
		int status = msg->getError();
		browser->m_listener->onSlot18( status );
	}
	else
	{
		browser->m_listener->onSlot18( 0 );
	}
}
