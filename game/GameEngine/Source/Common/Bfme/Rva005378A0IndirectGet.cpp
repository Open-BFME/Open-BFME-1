// cl: /DNDEBUG /MD /EHsc

class Rva005378A0
{
	unsigned char padding[4];
	void **value;

public:
	void *get() const;
};

void *Rva005378A0::get() const
{
	return *value;
}
