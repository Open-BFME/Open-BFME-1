// Open-BFME: state initializer reconstructed from retail RVA 0x0095C7F0.

extern int g_Va0133F420;

class Rva0095C7F0State
{
public:
    void initialize(void);

private:
    char m_pad0[0x2C];
    int m_syncTime;
    int m_value30;
    int m_value34;
};

void Rva0095C7F0State::initialize(void)
{
    m_syncTime = g_Va0133F420;
    m_value30 = 0;
    m_value34 = 0;
}
