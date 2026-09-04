// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/stringinline
//
// BFME expands the W3DTreeBuffer TTreeType record to 0x5C bytes. Its 64-element
// m_treeTypes array is destroyed through the 0x0071EA00 body; 0x0071EAC0 is the
// reciprocal constructor. The vector helpers use Coord2D's matched lifecycle
// bodies at 0x00421710 and 0x0043EAB8.

#include "coord2d.h"
#include "StringInline.h"

class TTreeType
{
public:
	TTreeType();
	~TTreeType();

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

TTreeType::TTreeType()
{
}

TTreeType::~TTreeType()
{
}
