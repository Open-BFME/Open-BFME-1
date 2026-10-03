// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail201B at675A80; retain address because full owner/method identity is unproven.
// Direct base/string calls prove canonical NetCommandMsg and AsciiString views.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
class NetCommandMsg
{
public:
 virtual ~NetCommandMsg();
 virtual int getSortNumber();
 virtual bool unknownSlot08();
 virtual AsciiString getContentsAsAsciiString();
 char m_pad[0x18];
};
class Rva00675A80 : public NetCommandMsg
{
public:
 AsciiString method();
 AsciiString m_bfmeChallengeZR;
};
AsciiString Rva00675A80::method()
{
 AsciiString text;
 text.format(AsciiString("%s, challenge=%s"),
  NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeChallengeZR.str());
 return text;
}
