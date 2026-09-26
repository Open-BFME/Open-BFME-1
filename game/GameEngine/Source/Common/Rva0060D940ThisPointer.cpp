// The carved body returns its this pointer and has no proven semantic owner.

class Rva0060D940ThisPointer
{
public:
	void *get() const;
};

void *Rva0060D940ThisPointer::get() const
{
	return (void *)this;
}
