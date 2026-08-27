// Open-BFME: field store followed by notification reconstructed from retail RVA 0x001BF2E0.

void j_0002f0a4();

class Rva001BF2E0Source
{
public:
    void setAndNotify(int value);

private:
    unsigned char m_padding[0x370];
    int m_value;
};

void Rva001BF2E0Source::setAndNotify(int value)
{
    m_value = value;
    j_0002f0a4();
}
