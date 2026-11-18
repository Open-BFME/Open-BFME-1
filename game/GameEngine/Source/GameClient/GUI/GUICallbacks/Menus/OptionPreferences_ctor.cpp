// cl: /DNDEBUG /MD /EHsc
// readable body of ??0OptionPreferences@@QAE@XZ: game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp
// Open-BFME: OptionPreferences::OptionPreferences, retail 0x000904E0, 92 bytes.
//
// The reference's one line. Everything around it is what a constructor costs:
// the base preferences object first, then this class's vtable, then the
// leaf name built in the outgoing argument slot from the literal and handed to
// load -- called directly rather than through the vtable, which is what a
// virtual reached from a constructor comes to.

#include "../../../../../Include/Common/ScalarTypes.h"



#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	UserPreferences(void);					// ILT 0x0004B19B

	virtual ~UserPreferences();
	virtual Bool load(AsciiString filename);		// ILT 0x00014308
	virtual Bool write(void);

private:
	char m_bfme_body[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences(void);
};

OptionPreferences::OptionPreferences( void )
{
	// note, the superclass will put this in the right dir automatically, this is just a leaf name
	load("Options.ini");
}
