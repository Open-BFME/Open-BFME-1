// cl: /O2
// Initialise a virtual logger and its bound callback at retail 0x007EB820.
void Rva007EB820BoundCallback();

class Rva007EB850Log
{
public:
    Rva007EB850Log();
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
private:
    void (*m_callback)();
    unsigned int m_flag;
    unsigned int m_state;
    unsigned int m_count;
};

Rva007EB850Log::Rva007EB850Log()
    : m_callback(&Rva007EB820BoundCallback), m_flag(0), m_state(0), m_count(0)
{
}
