// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?removeMilitarySubtitle@InGameUI@@UAEXXZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Lift the InGameUI::removeMilitarySubtitle naked dump to clean C++.
//
// Zero Hour's InGameUI.cpp body with one BFME addition. ZH frees only the
// display strings the loop walks; retail frees one more afterwards, the pointer
// at subtitle+0x28, before deleting the record.
//
// BFME also reorders the record. ZH puts an ICoord2D position between the index
// and the array, which would place displayStrings at +0x10; retail's loop starts
// at +0x08 and steps by four, so the array follows the index directly and the
// position is not there.
//
// The leading call goes through the TheInGameUI global rather than this, which
// is what ZH's source literally says -- worth keeping, since a this-> call
// would compile to a different instruction.
//
// The loop compare is `jbe`, unsigned: ZH's `Int i` against an UnsignedInt
// currentDisplayString converts to unsigned, so the ZH declaration is right.
//
// Only the two virtual slots are reconstructed -- clearTooltipsDisabled at
// vtable +0x190 and freeDisplayString at +0x28 -- and the entries ahead of them
// are declared to place them and never defined or called.

typedef int Int;
typedef unsigned int UnsignedInt;

class DisplayString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();

	virtual void freeDisplayString(DisplayString *string);	///< vtable +0x28
};

extern DisplayStringManager *TheDisplayStringManager;		///< retail [0x012F12CC]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void unused000();
	virtual void unused001();
	virtual void unused002();
	virtual void unused003();
	virtual void unused004();
	virtual void unused005();
	virtual void unused006();
	virtual void unused007();
	virtual void unused008();
	virtual void unused009();
	virtual void unused010();
	virtual void unused011();
	virtual void unused012();
	virtual void unused013();
	virtual void unused014();
	virtual void unused015();
	virtual void unused016();
	virtual void unused017();
	virtual void unused018();
	virtual void unused019();
	virtual void unused020();
	virtual void unused021();
	virtual void unused022();
	virtual void unused023();
	virtual void unused024();
	virtual void unused025();
	virtual void unused026();
	virtual void unused027();
	virtual void unused028();
	virtual void unused029();
	virtual void unused030();
	virtual void unused031();
	virtual void unused032();
	virtual void unused033();
	virtual void unused034();
	virtual void unused035();
	virtual void unused036();
	virtual void unused037();
	virtual void unused038();
	virtual void unused039();
	virtual void unused040();
	virtual void unused041();
	virtual void unused042();
	virtual void unused043();
	virtual void unused044();
	virtual void unused045();
	virtual void unused046();
	virtual void unused047();
	virtual void unused048();
	virtual void unused049();
	virtual void unused050();
	virtual void unused051();
	virtual void unused052();
	virtual void unused053();
	virtual void unused054();
	virtual void unused055();
	virtual void unused056();
	virtual void unused057();
	virtual void unused058();
	virtual void unused059();
	virtual void unused060();
	virtual void unused061();
	virtual void unused062();
	virtual void unused063();
	virtual void unused064();
	virtual void unused065();
	virtual void unused066();
	virtual void unused067();
	virtual void unused068();
	virtual void unused069();
	virtual void unused070();
	virtual void unused071();
	virtual void unused072();
	virtual void unused073();
	virtual void unused074();
	virtual void unused075();
	virtual void unused076();
	virtual void unused077();
	virtual void unused078();
	virtual void unused079();
	virtual void unused080();
	virtual void unused081();
	virtual void unused082();
	virtual void unused083();
	virtual void unused084();
	virtual void unused085();
	virtual void unused086();
	virtual void unused087();
	virtual void unused088();
	virtual void unused089();
	virtual void unused090();
	virtual void unused091();
	virtual void unused092();
	virtual void unused093();
	virtual void unused094();
	virtual void unused095();
	virtual void unused096();
	virtual void unused097();
	virtual void unused098();
	virtual void unused099();

	virtual void clearTooltipsDisabled(void);				///< vtable +0x190

	virtual void removeMilitarySubtitle(void);

private:
	enum { MAX_SUBTITLE_LINES = 8 };

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
	struct MilitarySubtitleData
	{
		// declared out of line: without this MSVC inlines the implicit
		// destructor into a direct call of UnicodeString's, where retail
		// calls the record's own destructor through its thunk
		~MilitarySubtitleData();

		UnicodeString subtitle;							///< retail this+0x00
		UnsignedInt index;								///< retail this+0x04
		DisplayString *displayStrings[MAX_SUBTITLE_LINES];	///< retail this+0x08
		DisplayString *blockString;						///< retail this+0x28
		UnsignedInt currentDisplayString;				///< retail this+0x2C
	};

	unsigned char m_unreconstructed_04[0x818 - 4];
	MilitarySubtitleData *m_militarySubtitle;			///< retail this+0x818
};

extern InGameUI *TheInGameUI;							///< retail [0x012F148C]

// ?removeMilitarySubtitle@InGameUI@@UAEXXZ
void InGameUI::removeMilitarySubtitle( void )
{
	// sanity (is there really such a thing in this world?)
	if(!m_militarySubtitle)
		return;

	TheInGameUI->clearTooltipsDisabled();

	// loop through and free up the display strings
	for(Int i = 0; i <= m_militarySubtitle->currentDisplayString; i ++)
	{
		TheDisplayStringManager->freeDisplayString(m_militarySubtitle->displayStrings[i]);
		m_militarySubtitle->displayStrings[i] = 0;
	}

	TheDisplayStringManager->freeDisplayString(m_militarySubtitle->blockString);

	//delete it man!
	delete m_militarySubtitle;
	m_militarySubtitle= 0;
}
