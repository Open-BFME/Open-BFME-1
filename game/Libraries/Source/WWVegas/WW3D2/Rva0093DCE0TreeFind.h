#ifndef RVA0093DCE0_TREE_FIND_H
#define RVA0093DCE0_TREE_FIND_H

struct Rva0093DCE0Node;

// Structural view of the receiver used by retail 0093DCE0. The original
// declaring class and mapped value type are not established by the lookup.
class Rva0093DCE0Tree
{
public:
	Rva0093DCE0Node *find(const unsigned short &key) const;

private:
	Rva0093DCE0Node *m_header;
};

#endif
