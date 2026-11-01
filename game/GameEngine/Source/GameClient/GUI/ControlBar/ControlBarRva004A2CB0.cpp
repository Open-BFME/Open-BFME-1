// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x004A2CB0 (576 bytes, thiscall, no stack arguments). Its only caller is
// the carved GameLogic body at 0x00394260, which loads ECX from TheControlBar and
// calls through ILT 0x00002914, so the body is a ControlBar member. It preloads the
// local player's side assets: it walks TheThingFactory's template list (+0x38C next),
// keeps templates with kindof bit 1 whose side string (+0x28) equals the player's
// side (+0x28), walks their command set (+0x2C) with ControlBar::commandSetButtonWalk
// and loads their two button/portrait images, walks the player template's command
// set (+0xA4), then loads the five Radial images from TheMappedImageCollection. No
// matched caller names it, so the name keeps the address.
//
// Shape: the early `return` on a null TheMappedImageCollection (rather than an
// enclosing `if` block) is what puts the side copy at frame +0 and the shared
// string temporary at +4, as in retail.
#include "ascii_string.h"

class Image
{
public:
	void load();
};

class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};
extern ImageCollection *TheMappedImageCollection;

class BfmeHolderBF
{
public:
	void *bfmeResolveBF();
};

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;
};

class ThingTemplate
{
public:
	char m_rva000[ 0x28 ];
	AsciiString m_defaultOwningSide;
	char m_rva02C[ 0xC8 - 0x2C ];
	unsigned int m_kindof[ 3 ];
	char m_rva0D4[ 0x38C - 0xD4 ];
	ThingTemplate *m_nextThingTemplate;

	const Image *getSelectedPortraitImage() const { return ( (const ThingTemplatePortraitShim *)this )->getSelectedPortraitImage(); }
	Image *getRva13EE70Image() { return (Image *)( (BfmeHolderBF *)this )->bfmeResolveBF(); }
	// +0x2C is the command-set name (ZH m_commandSetString; the 59-vote ThingTemplate
	// parse table 0x00C910A0 puts CommandSet there).
	const AsciiString &getCommandSetString() const { return *(const AsciiString *)m_rva02C; }
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }
};

class ThingFactory
{
public:
	char m_rva00[ 8 ];
	ThingTemplate *m_firstTemplate;
	ThingTemplate *firstTemplate() { return m_firstTemplate; }
};
extern ThingFactory *TheThingFactory;

class PlayerTemplate
{
public:
	char m_rva000[ 0xA4 ];
	AsciiString m_rvaA4CommandSet;
};

class Player
{
public:
	char m_rva00[ 4 ];
	const PlayerTemplate *m_playerTemplate;
	char m_rva08[ 0x28 - 8 ];
	AsciiString m_side;
};

class PlayerList
{
public:
	char m_rva00[ 0xC ];
	Player *m_local;
	Player *getLocalPlayer() { return m_local; }
};
extern PlayerList *ThePlayerList;

class ControlBar
{
public:
	void commandSetButtonWalk( const AsciiString &commandSet );
	void rva004A2CB0();
};

void ControlBar::rva004A2CB0()
{
	if( ThePlayerList == 0 || TheThingFactory == 0 )
		return;
	Player *player = ThePlayerList->getLocalPlayer();
	if( player == 0 )
		return;
	AsciiString side = player->m_side;

	for( ThingTemplate *tmplate = TheThingFactory->firstTemplate(); tmplate; tmplate = tmplate->friend_getNextTemplate() )
	{
		if( ( tmplate->m_kindof[ 0 ] & 2 ) == 0 )
			continue;
		if( ( (const StringBase<char> *)&tmplate->m_defaultOwningSide )->compare( *(const StringBase<char> *)&side ) != 0 )
			continue;
		commandSetButtonWalk( tmplate->getCommandSetString() );
		if( tmplate->getSelectedPortraitImage() )
			( (Image *)tmplate->getSelectedPortraitImage() )->load();
		if( tmplate->getRva13EE70Image() )
			tmplate->getRva13EE70Image()->load();
	}

	if( player->m_playerTemplate )
		commandSetButtonWalk( player->m_playerTemplate->m_rvaA4CommandSet );

	if( TheMappedImageCollection == 0 )
		return;
	Image *push = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialPush" ) );
	Image *over = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialOver" ) );
	Image *border = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialBorder" ) );
	Image *clock1 = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialClockOverlay1" ) );
	Image *clock2 = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialClockOverlay2" ) );
	if( push ) push->load();
	if( over ) over->load();
	if( border ) border->load();
	if( clock1 ) clock1->load();
	if( clock2 ) clock2->load();
}
