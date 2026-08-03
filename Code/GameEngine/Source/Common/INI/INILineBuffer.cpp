// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Include /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// INILineBuffer -- BFME's INI line array. The layout is read from the retail
// accessors: an unused word, a freed buffer, and a vector of 8-byte lines.

#include "Common/INI/INILineBuffer.h"

// Retail 0x009CBC60, 33 bytes. Negative indices are not rejected.
const char *INILineBuffer::getText( Int index ) const
{
	if (index < (Int)m_lines.size()) {
		return m_lines[index].m_text;
	}

	return NULL;
}

// Retail 0x009CBF50, 69 bytes. The range erase preserves retail's emitted
// zero-trip copy loop before releasing the line buffer.
void INILineBuffer::clear( void )
{
	m_lines.erase( m_lines.begin(), m_lines.end() );

	if (m_buffer != NULL) {
		delete [] m_buffer;
		m_buffer = NULL;
	}
}
