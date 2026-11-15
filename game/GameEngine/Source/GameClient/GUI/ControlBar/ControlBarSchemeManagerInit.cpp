// cl: /DNDEBUG /MD /EHsc
// BFME's compact INI view used by the ControlBar scheme loader.


#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


enum INILoadType { INI_LOAD_OVERWRITE = 1 };
class Xfer;

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	unsigned char m_unmodelled[0x848];
};

struct SchemeNode { SchemeNode *m_next; };

class SchemeIterator
{
public:
	SchemeIterator(SchemeNode *node) : m_node(node) {}
	SchemeNode *m_node;
};

class SchemeList
{
public:
	SchemeIterator begin() const { return SchemeIterator(m_sentinel->m_next); }
	SchemeIterator end() const { return SchemeIterator(m_sentinel); }
	static unsigned int distance(SchemeIterator sentinel, SchemeIterator node)
	{
		unsigned int count = 0;
		while (node.m_node != sentinel.m_node) {
			++count;
			node.m_node = node.m_node->m_next;
		}
		return count;
	}
	unsigned int size() const
	{
		return distance(end(), begin());
	}
private:
	SchemeNode *m_sentinel;
};

class ControlBarSchemeManager
{
public:
	void init();

private:
	unsigned char m_unmodelled[0x0c];
	SchemeList m_schemeList;
};

void ControlBarSchemeManager::init()
{
	INI ini;
	ini.load(AsciiString("Data\\INI\\Default\\ControlBarScheme.ini"), INI_LOAD_OVERWRITE, 0);
	ini.load(AsciiString("Data\\INI\\ControlBarScheme.ini"), INI_LOAD_OVERWRITE, 0);

	if (m_schemeList.size() <= 0)
		return;
}
