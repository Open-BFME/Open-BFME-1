// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

enum ObjectID {};

namespace _STL
{
template <typename T>
class allocator
{
};

template <typename T, typename A = allocator<T> >
class list
{
public:
	void remove(const T &value);
};
}

class Rva002E0970
{
	unsigned char m_pad[8];
	_STL::list<ObjectID> m_ids;

public:
	void removeId(ObjectID id);
};

void Rva002E0970::removeId(ObjectID id)
{
	m_ids.remove(id);
}
