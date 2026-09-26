class Rva00360AE0SelfGetter
{
public:
	void *get() const;
};

void *Rva00360AE0SelfGetter::get() const
{
	return (void *)this;
}
