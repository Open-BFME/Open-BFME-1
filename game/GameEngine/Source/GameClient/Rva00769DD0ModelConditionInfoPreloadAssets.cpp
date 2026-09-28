// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: address-derived ModelConditionInfo asset preload body at retail 0x00769DD0.
// Its only caller, 0x007710F0, passes (AssetList at +0x134, context, mode, zero-extended bool).

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <string.h>

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

public:
	void set(const StringBase<T> &source);
	void concat(const T *text, int length);
	const T *str() const { return m_data ? &m_data->data[0] : 0; }

private:
	StringBase(const StringBase<T> &source);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() {}

	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? &m_data->data[0] : &TheNullChr;
	}
	void set(const AsciiString &source)
	{
		StringBase<char>::set(source);
	}
	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	friend AsciiString operator+(AsciiString left, const char *right);
};

void *bfmeGoEMEb(void *value);
bool __cdecl Render_Obj_Exists(const char *name);

struct Rva0013FA60Target;
typedef Rva0013FA60Target *Rva00769DD0Key;
typedef _STL::set<Rva00769DD0Key, _STL::less<Rva00769DD0Key>,
	_STL::allocator<Rva00769DD0Key> > Rva00769DD0Set;

class AssetList
{
public:
	AssetList &operator <<(const AsciiString &name)
	{
		if (m_prototypes.insert((Rva00769DD0Key)bfmeGoEMEb((void *)name.str())).second)
			m_changed = true;
		return *this;
	}

private:
	Rva00769DD0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

class Rva00769DD0Client
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void forward(AssetList *assets, void *context);
};

class Gen_002DDCC0Target
{
public:
	void bfmeForward(void *one, void *two);
};

enum Rva00769DD0Mode
{
	RVA00769DD0_MODE_UNKNOWN = -1,
	RVA00769DD0_MODE_LOW = 0,
	RVA00769DD0_MODE_MEDIUM = 1,
	RVA00769DD0_MODE_HIGH = 2,
	RVA00769DD0_MODE_CUSTOM = 3,
	RVA00769DD0_MODE_COUNT = 6
};

struct Rva00769DD0Node
{
	Rva00769DD0Node *m_next;
	unsigned char m_pad[0x18];
	Rva00769DD0Client *m_client;
};

struct Rva00769DD0Slot
{
	unsigned char m_pad[0x10];
	Gen_002DDCC0Target *m_target;
};

template <typename T>
class Rva00769DD0Vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

class Rva00769DD0ModelConditionInfo
{
public:
	void preloadAssets(AssetList *assets, void *context, Rva00769DD0Mode mode, bool extra);

private:
	char m_unknown00[0x28];
	Rva00769DD0Vector<AsciiString> m_modelNames;
	AsciiString m_unknown34;
	char m_unknown38[0x64];
	Rva00769DD0Node *m_sentinel;
	Rva00769DD0Slot *m_slotsABegin;
	Rva00769DD0Slot *volatile m_slotsAEnd;
	char m_unknownA8[4];
	Rva00769DD0Slot *m_slotsBBegin;
	Rva00769DD0Slot *volatile m_slotsBEnd;
	char m_unknownB4[8];
	AsciiString m_unknownBC;
};

// ?preloadAssets@Rva00769DD0ModelConditionInfo@@QAEXPAVAssetList@@PAXW4Rva00769DD0Mode@@_N@Z
// Mode 0 and 1 add the "L" suffix and mode 2 the "M" suffix; separate case bodies keep retail's sub/dec dispatch.
void Rva00769DD0ModelConditionInfo::preloadAssets(AssetList *assets, void *context,
	Rva00769DD0Mode mode, bool extra)
{
	for (AsciiString *it = m_modelNames.m_start; it != m_modelNames.m_finish; ++it)
	{
		AsciiString current(*it);
		switch (mode)
		{
		case RVA00769DD0_MODE_LOW:
			current.concat("L", 1);
			break;
		case RVA00769DD0_MODE_MEDIUM:
			current.concat("L", 1);
			break;
		case RVA00769DD0_MODE_HIGH:
			current.concat("M", 1);
			break;
		}

		if (!Render_Obj_Exists(current.str()))
			current.set(*it);

		if (extra)
		{
			*assets << current;
			*assets << (current + "_n");
			*assets << (current + "_nr");
			*assets << (current + "_ne");
			*assets << (current + "_nd");
			*assets << (current + "_r");
			*assets << (current + "_e");
			*assets << (current + "_d");
		}
		else
		{
			*assets << current;
		}
	}

	if (!m_unknown34.isEmpty())
		*assets << m_unknown34;

	for (Rva00769DD0Node *node = m_sentinel->m_next; node != m_sentinel;
		node = node->m_next)
	{
		if (node->m_client)
			node->m_client->forward(assets, context);
	}

	Rva00769DD0Slot *slot = m_slotsABegin;
	Rva00769DD0Slot *end = m_slotsAEnd;
	while (slot != end)
	{
		if (slot->m_target)
			slot->m_target->bfmeForward(assets, context);
		end = m_slotsAEnd;
		++slot;
	}

	slot = m_slotsBBegin;
	end = m_slotsBEnd;
	while (slot != end)
	{
		if (slot->m_target)
			slot->m_target->bfmeForward(assets, context);
		end = m_slotsBEnd;
		++slot;
	}

	if (!m_unknownBC.isEmpty())
		*assets << (m_unknownBC + ".tga");
}
