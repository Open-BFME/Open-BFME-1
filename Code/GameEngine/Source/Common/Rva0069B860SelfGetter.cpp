class Rva0069B860SelfGetter
{
public:
	void *get() const;
};

void *Rva0069B860SelfGetter::get() const
{
	return (void *)this;
}
