// ?bfmeLinkXB@BfmeBaseXB@@QAEXPAVBfmeItemXB@@@Z
// partial score=0.33 date=2026-09-21
// Retail RVA 0x00616BC0, 557 bytes.
//
// The named caller and ILT identify this as BfmeBaseXB::bfmeLinkXB, while the
// item and value classes remain the established opaque ABI names.  The map at
// +0x194 is the native STLport AsciiString-keyed table witnessed by the
// adjacent LivingWorld bodies.  Its node is {next, key, BfmeItemEQV *}; the
// lookup body returns that node, so the mapped value is read at +8.
//
// The two branches intentionally retain the native temporary lifetimes: the
// first has a per-iteration key, and the second has a copied mapped key inside
// the iterator loop.  The resulting cleanup states are part of the ABI shape.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /FAsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_bfmeBufXB(0) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other);
	~BFMERetailAsciiString() { releaseBuffer(); }

	bool operator==(const BFMERetailAsciiString &other) const
	{
		return strcmp((const char *)m_bfmeBufXB,
			(const char *)other.m_bfmeBufXB) == 0;
	}

	void *m_bfmeBufXB;

private:
	void releaseBuffer();
};

namespace rts
{
	template<> struct hash<BFMERetailAsciiString>
	{
		size_t operator()(BFMERetailAsciiString ast) const
		{
			std::hash<const char *> tmp;
			return tmp((const char *)ast.m_bfmeBufXB);
		}
	};
}

class BfmeItemEQV
{
public:
	BfmeItemEQV(void *key);

	void *m_vtable;
	BFMERetailAsciiString m_key;
	unsigned char m_rest[0x2c];
};

class BfmeItemXB
{
public:
	virtual void bfmeV0XB();
	virtual bool bfmeV1XB();
	virtual void bfmeV2XB();
	virtual void bfmeV3XB();
	virtual void bfmeV4XB();
	virtual void bfmeV5XB();
	virtual void bfmeV6XB();
	virtual void bfmeV7XB();
	virtual void bfmeV8XB();
	virtual void bfmeV9XB();
	virtual void bfmeV10XB();
	virtual void bfmeV11XB();
	virtual void bfmeV12XB(BfmeItemEQV *value);
	virtual void bfmeV13XB();
	virtual void bfmeV14XB();
	virtual void bfmeV15XB();
	virtual void bfmeV16XB();
	virtual void bfmeV17XB();
	virtual void bfmeV18XB();
	virtual void bfmeV19XB();
	virtual void bfmeV20XB();
	virtual void bfmeV21XB();
	virtual void bfmeV22XB();
	virtual void bfmeV23XB();
	virtual void bfmeV24XB();
	virtual void bfmeV25XB();
	virtual void bfmeV26XB(BFMERetailAsciiString *key);
	virtual void bfmeV27XB();
	virtual void bfmeV28XB();
	virtual void bfmeV29XB();
	virtual void bfmeV30XB(void *out);
};

typedef _STL::hash_map<BFMERetailAsciiString, BfmeItemEQV *,
	rts::hash<BFMERetailAsciiString>, _STL::equal_to<BFMERetailAsciiString> >
	BfmeMapXB;

class BfmeBaseXB
{
public:
	void bfmeLinkXB(BfmeItemXB *item);

private:
	unsigned char m_prefix[0x194];
	BfmeMapXB m_items;
	void *m_field1a4;
};

void BfmeBaseXB::bfmeLinkXB(BfmeItemXB *item)
{
	if (item->bfmeV1XB())
	{
		int count;
		item->bfmeV30XB(&count);

		for (int index = 0; index < count; ++index)
		{
			BFMERetailAsciiString key;
			item->bfmeV26XB(&key);

			BfmeMapXB::iterator found = m_items.find(key);
			if (found == m_items.end())
			{
				BfmeItemEQV *value = new BfmeItemEQV(&key);
				if (value != 0)
				{
					value->m_vtable = (void *)0x01116ac0;
					item->bfmeV12XB(value);
				}
				else
				{
					item->bfmeV12XB(0);
				}
			}
			else
			{
				item->bfmeV12XB(found->second);
			}
		}
	}
	else
	{
		void *field = m_field1a4;
		item->bfmeV30XB(&field);

		for (BfmeMapXB::iterator it = m_items.begin();
			it != m_items.end(); ++it)
		{
			BFMERetailAsciiString key(it->second->m_key);
			item->bfmeV26XB(&key);
			item->bfmeV12XB(it->second);
		}
	}
}
