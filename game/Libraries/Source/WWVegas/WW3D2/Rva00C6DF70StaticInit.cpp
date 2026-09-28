// cl: /O2 /MD
class VertexMaterialClass;

template <class T>
class SimpleDynVecClass
{
public:
	SimpleDynVecClass(int size = 0);
	virtual ~SimpleDynVecClass();

private:
	void *m_storage[4];
};

static SimpleDynVecClass<VertexMaterialClass *> Rva00C6DF70Global;
