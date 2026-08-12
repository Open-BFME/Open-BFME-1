// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define DECLARE_TEN_SLOTS(prefix) \
    virtual void slot##prefix##0(); \
    virtual void slot##prefix##1(); \
    virtual void slot##prefix##2(); \
    virtual void slot##prefix##3(); \
    virtual void slot##prefix##4(); \
    virtual void slot##prefix##5(); \
    virtual void slot##prefix##6(); \
    virtual void slot##prefix##7(); \
    virtual void slot##prefix##8(); \
    virtual void slot##prefix##9()

class BfmeMouse_setVisibility
{
public:
    DECLARE_TEN_SLOTS(0);
    DECLARE_TEN_SLOTS(1);
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void applyVisibility(bool, unsigned char *);

    void setVisibility(bool);

private:
    unsigned char padding[0x4d9d];
    unsigned char currentCursor;
    unsigned char currentState;
    unsigned char pendingCursor;
    unsigned char pendingState;
    bool hasPendingState;
};

#undef DECLARE_TEN_SLOTS

// ?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z
void BfmeMouse_setVisibility::setVisibility(bool visible)
{
    if (hasPendingState) {
        currentCursor = pendingCursor;
        currentState = pendingState;
        hasPendingState = false;
    }
    applyVisibility(visible, &currentState);
}
