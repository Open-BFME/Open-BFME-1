// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ??0Image@@QAE@XZ: game/GameEngine/Source/GameClient/System/Image.cpp
// Open-BFME5: Image::Image constructor, retail 0x005D2260.
//
// The parser TU keeps its historical facade so its already-matched body and
// EH funclets remain stable.  This TU carries the real retail inheritance and
// field layout needed by the constructor itself.
#include "Common/AsciiString.h"
#include "Lib/BaseType.h"

// Only the virtual slot matters to this isolated constructor TU.  Keeping a
// tiny local base avoids pulling the pool-glue allocator machinery into the
// parser's translation unit while preserving the retail +0x04 field offsets.
class ImageBase
{
public:
	virtual void anchor();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class Image : public ImageBase
{
public:
	Image( void );
	virtual ~Image() {}

protected:
	AsciiString m_name;
	AsciiString m_filename;
	ICoord2D m_textureSize;
	Region2D m_UVCoords;
	ICoord2D m_imageSize;
	void *m_rawTextureData;
	UnsignedInt m_status;
};

// ??0Image@@QAE@XZ
Image::Image( void )
{
	m_rawTextureData = NULL;
	m_name.clear();
	m_filename.clear();
	m_textureSize.x = 0;
	m_textureSize.y = 0;
	m_UVCoords.lo.x = 0.0f;
	m_UVCoords.lo.y = 0.0f;
	m_UVCoords.hi.x = 1.0f;
	m_UVCoords.hi.y = 1.0f;
	m_imageSize.x = 0;
	m_imageSize.y = 0;
	m_status = 0;
}
