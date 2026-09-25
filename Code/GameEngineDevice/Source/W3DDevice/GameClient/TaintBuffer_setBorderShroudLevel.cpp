// cl: /DNDEBUG /MD /EHsc

// TaintBuffer::setBorderShroudLevel, retail 0x00727010: the same body as
// W3DShroud's (0x0071A0D0), on the taint buffer the terrain keeps at +0x30BC.

class TaintBuffer
{
private:
	unsigned char m_unmodelled_00[ 0x35 ];
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;

public:
	void setBorderShroudLevel( unsigned char level );
};

// ?setBorderShroudLevel@TaintBuffer@@QAEXE@Z
void TaintBuffer::setBorderShroudLevel( unsigned char level )
{
	m_borderShroudLevel = level;
	m_clearDstTexture = 1;
}
