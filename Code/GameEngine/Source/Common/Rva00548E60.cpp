class Rva00548E60
{
public:
	__declspec(noinline) void *get() const;
};

void *Rva00548E60::get() const
{
	return (char *)*(void **)this + 0x10;
}
