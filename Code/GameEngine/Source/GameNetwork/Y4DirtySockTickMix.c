// cl: /Od /GZ /MD /DNDEBUG
/* DirtySock -- mix the tick counters with a 32-dword window off iCount, then
 * optionally RC4-key the caller's state from those 16 bytes.  Retail names the
 * index local iCount (GZ frame descriptor). */

unsigned int Rva007FEA00( void );
void Rva0080F200( void *state, const unsigned char *key, int length, int rounds );
void Rva0080F300( void *state, unsigned char *data, int length );

unsigned int g_Rva0130ACE8;
unsigned int g_Rva0130ACEC;
unsigned int g_Rva0130ACF0;
unsigned int g_Rva0130ACF4;

void Rva0080AD00( unsigned char *data, int length, void *state )
{
	int iCount[ 1 ];

	if ( g_Rva0130ACE8 == 0 )
	{
		g_Rva0130ACE8 = Rva007FEA00();
	}
	g_Rva0130ACEC = g_Rva0130ACEC + Rva007FEA00();
	g_Rva0130ACF0 = g_Rva0130ACF0 + 1;

	for ( iCount[ 0 ] = 0; iCount[ 0 ] < 0x20; iCount[ 0 ]++ )
	{
		g_Rva0130ACF4 = g_Rva0130ACF4 + ( (int *)iCount )[ iCount[ 0 ] ];
	}

	if ( data != 0 )
	{
		Rva0080F200( state, (unsigned char *)&g_Rva0130ACE8, 0x10, 3 );
		Rva0080F300( state, data, length );
	}
}
