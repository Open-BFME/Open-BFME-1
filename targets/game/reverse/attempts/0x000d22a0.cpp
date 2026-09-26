// ?rva000D22A0@Rva000D22A0Player@@QAEXVAsciiString@@_N@Z
// partial score=0.39 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs- /EHc- /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// ?rva000D22A0@Rva000D22A0Player@@QAEXVAsciiString@@_N@Z
// Retail body at 0x000D22A0, 332 bytes. The owner remains address-derived.

#include <list>
#include "GameLogic/ObjectScriptStatusBits.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

extern void j_00001140();
extern void j_000022bb();
extern void j_0002bf2b();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?setScriptStatus@Object@@QAEXW4ObjectScriptStatusBit@@_N@Z=?j_0002bf2b@@YAXXZ")

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	~StringBase();

	int getLength() const { return m_data ? m_data->m_len : 0; }
	const char *str() const
	{
		return m_data ? (const char *)(m_data + 1) : (const char *)0x0107388B;
	}

	int compare(const StringBase &other) const
	{
		const BfmeAsciiStringData *otherData =
			*reinterpret_cast<const BfmeAsciiStringData * const *>(&other);
		int lenOther = otherData ? otherData->m_len : 0;
		const char *pOther = otherData ?
			(const char *)(otherData + 1) : (const char *)0x0107388B;
		int lenThis = getLength();
		const char *pThis = str();
		int shorter = lenThis < lenOther ? lenThis : lenOther;
		int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;
		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int getLength() const { return StringBase<char>::getLength(); }
	const char *str() const { return StringBase<char>::str(); }
	int compare(const AsciiString &other) const
	{
		const BfmeAsciiStringData *otherData =
			*reinterpret_cast<const BfmeAsciiStringData * const *>(
				*reinterpret_cast<const void * const *>(&other));
		int lenOther = otherData ? otherData->m_len : 0;
		const char *pOther;
		if (otherData)
			pOther = (const char *)(otherData + 1);
		else
			pOther = (const char *)0x0107388B;
		int lenThis = getLength();
		const char *pThis = str();
		int shorter = lenThis < lenOther ? lenThis : lenOther;
		int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;
		return lenThis - lenOther;
	}
};

class BfmeThingName
{
public:
	int getLength() const { return m_data ? m_data->m_len : 0; }
	const char *str() const
	{
		return m_data ? (const char *)(m_data + 1) : (const char *)0x0107388B;
	}

	int compare(const AsciiString &other) const
	{
		const BfmeAsciiStringData *otherData =
			*reinterpret_cast<const BfmeAsciiStringData * const *>(
				*reinterpret_cast<const void * const *>(&other));
		int lenOther;
		if (otherData)
			lenOther = otherData->m_len;
		else
			lenOther = 0;
		const char *pOther = (const char *)0x0107388B;
		if (otherData)
			pOther = (const char *)(otherData + 1);
		int lenThis = getLength();
		const char *pThis = str();
		int shorter = lenThis < lenOther ? lenThis : lenOther;
		int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;
		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

class Rva000D22A0Player
{
public:
	void rva000D22A0(AsciiString templateTypeToAffect, Bool enable);
};

class BfmePlayerTeamPrototypeInstances;

typedef std::list<BfmePlayerTeamPrototypeInstances *> BfmePlayerTeamList;

struct BfmePlayerTeamFields
{
	unsigned char m_unreconstructed_000[0x288];
	BfmePlayerTeamList m_playerTeamPrototypes;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Object;

typedef Object *(__fastcall *BfmeDlinkNext)(Object *);

struct BfmeDlinkPmf
{
	BfmeDlinkNext pfn;
	int delta;
	int vbindex;
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0x20 - 0x08];
	BfmeThingName m_name;

	const BfmeThingName &getName() const { return m_name; }
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (!value)
			return 0;
		if (value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	void setScriptStatus(ObjectScriptStatusBit status, Bool value);
	unsigned char m_tail[0x40];
};

class BfmePlayerObjectView
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
};

class BfmePlayerTeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	Object *m_head;
};

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *cur) : m_cur(cur) {}

	Bool done() const { return m_cur == NULL; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	BfmePlayerTeamView *m_cur;
	Int m_unmodelled;
};

template <class ObjectType> class BfmePlayerDlinkIterator
{
public:
	BfmePlayerDlinkIterator(ObjectType *cur, BfmeDlinkPmf getNext)
		: m_cur(cur), m_getNext(getNext) {}

	Bool done() const { return m_cur == NULL; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		ObjectType *object = m_cur;
		if (!object)
			return;
		int vbindex = m_getNext.vbindex;
		char *vbptr = *(char **)((char *)object + 0x68);
		char *adjusted = (char *)object + 0x68;
		adjusted += *(int *)(vbptr + vbindex);
		adjusted += m_getNext.delta;
		m_cur = m_getNext.pfn((ObjectType *)adjusted);
	}

private:
	ObjectType *m_cur;
	int m_padding;
	BfmeDlinkPmf m_getNext;
	int m_tailPadding;
};

void Rva000D22A0Player::rva000D22A0(AsciiString templateTypeToAffect, Bool enable)
{
	BfmePlayerTeamFields *self = (BfmePlayerTeamFields *)this;
	for (BfmePlayerTeamList::iterator it = self->m_playerTeamPrototypes.begin();
			it != self->m_playerTeamPrototypes.end(); ++it)
	{
		BfmePlayerTeamPrototypeInstances *prototype =
			(BfmePlayerTeamPrototypeInstances *)*it;
		for (BfmePlayerTeamInstanceIterator iter(prototype->m_teamInstanceList);
				!iter.done(); iter.advance())
		{
			BfmePlayerTeamView *team = iter.cur();
			if (!team)
				continue;

			BfmeDlinkPmf pmf = {(BfmeDlinkNext)0x00401140, -100, 0};
			BfmePlayerDlinkIterator<Object> iterObj(team->m_head, pmf);
			for (; !iterObj.done(); iterObj.advance())
			{
				Object *obj = iterObj.cur();
				if (!obj)
					continue;

				const ThingTemplate *thingTemplate = obj->getTemplate();

				if (thingTemplate->getName().compare(templateTypeToAffect) == 0)
					obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !enable);
			}
		}
	}
}
