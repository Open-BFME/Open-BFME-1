// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


bool GetStringFromRegistry( AsciiString path, AsciiString key, AsciiString &value );

class BfmeAptScreenOnlineLogin
{
public:
	bool _bfme_loginGadgetsState();
};

bool BfmeAptScreenOnlineLogin::_bfme_loginGadgetsState()
{
	AsciiString registeredValue;
	GetStringFromRegistry( "", "Registered", registeredValue );
	return ((const StringBase<char> *)&registeredValue)->compareNoCase( "true" ) == 0;
}
