// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ?adjustFont@Rva00476B00FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
// retail 0x00476B00, 260 bytes.
//
// WHAT IS PROVEN AND WHAT IS NOT.  The class word carries the address, so the
// symbol is self-labelling whatever the rest of it turns out to be.  The method
// word `adjustFont` is NOT proven: this body references no string, occupies no
// vtable slot, and its only caller is the anonymous gen-dump ?d_00476C50
// reaching it through ILT 0x00001ED3.  Read `adjustFont` as a description of
// what the body does, not as a recovered retail name.
//
// m_fontSubstitution IS evidence-backed.  The tree at this+0x1C is the one the
// FontSubstitution INI parser at 0x004779C0 writes -- targets/game/reverse/symbols.csv pins
// both ?find@Rva00475680Tree@@... and ?at@Rva00475680Tree@@... to that parser --
// and the loader at 0x00473500 pushes the literal "data\ini\fontsubstitution.ini"
// (VA 0x010F762C).  Each vector record is 16 bytes: input point size, output
// point size, a two-bit style flag, and a replacement name.  The routine picks
// the record immediately below the requested size and linearly interpolates the
// output size when a following record exists.
//
// CALLEE CONTRACT -- the two name assignments are DIFFERENT callees.
//   +0x88 (interpolating branch) `call 0x00003765`, an ILT thunk to 0x0005C500,
//         ??4AsciiString@@QAEAAV0@ABV0@@Z: 19 bytes that forward to 0x00887C90
//         and return this.  That is the OUT-OF-LINE AsciiString::operator=, so
//         this site needs an operator= the compiler cannot inline -- hence the
//         TU-local AsciiString whose operator= is declared, not defined.
//   +0xd1 (flat branch) `call 0x00887C90` DIRECTLY:
//         ?set@?$StringBase@D@@QAEXABV1@@Z, StringBase<char>::set, 135 bytes.
//         That is exactly what ascii_string.h:41-44 inlines operator= to, so it
//         is spelled here as the set call it is.
// Spelling both sites `*name = ...` is what the earlier revision did; it only
// looked green because targets/game/reverse/symbols.csv carries an additive candidate
// `??4AsciiString@@QAEAAV0@ABV0@@Z,0x00887C90,folded with UnicodeString::set
// per-TU copy` alongside the real 0x0005C500 row in targets/game/reverse/functions.csv, and
// an additive pin proves nothing about which body a site actually calls.  With
// site 2 spelled as set, only site 1 names operator= here, and site 1 wants the
// 0x0005C500 body the functions.csv row already holds.
//
// Shape note: the flat branch assigns `previous = first` UNCONDITIONALLY and
// then overwrites it when next == last.  That single statement is what lets
// VC7.1 thread the first `je` past the re-test, so next == last reaches the
// last-record lea at +0xb7 instead of the shared compare at +0xb3 -- the one
// non-relocation byte twelve earlier verdicts left standing at +0x6b.

#include "string_base.h"

extern "C" long __ftol2(double value);

class AsciiString
{
public:
	// Declared, never defined: the +0x88 site must emit the out-of-line
	// ??4AsciiString call through ILT 0x00003765 (see CALLEE CONTRACT above).
	AsciiString &operator=(const AsciiString &other);
	// StringBase<char>::Header, string_base.h:73-76.  Only the length halfword
	// at +4 is witnessed here (`movzx eax, word ptr [eax+4]`); the other two
	// keep their canonical spelling rather than a guess.
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
	};
	int getLength() const
	{
		return m_data == 0 ? 0 : m_data->length;
	}

	Header *m_data;
};

// Same tree, same 12-byte mapped vector and same node as the landed sibling
// game/GameEngine/Source/GameClient/GUI/INIFontSubstitution.cpp; the
// Rva004779C0Vector spelling is the one targets/game/reverse/symbols.csv already uses in
// ?at@Rva00475680Tree@@QAEPAPAVRva004779C0Vector@@ABVAsciiString@@@Z.
struct Rva004779C0Vector
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
	Rva004779C0Vector *m_value;
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

// STLport's __upper_bound takes its comparator BY VALUE, and retail hands it a
// 4-byte stack slot whose first byte it zeroes (`mov byte ptr [esp+0x10],0` at
// +0x43) before pushing the whole dword.  A real one-byte member assigned zero
// reproduces that exactly.  An EMPTY functor does not: value-initialising
// `Gen00473A40Less()` elides the store and the body comes out 259 bytes, which
// is why the earlier revision forced the byte with `*(unsigned char *)&less = 0`
// through a cast into an empty struct.  What the byte MEANS is still unknown --
// no member of this comparator is read here -- so it is spelled by its offset
// rather than given an invented name.
struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;

	unsigned char m_pad0x00;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first,
	Gen00473A40Elem *last, const int &value, Gen00473A40Less,
	int *);

class Rva00476B00FontLibrary
{
public:
	void adjustFont(AsciiString *name, float *size,
		unsigned char *style);

	// Nothing before the tree is read here.  The landed sibling
	// FontLibraryBFME.cpp spells the real prefix (subsystem vtable, font list,
	// two STLport maps); this body witnesses none of it, so it stays a pad.
	char m_pad0x00[0x1c];
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

	Rva004779C0Vector *list = node->m_value;
	if (list == 0)
		return;

	Gen00473A40Elem *first = (Gen00473A40Elem *)list->m_first;
	Gen00473A40Elem *last = (Gen00473A40Elem *)list->m_last;
	if ((((char *)last - (char *)first) & ~0x0f) == 0)
		return;

	Gen00473A40Less less;
	less.m_pad0x00 = 0;
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
			((StringBase<char> *)name)->set(
				*(const StringBase<char> *)&previous->m_name);
		flags = previous->m_flags;
		*size = (float)previous->m_outputSize;
	}

	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
