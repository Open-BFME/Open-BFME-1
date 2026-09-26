// cl: /DNDEBUG /MD -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader
// RVA 0x00825D80: clear 274 short counters through the first pointer field.
// The class identity has no matched caller, so this keeps its address.
#include <string.h>

struct Rva00825D80Owner
{
    unsigned short *m_counters;
    void clearStats();
};

void Rva00825D80Owner::clearStats()
{
    memset(m_counters, 0, 274 * sizeof(unsigned short));
}
