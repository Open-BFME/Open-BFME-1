// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: GhostObjectManager scalar-deleting destructor at retail RVA
// 0x001B3B40 (30 bytes). The exact constructor at 0x001B3AA0 installs vtable
// 0x0109CE28, whose slot zero routes through ILT 0x0003837F to this wrapper.
// GameLogic's concrete factory and the global manager corroborate identity;
// the complete destructor is called through ILT 0x000231A5.

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
};

void forceGhostObjectManagerDeletingDestructor()
{
	GhostObjectManager value;
}
