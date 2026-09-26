// ?get@Rva003AC4C0OffsetGetter@@QAEPAXXZ
// The carved boundary proves a thiscall getter returning this plus 0x08.
// No caller identifies a stronger semantic owner.
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva003AC4C0OffsetGetter
{
public:
	void *get();
};

void *Rva003AC4C0OffsetGetter::get()
{
	return reinterpret_cast<char *>(this) + 8;
}
