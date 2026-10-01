// Retail RVA 0x001946E0: 243B; RET8 at +0xF0, INT3 at +0xF3.
// ECX receiver, two integer index words; no callees or relocations.
// Native declared return type and semantic owner are unproved; this view
// selects void and retains the address in both class and record identities.
// The table pointer is at receiver+0x0C. Records have a 16-byte stride
// with signed 16-bit link words at +0/+2; the remaining bytes are opaque.
// Detach both records, then reconnect each at the other position. Swap
// input indices first when the +2 link of a names b, matching the retail
// adjacency path. No semantic member/type names or extra checks are inferred.

struct Rva001946E0Record
{
    short m_at00;
    short m_at02;
    char m_at04[12];
};

class Rva001946E0
{
public:
    void method(int a, int b);
    char m_at00[12];
    Rva001946E0Record *m_at0c;
};

void Rva001946E0::method(int a, int b)
{
    if (a == b)
        return;
    if (m_at0c[a].m_at02 == b)
    {
        int temporary = a;
        a = b;
        b = temporary;
    }

    Rva001946E0Record *first = m_at0c + a;
    Rva001946E0Record *second = m_at0c + b;
    int firstNext = first->m_at02;
    m_at0c[firstNext].m_at00 = first->m_at00;
    m_at0c[first->m_at00].m_at02 = (short)firstNext;
    int secondNext = second->m_at02;
    m_at0c[secondNext].m_at00 = second->m_at00;
    m_at0c[second->m_at00].m_at02 = (short)secondNext;

    first->m_at00 = m_at0c[secondNext].m_at00;
    first->m_at02 = (short)secondNext;
    m_at0c[secondNext].m_at00 = (short)a;
    m_at0c[first->m_at00].m_at02 = (short)a;

    second->m_at00 = m_at0c[firstNext].m_at00;
    second->m_at02 = (short)firstNext;
    m_at0c[firstNext].m_at00 = (short)b;
    m_at0c[second->m_at00].m_at02 = (short)b;
}
