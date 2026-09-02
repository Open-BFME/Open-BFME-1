struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	void setPosition(const Coord3D *position);
};

struct Rva21E970Data
{
	char gap[0x170];
	bool enabled;
};

struct Rva21E970Node
{
	Rva21E970Node *next;
	Rva21E970Node *previous;
	Object *object;
};

class Rva21E970PositionPropagation
{
public:
	void propagate(void);

private:
	unsigned long unknown;
	Rva21E970Data *m_data;
	Object *m_anchor;
	char m_gap[0x2C];
	Rva21E970Node *m_objects;
};

void Rva21E970PositionPropagation::propagate(void)
{
	if (!m_data->enabled)
		return;

	Rva21E970Node *node = m_objects->next;

	while (node != m_objects) {
		node->object->setPosition((const Coord3D *)((const char *)m_anchor + 0x38));
		node = node->next;
	}
}
