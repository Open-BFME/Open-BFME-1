// Retail returns this minus 0x34 at 0x001D3FB0. The caller and neighboring
// virtual-base thunks do not prove an owning class or semantic method name.

class Rva001D3FB0OffsetPointer
{
public:
	void *get();
};

void *Rva001D3FB0OffsetPointer::get()
{
	return (char *)this - 0x34;
}
