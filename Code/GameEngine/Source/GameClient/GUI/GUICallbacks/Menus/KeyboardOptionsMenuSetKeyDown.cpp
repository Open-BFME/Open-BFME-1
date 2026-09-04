// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: KeyboardOptionsMenu::setKeyDown, retail 0x004C9390.

// Keep the complete BFME include surface available, but reserve the retail
// StringBase name for the narrow Unicode facade below.  The source headers'
// StringBase is only needed by their unrelated ASCII shims in this TU.
#define UNICODESTRING_H
#define StringBase BfmeHeaderStringBase
#include "string_base.h"
#undef StringBase

class AsciiString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	StringBase() : m_data( 0 ) {}
	int compare( const StringBase<T> &that ) const throw();
	int compareNoCase( const StringBase<T> &that ) const;

private:
	StringBase( const StringBase<T> &that );
	~StringBase();
	void *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
};

inline bool operator==( const UnicodeString &a, const UnicodeString &b )
{
	return ((const StringBase<unsigned short> *)&a)->compare( *(const StringBase<unsigned short> *)&b ) == 0;
}

#define StringBase BfmeHeaderStringBase
#include "PreRTS.h"
#undef StringBase

#include "GameClient/GameText.h"

Bool shiftDown = false;
Bool altDown = false;
Bool ctrlDown = false;

void setKeyDown( UnicodeString mod, Bool b )
{
	if( mod.compare( TheGameText->fetch( "KEYBOARD:Shift+" ) ) == 0 )
		shiftDown = b;
	else
	{
		if( mod.compare( TheGameText->fetch( "KEYBOARD:Ctrl+" ) ) == 0 )
			ctrlDown = b;
		else
			altDown = b;
	}
}
