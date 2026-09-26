// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006675C0 (20 bytes).
// Retail clears this object's 0x2000-byte storage and returns this.

#include <cstring>

class Rva006675C0
{
public:
	void *clear();

private:
	unsigned m_storage[0x800];
};

void *Rva006675C0::clear()
{
	memset(this, 0, sizeof m_storage);
	m_storage[0] = 0;
	return this;
}
