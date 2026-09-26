// ??_ERva005D5D90Elem@@UAEPAXI@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: compiler-generated vector deleting destructor (84 B) for a
// 0x28-byte polymorphic element whose destructor is reached through thunk
// 0x00013F2F (hlod model array); emitted with the vtable by array new/delete.
void __cdecl operator delete[](void* block);
struct Rva005D5D90Elem {
	virtual ~Rva005D5D90Elem();
	char m_body[0x28 - 4];
	static void operator delete[](void* block) { ::operator delete[](block); }
};
// ??1Rva005D5D90Elem@@UAE@XZ absent-from-retail
__declspec(noinline) Rva005D5D90Elem::~Rva005D5D90Elem()
{
}
// ?Rva005D5D90MakeArray@@YAPAURva005D5D90Elem@@H@Z absent-from-retail
Rva005D5D90Elem* Rva005D5D90MakeArray(int count)
{
	return new Rva005D5D90Elem[count];
}
// ?Rva005D5D90DeleteArray@@YAXPAURva005D5D90Elem@@@Z absent-from-retail
void Rva005D5D90DeleteArray(Rva005D5D90Elem* array)
{
	delete[] array;
}
