// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

#define BFME_FORWARD_SEVEN(ADDR, SLOT)                                        \
class Rva##ADDR##VirtualForwarder                                             \
{                                                                            \
public:                                                                      \
    virtual void slot00(void *, int, int, int, int, int, int);                \
    virtual void slot01(void *, int, int, int, int, int, int);                \
    virtual void slot02(void *, int, int, int, int, int, int);                \
    virtual void slot03(void *, int, int, int, int, int, int);                \
    void *forward_##ADDR(void *, int, int, int, int, int, int);               \
};                                                                           \
void *Rva##ADDR##VirtualForwarder::forward_##ADDR(                            \
    void *result, int a, int b, int c, int d, int e, int f)                  \
{                                                                            \
    slot##SLOT(result, a, b, c, d, e, f);                                    \
    return result;                                                           \
}

BFME_FORWARD_SEVEN(00845350, 03)
BFME_FORWARD_SEVEN(00845380, 02)

class Rva008453B0VirtualForwarder
{
public:
    virtual void slot00(void *, int, int, int, int, double);
    virtual void slot01(void *, int, int, int, int, double);
    virtual void slot02(void *, int, int, int, int, double);
    virtual void slot03(void *, int, int, int, int, double);
    virtual void slot04(void *, int, int, int, int, double);
    void *forward_008453B0(void *result, int a, int b, int c, int d, double value);
};
void *Rva008453B0VirtualForwarder::forward_008453B0(
    void *result, int a, int b, int c, int d, double value)
{
    slot04(result, a, b, c, d, value);
    return result;
}

class Rva008453E0VirtualForwarder
{
public:
    virtual void slot00(void *, int, int, int, int, int);
    virtual void slot01(void *, int, int, int, int, int);
    void *forward_008453E0(void *, int, int, int, int, int);
};
void *Rva008453E0VirtualForwarder::forward_008453E0(
    void *result, int a, int b, int c, int d, int e)
{
    slot01(result, a, b, c, d, e);
    return result;
}
