// Open-BFME: address-derived reconstruction of retail RVA 0x0013CF30.
// The body follows two override links when available, delegates the remainder
// to Overridable::friend_getFinalOverride, and falls back to its owner.  The
// original owning type and method spelling are not currently recovered.

class Overridable
{
public:
    Overridable *friend_getFinalOverride();
    void *memoryPoolVtable;
    Overridable *nextOverride;
};

class Rva0013CF30Owner : public Overridable
{
public:
    Overridable *resolveFinalOverride();
};

Overridable *Rva0013CF30Owner::resolveFinalOverride()
{
    Overridable *result;
    if (nextOverride)
    {
        result = nextOverride->nextOverride
            ? nextOverride->nextOverride->friend_getFinalOverride()
            : nextOverride;
    }
    else
    {
        result = this;
    }

    return result ? result : this;
}
