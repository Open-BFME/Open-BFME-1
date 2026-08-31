// cl: /DNDEBUG /MD
// Clean reconstruction of the UI reset sequence at RVA 0x0060FFC0.

class Rva0060FFC0Optional
{
public:
    void reset(void);
};

class Mouse
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
    virtual void slot28(void);
    virtual void slot2c(void);
    virtual void slot30(void);
    virtual void slot34(void);
    virtual void setMode(int mode);
};

extern Mouse *TheMouse;

class Rva0060FFC0Owner
{
public:
    void resetUiState(void);
    void prepare(void);

private:
    unsigned char m_prefix[0x28c];
    Rva0060FFC0Optional *m_optional;
};

void Rva0060FFC0Owner::resetUiState(void)
{
    prepare();

    if (m_optional)
        m_optional->reset();

    TheMouse->setMode(40);
}
