// cl: /Od /GZ /GS /MD /DNDEBUG

struct Rva00819F50Comm
{
	char m_head[ 0x7c ];
	void *m_handle;
	unsigned int m_readInternal;
	unsigned int m_readInternalHigh;
	unsigned int m_readOffset;
	unsigned int m_readOffsetHigh;
	void *m_readEvent;
	unsigned int m_waitInternal;
	unsigned int m_waitInternalHigh;
	unsigned int m_waitOffset;
	unsigned int m_waitOffsetHigh;
	void *m_waitEvent;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	unsigned int m_bytesRead;
	unsigned int m_commMask;
	char m_gapC4[ 0x44 ];
	unsigned char m_buffer[ 0x800 ];
	int m_bufferLength;
};

struct Rva00819F50Record
{
	int m_length;
	unsigned int m_tick;
	unsigned char m_data[ 4 ];
};

extern "C"
{
	__declspec( dllimport ) int __stdcall ReadFile( void *handle,
		void *buffer, unsigned int count, unsigned int *read,
		void *overlapped );
	__declspec( dllimport ) unsigned long __stdcall GetLastError( void );
	__declspec( dllimport ) int __stdcall GetOverlappedResult( void *handle,
		void *overlapped, unsigned int *transferred, int wait );
	__declspec( dllimport ) unsigned long __stdcall WaitForSingleObject(
		void *handle, unsigned long timeout );
	__declspec( dllimport ) int __stdcall WaitCommEvent( void *handle,
		unsigned int *mask, void *overlapped );
	__declspec( dllimport ) unsigned int __stdcall GetTickCount( void );
	__declspec( dllimport ) void __stdcall OutputDebugStringA(
		const char *text );
	void *__cdecl memcpy( void *destination, const void *source,
		unsigned int count );
	unsigned short __cdecl Rva0081A360( const unsigned char *data,
		int length );
}

extern "C" int __cdecl Rva00819F50( struct Rva00819F50Comm *comm,
	struct Rva00819F50Record *record )
{
	int state;
	int available;
	int packetLength;
	unsigned char *data;
	unsigned char *packet;

	available = comm->m_bufferLength;
	data = comm->m_buffer;
	state = 0;

	for ( ;; )
	{
		if ( state != 0 || available < 8 )
		{
			comm->m_readInternal = 0;
			comm->m_readInternalHigh = 0;
			comm->m_readOffset = 0;
			comm->m_readOffsetHigh = 0;

			if ( ReadFile( comm->m_handle, data + available,
				0x800 - available, &comm->m_bytesRead,
				&comm->m_readInternal ) == 0
				&& GetLastError() == 0x3e5 )
			{
				GetOverlappedResult( comm->m_handle,
					&comm->m_readInternal, &comm->m_bytesRead, 1 );
			}

			if ( comm->m_bytesRead > 0 )
			{
				available = available + comm->m_bytesRead;
				state = 0;
				continue;
			}

			if ( WaitForSingleObject( comm->m_waitEvent, 0 ) == 0x102 )
			{
				comm->m_bufferLength = available;
				return 0;
			}

			comm->m_readInternal = 0;
			comm->m_readInternalHigh = 0;
			comm->m_readOffset = 0;
			comm->m_readOffsetHigh = 0;

			if ( WaitCommEvent( comm->m_handle, &comm->m_commMask,
				&comm->m_waitInternal ) == 0
				&& GetLastError() == 0x3e5 )
			{
				comm->m_bufferLength = available;
				return 0;
			}

			state = 1;
			continue;
		}

		if ( data[ 0 ] != 'G' || data[ 1 ] != 'S'
			|| data[ 2 ] != ( data[ 3 ] ^ 0xff ) )
		{
			if ( data[ 0 ] != 0 )
				OutputDebugStringA( "bogus packet\n" );
			data++;
			available--;
			goto rva00819f50_scan_condition;

	rva00819f50_scan_advance:
			data++;
			available--;

	rva00819f50_scan_condition:
			if ( available > 0 )
			{
				if ( data[ 0 ] != 'G' )
					goto rva00819f50_scan_advance;
				if ( available > 1 )
				{
					if ( data[ 1 ] != 'S' )
						goto rva00819f50_scan_advance;
				}
				if ( available > 3 )
				{
					if ( data[ 2 ] !=
						( data[ 3 ] ^ 0xff ) )
						goto rva00819f50_scan_advance;
				}
			}

	rva00819f50_scan_done:
			if ( available > 0 )
			{
				memcpy( comm->m_buffer, data, available );
			}
			data = comm->m_buffer;
			continue;
		}

		packetLength = data[ 2 ] + 8;
		if ( available < packetLength + 8 )
		{
			state = 1;
			continue;
		}

		packet = data + packetLength + 4;
		if ( packet[ 2 ] != 0x0d || packet[ 3 ] != 0x0a
			|| Rva0081A360( data + 4, packetLength )
			!= ( packet[ 0 ] | ( packet[ 1 ] << 8 ) ) )
		{
			data[ 0 ] = 0;
			state = 0;
			OutputDebugStringA( "bogus packet\n" );
			continue;
		}

		memcpy( (char *)record + 8, data + 4, packetLength );
		record->m_length = packetLength - 8;
		record->m_tick = GetTickCount();
		comm->m_bufferLength = available - ( packetLength + 8 );

		if ( comm->m_bufferLength != 0 )
			memcpy( comm->m_buffer, packet + 4, comm->m_bufferLength );

		return 1;
	}
}
