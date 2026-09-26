// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// The carved boundary at 0x005C0610 contains only ret 8. The caller proves a
// member entry point, but no evidence names its owner or the two arguments.
class Rva005C0610Owner
{
public:
	void reset(unsigned int first, unsigned int second);
};

void Rva005C0610Owner::reset(unsigned int first, unsigned int second)
{
}
