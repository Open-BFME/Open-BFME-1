// cl: /DNDEBUG /MD /EHsc

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);
private:
	unsigned char m_data[0x0C];
};

class BfmeAttributeP128Vector
{
public:
	BfmeAttributeP128Vector &operator=(const BfmeAttributeP128Vector &other);
private:
	unsigned char m_data[0x0C];
};

extern bool bfmeAttributeStringVectorsEqual(const Rva0076F980Mid *left,
	const Rva0076F980Mid *right);
extern bool bfmeAttributeP128VectorsEqual(const BfmeAttributeP128Vector *left,
	const BfmeAttributeP128Vector *right);

struct BfmeAttributePlainBlock
{
	bool operator==(const BfmeAttributePlainBlock &other) const;
	unsigned int m_values[6];
};

struct Gen_t_0039e9d0_p128pod
{
	Rva0076F980Mid m_names;
	Rva0076F980Mid m_values;
	BfmeAttributeP128Vector m_lists[4];
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	unsigned int m_kind;
	unsigned int m_index;
	bool m_enabled;
	unsigned char m_pad[3];
	unsigned int m_useCount;

	Gen_t_0039e9d0_p128pod &operator=(const Gen_t_0039e9d0_p128pod &other);
	unsigned char operator==(const Gen_t_0039e9d0_p128pod &other) const;
};

Gen_t_0039e9d0_p128pod &Gen_t_0039e9d0_p128pod::operator=(
		const Gen_t_0039e9d0_p128pod &other)
{
	m_names = other.m_names;
	m_values = other.m_values;
	m_lists[0] = other.m_lists[0];
	m_lists[1] = other.m_lists[1];
	m_lists[2] = other.m_lists[2];
	m_lists[3] = other.m_lists[3];
	m_firstPlain = other.m_firstPlain;
	m_secondPlain = other.m_secondPlain;
	m_kind = other.m_kind;
	m_index = other.m_index;
	m_enabled = other.m_enabled;
	m_useCount = other.m_useCount;
	return *this;
}

unsigned char Gen_t_0039e9d0_p128pod::operator==(
		const Gen_t_0039e9d0_p128pod &other) const
{
	return m_kind == other.m_kind
		&& m_enabled == other.m_enabled
		&& m_index == other.m_index
		&& m_firstPlain == other.m_firstPlain
		&& m_secondPlain == other.m_secondPlain
		&& bfmeAttributeP128VectorsEqual(&m_lists[2], &other.m_lists[2])
		&& bfmeAttributeP128VectorsEqual(&m_lists[3], &other.m_lists[3])
		&& bfmeAttributeP128VectorsEqual(&m_lists[0], &other.m_lists[0])
		&& bfmeAttributeP128VectorsEqual(&m_lists[1], &other.m_lists[1])
		&& bfmeAttributeStringVectorsEqual(&m_names, &other.m_names)
		&& bfmeAttributeStringVectorsEqual(&m_values, &other.m_values);
}

namespace _STL
{
struct random_access_iterator_tag {};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
		OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	Distance count = last - first;
	for (; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_0039e9d0_p128pod *__copy_backward(
	Gen_t_0039e9d0_p128pod *, Gen_t_0039e9d0_p128pod *,
	Gen_t_0039e9d0_p128pod *, const random_access_iterator_tag &, int *);
}

struct BfmeAttributeEntryPool
{
	Gen_t_0039e9d0_p128pod *m_begin;
	Gen_t_0039e9d0_p128pod *m_end;
};

extern BfmeAttributeEntryPool TheBfmeAttributePool;
extern void bfmeDestroyAttributeEntry(Gen_t_0039e9d0_p128pod *entry);

void bfmeDestroyAttributePoolEntries()
{
	int count = TheBfmeAttributePool.m_end - TheBfmeAttributePool.m_begin;
	for (int i = 0; i < count; ++i)
		bfmeDestroyAttributeEntry(TheBfmeAttributePool.m_begin + i);
}
