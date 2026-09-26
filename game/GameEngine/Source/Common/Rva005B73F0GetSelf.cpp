// The carved body at 0x005B73F0 returns its receiver unchanged.
// No evidence proves a semantic owner, so the class name keeps the retail address.
class Rva005B73F0
{
public:
	void *getSelf();
};

void *Rva005B73F0::getSelf()
{
	return this;
}
