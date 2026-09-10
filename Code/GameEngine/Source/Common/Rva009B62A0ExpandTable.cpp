// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 six-bit prefix lookup expansion, retail [9B62A0,9B6314).
// Only the low byte is needed before loading a complete node from the tree.
// Bitfield initialization preserves the unused bits without treating the
// compiler scratch word (allocated with push ecx) as an incoming argument.
// Every index/leaf read uses initialized bits; no raw uninitialized value is read.
union Vp6TreeNode {
    unsigned value;
    struct { unsigned low:8; unsigned high:24; } bytes;
    struct { unsigned leaf:1; unsigned index:7; unsigned rest:24; } fields;
};
void Rva009B62A0ExpandTable(const unsigned *tree, unsigned short *output)
{
    Vp6TreeNode node;
    for (int index=0; index<64; ++index) {
        int prefix=0;
        node.bytes.low=0;
        int bit=6;
        do {
            ++prefix;
            --bit;
            int branch=index>>bit;
            if(branch & 1) node.value=tree[node.fields.index*3+1];
            else node.value=tree[node.fields.index*3];
        } while(!node.fields.leaf && bit>0);
        unsigned result=node.fields.index;
        unsigned low=node.fields.leaf;
        result=(result | (prefix<<11))<<1;
        result|=low;
        output[index]=(unsigned short)result;
    }
}
