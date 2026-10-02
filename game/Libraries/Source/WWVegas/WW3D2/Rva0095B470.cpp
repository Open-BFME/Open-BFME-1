// Retail RVA 0x0095B470, 129 bytes; leaf with RET 4 at +0x7E and INT3 padding.
// Opaque owner: the motchan binary-search twin suggests placement but does not
// prove which channel owns this out-of-line copy. Keep the address in its name.
// Fields and signed midpoint arithmetic follow the retail loads/instructions.
// The inline address calculation preserves retail MOV ECX,EBX; IMUL ECX,EAX.
struct Rva0095B470 {
    unsigned int m_00, m_04, m_08;
    int m_0c, m_10, m_14;
    unsigned int *m_18;

    unsigned int *rva0095B470Element(int n) { return m_18 + m_0c * n; }
    int method(unsigned int value);
};

int Rva0095B470::method(unsigned int value)
{
    unsigned int *data = m_18;
    int index = m_14;
    if (value >= (data[index] & 0x7fffffffU)) return index;

    int stride = m_0c;
    int left = 0;
    int right = m_10 - 2;
    for (;;) {
        int mid = (right + left) / 2;
        unsigned int *packet = rva0095B470Element(mid);
        if (value < (*packet & 0x7fffffffU)) {
            right = mid;
            continue;
        }
        if (value < (packet[stride] & 0x7fffffffU)) return packet - data;
        if (left ^ mid) {
            left = mid;
            continue;
        }
        ++left;
    }
}
