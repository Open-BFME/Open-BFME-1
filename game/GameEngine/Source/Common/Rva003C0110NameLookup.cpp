// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
//
// Address-derived member lookup at retail 0x003C0110 (214 bytes).
//
// The receiver is a pointer-vector owner: the begin/end pair is at this+0x0c
// and this+0x10.  Each element is passed to the existing incremental-link
// thunk j_0004958a.  Retail's thunk target is the already identified 32-byte
// copy/getter body at 0x003A4390; its call site proves ECX=element, one stack
// out-string argument, and a returned pointer to that out-string.  The local
// narrow string uses the retail StringBase<char> header (length +4, text +8)
// and releases through the existing StringBase<char>::releaseBuffer body.
//
// No semantic class name is asserted: the target's own caller set only proves
// the raw member ABI and the pointer-vector/name comparison described above.

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

extern const char g_bfmeEmptyAscii[];

class Rva003C0110Owner;

template <typename T>
class StringBase
{
public:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	friend class Rva003C0110Owner;

	private:
	void releaseBuffer();

	public:
	Header *m_data;
};

struct Rva003C0110Element;

// The generated declaration carries the existing thunk's identity.  The
// typed cast is TU-local ABI information recovered from 0x003A4390; it does
// not create an alternatename or a new ledger pin.
extern void j_0004958a(void);
struct Rva003C0110NameCopyView
{
	StringBase<char> *copyName(StringBase<char> *out);
};
typedef StringBase<char> *(Rva003C0110NameCopyView::*Rva003C0110NameCopy)(
	StringBase<char> *);

struct Rva003C0110Range
{
	Rva003C0110Element **m_begin;
	Rva003C0110Element **m_end;

	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

class Rva003C0110Owner
{
public:
	struct Rva003C0110ElementResult;
	Rva003C0110ElementResult *findByName(StringBase<char> *key);

private:
	unsigned char m_unreconstructed00[0x0c];
	Rva003C0110Range m_elements;
};

// ?findByName@Rva003C0110Owner@@QAEPAURva003C0110ElementResult@1@PAV?$StringBase@D@@@Z
Rva003C0110Owner::Rva003C0110ElementResult *
Rva003C0110Owner::findByName(StringBase<char> *key)
{
	Rva003C0110Owner *owner = this;
	unsigned int count = owner->m_elements.size();
	int index = 0;
	if (count > 0)
	{
		do
		{
			StringBase<char> elementName;
			union
			{
				void (*asFunction)(void);
				Rva003C0110NameCopy asMember;
			} copy;
			copy.asFunction = j_0004958a;
			StringBase<char> *name =
				(reinterpret_cast<Rva003C0110NameCopyView *>(
					owner->m_elements.m_begin[index])->*copy.asMember)(
					&elementName);

			int elementLength = name->m_data ?
				name->m_data->m_length : 0;
			const char *elementText = name->m_data ?
				&name->m_data->m_text[0] : g_bfmeEmptyAscii;
			int keyLength = key->m_data ? key->m_data->m_length : 0;
			const char *keyText = key->m_data ?
				&key->m_data->m_text[0] : g_bfmeEmptyAscii;
			int compareResult = memcmp(keyText, elementText,
				keyLength < elementLength ? keyLength : elementLength);
			int difference;
			if (compareResult != 0)
				difference = compareResult;
			else
				difference = keyLength - elementLength;

			elementName.releaseBuffer();
			if (difference == 0)
				return (Rva003C0110ElementResult *)
					owner->m_elements.m_begin[index];
			++index;
		} while ((unsigned int)index <
			(unsigned int)(owner->m_elements.m_end - owner->m_elements.m_begin));
	}
	return 0;
}
