// ?Rva009B60E0BuildTree@@YAXPAUVp6BuildOutput@@PAHH@Z
// partial score=0.65 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
struct Vp6PackedChild { unsigned leaf:1; unsigned index:7; };
struct Vp6BuildOutput { Vp6PackedChild left,right; unsigned char probability; };
struct Vp6BuildEntry { int next,weight; Vp6PackedChild child; };
typedef char CheckChildSize[(sizeof(Vp6PackedChild)==4)?1:-1];
typedef char CheckOutputSize[(sizeof(Vp6BuildOutput)==12)?1:-1];
void Rva009B60E0BuildTree(Vp6BuildOutput *out,int *frequencies,int count)
{
    Vp6BuildEntry entries[64];
    int head=0;
    int root=count-1;
    int i;
    for(i=0;i<count;++i) {
        entries[i].child.index=i;
        entries[i].child.leaf=1;
        if(frequencies[i]==0) frequencies[i]=1;
        entries[i].weight=frequencies[i];
        entries[i].next=-1;
    }
    int freeEntry=count;
    for(i=1;i<count;++i) {
        int cursor=head,previous=head;
        while(cursor!=-1 && entries[i].weight>entries[cursor].weight) {
            previous=cursor;cursor=entries[cursor].next;
        }
        if(cursor==head) head=i;
        else entries[previous].next=i;
        entries[i].next=cursor;
    }
    Vp6BuildEntry *newEntry=entries+freeEntry;
    Vp6BuildOutput *destination=out+root;
    while(entries[head].next!=-1) {
        int first=head;
        int second=entries[first].next;
        int firstWeight=entries[first].weight;
        int weight=firstWeight+entries[second].weight;
        --destination;
        destination->left=entries[first].child;
        destination->right=entries[second].child;
        newEntry->weight=weight;
        newEntry->next=-1;
        destination->probability=(unsigned char)((firstWeight<<8)/weight);
        --root;
        newEntry->child.index=root;
        newEntry->child.leaf=0;
        head=entries[second].next;
        int cursor=head,previous=head;
        while(cursor!=-1 && weight>entries[cursor].weight) {
            previous=cursor;cursor=entries[cursor].next;
        }
        if(cursor==head) head=freeEntry;
        else entries[previous].next=freeEntry;
        newEntry->next=cursor;
        ++freeEntry;
        ++newEntry;
    }
}
