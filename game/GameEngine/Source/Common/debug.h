#pragma once

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
int rva0088C4E0PostStaticInitLookup();

class Debug {
    // retail PostStaticInit@Debug@@CAXXZ (0x0088AF60) is private; the 0x0088C4E0
    // resolver takes its address as a fallback.
    friend int rva0088C4E0PostStaticInitLookup();
    static void PostStaticInit();

public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);

private:
    static Debug *PreStaticInit();
};
