// Open-BFME: conditional byte setter reconstructed from retail RVA 0x0043AD70.

class Rva0043AD70Source
{
public:
    void set(unsigned char value);

private:
    unsigned char m_padding[0x821];
    unsigned char m_value;
};

void Rva0043AD70Source::set(unsigned char value)
{
    if (m_value != value)
        m_value = value;
}
