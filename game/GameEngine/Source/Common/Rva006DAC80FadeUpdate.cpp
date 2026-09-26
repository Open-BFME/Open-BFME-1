// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x006DAC80, 120 bytes: the switch body, a nop, and its four-entry
// jump table at +0x68 (int3 padding follows).  A fade stepping 1/12 per call
// between 0 and 1 in states 0 and 2, holding at the end states 1 and 3.
// Nothing calls it directly, so the names keep the address.  The case order
// 0, 2, 1, 3 is the one that stops the compiler cross-jumping the case-1
// store into case 0, as retail's code does not.

class Rva006DAC80Fade
{
public:
	void update( void );
private:
	char m_unmodelled00[ 8 ];
	int m_state;
	float m_value;
};
void Rva006DAC80Fade::update( void )
{
	switch( m_state )
	{
	case 0: m_value += 1.0f / 12.0f; if( m_value >= 1.0f ) { m_value = 1.0f; m_state = 1; } break;
	case 2: m_value -= 1.0f / 12.0f; if( m_value <= 0.0f ) { m_state = 3; m_value = 0.0f; } break;
	case 1: m_value = 1.0f; break;
	case 3: m_value = 0.0f; break;
	}
}
