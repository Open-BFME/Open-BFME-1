// ?adjustFont@Rva00476B00FontLibrary@@QAEXPAVRva00476B00FontName@@PAMPAE@Z
// partial score=0.99 date=2026-09-17
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// FontSubstitution's lookup is the second FontLibrary tree, at this+0x1c.
// Each vector record is 16 bytes: input point size, output point size, a
// two-bit style flag, and an AsciiString replacement name.  The routine picks
// the record immediately below the requested size and linearly interpolates
// the output size when a following record exists.

#include "Common/AsciiString.h"

extern "C" void _ReadWriteBarrier(void);
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_WriteBarrier)

extern "C" long __ftol2(double value);

class Rva00476B00FontName
{
public:
	Rva00476B00FontName &operator=(const Rva00476B00FontName &other);
	void set(const Rva00476B00FontName &other);
	struct Data
	{
		int m_refCount;
		volatile unsigned short m_length;
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
	Rva00476B00FontName m_name;
};

struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first,
	Gen00473A40Elem *last, const int &value, Gen00473A40Less,
	int *);

static __forceinline bool rva00476B00Same(
	Gen00473A40Elem *left, Gen00473A40Elem *right)
{
	return left == right;
}

class Rva00476B00FontLibrary
{
public:
	void adjustFont(Rva00476B00FontName *name, float *size,
		unsigned char *style);

	char m_padding[0x1c];
	Rva00475680Tree m_fontSubstitution;
};

// ?adjustFont@Rva00476B00FontLibrary@@QAEXPAVRva00476B00FontName@@PAMPAE@Z
void Rva00476B00FontLibrary::adjustFont(Rva00476B00FontName *name,
	float *size, unsigned char *style)
{
	Rva00475680Tree *tree = &m_fontSubstitution;
	Rva00475680Node *node = tree->find(*(const AsciiString *)name);
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
		_WriteBarrier();
		if (next == last)
			previous = last - 1;
		else
			previous = first;

		if (previous->m_name.getLength() != 0)
			name->set(previous->m_name);
		flags = previous->m_flags;
		*size = (float)previous->m_outputSize;
	}

apply_flags:
	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
