// cl: /O2
// Retail RVA 0x0048D3F0. The wrapper's scalar-destructor operand is ILT
// 0x0003B304, which routes to the matched destructor at 0x0005EEA0.
void operator delete[](void *block);

class UnicodeString
{
public:
    ~UnicodeString();
private:
    unsigned char m_data[0x04];
};

UnicodeString *MakeUnicodeStringArray()
{ return new UnicodeString[2]; }

void DeleteUnicodeStringArray(UnicodeString *array)
{ delete[] array; }
