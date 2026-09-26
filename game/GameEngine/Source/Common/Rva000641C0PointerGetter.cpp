// The carved body and its anonymous thunk prove only a pointer-sized field
// getter at this+4. Keep the RVA in the type until an owner is established.
class Rva000641C0PointerGetter
{
public:
	void *get() const;

private:
	void *m_first;
	void *m_value;
};

void *Rva000641C0PointerGetter::get() const
{
	return m_value;
}
