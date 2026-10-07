// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the BfmeDelayedLuaEvent scalar-deleting destructor at retail
// RVA 0x000EE700 (30 bytes). DelayedLuaEventList's exact constructor passes
// the element constructor and destructor ILTs to the vector iterator, while
// the recovered Lua setter and three-element list layout establish the type.

// The complete destructor 0x000ED4A0 (ILT 0x00041362): releases the narrow
// string at +0x10 (StringBase<char>::releaseBuffer), then the inlined empty
// virtual destructor of the polymorphic member at +0 re-seats its vftable.
template <class T> class StringBase
{
	void releaseBuffer();
	friend class BfmeDelayedLuaEventString;
};

class BfmeDelayedLuaEventString
{
public:
	__forceinline ~BfmeDelayedLuaEventString() { reinterpret_cast<StringBase<char> *>(this)->releaseBuffer(); }
};

class Inner01073744
{
public:
	virtual ~Inner01073744() {}
};

class BfmeDelayedLuaEvent
{
public:
	~BfmeDelayedLuaEvent();
	Inner01073744 m_head;
	char m_pad[12];
	BfmeDelayedLuaEventString m_name;
};

BfmeDelayedLuaEvent::~BfmeDelayedLuaEvent()
{
}

void forceBfmeDelayedLuaEventDelete(BfmeDelayedLuaEvent *event)
{
	delete event;
}
