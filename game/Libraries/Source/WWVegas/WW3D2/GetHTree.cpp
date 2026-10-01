// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Free hierarchy lookup at retail RVA 0x00971810. The asset registry returns
// a counted reference; conversion verifies its HIER tag before tree access.

extern "C" char *strcpy(char *destination, const char *source);
#pragma intrinsic(strcpy)
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *string);

class HTreeClass;

// The shared leaf at RVA 0x009EB7A0 is TextureBaseClass::Release_Ref in the real
// WW3D2 header; the counted owners here release through it. It does not
// identify the HIER prototype as a TextureClass beyond that leaf.
#include "texture.h"

// The registry result owns one reference and is returned through hidden storage.
class Rva009EBCE0AssetReference
{
public:
	Rva009EBCE0AssetReference() : m_object( 0 ) {}
	Rva009EBCE0AssetReference( const Rva009EBCE0AssetReference &that )
		: m_object( that.m_object )
	{
		if ( m_object != 0 )
			++*(unsigned short *)((char *)m_object + 4);
	}
	~Rva009EBCE0AssetReference()
	{
		if ( m_object != 0 )
			((TextureBaseClass *)m_object)->Release_Ref();
	}
private:
	void *m_object;
};

class Vtable0113E7B0HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual int slot10();
	virtual void slot11();

	char m_pad[0x10];
	HTreeClass *m_tree;
};

class Rva00971730HierarchyReference
{
public:
	Rva00971730HierarchyReference(const Rva009EBCE0AssetReference &source);
	~Rva00971730HierarchyReference()
	{
		if (m_ptr != 0)
			((TextureBaseClass *)m_ptr)->Release_Ref();
	}

	Vtable0113E7B0HierarchyPrototype *m_ptr;
};

extern const unsigned short Rva00D3E7ECPrefixWord;
extern const unsigned char Rva00D3E7EEPrefixByte;

// The registry wrapper's historical name is not established.
// The return-by-value ABI supplies hidden storage plus the one explicit name.
extern Rva009EBCE0AssetReference __cdecl
	Rva009EBCE0_GetPrototype( const char *name );

// ?Get_HTree@@YAPAVHTreeClass@@PBD@Z
HTreeClass *Get_HTree(const char *name)
{
	if (name == 0)
		return 0;

	char lookup[512];
	*(unsigned short *)lookup = Rva00D3E7ECPrefixWord;
	lookup[2] = Rva00D3E7EEPrefixByte;
	strcpy(lookup + 2, name);
	_strlwr(lookup);

	Rva00971730HierarchyReference owner(Rva009EBCE0_GetPrototype(lookup));
	if (owner.m_ptr == 0)
		return 0;

	Vtable0113E7B0HierarchyPrototype *object = owner.m_ptr;
	if ((unsigned char)object->slot10() == 0)
		object->slot11();
	return object->m_tree;
}
