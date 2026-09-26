// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

#define BFME_FORWARD_SEVEN(ADDR, SLOT)                                         \
class Rva##ADDR##VirtualForwarder                                              \
{                                                                             \
public:                                                                       \
    virtual void slot00(void *, int, int, int, int, int, int);                 \
    virtual void slot01(void *, int, int, int, int, int, int);                 \
    virtual void slot02(void *, int, int, int, int, int, int);                 \
    virtual void slot03(void *, int, int, int, int, int, int);                 \
    void *forward_##ADDR(void *, int, int, int, int, int, int);                \
};                                                                            \
void *Rva##ADDR##VirtualForwarder::forward_##ADDR(                             \
    void *result, int a, int b, int c, int d, int e, int f)                   \
{                                                                             \
    slot##SLOT(result, a, b, c, d, e, f);                                     \
    return result;                                                            \
}
BFME_FORWARD_SEVEN(00845500, 03)
BFME_FORWARD_SEVEN(00845530, 02)

#define BFME_FORWARD_DOUBLE(ADDR, SLOT)                                        \
class Rva##ADDR##VirtualForwarder                                              \
{                                                                             \
public:                                                                       \
    virtual void slot00(void *, int, int, int, int, double);                  \
    virtual void slot01(void *, int, int, int, int, double);                  \
    virtual void slot02(void *, int, int, int, int, double);                  \
    virtual void slot03(void *, int, int, int, int, double);                  \
    virtual void slot04(void *, int, int, int, int, double);                  \
    virtual void slot05(void *, int, int, int, int, double);                  \
    void *forward_##ADDR(void *, int, int, int, int, double);                 \
};                                                                            \
void *Rva##ADDR##VirtualForwarder::forward_##ADDR(                             \
    void *result, int a, int b, int c, int d, double value)                   \
{                                                                             \
    slot##SLOT(result, a, b, c, d, value);                                    \
    return result;                                                            \
}
BFME_FORWARD_DOUBLE(00845560, 05)
BFME_FORWARD_DOUBLE(00845590, 04)

class Rva008455C0VirtualForwarder
{
public:
    virtual void slot00(void *, int, int, int, int, int);
    virtual void slot01(void *, int, int, int, int, int);
    void *forward_008455C0(void *, int, int, int, int, int);
};
void *Rva008455C0VirtualForwarder::forward_008455C0(
    void *result, int a, int b, int c, int d, int e)
{
    slot01(result, a, b, c, d, e);
    return result;
}
