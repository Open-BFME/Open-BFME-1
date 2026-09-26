// cl: /DNDEBUG /MD /EHsc

class Rva00537850
{
	unsigned char padding[4];
	void **value;

public:
	void *get() const;
};

void *Rva00537850::get() const
{
	return *value;
}
