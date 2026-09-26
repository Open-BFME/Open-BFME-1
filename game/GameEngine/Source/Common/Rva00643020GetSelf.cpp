// The carved body at 0x00643020 returns its receiver without semantic owner evidence.
class Rva00643020Self
{
public:
    void *getSelf();
};

void *Rva00643020Self::getSelf()
{
    return this;
}
