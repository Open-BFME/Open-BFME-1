// The carved body returns its this pointer and has no proven semantic owner.

class Rva005C0C10ReturnThis
{
public:
	void *returnThis();
};

void *Rva005C0C10ReturnThis::returnThis()
{
	return this;
}
