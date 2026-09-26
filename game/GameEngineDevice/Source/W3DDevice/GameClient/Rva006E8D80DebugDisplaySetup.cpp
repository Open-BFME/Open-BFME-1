// cl: /DNDEBUG /MD
// Clean reconstruction of the two-call debug-display setup at RVA 0x006E8D80.

class Rva006E8D80DebugDisplay
{
public:
    virtual void slot00(void);
    virtual void slot04(void);
    virtual void slot08(void);
    virtual void slot0c(void);
    virtual void slot10(void);
    virtual void slot14(void);
    virtual void slot18(void);
    virtual void slot1c(void);
    virtual void slot20(void);
    virtual void slot24(void);
    virtual void setColors(int background, unsigned int foreground);
    virtual void slot2c(void);
    virtual void slot30(void);
    virtual void slot34(void);
    virtual void setLayout(int x, int y, int columns, int rows);
};

class Rva006E8D80DisplayOwner
{
public:
    void setupDebugDisplay(void);

private:
    unsigned char m_prefix[0x270];
    Rva006E8D80DebugDisplay *m_debugDisplay;
};

void Rva006E8D80DisplayOwner::setupDebugDisplay(void)
{
    m_debugDisplay->setColors(-1, 0xff000000u);
    m_debugDisplay->setLayout(3, 20, 1, 1);
}
