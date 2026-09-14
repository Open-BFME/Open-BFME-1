// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: scalar-deleting destructor for the BFME delayed-event list at
// retail RVA 0x000EDCA0 (30 bytes).
//
// The constructor at 0x000EDBB0 installs the named DelayedLuaEventList
// vtable 0x01085E10, whose slot zero reaches this wrapper through ILT
// 0x0003A58F. Its three 0x18-byte event records begin at +4; the matched
// complete destructor at 0x000EDC40 tears those records down and restores the
// empty polymorphic base. The existing BfmeDelayedLuaEventList destructor
// pin at ILT 0x00013156 is the local identity adapter for that DelayedLuaEventList
// body, so this wrapper uses the same ABI spelling.

class BfmeDelayedLuaEventList
{
public:
	__declspec(noinline) virtual ~BfmeDelayedLuaEventList();
};

BfmeDelayedLuaEventList::~BfmeDelayedLuaEventList()
{
}

void Force_BfmeDelayedLuaEventList_Deleting_Destructor()
{
	BfmeDelayedLuaEventList value;
}
