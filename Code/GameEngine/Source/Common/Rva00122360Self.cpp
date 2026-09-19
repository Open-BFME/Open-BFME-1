// cl: /DNDEBUG /MD
// The carved body returns its this pointer and has no proven semantic owner.

class Rva00122360Self
{
public:
	void *getSelf();
};

void *Rva00122360Self::getSelf()
{
	return this;
}
