// cl: /DNDEBUG /MD /EHsc
// StateMachine::halt, retail body 0x000A00A0 behind ILT 0x00025676.

class StateMachine
{
public:
	virtual void halt( void );

private:
	unsigned char m_unreconstructed_04[0x3c];
	unsigned char m_halted;                    // retail this+0x40
};

// ?halt@StateMachine@@UAEXXZ
void StateMachine::halt( void )
{
	m_halted = 1;
}
