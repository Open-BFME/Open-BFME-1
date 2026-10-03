// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 0x008B4370: unpack an Apt integer into three float channel setters.
class AptValue
{
public:
    int toInteger() const;
};

class BfmeSlotState1289
{
public:
    void bfmeSetAxis1289(int axis, float value, int enabled);

    char m_padding00[0x2c];
    int m_output2c;
    int m_output30;
    int m_output34;
    char m_padding38[0x60 - 0x38];
    unsigned int m_flags;
};

struct Rva008B4370Owner
{
    char m_padding00[0x20];
    BfmeSlotState1289 *m_state;
};

struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;

AptValue *aptSetPackedChannels008B4370(Rva008B4370Owner *self, int argc)
{
    Rva008AE770Stack& stk = Rva008AE770TheStack;
    AptValue** args = stk.m_rva01338750;
    AptValue *value = args[stk.field00 - 1];
    BfmeSlotState1289 *state = self->m_state;
    if (state)
    {
        int packed = value->toInteger();
        state->bfmeSetAxis1289(8, (float)((packed >> 16) & 0xff), 0);
        state->bfmeSetAxis1289(9, (float)((packed >> 8) & 0xff), 0);
        state->bfmeSetAxis1289(10, (float)(packed & 0xff), 0);
        state->m_output2c = 0;
        state->m_output30 = 0;
        state->m_output34 = 0;
        state->m_flags |= 0x10000;
    }
    return g_bfmeFallbackDB;
}
