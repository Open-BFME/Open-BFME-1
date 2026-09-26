// Open-BFME: byte flag guard reconstructed from retail RVA 0x00297370.

class Gen00296F90
{
public:
    void handle();
};

class Rva00297370FlagGuard
{
public:
    void invoke();

private:
    char m_pad[0x65];
    unsigned char m_initialized;
};

void Rva00297370FlagGuard::invoke()
{
    if (m_initialized == 0)
    {
        ((Gen00296F90 *)this)->handle();
    }
}
