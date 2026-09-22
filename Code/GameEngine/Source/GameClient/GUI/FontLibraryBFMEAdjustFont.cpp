// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ?adjustFont@Rva00476B00FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
// Open-BFME5: address-derived FontLibrary::adjustFont, retail 0x00476B00, 260
// bytes.  FontSubstitution's lookup is the second FontLibrary tree, at
// this+0x1c.  Each vector record is 16 bytes: input point size, output point
// size, a two-bit style flag, and a replacement name.  The routine picks the
// record immediately below the requested size and linearly interpolates the
// output size when a following record exists.
//
// Shape note: the edge case assigns `previous = first` UNCONDITIONALLY and then
// overwrites it when next == last.  That single statement is what lets VC7.1
// thread the first `je` past the re-test, so next == last reaches the
// last-record lea at +0xb7 instead of the shared compare at +0xb3 -- the one
// non-relocation byte twelve earlier verdicts left standing at +0x6b.


extern "C" long __ftol2(double value);

class AsciiString
{
public:
	// Retail assigns through the out-of-line operator= twice (ILT 0x00003765 and
	// the folded copy at 0x00887C90); ascii_string.h inlines it to
	// StringBase<char>::set, which neither site encodes, so the class stays
	// TU-local with the members this body witnesses.
	AsciiString &operator=(const AsciiString &other);
	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};
	int getLength() const
	{
		return m_data == 0 ? 0 : m_data->m_length;
	}

	Data *m_data;
};

struct Rva00476B00Vector
{
	char *m_first;
	char *m_last;
	char *m_end;
};

struct Rva00475680Node
{
	int m_color;
	Rva00475680Node *m_parent;
	Rva00475680Node *m_left;
	Rva00475680Node *m_right;
	AsciiString m_key;
	Rva00476B00Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *find(const AsciiString &key) const;

	Rva00475680Node *m_header;
};

struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	AsciiString m_name;
};

struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first,
	Gen00473A40Elem *last, const int &value, Gen00473A40Less,
	int *);

class Rva00476B00FontLibrary
{
public:
	void adjustFont(AsciiString *name, float *size,
		unsigned char *style);

	char m_padding[0x1c];
	Rva00475680Tree m_fontSubstitution;
};

// ?adjustFont@Rva00476B00FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
void Rva00476B00FontLibrary::adjustFont(AsciiString *name,
	float *size, unsigned char *style)
{
	Rva00475680Tree *tree = &m_fontSubstitution;
	Rva00475680Node *node = tree->find(*name);
	if (node == tree->m_header)
		return;

	Rva00476B00Vector *list = node->m_value;
	if (list == 0)
		return;

	Gen00473A40Elem *first = (Gen00473A40Elem *)list->m_first;
	Gen00473A40Elem *last = (Gen00473A40Elem *)list->m_last;
	if ((((char *)last - (char *)first) & ~0x0f) == 0)
		return;

	Gen00473A40Less less;
	*(unsigned char *)&less = 0;
	Gen00473A40Elem *next = Gen00473A40(first, last, (int)*size,
		less, 0);
	Gen00473A40Elem *previous;
	int flags;

	if (next != last && next != first)
	{
		previous = next - 1;
		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;

		flags = previous->m_flags;
		*size = (float)previous->m_outputSize +
			(*size - (float)previous->m_inputSize) *
				((float)next->m_outputSize -
					(float)previous->m_outputSize) /
				((float)next->m_inputSize -
					(float)previous->m_inputSize);
	}
	else
	{
		previous = first;
		if (next == last)
			previous = last - 1;

		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;
		flags = previous->m_flags;
		*size = (float)previous->m_outputSize;
	}

	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
