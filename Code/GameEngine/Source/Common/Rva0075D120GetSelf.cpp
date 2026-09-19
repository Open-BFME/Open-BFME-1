// The carved body at 0x0075D120 returns its receiver without semantic owner evidence.
class Rva0075D120Self
{
public:
    void *getSelf();
};

void *Rva0075D120Self::getSelf()
{
    return this;
}
