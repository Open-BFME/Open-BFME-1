// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: anonymous asset walker at retail 0x00769490, 429 bytes.
//
// What the body does is provable; who owns it is not. The only caller is the
// 970-byte walker at 0x007710F0 (through ILT 0x0002CB29), which calls it on
// each 0xBC-byte element of a vector with (AssetList, context, prefix string,
// int). So the class and method keep the address token.
//
// The list is an AssetList: the body is AssetList::operator<<(const
// AsciiString &) (matched at 0x00141D00) inlined -- the same insert_unique
// thunk 0x00030413, the same changed flag at +0x10 -- and the temporary it is
// handed lives until the end of that statement, which is why its release
// follows the flag store. For each 0x38-byte record in the vector at +0x2C the
// name added is "a*" + (prefix + "." when the prefix is not empty) + the
// record's string at +8.
//
// Then (list, context) goes to the object at +0x44, to the slot-3 virtual of
// the object each node of the list at +0x50 carries at +0x1C, and to the
// object at +0x10 of every 0x14-byte element of the two arrays at +0x54 and
// +0x60. The two-pointer forwarder at ILT 0x00022D86 is spelled with the pin
// the other AssetList walkers use (GenericObjectCreationNugget::GetAssetList).
// The fourth argument is never read.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <vector>
#include <string.h>

// TU-local string shim instead of WWLib/ascii_string.h: that header forwards
// isEmpty, getLength, str and concat(const char *) to out-of-line StringBase
// members and declares ~AsciiString out of line, where retail inlines them;
// with the header this body compiles to 397 bytes, not 429.
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
	int getLength() const { return m_data ? m_data->length : 0; }
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }
	void concat(const T *text, int length);

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int getLength() const { return StringBase<char>::getLength(); }
	const char *str() const { return StringBase<char>::str(); }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	void concat(const char *text)
	{
		StringBase<char>::concat(text, text ? (int)strlen(text) : 0);
	}
	void concat(const AsciiString &source)
	{
		StringBase<char>::concat(source.str(), source.getLength());
	}

	friend AsciiString operator+(AsciiString left, const AsciiString &right);
};

// Prototype lookup at 0x009EC0B0.
void *bfmeGoEMEb(void *a);

struct Rva0013FA60Target;

typedef Rva0013FA60Target *Rva00769490Key;
typedef _STL::set<Rva00769490Key, _STL::less<Rva00769490Key>,
	_STL::allocator<Rva00769490Key> > Rva00769490Set;

class AssetList
{
public:
	AssetList &operator <<(const AsciiString &name)
	{
		if (m_prototypes.insert((Rva00769490Key)bfmeGoEMEb((void *)name.str())).second)
			m_changed = true;
		return *this;
	}

private:
	Rva00769490Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

// ILT 0x00022D86, body 0x00428250: hands (list, context) to every object in
// the list at +4 through slot 3.
class Gen_002DDCC0Target
{
public:
	void bfmeForward(void *one, void *two);
};

class Rva00769490Client1C
{
public:
	virtual void _bfme_slot0();
	virtual void _bfme_slot1();
	virtual void _bfme_slot2();
	virtual void bfmeForward(void *one, void *two);
};

struct Rva00769490Node50
{
	Rva00769490Node50 *m_next;
	unsigned char m_pad[0x18];
	Rva00769490Client1C *m_client1C;
};

struct Rva00769490SlotRecord
{
	unsigned char m_pad[0x10];
	Gen_002DDCC0Target *m_target10;
};

struct Rva00769490Record38
{
	unsigned char m_pad[8];
	AsciiString m_name;
	unsigned char m_tail[0x38 - 0xc];
};

class Rva00769490Owner
{
public:
	void invoke(AssetList *assets, void *context, const AsciiString &prefix, int arg4);

private:
	unsigned char m_pad0[0x2c];
	_STL::vector<Rva00769490Record38> m_records2C;
	unsigned char m_pad1[0x44 - 0x38];
	Gen_002DDCC0Target *m_broadcastTarget;
	unsigned char m_pad2[0x50 - 0x48];
	Rva00769490Node50 *m_sentinel;
	Rva00769490SlotRecord *m_slotsABegin;
	Rva00769490SlotRecord *m_slotsAEnd;
	unsigned char m_pad3[0x60 - 0x5c];
	Rva00769490SlotRecord *m_slotsBBegin;
	Rva00769490SlotRecord *m_slotsBEnd;
};

// ?invoke@Rva00769490Owner@@QAEXPAVAssetList@@PAXABVAsciiString@@H@Z
void Rva00769490Owner::invoke(AssetList *assets, void *context,
	const AsciiString &prefix, int /*arg4*/)
{
	for (_STL::vector<Rva00769490Record38>::const_iterator record = m_records2C.begin();
		record != m_records2C.end(); ++record)
	{
		AsciiString key("a*");
		if (!prefix.isEmpty())
		{
			key.concat(prefix);
			key.concat(".");
		}
		*assets << (key + record->m_name);
	}

	if (m_broadcastTarget)
		m_broadcastTarget->bfmeForward(assets, context);

	for (Rva00769490Node50 *node = m_sentinel->m_next; node != m_sentinel;
		node = node->m_next)
	{
		if (node->m_client1C)
			node->m_client1C->bfmeForward(assets, context);
	}

	for (Rva00769490SlotRecord *slot = m_slotsABegin; slot != m_slotsAEnd; ++slot)
	{
		if (slot->m_target10)
			slot->m_target10->bfmeForward(assets, context);
	}

	for (Rva00769490SlotRecord *slot = m_slotsBBegin; slot != m_slotsBEnd; ++slot)
	{
		if (slot->m_target10)
			slot->m_target10->bfmeForward(assets, context);
	}
}
