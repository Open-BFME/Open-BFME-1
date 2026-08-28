// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// 0x003CDF50:
//
//     INI ini;
//     ini.load( AsciiString( "Data\\INI\\LargeGroupAudio.ini" ), INI_LOAD_OVERWRITE, NULL );
//     m_loaded = TRUE;
//
// WHAT THE BYTES SHOW.  The frame is 0x84C bytes of stack for one local, the
// local is constructed by 0x00851230 and destroyed by 0x008512E0 -- the INI
// default constructor and destructor the tree already matches in
// INIDefaultConstructorThunk.cpp / INIDestructorThunk.cpp -- and between them
// 0x00853A20, INI::load, is called with an AsciiString temporary built from
// "Data\\INI\\LargeGroupAudio.ini", the immediate 1, and a null third argument.
// That is the ordinary INI-file-loading idiom, and this is the twelfth instance
// of it in the ledger.
//
// The one thing that distinguishes it from the others is the store retail makes
// AFTER the load and BEFORE the destructor call: `mov byte ptr [esi+0x34], 1`,
// where esi is the `this` saved on entry.  A one-byte store of the literal 1 is
// a Bool member; its position after the load, not before, is source order,
// because MSVC 7.1 does not move a store across a call.
//
// WHY ITS OWN TRANSLATION UNIT.  Same reason CampaignManager::init has one:
// every INI header in the tree carries an 8K read buffer that makes the class
// roughly 0x2438 bytes, large enough that the frame would take a __chkstk probe
// retail does not have.  BFME's INI is 0x848.  Declaring INI locally keeps that
// size to this function.  The AsciiString is the shim's rather than a
// hand-rolled stand-in: the temporary is passed by value, and only the
// StringBase-backed shim emits `mov [esp+N],esp` before `mov ecx,esp` the way
// retail does.
//
// IDENTITY IS NOT RECOVERED.  "Data\INI\LargeGroupAudio.ini" says what is being
// loaded and nothing in the image names the owner or the member, so the class
// name is address-derived and the member is spelled for what the byte does.
// The 0x34 bytes ahead of it are padding to place that member, NOT a claim
// about the object's layout: only the one offset is established.
#include "Common/AsciiString.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	INI();
	~INI();

	void load(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	char m_storage[0x848];
};

class Rva003CDF50
{
public:
	char m_lead[0x34];
	bool m_loaded;

	void init(void);
};

void Rva003CDF50::init(void)
{
	INI ini;
	ini.load(AsciiString("Data\\INI\\LargeGroupAudio.ini"), INI_LOAD_OVERWRITE, 0);
	m_loaded = true;
}
