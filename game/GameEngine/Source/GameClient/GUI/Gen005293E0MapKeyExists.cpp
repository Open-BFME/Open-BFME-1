// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x005293E0, 209 bytes.  This address-derived helper normalizes a
// seven-character map key when the incoming name lacks the retail prefix and
// tests the resulting key against the embedded STL tree.  The second
// parameter is the BFME AsciiString value passed by value; its WWLib header
// keeps the one-word handle and retail copy shape.

#include <set>
#include "ascii_string.h"

typedef _STL::set<AsciiString> Rva006AEE00Tree;

class Gen005293E0Object
{
public:
	char m_prefix[8];
	Rva006AEE00Tree m_tree;
	int m_ready;
};

// ?bfmeGen005293E0@@YA_NPAVGen005293E0Object@@PAX@Z
bool bfmeGen005293E0(Gen005293E0Object *object, void *text)
{
	Rva006AEE00Tree *tree = (Rva006AEE00Tree *)((char *)object + 8);
	if (!*(int *)((char *)tree + 4))
		return true;

	AsciiString key(*(AsciiString *)text);
	StringBase<char> *textView = (StringBase<char> *)text;
	if (!textView->startsWith("Faction", 7))
	{
		((StringBase<char> *)&key)->set("Faction", 7);
		((StringBase<char> *)&key)->concat(textView->str(), textView->getLength());
	}

	void *root = *(void **)tree;
	Rva006AEE00Tree::iterator found = tree->find(key);
	return *(void **)&found != root;
}
