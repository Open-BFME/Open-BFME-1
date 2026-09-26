// ??_ERva00892890@@UAEPAXI@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: compiler-generated vector deleting destructor (84 B) for the
// 8-byte polymorphic class whose destructor is the landed release body at
// 0x00892890; emitted with the vtable by an array new/delete of the class.
struct Rva00892890 {
	virtual ~Rva00892890();
	int m_value;
};
// ??1Rva00892890@@UAE@XZ absent-from-retail
__declspec(noinline) Rva00892890::~Rva00892890()
{
}
// ?Rva00892D40MakeArray@@YAPAURva00892890@@H@Z absent-from-retail
Rva00892890* Rva00892D40MakeArray(int count)
{
	return new Rva00892890[count];
}
// ?Rva00892D40DeleteArray@@YAXPAURva00892890@@@Z absent-from-retail
void Rva00892D40DeleteArray(Rva00892890* array)
{
	delete[] array;
}
