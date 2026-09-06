// cl: /Od /GZ /GS /MD /DNDEBUG

struct Rva00812DD0Comm
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
	int Rva00812FD0( void *comm );
	void *memset( void *dest, int value, unsigned int size );
	char *strcpy( char *dest, const char *source );
	void *Rva01358DDC;
	void *Rva01358E3C;
	void *Rva01358E44;
	void __cdecl _RTC_CheckEsp( void );
	void Rva00819630( void );
}

void rva00813CF0( void );
void rva00813A40( void );
void Rva00814020( void );

typedef int ( __stdcall *Rva00812DD0LineInitProc )(
	int first, int second, void *callback, void *comm, int fifth,
	unsigned int *workerId );
typedef void ( __stdcall *Rva00812DD0CloseProc )( int result );
typedef void ( __stdcall *Rva00812DD0YieldProc )( int interval );

extern "C" Rva00812DD0Comm *Rva00812DD0( int first, int second, int third )
{
	int result;
	Rva00812DD0Comm *comm;

	__asm
	{
		mov esi, esp
		push 019Ch
		push 0
		mov edi, esp
		call dword ptr [Rva01358DDC]
		cmp edi, esp
		call _RTC_CheckEsp
		push eax
		call dword ptr [Rva01358E3C]
		cmp esi, esp
		call _RTC_CheckEsp
		mov comm, eax
	}
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
	strcpy( comm->m_name, (const char *)0x012C4A60 );
	comm->m_state = 0;
	result = ( *(Rva00812DD0LineInitProc *)0x01358D00 )(
		0, 0, (void *)Rva00812FD0, comm, 0, &comm->m_workerId );
	( *(Rva00812DD0CloseProc *)0x01358CCC )( result );
	while ( comm->m_state == 0 )
		( *(Rva00812DD0YieldProc *)0x01358F30 )( 0 );

	if ( comm->m_state == 1 )
	{
		__asm
		{
			mov esi, esp
			mov ecx, comm
			push ecx
			push 0
			mov edi, esp
			call dword ptr [Rva01358DDC]
			cmp edi, esp
			call _RTC_CheckEsp
			push eax
			call dword ptr [Rva01358E44]
			cmp esi, esp
			call _RTC_CheckEsp
		}
		return 0;
	}

	__asm
	{
		mov edx, third
		push edx
		mov eax, second
		push eax
		mov ecx, first
		push ecx
		call Rva00819630
		add esp, 0Ch
		mov edx, comm
		mov dword ptr [edx+78h], eax
		mov eax, comm
		mov dword ptr [eax+88h], 0FFFFFFFFh
		mov ecx, comm
		mov dword ptr [ecx+8Ch], 0FFFFFFFFh
		mov edx, comm
		mov dword ptr [edx+90h], 2
	}
	return comm;
}
