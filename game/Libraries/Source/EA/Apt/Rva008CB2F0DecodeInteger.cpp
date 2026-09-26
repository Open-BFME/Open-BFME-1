// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008CB2F0: consume a little-endian integer and append its Apt value.
class AptValue {
public:
    virtual void rva008CB2F0Virtual0();
    unsigned int flags;
};

class AptInteger : public AptValue {
public:
    static AptInteger *Create(int value);
};

struct Rva008CB2F0Stack {
    int count;
    int capacity;
    AptValue **values;
};

void rva008CB2F0DecodeInteger(Rva008CB2F0Stack *state, const unsigned char **cursor)
{
    const unsigned char *p = *cursor;
    int value;
    unsigned char *out = (unsigned char *)&value;
    out[0] = *p++;
    out[1] = *p++;
    out[2] = *p++;
    out[3] = *p++;
    *cursor = p;

    AptValue *result = AptInteger::Create(value);
    state->values[state->count] = result;
    ++state->count;
    if (!((unsigned char)(result->flags >> 30) & 1))
        result->rva008CB2F0Virtual0();
}
