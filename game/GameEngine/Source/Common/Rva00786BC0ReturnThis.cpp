// Retail returns the receiver at 0x00786BC0. No caller proves the owning
// class or the semantic method name.

class Rva00786BC0ReturnThis
{
public:
	void *get();
};

void *Rva00786BC0ReturnThis::get()
{
	return this;
}
