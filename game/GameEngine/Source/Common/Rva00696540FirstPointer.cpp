// ?get@Rva00696540FirstPointer@@QAEPAXXZ
// The carved boundary proves a thiscall getter that reads the first pointer.
// No caller identifies a stronger semantic owner.
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva00696540FirstPointer
{
public:
	void *get();
};

void *Rva00696540FirstPointer::get()
{
	return *reinterpret_cast<void *const *>(this);
}
