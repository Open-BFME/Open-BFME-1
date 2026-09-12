// cl: /Od /GZ /GS /MD /DNDEBUG

struct CommTAPIRef
{
	void *m_ops[ 14 ];
	char m_gap38[ 0x14 ];
	char m_name[ 0x2C ];
	void *m_transport;
	char m_gap7C[ 0x0C ];
	int m_field88;
	int m_field8C;
	int m_state;
	char m_gap94[ 0x104 ];
	unsigned int m_workerId;
};

extern "C"
{
	void Rva008139A0( void *comm );
	void Rva00813A50( void );
	void Rva00813D00( void );
	void Rva00813E30( void );
	void Rva00813E50( void );
	void Rva00813F20( void );
	void Rva00813F90( void );
	void Rva00814040( void );
	void Rva00814070( void );
	void Rva008140A0( void );
	// Rva00812FD0 is the retail cdecl worker entry and returns its status in EAX.
	int Rva00812FD0( void *comm );
	void *memset( void *dest, int value, unsigned int size );
	char *strcpy( char *dest, const char *source );
	// These six IAT slots resolve to the named KERNEL32 APIs below.
	void *(__stdcall *Rva01358DDC)( void ); // GetProcessHeap
	void *(__stdcall *Rva01358E3C)( void *heap, unsigned int flags,
		unsigned int size ); // HeapAlloc
	int (__stdcall *Rva01358E44)( void *heap, unsigned int flags,
		void *block ); // HeapFree
	void *(__stdcall *Rva01358D00)( void *security, unsigned int stackSize,
		void *start, void *argument, unsigned int flags,
		unsigned int *threadId ); // CreateThread
	int (__stdcall *Rva01358CCC)( void *handle ); // CloseHandle
	void (__stdcall *Rva01358F30)( unsigned int interval ); // Sleep
	void *Rva00819630( int first, int second, int third );
}

void rva00813CF0( void );
void rva00813A40( void );
void Rva00814020( void );

extern "C" CommTAPIRef *Rva00812DD0( int first, int second, int third )
{
	void *threadHandle;
	CommTAPIRef *comm;

	comm = (CommTAPIRef *)Rva01358E3C( Rva01358DDC(), 0, 0x19C );
	if ( comm == 0 )
		return 0;

	memset( comm, 0, 0x19C );
	comm->m_ops[ 0 ] = (void *)Rva00812DD0;
	comm->m_ops[ 1 ] = (void *)Rva008139A0;
	comm->m_ops[ 2 ] = (void *)Rva00813A50;
	comm->m_ops[ 3 ] = (void *)rva00813CF0;
	comm->m_ops[ 4 ] = (void *)Rva00813D00;
	comm->m_ops[ 5 ] = (void *)Rva00813E30;
	comm->m_ops[ 6 ] = (void *)Rva00813E50;
	comm->m_ops[ 7 ] = (void *)Rva00813F20;
	comm->m_ops[ 8 ] = (void *)rva00813A40;
	comm->m_ops[ 9 ] = (void *)Rva00813F90;
	comm->m_ops[ 10 ] = (void *)Rva00814020;
	comm->m_ops[ 11 ] = (void *)Rva00814040;
	comm->m_ops[ 12 ] = (void *)Rva00814070;
	comm->m_ops[ 13 ] = (void *)Rva008140A0;
	strcpy( comm->m_name, "TAPI" );
	comm->m_state = 0;
	threadHandle = Rva01358D00(
		0, 0, (void *)Rva00812FD0, comm, 0, &comm->m_workerId );
	Rva01358CCC( threadHandle );
	while ( comm->m_state == 0 )
		Rva01358F30( 0 );

	if ( comm->m_state == 1 )
	{
		Rva01358E44( Rva01358DDC(), 0, comm );
		return 0;
	}

	comm->m_transport = Rva00819630( first, second, third );
	comm->m_field88 = -1;
	comm->m_field8C = -1;
	comm->m_state = 2;
	return comm;
}
