// cl: /O2 /Ob0

class Rva007F01F0
{
    int m_00;
    int m_04;
    int m_08;

public:
    void initialize(int first, int second);
};

extern int bfmeRva012C37F0Value;
extern Rva007F01F0 bfmeRva0130A490Slot;

void bfmeRva00C6C8E0InitializeSlot()
{
    bfmeRva0130A490Slot.initialize(bfmeRva012C37F0Value, 0x011299C8);
}
