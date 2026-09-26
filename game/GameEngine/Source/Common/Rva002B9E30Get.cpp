// cl: /O2 /Ob0

class Rva002B9E30
{
public:
	Rva002B9E30 *get();
};

Rva002B9E30 *Rva002B9E30::get()
{
	return ((char *)this - 0x20) ? this : 0;
}
