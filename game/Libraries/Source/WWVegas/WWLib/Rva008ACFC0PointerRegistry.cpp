// cl: /O2 /Ob0

class Rva008ACFC0RegisteredObject
{
public:
	virtual void onRegistered(void) = 0;
};

class Rva008ACFC0PointerRegistry
{
	int m_cursor;
	Rva008ACFC0RegisteredObject *m_entries[512];

public:
	void add(Rva008ACFC0RegisteredObject *object);
};

void Rva008ACFC0PointerRegistry::add(Rva008ACFC0RegisteredObject *object)
{
	int index = ++m_cursor;
	while (m_entries[index] != 0) {
		if (index < 511) {
			++index;
		} else {
			index = 0;
		}
	}

	m_entries[index] = object;
	object->onRegistered();
}
