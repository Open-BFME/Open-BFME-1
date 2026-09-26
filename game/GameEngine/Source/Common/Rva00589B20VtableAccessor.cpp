// The carved 0x00589B20 boundary contains only a thiscall vtable read.
// Its caller and nearby rows do not prove an owning class or semantic method,
// so the address-derived owner keeps the identity explicit.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva00589B20Owner
{
public:
	void *getVtable();
};

// ?getVtable@Rva00589B20Owner@@QAEPAXXZ
void *Rva00589B20Owner::getVtable()
{
	return *(void **)this;
}
