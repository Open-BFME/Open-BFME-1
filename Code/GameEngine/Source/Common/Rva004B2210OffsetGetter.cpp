// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva004B2210OffsetGetter
{
public:
	void *get() const;
};

void *Rva004B2210OffsetGetter::get() const
{
	return reinterpret_cast<char *>(const_cast<Rva004B2210OffsetGetter *>(this)) + 0x14;
}
