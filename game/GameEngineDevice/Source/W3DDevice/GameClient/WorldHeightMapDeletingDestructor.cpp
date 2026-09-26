// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Open-BFME: WorldHeightMap scalar-deleting destructor at retail RVA
// 0x0074E2E0 (30 bytes).  The primary WorldHeightMap vtable at 0x01121B94
// has the complete destructor in slot zero and this wrapper in slot one.
// The matched WorldHeightMap constructor at 0x0074E990 and complete
// destructor at 0x0074DE60 install that same vtable; this wrapper calls the
// complete body through ILT 0x0002CFA2 before operator delete.

class WorldHeightMap
{
public:
	virtual ~WorldHeightMap();
};

void forceWorldHeightMapDeletingDestructor()
{
	WorldHeightMap value;
}
