// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 prefix-code tree walker, retail [0x009B6320,0x009B63CF).
// A left leaf does not terminate the walk: the right child is processed too.
// Re-read node indices after output writes, preserving retail alias behavior.
// Distinct shift/add spellings preserve retail branch-local code construction.
struct Rva009B6320Node { unsigned m_first,m_second,m_unused; };
void Rva009B6320DecodeTree(Rva009B6320Node *nodes,int node,int *codes,unsigned char *lengths,int code,int depth)
{
    if(nodes[node].m_first & 1) {
        codes[(nodes[node].m_first>>1)&0x7f]=code<<1;
        lengths[(nodes[node].m_first>>1)&0x7f]=(unsigned char)(depth+1);
    } else {
        Rva009B6320DecodeTree(nodes,(nodes[node].m_first>>1)&0x7f,codes,lengths,code+code,depth+1);
    }
    if(nodes[node].m_second & 1) {
        codes[(nodes[node].m_second>>1)&0x7f]=(code<<1)+1;
        lengths[(nodes[node].m_second>>1)&0x7f]=(unsigned char)(depth+1);
    } else {
        Rva009B6320DecodeTree(nodes,(nodes[node].m_second>>1)&0x7f,codes,lengths,code+code+1,depth+1);
    }
}
