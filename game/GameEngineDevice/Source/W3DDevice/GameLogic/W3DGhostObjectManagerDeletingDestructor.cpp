// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DGhostObjectManager scalar-deleting destructor at retail RVA
// 0x006BDBE0 (30 bytes). The exact constructor at 0x006BC8C0 installs vtable
// 0x0111CFE0, whose slot zero routes through ILT 0x0000A3CB to this wrapper.
// Recovered ghost-object methods corroborate identity; dtor ILT 0x0000C694.

class W3DGhostObjectManager
{
public:
	virtual ~W3DGhostObjectManager();
};

void forceW3DGhostObjectManagerDeletingDestructor()
{
	W3DGhostObjectManager value;
}
