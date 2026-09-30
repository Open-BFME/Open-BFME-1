void Rva007EB820BoundCallback();

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
    m_callback = &Rva007EB820BoundCallback;
    for (int i = 0; i < 3; ++i)
        m_fields[i] = 0;
}
