// cl: /DNDEBUG /MD
// Clean reconstruction of the positive-state clamp at RVA 0x0024D4E0.

struct Rva0024D4E0State
{
    unsigned char m_prefix[0x3c];
    float m_value;
};

class Rva0024D4E0Owner
{
public:
    Rva0024D4E0State *getState(void);
};

class Rva0024D4E0View
{
public:
    void clampPositiveValue(void);
};

void Rva0024D4E0View::clampPositiveValue(void)
{
    Rva0024D4E0Owner *owner =
        *reinterpret_cast<Rva0024D4E0Owner **>(reinterpret_cast<unsigned char *>(this) - 0xdc);
    Rva0024D4E0State *state = owner->getState();

    if (state && state->m_value > 0.0f)
        state->m_value = 0.0f;
}
