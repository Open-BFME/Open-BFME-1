// The carved body returns this unchanged. No caller or class table names the
// owner so the helper keeps its address-derived identity.

class Rva006915B0Self
{
public:
	void *get();
};

void *Rva006915B0Self::get()
{
	return this;
}
