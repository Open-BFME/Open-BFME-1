// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// The caller at 0x0094D450 writes all four dwords of the 16-byte mapped value.
// The map insertion call reaches 0x0094CF90, and the temporary key releases through 0x009EB7A0.

#include "PreRTS.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

class TextureClass
{
public:
	void Release_Ref();
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(const RefCountPtr &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	T *Peek() const { return Referent; }
	bool operator<(const RefCountPtr &other) const
	{
		return Referent < other.Referent;
	}

private:
	T *Referent;
};

struct Rva0094D370Value
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;
};

typedef _STL::map<RefCountPtr<TextureClass>, Rva0094D370Value, _STL::less<RefCountPtr<TextureClass> >, _STL::allocator<_STL::pair<const RefCountPtr<TextureClass>, Rva0094D370Value> > > Rva0094D370Map;

// ??A?$map@V?$RefCountPtr@VTextureClass@@@@URva0094D370Value@@U?$less@V?$RefCountPtr@VTextureClass@@@@@_STL@@V?$allocator@U?$pair@$$CBV?$RefCountPtr@VTextureClass@@@@URva0094D370Value@@@_STL@@@4@@_STL@@QAEAAURva0094D370Value@@ABV?$RefCountPtr@VTextureClass@@@@@Z
template Rva0094D370Value &Rva0094D370Map::operator[](
	const RefCountPtr<TextureClass> &key);
