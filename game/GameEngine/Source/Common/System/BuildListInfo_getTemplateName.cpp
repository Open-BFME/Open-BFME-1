// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// BuildListInfo::getTemplateName, retail 0x00161DC0 (32 bytes, ILT 0x00049EFE).
//
// Identity: tools/ilt_oracle.py confirms
// ?getTemplateName@BuildListInfo@@QBE?AVAsciiString@@XZ at ILT 0x00049EFE
// (exact). The body is Zero Hour's SidesList.h accessor
// `AsciiString getTemplateName(void) const { return m_templateName; }`:
// it copy-constructs the AsciiString at this+8 into the hidden return buffer.
// It was ledgered as dup_161dc0, a byte twin of ControlBarObserver.cpp's
// address-named Rva000EE6D0StringAccessor::getString.

#include "Lib/BaseType.h"
#include "Common/AsciiString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SidesList.h
class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	AsciiString getTemplateName() const;

private:
	AsciiString m_buildingName;		///< this+4
	AsciiString m_templateName;		///< this+8
};

AsciiString BuildListInfo::getTemplateName() const
{
	return m_templateName;
}
