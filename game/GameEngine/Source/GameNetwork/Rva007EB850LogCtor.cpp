class Rva007EB850Log
{
public:
    Rva007EB850Log();
    virtual void emit();
private:
    void (*m_callback)();
    unsigned int m_fields[3];
};

Rva007EB850Log::Rva007EB850Log()
{
    m_callback = reinterpret_cast<void (*)()>(0x00BEB820);
    for (int i = 0; i < 3; ++i)
        m_fields[i] = 0;
}
