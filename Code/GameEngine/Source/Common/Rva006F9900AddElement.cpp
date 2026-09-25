// cl: /DNDEBUG /MD /O2 /EHsc

// Retail 0x006F9A90. Adds a floor element for a drawable to the owner whose
// sentinel list at +0x20 is searched by Rva006F9900Owner::find (0x006F9900).
// The element type is BaseHeightMapFloorElement: the matched BaseHeightMap
// +0x30A4 cleanup (0x006F9050) destroys the same list's payloads through the
// same destructor (0x006F8290) this body calls on its failure path.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class Alloc = allocator<T> > class list
{
public:
	void push_front(const T &value);
	void push_back(const T &value);
	unsigned int size() const;

private:
	void *m_node;
};
}

class Drawable;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void vf00() = 0;
	virtual void vf04() = 0;
	virtual void vf08() = 0;
	virtual void vf0c() = 0;
	virtual void vf10() = 0;
	virtual void vf14() = 0;
	virtual void vf18() = 0;
	virtual void vf1c() = 0;
	virtual void vf20() = 0;
	virtual void vf24() = 0;
	virtual void vf28() = 0;
	virtual Drawable *findDrawableByID(unsigned int id) = 0;
};

extern GameClient *TheGameClient;

class BaseHeightMapFloorElement
{
public:
	BaseHeightMapFloorElement() throw();
	virtual ~BaseHeightMapFloorElement();

	void apply006F8340(Drawable *drawable, AsciiString name,
		unsigned char atFront, unsigned char flag);
	bool init006F8A60();

private:
	unsigned char m_body[0x94];
};

class Rva006F9900Entry;

class Rva006F9900Owner
{
public:
	Rva006F9900Entry *find(int kind, AsciiString name);
	BaseHeightMapFloorElement *addElement006F9A90(int id, AsciiString name,
		unsigned char atFront, unsigned char flag);

private:
	char m_beforeList[0x20];
	_STL::list<BaseHeightMapFloorElement *> m_elements;
	int m_count;
	bool m_enabled;
	char m_pad29;
	bool m_changed;
};

BaseHeightMapFloorElement *Rva006F9900Owner::addElement006F9A90(int id,
	AsciiString name, unsigned char atFront, unsigned char flag)
{
	Drawable *drawable = TheGameClient ? TheGameClient->findDrawableByID(id) : 0;
	if (m_count < 450 && drawable != 0 && m_enabled && find(id, name) == 0)
	{
		BaseHeightMapFloorElement *element = new BaseHeightMapFloorElement;
		BaseHeightMapFloorElement *entry = element;
		element->apply006F8340(drawable, name, atFront, flag);
		if (element->init006F8A60())
		{
			if (atFront)
				m_elements.push_front(entry);
			else
				m_elements.push_back(entry);
			m_count = m_elements.size();
			m_changed = true;
			return element;
		}
		if (element)
		{
			element->BaseHeightMapFloorElement::~BaseHeightMapFloorElement();
			operator delete(element);
		}
	}
	return 0;
}
