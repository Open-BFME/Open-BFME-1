// cl: /DNDEBUG /MD

class Rva005DCBD0Owner
{
public:
	void *get() const;
};

void *Rva005DCBD0Owner::get() const
{
	return *(void * const *)this;
}
