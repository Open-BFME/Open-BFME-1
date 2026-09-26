// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail RVA 0x00184C00 contains an anonymous attack-machine factory.
// The body constructs AIAttackThenIdleStateMachine from the owner at +0x10.

#include "StringInline.h"

class Object;

class AIAttackThenIdleStateMachine
{
public:
	AIAttackThenIdleStateMachine( Object *owner, AsciiString name );
	virtual ~AIAttackThenIdleStateMachine();

private:
	char m_body[ 0x40 ];
};

class Rva00184C00AttackMachineFactory
{
public:
	AIAttackThenIdleStateMachine *create();

private:
	char m_padding[ 0x10 ];
	Object *m_owner;
};

// ?create@Rva00184C00AttackMachineFactory@@QAEPAVAIAttackThenIdleStateMachine@@XZ present-unmatched
AIAttackThenIdleStateMachine *Rva00184C00AttackMachineFactory::create()
{
	return new AIAttackThenIdleStateMachine(
		m_owner, AsciiString( "AIAttackThenIdleStateMachine" ) );
}

// ?create@Rva00184C00AttackMachineFactory@@QAEPAVAIAttackThenIdleStateMachine@@XZ
