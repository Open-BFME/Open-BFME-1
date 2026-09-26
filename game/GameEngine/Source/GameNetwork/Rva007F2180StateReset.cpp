class Rva007F2180State
{
public:
    void reset();
private:
    char m_padding00[0x10];
    unsigned char m_flag10;
    char m_padding11[0x1f];
    unsigned char m_flag30;
    char m_padding31[0x1f];
    unsigned int m_value50;
    unsigned char m_flag54;
    char m_padding55[0xff];
    unsigned int m_value154;
};

void Rva007F2180State::reset()
{
    m_flag10 = 0;
    m_flag30 = 0;
    m_value50 = 0;
    m_flag54 = 0;
    m_value154 = 0;
}
