// Retail 0x00605820 (61 bytes): STLport-style tree erasure.
// The direct call at +0x16 goes through ILT 0x82D3 back to this body:
// recurse right (+0x0c), then iterate left (+0x08), destroying +0x10.
// inputs/vendor/stlport/stl/_tree.c::_M_erase independently confirms the algorithm.
// Key/value template identities remain unknown. The payload destructor routes
// through ILT 0x14D8 to the matched Rva00605080Record destructor. That
// eight-byte destruction prefix releases a pointer at +4 and a string at +0;
// the remaining 0x58 bytes are opaque and do not establish a full value type.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class Rva00605080Record
{
public:
    ~Rva00605080Record();
private:
    char m_storage[0x08];
};

struct Rva00605820Node
{
    int m_00;
    int m_04;
    Rva00605820Node *m_left;
    Rva00605820Node *m_right;
    Rva00605080Record m_record; // known destruction prefix at +0x10
    char m_18[0x58]; // remaining node payload is opaque
};

class Rva00605820Tree
{
public:
    void eraseSubtree(Rva00605820Node *node);
};

void Rva00605820Tree::eraseSubtree(Rva00605820Node *node)
{
    while (node)
    {
        eraseSubtree(node->m_right);
        Rva00605820Node *left = node->m_left;
        node->m_record.~Rva00605080Record();
        bfmeDeallocate(node, sizeof(Rva00605820Node));
        node = left;
    }
}
