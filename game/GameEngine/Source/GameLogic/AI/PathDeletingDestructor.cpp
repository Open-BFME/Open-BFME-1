// cl: /DNDEBUG /MD /EHsc

// Open-BFME: Path scalar-deleting destructor at retail 0x001500D0 (30
// bytes). The matched Path constructor at 0x000335B4, complete destructor at
// 0x003FEB80, and the named Path pathfinding methods establish the authentic
// class identity. This focused shim emits the protected virtual deleting ABI;
// PathDestructor.cpp owns the real node-chain body.

class Path
{
protected:
	// Forced inline so the forcer installs the vftable without emitting a
	// second ??0Path COMDAT; the real constructor is matched elsewhere.
	__forceinline Path() {}
	virtual ~Path();
	friend void Force_Path_Deleting_Destructor();
};

void Force_Path_Deleting_Destructor()
{
	Path value;
}
