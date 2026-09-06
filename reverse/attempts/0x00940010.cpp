// ??1FontCharsClass@@UAE@XZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: FontCharsClass::~FontCharsClass at 0x00940010 (348 B), the BFME
// shape of render2dsentence.cpp: drain BufferList (each entry owns a byte
// buffer: delete[] the buffer, delete the entry, then DynamicVectorClass::Delete(0)
// inline), release the GDI font, Free_Character_Arrays, drop the process-wide
// GDI state's reference (VA 0x0134AEAC: refs, old bitmap, bitmap, unused, dc)
// and tear it down when it hits zero, then the members: an int-keyed map at
// +0x450, the StringClass at +0x44, the buffer vector at +0x10 and the
// StringClass at +0xc, and finally the RefCountClass vtable.
struct Gen_t_0093fa90_p4pod
{
	char m_body[4];
};

// The int-keyed map member is only destroyed here (one out-of-line call), so
// its STLport type is declared as shells that reproduce the mangled name.
namespace _STL
{
template <class T1, class T2> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	~_Rb_tree();
private:
	char m_body[8];
};
}
typedef _STL::pair<const int, Gen_t_0093fa90_p4pod> FontCharsMapPair;
typedef _STL::_Rb_tree<int, FontCharsMapPair, _STL::_Select1st<FontCharsMapPair>, _STL::less<int>,
	_STL::allocator<FontCharsMapPair> > FontCharsMapTree;

extern void __cdecl operator delete(void *);
extern void __cdecl operator delete[](void *);

extern void (__stdcall *const g_release)(void *);
extern void (__stdcall *g_pair)(void *, void *);
extern void (__stdcall *g_destroy)(void *);

class StringClass
{
public:
	~StringClass()
	{
		Free_String();
	}
private:
	void Free_String();
	char *m_Buffer;
};

struct FontCharsBufferClass
{
	unsigned char *Buffer;
	int Used;
};

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass()
	{
		if (Vector != 0 && IsAllocated)
		{
			delete[] Vector;
		}
		Vector = 0;
		IsAllocated = false;
		VectorMax = 0;
	}
	T &operator[](int index) { return Vector[index]; }
	int Count() const { return ActiveCount; }
	void Delete(int index)
	{
		if (index < ActiveCount)
		{
			ActiveCount--;
			for (int i = index; i < ActiveCount; i++)
			{
				Vector[i] = Vector[i + 1];
			}
		}
	}
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	int ActiveCount;
	int GrowthStep;
};

struct FontCharsGDIState
{
	int Refs;
	void *OldBitmap;
	void *Bitmap;
	int Unused;
	void *DC;
};
extern FontCharsGDIState *_TheFontCharsGDIState;

// The base subobject: ref count, one int and the Name string (its
// destruction is the last EH state before the base vtable store).
class RefCountClass
{
public:
	virtual ~RefCountClass() {}
	int NumRefs;
	int m_field08;
	StringClass Name;
};

class FontCharsClass : public RefCountClass
{
public:
	virtual ~FontCharsClass();
private:
	void Free_Character_Arrays();
	DynamicVectorClass<FontCharsBufferClass *> BufferList;
	char m_gap28[0x44 - 0x28];
	StringClass GDIFontName;
	void *GDIFont;
	char m_gap4c[0x450 - 0x4c];
	FontCharsMapTree CharMap;
};

FontCharsClass::~FontCharsClass()
{
	while (BufferList.Count())
	{
		FontCharsBufferClass *entry = BufferList[0];
		if (entry)
		{
			delete[] entry->Buffer;
			delete entry;
		}
		BufferList.Delete(0);
	}
	void (__stdcall *release)(void *) = g_release;
	if (GDIFont)
	{
		release(GDIFont);
		GDIFont = 0;
	}
	Free_Character_Arrays();
	FontCharsGDIState *state = _TheFontCharsGDIState;
	state->Refs--;
	state = _TheFontCharsGDIState;
	if (state->Refs == 0)
	{
		if (state->Bitmap)
		{
			g_pair(state->DC, state->OldBitmap);
			release(state->Bitmap);
			state->Bitmap = 0;
		}
		if (state->DC)
		{
			g_destroy(state->DC);
			state->DC = 0;
		}
		delete state;
		_TheFontCharsGDIState = 0;
	}
}
