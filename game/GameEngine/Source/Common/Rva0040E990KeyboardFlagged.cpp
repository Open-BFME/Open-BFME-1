// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef bool Bool;

struct Rva0040E990KeySlot
{
    unsigned char m_state;
    unsigned char m_pad1;
    unsigned char m_flags;
    unsigned char m_pad3;
    unsigned int m_pad4;
};

class Rva0040E990Keyboard
{
public:
    virtual void slot000(void);
    virtual void slot004(void);
    virtual void slot008(void);
    virtual void slot00C(void);
    virtual void slot010(void);
    virtual void updateKeys(void);
    unsigned char m_pad4[8];
    Rva0040E990KeySlot *m_begin;
    Rva0040E990KeySlot *m_end;
};

#define TheKeyboard (*(Rva0040E990Keyboard **)0x012F4C50)

Bool rva0040E990(Bool want)
{
    register Bool found = false;
    Rva0040E990Keyboard *keyboard = TheKeyboard;
    keyboard->updateKeys();
    keyboard = TheKeyboard;
    Rva0040E990KeySlot *end = keyboard->m_end;
    Rva0040E990KeySlot *it = keyboard->m_begin;
    if (it != end)
    {
        for (;;)
        {
            if (it->m_state != 1)
                goto next;
            if ((it->m_flags & 1) == 0)
                goto next;
            if (want)
            {
                found = true;
                break;
            }
next:
            it = (Rva0040E990KeySlot *)((char *)it + 8);
            if (it == end)
                break;
        }
    }
    return found;
}
