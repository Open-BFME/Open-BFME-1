// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the BfmeDelayedLuaEvent scalar-deleting destructor at retail
// RVA 0x000EE700 (30 bytes). DelayedLuaEventList's exact constructor passes
// the element constructor and destructor ILTs to the vector iterator, while
// the recovered Lua setter and three-element list layout establish the type.

class BfmeDelayedLuaEvent
{
public:
	~BfmeDelayedLuaEvent();
};

void forceBfmeDelayedLuaEventDelete(BfmeDelayedLuaEvent *event)
{
	delete event;
}
