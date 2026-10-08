// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class Object;

// The nested call goes through ILT 0x000160D1 to 0x001D6810, the matched
// ObjectCreationList::createInternal body.
class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
};

class Rva002D6EB0Parent
{
private:
	char m_pad00[8];

public:
	ObjectCreationList *m_nested;
};

class Rva002D6EB0
{
public:
	void update();

private:
	char m_pad00[0x0C];
	Rva002D6EB0Parent *m_parent;
	const Object *m_forwarded;
};

void Rva002D6EB0::update()
{
	Rva002D6EB0Parent *parent = m_parent;
	if (parent->m_nested != 0)
		parent->m_nested->createInternal(m_forwarded, 0, 0);
}
