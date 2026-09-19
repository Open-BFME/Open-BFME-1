// Retail 0x005DCAE0 returns the first pointer field; no owner identity is proven.
class Rva005DCAE0Object
{
public:
	void *getVtable() const;
};

void *Rva005DCAE0Object::getVtable() const
{
	return *(void * const *)this;
}
