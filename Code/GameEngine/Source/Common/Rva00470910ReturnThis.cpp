// The carved body at 0x00470910 returns its this pointer.
// No caller or class table proves a semantic owner.
class Rva00470910ReturnThis
{
public:
	void *returnThis();
};

void *Rva00470910ReturnThis::returnThis()
{
	return this;
}
