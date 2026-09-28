// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00945FE0 appends the argument to the GenericMultiListClass at
// this+0x34, taking the node only once. The node is null-guarded: a null
// argument returns without touching the list. IDENTITY IS NOT RECOVERED:
// the name keeps its address token.

class MultiListObjectClass
{
public:
	void *m_prev;
	void *m_next;
};

class GenericMultiListClass
{
	friend class Rva00945FE0Box;

protected:
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce = true);

private:
	unsigned char m_head[24];
};

class Rva00945FE0Box
{
public:
	void addTail(MultiListObjectClass *obj);
	char m_pad[0x34];
	GenericMultiListClass m_list;
};

void Rva00945FE0Box::addTail(MultiListObjectClass *obj)
{
	if (obj)
		m_list.Internal_Add_Tail(obj, true);
}
