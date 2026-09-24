// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x0016FAA0/99 is AIStateMachine vtable 0x0109AEF8 slot 10.
// The body reads the owner at +0x10, allocates 0x78 bytes, constructs the
// literal "AIGuardMachine" in the by-value argument slot, and calls the
// AIGuardMachine constructor through ILT 0x00026C15. The source-level method
// name is not independently established, so its address remains in the name.
#include "ascii_string.h"

class Object;

class AIGuardMachine
{
public:
    AIGuardMachine(Object *owner, AsciiString name);
    virtual ~AIGuardMachine();

private:
    char m_body[0x74];
};

class AIStateMachine
{
protected:
    virtual ~AIStateMachine();

public:
    AIGuardMachine *rva0016FAA0();

private:
    char m_padding[0x0c];
    Object *m_owner;
};

AIGuardMachine *AIStateMachine::rva0016FAA0()
{
    return new AIGuardMachine(m_owner, AsciiString("AIGuardMachine"));
}
