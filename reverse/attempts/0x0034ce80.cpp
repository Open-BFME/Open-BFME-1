// ?findByName@Rva0034CE80@@QBEPAXPBQBURva0034CE80StringHeader@@@Z
// partial score=0.15 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// stlport
// Carved body at retail RVA 0x0034CE80 (169 B).  Scans a this-relative
// vector [this+0x17628, this+0x1762c) of pointers; for each non-null
// element it calls a trivial "return member reference" accessor whose
// compiled body (lea eax,[ecx+4]; ret) is ICF-shared with the matched
// LadderList::getSpecialLadders (0x001DB5B0), yielding the address of a
// short-string-optimised AsciiString::Header-shaped record embedded at
// element+4; that record (length at +4 as ushort, data at +8, or the
// shared empty-string singleton Rva006A16B0Empty when the pointer chain
// is null) is compared byte-for-byte (repe cmpsb, matching
// AsciiString::compare's inlined memcmp shape) against the same-shaped
// record the sole stack argument points at.  On a match, returns the
// current vector slot's pointer; otherwise continues, and falls out to 0.
// Identity of the owning class/method and the element type is not
// provable from callers/vtables; every name below is address-derived.

struct Rva0034CE80StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

extern char Rva006A16B0Empty;

class LadderInfo;
namespace _STL { template <class T> class list; }

class LadderList
{
public:
	const _STL::list<LadderInfo *> *getSpecialLadders();
};

class Rva0034CE80
{
public:
	void *findByName(const Rva0034CE80StringHeader *const *key) const;

private:
	unsigned char m_pad0[0x17628];
	void *const *m_begin;			// +0x17628
	void *const *m_end;			// +0x1762c
};

// ?findByName@Rva0034CE80@@QBEPAXPBQBURva0034CE80StringHeader@@@Z
void *Rva0034CE80::findByName(const Rva0034CE80StringHeader *const *key) const
{
	for (void *const *iter = m_begin; iter != m_end; ++iter)
	{
		void *element = *iter;
		if (!element)
			continue;

		void *ref = (void *)((LadderList *)element)->getSpecialLadders();

		const Rva0034CE80StringHeader *keyHeader = *key;
		int keyLen = keyHeader ? keyHeader->length : 0;
		const char *keyData = keyHeader ? keyHeader->data : &Rva006A16B0Empty;

		const Rva0034CE80StringHeader *nameHeader = *(const Rva0034CE80StringHeader *const *)ref;
		int nameLen = nameHeader ? nameHeader->length : 0;
		const char *nameData = nameHeader ? nameHeader->data : &Rva006A16B0Empty;

		int n = (nameLen < keyLen) ? nameLen : keyLen;
		int c = memcmp(nameData, keyData, n);
		if (c == 0)
			c = nameLen - keyLen;

		if (c == 0)
			return element;
	}

	return 0;
}
