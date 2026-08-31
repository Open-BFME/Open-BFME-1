// cl: /DNDEBUG /MD /EHsc

typedef unsigned short WideChar;

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	__forceinline int compare(const StringBase<T> &other) const throw()
	{
		const int otherLength = other.m_data ? other.m_data->length : 0;
		const T *otherText = other.m_data ? other.m_data->text : (const T *)L"";
		const int thisLength = m_data ? m_data->length : 0;
		const T *thisText = m_data ? m_data->text : (const T *)L"";
		int remaining = thisLength < otherLength ? thisLength : otherLength;
		int result = 0;
		while (remaining > 0)
		{
			if (*thisText != *otherText)
			{
				result = *thisText - *otherText;
				break;
			}
			++thisText;
			++otherText;
			--remaining;
		}
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

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
	UnicodeString(const UnicodeString &other);
	~UnicodeString() { ((StringBase<WideChar> *)this)->releaseBuffer(); }

	int compareNoCase(const UnicodeString &other) const throw()
	{
		return ((const StringBase<WideChar> *)this)->compareNoCase(
			*(const StringBase<WideChar> *)&other);
	}

	__forceinline int compare(const UnicodeString &other) const throw()
	{
		return ((const StringBase<WideChar> *)this)->compare(
			*(const StringBase<WideChar> *)&other);
	}

	void destroyNodeValue();

private:
	void *m_data;
};

struct Rva0009F090WideNode
{
	Rva0009F090WideNode *next;
	Rva0009F090WideNode *previous;
	UnicodeString value;
};

void __cdecl Rva0009F3E0Deallocate(void *memory, unsigned int bytes);

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
	const UnicodeString &front() const { return m_head->next->value; }
	void remove(const UnicodeString &value);

private:
	Rva0009F090WideNode *m_head;
};

void Rva0009F090WideListData::remove(const UnicodeString &value)
{
	Rva0009F090WideNode *const end = m_head;
	Rva0009F090WideNode *node = end->next;
	while (node != end)
	{
		Rva0009F090WideNode *next = node->next;
		if (value.compare(node->value) == 0)
		{
			Rva0009F090WideNode *previous = node->previous;
			previous->next = next;
			next->previous = previous;
			node->value.destroyNodeValue();
			Rva0009F3E0Deallocate(node, sizeof(Rva0009F090WideNode));
		}
		node = next;
	}
}

class Rva0009F090WideList
{
public:
	UnicodeString first() const;
	int findNoCase(UnicodeString value);

private:
	char m_unknown[0x14];
	Rva0009F090WideListData m_values;
};

UnicodeString Rva0009F090WideList::first() const
{
	return m_values.front();
}

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
