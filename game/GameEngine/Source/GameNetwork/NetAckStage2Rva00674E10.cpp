// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail191B entry at674E10. Constructors673950/6739B0 prove the owner.
// Vtable111A4B0+0x0C -> ILT47528 ->674E10; retain the address in the entry name.
// This TU emits only the entry body; it does not construct a vtable.
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
class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
 AsciiString rva00674E10();
 unsigned short m_commandID;
 unsigned char m_originalPlayerID;
 unsigned int m_originalExecutionFrame;
};
AsciiString NetAckStage2CommandMsg::rva00674E10()
{
 AsciiString text;
 text.format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
  NetCommandMsg::getContentsAsAsciiString().str(), m_commandID, m_originalPlayerID, m_originalExecutionFrame);
 return text;
}
