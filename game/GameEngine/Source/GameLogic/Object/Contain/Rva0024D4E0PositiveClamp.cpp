// cl: /DNDEBUG /MD
// Clean reconstruction of the positive-state clamp at RVA 0x0024D4E0.

struct Rva0024D4E0State
{
    unsigned char m_prefix[0x3c];
    float m_value;
};

// Retail calls ILT 0x00021017 -> 0x001BE010, the matched guarded getter
// ?get@Rva001BE010@@QAEHXZ (R2GuardedFieldGetters.cpp).
class Rva001BE010
{
public:
    int get(void);
};

class Rva0024D4E0View
{
public:
    void clampPositiveValue(void);
};

void Rva0024D4E0View::clampPositiveValue(void)
{
    Rva001BE010 *owner =
        *reinterpret_cast<Rva001BE010 **>(reinterpret_cast<unsigned char *>(this) - 0xdc);
    Rva0024D4E0State *state = reinterpret_cast<Rva0024D4E0State *>(owner->get());

    if (state && state->m_value > 0.0f)
        state->m_value = 0.0f;
}
