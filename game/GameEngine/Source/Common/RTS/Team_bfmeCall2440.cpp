// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Team::bfmeCall2440, retail 0x000F75B0 (86 bytes).
// Team's constructor initializes the 20-byte hash member at +0x1C through
// +0x2C.  This local view preserves that embedded storage and its ABI.
// The operation removes an existing key for mode zero and inserts byte one
// for an absent key in mode one.

#define _STLP_NO_EXCEPTIONS 1

#include "ascii_string.h"

class BfmeTeamCall2440Iterator
{
public:
	void *m_cur;
	void *m_ht;
};

// The +0x1C Team member is an embedded 20-byte AsciiString hash object.  Its
// lookup returns a neutral node pointer; the actual mapped value is exposed
// only by operator[] below.
class Rva000F75B0HashMember
{
public:
    void *find(const AsciiString &key);
    void erase(const BfmeTeamCall2440Iterator &it);
    unsigned char &operator[](const AsciiString &key);

private:
    unsigned char m_opaque[0x14];
};

class Team
{
public:
    void bfmeCall2440(const AsciiString &key, unsigned char mode);
};

// ?bfmeCall2440@Team@@QAEXABVAsciiString@@E@Z
void Team::bfmeCall2440(const AsciiString &key, unsigned char mode)
{
    Rva000F75B0HashMember *values =
        (Rva000F75B0HashMember *)((char *)this + 0x1c);
    void *found = values->find(key);
    if (found != 0)
    {
        if (mode == 0)
        {
            BfmeTeamCall2440Iterator it;
            it.m_cur = found;
            it.m_ht = values;
            values->erase(it);
        }
    }
    else if (mode == 1)
    {
        (*values)[key] = 1;
    }
}
