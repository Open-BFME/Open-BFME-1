struct CodecState
{
	unsigned char m_unmodelled00[ 0x13c ];
	void *m_buffer;
	unsigned char m_unmodelled140[ 0x158 ];
	void *m_callback;
};

void releaseCodecMembers( CodecState *state );
void releaseCodecBuffer( void **buffer );
void releaseCodecCallback( void **callback );
void freeCodecMemory( void *memory );

// ?releaseCodecState@@YAXPAPAUCodecState@@@Z
void releaseCodecState( CodecState **state )
{
	if( *state )
	{
		releaseCodecMembers( *state );
		releaseCodecBuffer( &(*state)->m_buffer );
		releaseCodecCallback( &(*state)->m_callback );
	}
	freeCodecMemory( *state );
	*state = 0;
}
