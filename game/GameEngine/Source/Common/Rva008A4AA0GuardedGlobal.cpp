// Open-BFME: guarded global virtual dispatch reconstructed from retail RVA 0x008A4AA0.

class Rva008A4AA0Target
{
public:
    virtual void slot00();
    virtual void dispatch();
};

class Rva00899FC0;
extern Rva00899FC0 *g_rva01337abc;

void Rva008A4AA0Invoke()
{
    Rva008A4AA0Target *target =
        reinterpret_cast<Rva008A4AA0Target *>(g_rva01337abc);
    if (target)
    {
        target->dispatch();
        g_rva01337abc = 0;
    }
}
