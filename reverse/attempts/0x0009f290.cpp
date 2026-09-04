// ?insertCopies@Rva0009F090WideListData@@QAEXPAURva0009F090WideNode@@IABVUnicodeString@@@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
	void *m_data;
};

struct Rva0009F090WideNode
{
	Rva0009F090WideNode *next;
	Rva0009F090WideNode *previous;
	UnicodeString value;
};

void *__cdecl Rva0009F290Allocate(unsigned int bytes);
void __cdecl Rva0009F290Construct(UnicodeString *destination, const UnicodeString &value);

class Rva0009F090WideListData
{
public:
	void insertCopies(Rva0009F090WideNode *position, unsigned int count, const UnicodeString &value);

private:
	Rva0009F090WideNode *m_head;
};

void Rva0009F090WideListData::insertCopies(
	Rva0009F090WideNode *position,
	unsigned int count,
	const UnicodeString &value)
{
	unsigned int n = count;
	if (n > 0)
	{
		const UnicodeString *v = &value;
		Rva0009F090WideNode *p = position;
		do
		{
			Rva0009F090WideNode *node =
				(Rva0009F090WideNode *)Rva0009F290Allocate(sizeof(Rva0009F090WideNode));
			Rva0009F290Construct(&node->value, *v);
			Rva0009F090WideNode *previous = p->previous;
			node->next = p;
			node->previous = previous;
			previous->next = node;
			p->previous = node;
			--n;
		} while (n);
	}
}
