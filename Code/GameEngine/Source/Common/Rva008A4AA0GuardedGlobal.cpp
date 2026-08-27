// Open-BFME: guarded global virtual dispatch reconstructed from retail RVA 0x008A4AA0.

class Rva008A4AA0Target
{
public:
    virtual void slot00();
    virtual void dispatch();
};

void Rva008A4AA0Invoke()
{
    Rva008A4AA0Target *target =
        *reinterpret_cast<Rva008A4AA0Target **>(0x01337ABCu);
    if (target)
    {
        target->dispatch();
        *reinterpret_cast<Rva008A4AA0Target **>(0x01337ABCu) = 0;
    }
}
