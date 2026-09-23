// ?bfmeLinkXB@BfmeBaseXB@@QAEXPAVBfmeItemXB@@@Z
// partial score=0.95 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Retail RVA 0x00616BC0, 557 bytes.
//
// The named caller 0x00616E80 (BfmeHolderXB::bfmeOnXB) reaches this body
// through ILT 0x0001CDD7, pinned as BfmeBaseXB::bfmeLinkXB.  The receiver's
// +0x194 table is the native STLport AsciiString-keyed LivingWorldSound map
// the landed siblings 0x006155E0 and 0x006157C0 use: _M_find is 0x00613AE0
// (ILT 0x0002DB0A), begin is 0x006115A0 (ILT 0x00009561), node key +4 and
// mapped pointer +8.  The +0x1A4 dword is the table's element count.
//
// A missing key allocates 0x34 bytes, runs the LivingWorldSound constructor
// 0x0061BF00 and stores vtable 0x01116AC0: the inline constructor of the
// class whose out-of-line copy is U4Ctor0060D640 (0x0060D640).
//
// The saving loop copies each sound's name and releases it only after the
// inline ++it (its by-value hash copy is released first), so the copy
// outlives the increment: the iterator advances inside the body.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "StringInline.h"

// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
namespace rts
{
	template<class T> struct hash
	{
		size_t operator()(T value) const
		{
			_STL::hash<const char *> tmp;
			return tmp(value.str());
		}
	};
}

bool operator==(const AsciiString &, const AsciiString &);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer(void *xfer) = 0;
};

// 0x34 bytes: Code/GameEngine/Source/GameLogic/LivingWorld/Rva006155E0SoundLookup.cpp
class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound(const AsciiString &name);
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(void *xfer);

	AsciiString m_name;
	unsigned char m_rest[0x2c];
};

typedef LivingWorldSound BfmeItemEQV;

// vtable 0x01116AC0; out-of-line constructor 0x0060D640
class U4Ctor0060D640 : public LivingWorldSound
{
public:
	U4Ctor0060D640(const AsciiString &name) : LivingWorldSound(name) {}
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
	virtual void bfmeV26XB(AsciiString *key);
	virtual void bfmeV27XB();
	virtual void bfmeV28XB();
	virtual void bfmeV29XB();
	virtual void bfmeV30XB(int *count);
};

typedef _STL::hash_map<AsciiString, BfmeItemEQV *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeMapXB;

class BfmeBaseXB
{
public:
	void bfmeLinkXB(BfmeItemXB *item);

private:
	unsigned char m_prefix[0x194];
	BfmeMapXB m_items;
};

void BfmeBaseXB::bfmeLinkXB(BfmeItemXB *item)
{
	if (item->bfmeV1XB())
	{
		int count;
		item->bfmeV30XB(&count);

		for (int index = 0; index < count; ++index)
		{
			AsciiString key;
			item->bfmeV26XB(&key);

			BfmeMapXB::iterator found = m_items.find(key);
			if (found == m_items.end())
			{
				BfmeItemEQV *value = new U4Ctor0060D640(key);
				item->bfmeV12XB(value);
			}
			else
			{
				item->bfmeV12XB(found->second);
			}
		}
	}
	else
	{
		int count = m_items.size();
		item->bfmeV30XB(&count);

		BfmeMapXB::iterator it = m_items.begin();
		while (it != m_items.end())
		{
			AsciiString key = it->second->m_name;
			item->bfmeV26XB(&key);
			item->bfmeV12XB(it->second);
			++it;
		}
	}
}
