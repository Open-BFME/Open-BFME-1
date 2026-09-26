// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

void __cdecl operator delete[](void *memory);

class Rva007E4990Owner
{
public:
	void releaseArray(void *memory, int unused);
};

void Rva007E4990Owner::releaseArray(void *memory, int)
{
	::operator delete[](memory);
}
