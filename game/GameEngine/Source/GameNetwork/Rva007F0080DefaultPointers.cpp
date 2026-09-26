class Rva007F0080Owner
{
public:
    Rva007F0080Owner(void *first, void *second);
    virtual void slot();
private:
    void *m_first;
    void *m_second;
};

Rva007F0080Owner::Rva007F0080Owner(void *first, void *second)
{
    m_first = first ? first : reinterpret_cast<void *>(0x00BEFFE0);
    m_second = second ? second : reinterpret_cast<void *>(0x00BEFFF0);
}
