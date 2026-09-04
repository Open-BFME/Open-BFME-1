// ?readUntil@Rva007E32A0State@@QAE_NHH@Z
// retail body 0x007E32E0, 230 bytes
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

class BfmeB996
{
protected:
    char m_pad[4];
    BfmeDev996 *m_dev;
    int m_kind;
    int m_limit;

public:
    char bfmeTry996(int first, int second, char *stop);
};

class Rva007E32A0State : public BfmeB996
{
public:
    bool readUntil(int first, int second);
    bool forward(int first, int second, int third, int *thirdOut, int enabled);

};

bool Rva007E32A0State::readUntil(int first, int second)
{
    if (m_kind == 6) {
        int secondValue;
        int firstValue;
        char stop = 0;
        int secondArgument;
        char found = bfmeTry996((int)&firstValue, (int)&secondValue, &stop);
        secondArgument = second;

        if (found) {
            do {
                if (stop)
                    return false;
                if (firstValue == secondArgument)
                    break;

                int value = secondValue - 8;
                if (m_dev->read996() + value > m_limit)
                    return false;
                m_dev->set996(value, 1);

            } while (bfmeTry996((int)&firstValue, (int)&secondValue, &stop));
        }

        if (!stop && firstValue == secondArgument) {
            m_dev->set996(-8, 1);
            if (m_kind == 6 && forward(
                    first, (int)&firstValue, (int)&secondValue, &second, 1))
                return true;
        }
    }
    else {
        return false;
    }
    return false;
}
