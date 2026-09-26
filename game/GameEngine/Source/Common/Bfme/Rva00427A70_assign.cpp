// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00427A70 (20 bytes).
// Retail copies the source pointer, then increments its +0x28 reference count.

struct Rva00427A70Object
{
	unsigned char m_unmodelled_000[0x28];
	unsigned m_references;
};

class Rva00427A70
{
public:
	void *assign(void **source);

private:
	Rva00427A70Object *m_object;
};

void *Rva00427A70::assign(void **source)
{
	Rva00427A70Object *object = static_cast<Rva00427A70Object *>(*source);
	m_object = object;
	if (object)
		++object->m_references;
	return this;
}
