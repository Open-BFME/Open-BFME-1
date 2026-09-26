// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include <vector>

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	~BFMERetailAsciiString();
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class BfmeOtherX
{
public:
	BfmeOtherX() : m_value24( 0 ), m_value28( 0 ), m_value2c( 0 ) {}
	~BfmeOtherX();
	int m_value24;
	int m_value28;
	int m_value2c;
};

// The BFME TerrainType grew past the Zero Hour header.  This local declaration
// keeps the constructor's members at the offsets used by TerrainTypes.cpp's
// existing collection methods.
enum TerrainClass
{
	TERRAIN_NONE = 0
};

class TerrainType
{
public:
	TerrainType( void );
	virtual ~TerrainType();

private:
	BFMERetailAsciiString m_name;               // +0x04
	BFMERetailAsciiString m_texture;            // +0x08
	bool m_blendEdgeTexture;                    // +0x0C
	_STL::vector<TerrainClass> m_class;        // +0x10
	bool m_restrictConstruction;                // +0x1C
	TerrainType *m_next;                        // +0x20
	BfmeOtherX m_extra24;                       // +0x24
};

TerrainType::TerrainType( void )
{
	m_name.clear();
	m_texture.clear();
	m_blendEdgeTexture = false;
	m_class.push_back( TERRAIN_NONE );
	m_restrictConstruction = false;
	m_next = 0;
}
