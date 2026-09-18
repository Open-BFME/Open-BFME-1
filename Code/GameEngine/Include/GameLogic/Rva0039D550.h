#ifndef BFME_RVA0039D550_H
#define BFME_RVA0039D550_H

// Four-byte indexed-handle ABI view. The original C++ type name is unknown.
// The destructor at retail RVA 0x0039D550 reads the index, releases the
// entry at pool 0x012F1000 + index*0x88, and marks the handle 0xffffffff.
// Per-owner declarations retain the independently observed member offsets.
class Rva0039D550
{
public:
    ~Rva0039D550();

private:
    unsigned int m_index;
};

#endif
