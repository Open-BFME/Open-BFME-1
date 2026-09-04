// ?d_007e32e0@@YAXXZ
// partial score=0.9 date=2026-09-03
// ?readUntil@Rva007E32A0State@@QAE_NHH@Z [retail body 0x007E32E0]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
    virtual void v0(void); virtual void v1(void);
    virtual void v2(void); virtual void v3(void);
    virtual void v4(void);
    virtual void set996(int value, int enabled);
    virtual void v6(void); virtual void v7(void);
    virtual void v8(void); virtual void v9(void);
    virtual void v10(void); virtual void v11(void);
    virtual int read996(void);
};

class Rva007E32A0State
{
public:
    char bfmeTry996(int first, int second, char *stop);
    bool readUntil(int first, int second);
    bool forward(int first, int second, int third, int *thirdOut, int enabled);

private:
    char m_pad[4];
    BfmeDev996 *m_dev;
    int m_kind;
    int m_limit;
};

bool Rva007E32A0State::readUntil(int first, int second)
{
    if (m_kind == 6) {
        int secondValue;
        int firstValue;
        char stop = 0;

        if (bfmeTry996((int)&firstValue, (int)&secondValue, &stop)) {
            do {
                if (stop)
                    return false;
                if (firstValue == second)
                    break;

                int value = secondValue - 8;
                if (m_dev->read996() + value > m_limit)
                    return false;
                m_dev->set996(value, 1);

            } while (bfmeTry996((int)&firstValue, (int)&secondValue, &stop));
        }

        if (!stop && firstValue == second) {
            m_dev->set996(-8, 1);
            if (m_kind == 6 && forward(
                    first, second, firstValue, &secondValue, 1))
                return true;
        }
    }
    else {
        return false;
    }
    return false;
}
