// ?get@Rva0027F390Owner@@QAEPAXXZ
// The carved body returns the address of the object's field at offset 0x58.
// No caller names the owner, so the class keeps the retail address in its name.
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva0027F390Owner
{
public:
	void *get();
};

void *Rva0027F390Owner::get()
{
	return reinterpret_cast<char *>(this) + 0x58;
}
