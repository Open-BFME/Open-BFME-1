// cl: /DNDEBUG /MD
// The carved body returns its this pointer and has no proven semantic owner.

class Rva00122390Self
{
public:
	void *getSelf();
};

void *Rva00122390Self::getSelf()
{
	return this;
}
