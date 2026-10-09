// cl: /MD
union Rva009B63D0Edge {
    unsigned value;
    struct { unsigned low:8; unsigned high:24; } bytes;
    struct { unsigned leaf:1; unsigned index:7; unsigned rest:24; } fields;
};
struct Rva009B63D0Node {
    Rva009B63D0Edge left;
    Rva009B63D0Edge right;
    unsigned char probability;
};
int Rva009B4600DecodeBool(void *,int);

// ?Rva009B63D0DecodeValue@@YAHPAXPAURva009B63D0Node@@@Z
// Ported from Open BFME 2 Code/Libraries/Source/VP6/Huffman.cpp.
int Rva009B63D0DecodeValue(void *coder,Rva009B63D0Node *tree)
{
    Rva009B63D0Edge edge;
    edge.bytes.low=0;
    do {
        Rva009B63D0Node *node=&tree[edge.fields.index];
        if(Rva009B4600DecodeBool(coder,node->probability)) edge=node->right;
        else edge=node->left;
    } while(!edge.fields.leaf);
    return edge.fields.index;
}

