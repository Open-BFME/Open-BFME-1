// cl: /DNDEBUG /MD /EHsc
// readable body of ?makeStateMachine@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// FILE: AIUpdateMakeStateMachine.cpp /////////////////////////////////////////
//
// The makeStateMachine family: AIUpdateInterface at retail 0x00271D30,
// TransportAIUpdate at 0x002C71D0 and WanderAIUpdate at 0x002C7700.  Each is
// one line -- allocate an AIStateMachine and hand it the module's Object and a
// name -- and all three compile to the same 99 bytes but for the string.
//
// Found by the literal each pushes: "AIUpdateInterfaceMachine",
// "TransportAIUpdateMachine", "WanderAIUpdateMachine" each appear in exactly one
// reference source, and the function around them names the body.
//
// Written as its own TU rather than into AIUpdate.cpp because of the two facts
// the bytes measure, both of which live in shared headers:
//
//   push 0x70   sizeof(AIStateMachine) is 0x70; AIStateMachine.h gives 0x54.
//   [edi+0x8]   getObject() reads the module's Object * at +0x8, not +0xc.
//
// Trying it in place needs the allocation spelled out by hand to get the size,
// and that loses the unwind frame `new' generates -- retail has one.  Here the
// stand-in simply has the right size and `new' does the rest.
//
///////////////////////////////////////////////////////////////////////////////

template <class Type>
class StringBase
{
private:
	// Private so the symbol comes out AAE, which is how the ledger already names
	// this body; a public declaration would spell QAE and need a pin.
	StringBase(const char *s);
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	// The delegation has to be visible: a declared-only constructor leaves the
	// by-value temporary opaque and MSVC schedules its frame store after the
	// this-pointer load instead of before.
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &that);
	~AsciiString();

private:

	void *m_text;

};

class Object;

// 0x70 bytes.  Only the size and the constructor are claimed; nothing here
// knows what the machine holds.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIStateMachine
{
public:
	AIStateMachine( Object *owner, AsciiString name );
private:
	char m_bfmeBody[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:

	virtual AIStateMachine *makeStateMachine();

	Object *getObject() const { return *(Object **)((char *)this + 0x8); }

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate : public AIUpdateInterface
{
protected:
	virtual AIStateMachine *makeStateMachine();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WanderAIUpdate.h
class WanderAIUpdate : public AIUpdateInterface
{
protected:
	virtual AIStateMachine *makeStateMachine();
};

// BFME-only: no AnimalAIUpdate exists in the reference tree.  The class name is
// read off the literal, which every sibling in this family spells as
// "<ClassName>Machine".
class AnimalAIUpdate : public AIUpdateInterface
{
protected:
	virtual AIStateMachine *makeStateMachine();
};

AIStateMachine *AIUpdateInterface::makeStateMachine()
{
	return new AIStateMachine( getObject(), "AIUpdateInterfaceMachine" );
}

AIStateMachine *TransportAIUpdate::makeStateMachine()
{
	return new AIStateMachine( getObject(), "TransportAIUpdateMachine" );
}

AIStateMachine *WanderAIUpdate::makeStateMachine()
{
	return new AIStateMachine( getObject(), "WanderAIUpdateMachine" );
}

AIStateMachine *AnimalAIUpdate::makeStateMachine()
{
	return new AIStateMachine( getObject(), "AnimalAIUpdateMachine" );
}
