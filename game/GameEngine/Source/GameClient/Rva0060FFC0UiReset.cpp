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

private:
    unsigned char m_prefix[0x28c];
    Rva0060FFC0Optional *m_optional;
};

// 0x00028F92 is an incremental-link thunk (row ?j_00028f92@@YAXXZ,
// game/gen_small/thunks_019.cpp): a tail jump, so the prepare it enters still
// reads this frame's `this` in ECX. The body behind it is unclaimed, so the
// call names the thunk.
extern void j_00028f92(void);

void Rva0060FFC0Owner::resetUiState(void)
{
    ((void (__fastcall *)(Rva0060FFC0Owner *))j_00028f92)(this);

    if (m_optional)
        m_optional->reset();

    TheMouse->setMode(40);
}
