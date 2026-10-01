// Open-BFME: zeroing destructor body reconstructed from retail RVA 0x004ACD70.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef AsciiString BfmeDtorMemberC;

class Rva004ACD70Object : public BfmeDtorMemberC
{
public:
    ~Rva004ACD70Object();
    unsigned char m_padding[0x10];
    int m_value;
};

// ?dup_00580830@@YAXXZ
Rva004ACD70Object::~Rva004ACD70Object()
{
    m_value = 0;
}
