// cl: /O2
// Retail RVA 0x00437460. The wrapper's scalar-destructor operand is ILT
// 0x0001510E, which routes to the matched destructor at 0x004368F0.
void operator delete[](void *block);

class StringInfo
{
public:
    ~StringInfo();
private:
    unsigned char m_data[0x08];
};

StringInfo *MakeStringInfoArray()
{ return new StringInfo[2]; }

void DeleteStringInfoArray(StringInfo *array)
{ delete[] array; }
