// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
//
// Implicit destructor at 0x000EDC40. Retail is the `eh vector destructor
// iterator' (??_M at 0x009F6D76) setup: destroy 3 elements of 0x18 bytes at
// this+4, element dtor ILT 0x00041362 -> 0x000ED4A0, the matched
// BfmeDelayedLuaEvent destructor, then inline
// the empty virtual destructor of the polymorphic member at offset 0 (one
// trailing Snapshot vptr store). Owner is not itself polymorphic.

class BfmeDelayedLuaEvent
{
public:
	~BfmeDelayedLuaEvent();

private:
	char m_body[0x18];
};

class Inner01073744
{
public:
	virtual ~Inner01073744() {}
};

class Rva000EDC40
{
public:
	~Rva000EDC40();

private:
	Inner01073744 m_head;
	BfmeDelayedLuaEvent m_items[3];
};

Rva000EDC40::~Rva000EDC40()
{
}
