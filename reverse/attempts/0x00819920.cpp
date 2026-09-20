// _Rva00819920
// partial score=0.88 date=2026-09-21
// cl: /Od /GZ /GS /MD /DNDEBUG

struct Rva00819920Comm;

struct Rva00819920Message
{
	int m_length;
	unsigned int m_tick;
	int m_sequence;
	int m_value;
	char m_data[ 0x800 ];
};

struct Rva00819920Comm
{
	char m_head[ 0xa4 ];
	void *m_event1;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	char m_gapBC[ 0x0c ];
	int m_threadId;
	int m_state;
	int m_pendingValue;
	char m_gapD4[ 0x20 ];
	int m_sendWriteOffset;
	char m_gapF8[ 4 ];
	int m_sendAckOffset;
	char m_gap100[ 0x1810 ];
	int m_streamLength;
	char m_gap1914[ 8 ];
	unsigned int m_lastTick;
	char m_lock[ 0x18 ];
	int m_depth;
	int m_flags;
	void ( __cdecl *m_callback )( struct Rva00819920Comm *comm, int flags );
};

extern "C"
{
	__declspec( dllimport ) void __stdcall Rva01358D18Enter( void *lock );
	__declspec( dllimport ) void __stdcall Rva01358E74Leave( void *lock );
	__declspec( dllimport ) void __stdcall Rva01358F30Sleep( int interval );
	__declspec( dllimport ) unsigned int __stdcall Rva01358E0CTick( void );
	__declspec( dllimport ) unsigned int __stdcall Rva01358F64Wait(
		void *handle, unsigned int timeout );
	__declspec( dllimport ) unsigned int __stdcall Rva01358F60WaitMultiple(
		unsigned int count, void **handles, int waitAll, unsigned int timeout );

	void Rva00819F50( struct Rva00819920Comm *comm,
		struct Rva00819920Message *message );
	void Rva0081A3B0( struct Rva00819920Comm *comm, void *record );
	void Rva0081A5C0( struct Rva00819920Comm *comm );
	void Rva0081A6A0( struct Rva00819920Comm *comm,
		struct Rva00819920Message *message, int threadId );
	void Rva0081A740( struct Rva00819920Comm *comm );
	void Rva0081A810( struct Rva00819920Comm *comm );
	void Rva0081A8C0( struct Rva00819920Comm *comm );
	void Rva0081AA20( struct Rva00819920Comm *comm,
		struct Rva00819920Message *message );
	void Rva0081AB40( struct Rva00819920Comm *comm,
		struct Rva00819920Message *message, int threadId );
}

extern "C" void Rva00819920( struct Rva00819920Comm *parameter )
{
	Rva00819920Message message;
	unsigned int tick;
	Rva00819920Comm *comm;
	int eventCount;
	void *events[ 2 ];

	comm = parameter;

	while ( comm->m_state != 9 )
	{
		if ( comm->m_state == 8 )
			comm->m_state = 1;

		if ( comm->m_state == 1 || comm->m_state == 0
			|| comm->m_state == 7 )
		{
		}
		else if ( comm->m_state != 5 )
			goto waitForEvents;

		if ( comm->m_state != 7 || comm->m_streamLength <= 0 )
			goto sleepForFifty;

		Rva01358D18Enter( comm->m_lock );
		Rva0081A3B0( comm, 0 );
		Rva01358E74Leave( comm->m_lock );
		Rva01358F30Sleep( 0x19 );
		continue;

sleepForFifty:
		Rva01358F30Sleep( 0x32 );
		continue;

waitForEvents:
		if ( Rva01358F64Wait( comm->m_event1, 0 ) == 0x102 )
		{
			eventCount = 0;
			events[ eventCount++ ] = comm->m_event1;

			if ( comm->m_streamLength > 0
				&& Rva01358F64Wait( comm->m_event2, 0 ) == 0x102 )
				events[ eventCount++ ] = comm->m_event2;

			Rva01358F60WaitMultiple( eventCount, events, 0, 0x64 );
		}

		message.m_length = -1;
		Rva00819F50( comm, &message );
		tick = Rva01358E0CTick();

		Rva01358D18Enter( comm->m_lock );
		Rva0081A3B0( comm, 0 );

		if ( comm->m_state == 4 && tick - comm->m_lastTick > 0xafc8 )
			comm->m_state = 6;

		if ( comm->m_state == 6 )
			Rva0081A5C0( comm );

		if ( comm->m_state == 4
			&& comm->m_sendAckOffset != comm->m_sendWriteOffset )
			Rva0081A8C0( comm );

		tick = Rva01358E0CTick();

		if ( comm->m_state == 2
			&& tick - *(unsigned int *)( (char *)comm + 0x1918 ) > 0x3e8 )
		{
			Rva0081A740( comm );
			tick = Rva01358E0CTick();
		}

		if ( comm->m_state == 4
			&& comm->m_sendAckOffset == comm->m_sendWriteOffset
			&& tick - *(unsigned int *)( (char *)comm + 0x1918 ) > 0x3e8 )
		{
			Rva0081A810( comm );
			tick = Rva01358E0CTick();
		}

		if ( message.m_length >= 0
			&& ( comm->m_state == 4 || comm->m_state == 2 ) )
		{
			if ( message.m_sequence == 4 )
			{
				Rva0081AA20( comm, &message );
				goto resetMessage;
			}

			if ( message.m_sequence == 1 || message.m_sequence == 2
				|| message.m_sequence == 3 )
			{
				Rva0081A6A0( comm, &message, comm->m_threadId );
				goto resetMessage;
			}

			Rva0081AA20( comm, &message );
			Rva0081AB40( comm, &message, comm->m_threadId );

resetMessage:
			message.m_length = -1;
			comm->m_lastTick = Rva01358E0CTick();
		}

		if ( comm->m_state == 3 && message.m_length == 0
			&& message.m_value != 0 && message.m_sequence == 1 )
		{
			comm->m_pendingValue = message.m_value;
			comm->m_state = 4;
			Rva0081A6A0( comm, &message, comm->m_threadId );
			message.m_length = -1;
			comm->m_lastTick = Rva01358E0CTick();
		}

		Rva01358E74Leave( comm->m_lock );

		if ( comm->m_flags != 0 )
		{
			if ( comm->m_callback != 0 )
				comm->m_callback( comm, comm->m_flags );
			comm->m_flags = 0;
		}
	}

	comm->m_state = 1;
}
