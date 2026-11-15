// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


struct Rva14B630StringRecord
{
    AsciiString text;
    int value;

    Rva14B630StringRecord(const Rva14B630StringRecord &source);
};

// ??0Rva14B630StringRecord@@QAE@ABU0@@Z
Rva14B630StringRecord::Rva14B630StringRecord(const Rva14B630StringRecord &source) :
    text(source.text),
    value(source.value)
{
}
