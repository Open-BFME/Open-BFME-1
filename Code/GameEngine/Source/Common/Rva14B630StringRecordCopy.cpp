// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    AsciiString(const AsciiString &source);

private:
    void *data;
};

struct Rva14B630StringRecord
{
    AsciiString text;
    int value;

    Rva14B630StringRecord(const Rva14B630StringRecord &source);
};

// ??0Rva14B630StringRecord@@ absent-from-retail
Rva14B630StringRecord::Rva14B630StringRecord(const Rva14B630StringRecord &source) :
    text(source.text),
    value(source.value)
{
}
