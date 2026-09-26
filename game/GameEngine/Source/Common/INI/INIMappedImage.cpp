// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The MappedImage block, plus Image::setName which BFME moves out of the header.
// Zero Hour defines setName inline as m_name = name; retail has it out of line
// at 0x000C2420, in this translation unit rather than Image's -- it adds 4 to
// this, assigns through AsciiString::set, and destroys the by-value parameter,
// which is why it needs an exception frame for 75 bytes of work.
//
// The collection's two methods are already matched --
// ImageCollection::findImageByName and ImageCollection::addImage -- so the only
// names this file adds are Image's constructor and setName, and both are pinned
// by what the parser does with the object: allocate 0x34 bytes, construct, name
// it, hand it to addImage(Image *).
#include "PreRTS.h"
#include "Common/INI.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class Image
{
public:
	Image( void );
	void setName( AsciiString name );

	static const FieldParse m_imageFieldParseTable[];

private:
	void *m_unknown00;
	AsciiString m_name;			// 0x04
	char m_unknown08[ 0x34 - 0x08 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
	void addImage( Image *image );
};

extern ImageCollection *TheMappedImageCollection;

void Image::setName( AsciiString name )
{
	m_name = name;
}

void INI::parseMappedImageDefinition( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	if( TheMappedImageCollection )
	{
		Image *image = const_cast<Image *>( TheMappedImageCollection->findImageByName( name ) );
		if( image == NULL )
		{
			image = new Image;
			image->setName( name );
			TheMappedImageCollection->addImage( image );
		}

		ini->initFromINI( image, Image::m_imageFieldParseTable );
	}
}
