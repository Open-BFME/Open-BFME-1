// ?rva0021BA10@Rva0021BA10ContestInterface@@QAE_NPAVRvaC4390Second@@PAPAVImage@@@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x0021BA10 (170 bytes): ContestableContain secondary-interface slot
// 0xC8 (secondary vtable 0x010AB140, ILT 0x0003C277).  When the interface's
// slot 49 allows it, looks the object up by its address in the contest map at
// +0x9A4 (an STLport map<UnsignedInt, Image *> instantiation shared with
// Image.cpp); on a miss it asks the primary part (slot 27) and retries with
// the object's resolved index-0 entry.  A hit stores the mapped value.
// IDENTITY IS NOT RECOVERED: the slot name keeps the address.

#include <map>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Image;

typedef _STL::map<UnsignedInt, Image *> Rva0021BA10Map;

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int index);
};

class Rva0021BA10Primary
{
public:
#define PRIMARY_SLOT(N) virtual void slot##N() = 0
	PRIMARY_SLOT(00); PRIMARY_SLOT(01); PRIMARY_SLOT(02); PRIMARY_SLOT(03);
	PRIMARY_SLOT(04); PRIMARY_SLOT(05); PRIMARY_SLOT(06); PRIMARY_SLOT(07);
	PRIMARY_SLOT(08); PRIMARY_SLOT(09); PRIMARY_SLOT(10); PRIMARY_SLOT(11);
	PRIMARY_SLOT(12); PRIMARY_SLOT(13); PRIMARY_SLOT(14); PRIMARY_SLOT(15);
	PRIMARY_SLOT(16); PRIMARY_SLOT(17); PRIMARY_SLOT(18); PRIMARY_SLOT(19);
	PRIMARY_SLOT(20); PRIMARY_SLOT(21); PRIMARY_SLOT(22); PRIMARY_SLOT(23);
	PRIMARY_SLOT(24); PRIMARY_SLOT(25); PRIMARY_SLOT(26);
#undef PRIMARY_SLOT
	virtual void *slot27(RvaC4390Second *obj) = 0;
};

class Rva0021BA10ContestInterface
{
public:
#define IFACE_SLOT(N) virtual void slot##N() = 0
	IFACE_SLOT(00); IFACE_SLOT(01); IFACE_SLOT(02); IFACE_SLOT(03);
	IFACE_SLOT(04); IFACE_SLOT(05); IFACE_SLOT(06); IFACE_SLOT(07);
	IFACE_SLOT(08); IFACE_SLOT(09); IFACE_SLOT(10); IFACE_SLOT(11);
	IFACE_SLOT(12); IFACE_SLOT(13); IFACE_SLOT(14); IFACE_SLOT(15);
	IFACE_SLOT(16); IFACE_SLOT(17); IFACE_SLOT(18); IFACE_SLOT(19);
	IFACE_SLOT(20); IFACE_SLOT(21); IFACE_SLOT(22); IFACE_SLOT(23);
	IFACE_SLOT(24); IFACE_SLOT(25); IFACE_SLOT(26); IFACE_SLOT(27);
	IFACE_SLOT(28); IFACE_SLOT(29); IFACE_SLOT(30); IFACE_SLOT(31);
	IFACE_SLOT(32); IFACE_SLOT(33); IFACE_SLOT(34); IFACE_SLOT(35);
	IFACE_SLOT(36); IFACE_SLOT(37); IFACE_SLOT(38); IFACE_SLOT(39);
	IFACE_SLOT(40); IFACE_SLOT(41); IFACE_SLOT(42); IFACE_SLOT(43);
	IFACE_SLOT(44); IFACE_SLOT(45); IFACE_SLOT(46); IFACE_SLOT(47);
	IFACE_SLOT(48);
#undef IFACE_SLOT
	virtual Bool slot49() = 0;

	Bool rva0021BA10(RvaC4390Second *obj, Image **out);

private:
	unsigned char m_pad004[0x9a0];
	Rva0021BA10Map m_contestMap;
};

Bool Rva0021BA10ContestInterface::rva0021BA10(RvaC4390Second *obj, Image **out)
{
	if (!slot49() || obj == 0)
		return false;

	Rva0021BA10Map::iterator it = m_contestMap.find(*(UnsignedInt *)&obj);
	if (it == m_contestMap.end())
	{
		Rva0021BA10Primary *primary = (Rva0021BA10Primary *)((char *)this - 0x20);
		if (primary->slot27(obj) != 0)
		{
			obj = (RvaC4390Second *)obj->resolve(0);
			it = m_contestMap.find(*(UnsignedInt *)&obj);
			if (it != m_contestMap.end())
			{
				*out = (*it).second;
				return true;
			}
		}
		return false;
	}
	*out = (*it).second;
	return true;
}
