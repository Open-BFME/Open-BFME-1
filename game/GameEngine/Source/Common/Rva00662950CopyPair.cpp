// Open-BFME: two-field copy reconstructed from retail RVA 0x00662950.

class Rva00662950Object
{
public:
    void copyTo(void *out);

private:
    char m_pad0[0x0C];
    int m_first;
    int m_second;
};

void Rva00662950Object::copyTo(void *out)
{
    *reinterpret_cast<int *>(out) = m_first;
    *reinterpret_cast<int *>(reinterpret_cast<char *>(out) + 4) = m_second;
}
