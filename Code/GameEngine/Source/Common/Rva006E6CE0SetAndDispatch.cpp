// Open-BFME: setter and guarded virtual tail dispatch reconstructed from retail RVA 0x006E6CE0.

class Rva006E6CE0Target
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void notify(int value);
};

class Rva006E6CE0Source
{
public:
    void setAndNotify(int value);

private:
    unsigned char m_padding[0x20];
    int m_value;
    unsigned char m_gap[8];
    Rva006E6CE0Target* m_target;
};

void Rva006E6CE0Source::setAndNotify(int value)
{
    m_value = value;
    if (m_target)
        m_target->notify(value);
}
