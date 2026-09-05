// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/stringinline
//
// Byte-twin of ??0TTreeType@@QAE@XZ at 0x0071EAC0
// (W3DTreeTypeLifecycle.cpp): identical 113 bytes once relocations are
// masked. Both array-construct calls go through the same generic
// ??_L@YGXPAXIHP6EX0@Z1@Z helper with the same Coord2D ctor/dtor function
// pointers, so the callees do not depend on the class name; no real name is
// provable for this record, so it is claimed address-derived.

#include "coord2d.h"
#include "StringInline.h"

class Rva00735D80TreeType
{
public:
	Rva00735D80TreeType();
	~Rva00735D80TreeType();

private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiString m_modelName;
	AsciiString m_textureName;
	AsciiString m_shadowName;
	AsciiString m_animationName;
};

Rva00735D80TreeType::Rva00735D80TreeType()
{
}

Rva00735D80TreeType::~Rva00735D80TreeType()
{
}
