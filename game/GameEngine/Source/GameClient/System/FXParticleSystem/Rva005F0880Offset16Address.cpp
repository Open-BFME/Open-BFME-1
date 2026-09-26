// cl: /DNDEBUG /MD /EHsc
// Open-BFME: retail 0x005F0880, address of the +0x10 subobject.

class Rva005F0880Owner
{
public:
	void *rva005f0880() const;
};

void *Rva005F0880Owner::rva005f0880() const
{
	return (char *)this + 0x10;
}
