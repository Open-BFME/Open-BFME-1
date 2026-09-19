// Retail returns the receiver at 0x0059FD30. No caller or table proves the
// owning class or the method's semantic name.

class Rva0059FD30ReturnThis
{
public:
	void *get();
};

void *Rva0059FD30ReturnThis::get()
{
	return this;
}
