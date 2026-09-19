// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-
// The carved body proves only a this-pointer return.

class Rva0075D3F0Self
{
public:
	void *returnThis();
};

void *Rva0075D3F0Self::returnThis()
{
	return this;
}
