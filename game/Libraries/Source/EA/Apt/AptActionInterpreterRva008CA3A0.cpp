// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt opcode-table entry 0x66.
// Boundary and ABI evidence: targets/game/reverse/identity_evidence/008CA3A0-boundary.md
#include <math.h>
extern "C" int __cdecl _strcmpi(const char *, const char *);

struct AptStringData
{
    unsigned short m_refs;
    unsigned short m_length;
    unsigned int m_capacity;
    char m_text[1];
};

class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
    float toNumber();
    int toInteger() const;
    bool isUndefined() const { return (m_valueBits >> 15 & 1) == 0; }
    bool GetMaxRefCountHit() const { return (m_valueBits >> 30 & 1) != 0; }
    unsigned int getType() const { return m_valueBits & 0x3f; }
    __forceinline bool isInteger() const { return getType() == 7 && !isUndefined(); }
    bool isFloat() const { return getType() == 6 && !isUndefined(); }
    AptValue *stringValue() { return getType() == 1 ? this : m_indirectValue; }
    AptStringData *stringData() { return m_string; }
private:
    unsigned int m_valueBits;
    union { unsigned char m_boolean; int m_integer; float m_float; AptStringData *m_string; };
    unsigned char m_unmodelled_0C[0x14];
    AptValue *m_indirectValue;
};
class AptBoolean : public AptValue { public: static AptBoolean *Create(bool value); };
class AptActionInterpreter
{
public:
    struct LocalContextT;
    static void _FunctionRva008CA3A0(AptActionInterpreter *, LocalContextT *);
    int m_stackTop;
    int m_stackCapacity;
    AptValue **m_stack;
};
extern AptValue *g_bfmeFallbackDB;
unsigned int AptGetSwfVersion();

// ?_FunctionRva008CA3A0@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008CA3A0(AptActionInterpreter *interpreter, LocalContextT *)
{
    AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
    AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
    int equal = 0;
    if (top->getType() == 19) top = g_bfmeFallbackDB;
    if (under->getType() == 19) under = g_bfmeFallbackDB;
    if (AptGetSwfVersion() == 7)
    {
        if (top->isUndefined()) ++equal;
        if (under->isUndefined()) ++equal;
        if (equal > 0)
        {
            for (int index = 1; index <= 2; ++index)
            {
                AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];
                if (!value->GetMaxRefCountHit()) value->Release();
            }
            interpreter->m_stackTop -= 2;
            AptValue *result = AptBoolean::Create(equal == 2);
            interpreter->m_stack[interpreter->m_stackTop++] = result;
            if (!result->GetMaxRefCountHit()) result->AddRef();
            return;
        }
    }
    if (((top->isInteger() || top->isFloat()) && (under->isInteger() || under->isFloat())) || top->getType() == under->getType())
    {
        switch (top->getType())
        {
        case 1:
        case 42:
        {
            AptValue *topString = top->stringValue();
            AptValue *underString = under->stringValue();
            AptStringData *a = topString->stringData();
            AptStringData *b = underString->stringData();
            if (b->m_length != a->m_length) break;
            if (b != a && _strcmpi(b->m_text, a->m_text) != 0) break;
            equal = 1;
            break;
        }
        case 6:
        {
            float a = top->toNumber();
            if (under->isInteger()) equal = fabs(a - under->toInteger()) < 0.001f;
            else equal = fabs(a - under->toNumber()) < 0.001f;
            break;
        }
        case 5:
        case 7:
        {
            int a = top->toInteger();
            if (under->isInteger()) equal = a == under->toInteger();
            else equal = fabs((float)a - under->toNumber()) < 0.001f;
            break;
        }
        default:
            equal = top == under;
        }
    }
    for (int index = 1; index <= 2; ++index)
    {
        AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];
        if (!value->GetMaxRefCountHit()) value->Release();
    }
    interpreter->m_stackTop -= 2;
    AptValue *result = AptBoolean::Create(equal != 0);
    interpreter->m_stack[interpreter->m_stackTop++] = result;
    if (!result->GetMaxRefCountHit()) result->AddRef();
}
