// cl: /O2 /DNDEBUG /MD /EHsc

struct Rva0021C380Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva0021C380Object
{
	unsigned char m_pad00[0x94];
	unsigned char m_status;

	const Rva0021C380Coord3D *getPosition() const
	{
		return reinterpret_cast<const Rva0021C380Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}
};

struct Rva0021C380Node
{
	Rva0021C380Node *m_next;
	Rva0021C380Node *m_previous;
	Rva0021C380Object *m_object;
};

struct Rva0021C380List
{
	Rva0021C380Node *m_head;

	struct Iterator
	{
		Rva0021C380Node *m_node;

		Rva0021C380Object *operator*() const
		{
			return m_node->m_object;
		}

		Iterator &operator++()
		{
			m_node = m_node->m_next;
			return *this;
		}

		bool operator!=(const Iterator &other) const
		{
			return m_node != other.m_node;
		}
	};

	Iterator begin() const
	{
		Iterator iterator = { m_head->m_next };
		return iterator;
	}

	Iterator end() const
	{
		Iterator iterator = { m_head };
		return iterator;
	}
};

class Rva0021C380Contain;

extern void j_0003a1a7(void);
extern void j_0003f675(void);

typedef void (Rva0021C380Object::*Rva0021C380SetPosition)(
	const Rva0021C380Coord3D *);
typedef void (Rva0021C380Contain::*Rva0021C380RemoveObject)(
	Rva0021C380Object *, int);

class Rva0021C380Contain
{
public:
	void process(void);

private:
	void *m_vtable;
	unsigned char m_pad04[4];
	Rva0021C380Object *m_object;
	unsigned char m_pad0c[0x2c];
	Rva0021C380List m_first;
	unsigned char m_pad3c[0x980];
	Rva0021C380List m_second;
};

static void Rva0021C380SetPositionCall(
	Rva0021C380Object *object, const Rva0021C380Coord3D *position)
{
	union {
		void (*function)(void);
		Rva0021C380SetPosition member;
	} thunk;
	thunk.function = j_0003a1a7;
	(object->*thunk.member)(position);
}

static void Rva0021C380RemoveObjectCall(
	Rva0021C380Contain *contain, Rva0021C380Object *object, int index)
{
	union {
		void (*function)(void);
		Rva0021C380RemoveObject member;
	} thunk;
	thunk.function = j_0003f675;
	(contain->*thunk.member)(object, index);
}

// ?process@Rva0021C380Contain@@QAEXXZ
void Rva0021C380Contain::process(void)
{
	Rva0021C380List::Iterator iterator = m_first.begin();
	const Rva0021C380Coord3D &position = *m_object->getPosition();
	const unsigned char mask = 0x10;
	if (iterator != m_first.end())
	{
		do
		{
			if (((*iterator)->m_status & mask) != 0)
			{
				Rva0021C380SetPositionCall(*iterator, &position);
				Rva0021C380RemoveObjectCall(this, *iterator, -1);
			}
			++iterator;
		}
		while (iterator != m_first.end());
	}

	for (Rva0021C380List::Iterator iterator = m_second.begin();
		iterator != m_second.end(); ++iterator)
	{
		if (((*iterator)->m_status & mask) != 0)
		{
			Rva0021C380SetPositionCall(*iterator, &position);
			Rva0021C380RemoveObjectCall(this, *iterator, -1);
		}
	}
}
