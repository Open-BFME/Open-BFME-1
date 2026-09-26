// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva004B2220OffsetGetter
{
public:
	void *get() const;
};

void *Rva004B2220OffsetGetter::get() const
{
	return reinterpret_cast<char *>(const_cast<Rva004B2220OffsetGetter *>(this)) + 0x10;
}
