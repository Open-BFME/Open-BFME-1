// Open-BFME: reference-array release reconstructed from retail RVA 0x008A0DA0.

class Rva008A0DA0Reference
{
public:
    virtual void slot00();
    virtual void release();
};

class Rva008A0DA0Owner
{
public:
    void releaseLast();

private:
    int m_count;
    unsigned char m_padding[4];
    Rva008A0DA0Reference** m_references;
};

void Rva008A0DA0Owner::releaseLast()
{
    m_references[m_count - 1]->release();
    --m_count;
}
