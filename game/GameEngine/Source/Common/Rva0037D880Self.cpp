// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// The carved boundary at 0x0037D880 contains mov eax, ecx and ret. The
// caller proves a member entry point, but no evidence names its owner.
class Rva0037D880Self
{
public:
	void *returnThis();
};

void *Rva0037D880Self::returnThis()
{
	return this;
}
