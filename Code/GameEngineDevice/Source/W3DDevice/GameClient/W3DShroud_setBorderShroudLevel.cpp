// cl: /DNDEBUG /MD /EHsc

// W3DShroud::setBorderShroudLevel, retail 0x0071A0D0: Zero Hour's body, which
// stores the border level and flags the destination texture for clearing.

class W3DShroud
{
private:
	unsigned char m_unmodelled_00[ 0x35 ];
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;

public:
	void setBorderShroudLevel( unsigned char level );
};

// ?setBorderShroudLevel@W3DShroud@@QAEXE@Z
void W3DShroud::setBorderShroudLevel( unsigned char level )
{
	m_borderShroudLevel = level;
	m_clearDstTexture = 1;
}
