// cl: /DNDEBUG /MD /EHsc
// Lazy clone of the 0x5C object at +0xAC into the pointer at +0x108, then
// forward the argument to it.

struct BfmeCopyElementA
{
	BfmeCopyElementA();
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *other);

private:
	char m_bytes[0x5C];
};

class Object
{
public:
	void lazySet(void *arg);

private:
	char m_pad[0xAC];
	BfmeCopyElementA m_embedded;
	BfmeCopyElementA *m_ptr;
};

void Object::lazySet(void *arg)
{
	if (m_ptr == &m_embedded)
		m_ptr = new BfmeCopyElementA;
	m_ptr->bfmeAssign((BfmeCopyElementA *)arg);
}
