// Retail 0x0029BD80: scan the linked list at this+0x08 and apply the first
// matching payload through virtual slot 0x20.

class Rva0029BD80Helper
{
public:
	char query(void *value);
};

struct Rva0029BD80Node
{
	unsigned char m_pad00[4];
	int m_type;
	void *m_key;
	unsigned char m_pad0c[4];
	void *m_payload;
	unsigned char m_pad14[0x28];
	Rva0029BD80Node *m_next;
};

class Rva0029BD80
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void applyPayload(void *payload);

	void find(Rva0029BD80Helper *helper);

private:
	void *m_pad04;
	Rva0029BD80Node *m_head;
};

extern void j_0003e80b();

typedef char (Rva0029BD80Helper::*Rva0029BD80Query)(void *);

static __forceinline char rva0029BD80Query(Rva0029BD80Helper *helper, void *value)
{
	union { void (*raw)(); Rva0029BD80Query member; } fn;
	fn.raw = j_0003e80b;
	return (reinterpret_cast<Rva0029BD80Helper *>(helper)->*fn.member)(value);
}

void Rva0029BD80::find(Rva0029BD80Helper *helper)
{
	Rva0029BD80Node *node = m_head;
	if (node == 0)
		return;
	do
	{
		int type = node->m_type;
		if (type == 1 || type == 3)
		{
			if (rva0029BD80Query(helper, node->m_key))
			{
				applyPayload(node->m_payload);
				return;
			}
		}
		node = node->m_next;
	} while (node != 0);
}
