// cl: /DNDEBUG /MD /EHsc

typedef unsigned short WideChar;

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	int compareNoCase(const StringBase<T> &other) const throw()
	{
		const int otherLength = other.m_data ? other.m_data->length : 0;
		const T *const otherText = other.m_data ? other.m_data->text : (const T *)L"";
		const int thisLength = m_data ? m_data->length : 0;
		const T *const thisText = m_data ? m_data->text : (const T *)L"";
		const int commonLength = thisLength < otherLength ? thisLength : otherLength;
		const int result = compareNoCaseRaw(thisText, otherText, commonLength);
		return result == 0 ? thisLength - otherLength : result;
	}

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	void releaseBuffer();
	int compareNoCaseRaw(const T *left, const T *right, int length) const throw();

	Header *m_data;
};

class UnicodeString
{
public:
	~UnicodeString() { ((StringBase<WideChar> *)this)->releaseBuffer(); }

	int compareNoCase(const UnicodeString &other) const throw()
	{
		return ((const StringBase<WideChar> *)this)->compareNoCase(
			*(const StringBase<WideChar> *)&other);
	}

private:
	void *m_data;
};

struct Rva0009F090WideNode
{
	Rva0009F090WideNode *next;
	Rva0009F090WideNode *previous;
	UnicodeString value;
};

class Rva0009F090WideIterator
{
public:
	Rva0009F090WideIterator(Rva0009F090WideNode *node) : m_node(node) {}

	UnicodeString &operator*() const { return m_node->value; }
	Rva0009F090WideIterator &operator++() { m_node = m_node->next; return *this; }
	bool operator!=(const Rva0009F090WideIterator &other) const { return m_node != other.m_node; }

private:
	Rva0009F090WideNode *m_node;
};

class Rva0009F090WideListData
{
public:
	Rva0009F090WideIterator begin() { return Rva0009F090WideIterator(m_head->next); }
	Rva0009F090WideIterator end() { return Rva0009F090WideIterator(m_head); }

private:
	Rva0009F090WideNode *m_head;
};

class Rva0009F090WideList
{
public:
	int findNoCase(UnicodeString value);

private:
	char m_unknown[0x14];
	Rva0009F090WideListData m_values;
};

int Rva0009F090WideList::findNoCase(UnicodeString value)
{
	int index = 0;
	for (Rva0009F090WideIterator it = m_values.begin(); it != m_values.end(); ++it)
	{
		if (value.compareNoCase(*it) == 0)
			return index;

		++index;
	}

	return -1;
}
