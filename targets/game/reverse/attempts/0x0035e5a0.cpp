// ?bfmeDoZN@Rva0035E710Owner@@QAEXPAXPAPAUBfmeNodeZN@@0@Z
// partial score=0.4859 date=2026-09-30
// stlport
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /I.
#include "game/GameEngine/Source/Common/Rva0035E510LinkEAT.cpp"
#include "game/GameEngine/Source/Common/BfmeConv1850.cpp"
struct Rva0035E5A0Link { Rva0035E5A0Link *next; int index,extra; };
struct Rva0035E5A0Record { char pad00[0xC];char released,pad0D;short count;struct Rva0035E5A0Entry *first; };
struct Rva0035E5A0Entry { Rva0035E5A0Entry *next;int field04;int *child08,*child0C; };
struct Rva0035E5A0OwnerView { int field00;int *head04,*head08;char table0C[0xC];Rva0035E5A0Record *records; };
void Rva0035E710Owner::bfmeDoZN(void *a,BfmeNodeZN **link,void *what) {
    Rva0035E5A0OwnerView *source=(Rva0035E5A0OwnerView *)a;
    Rva0035E5A0OwnerView *self=(Rva0035E5A0OwnerView *)this;
    Rva0035E5A0Link **slot=(Rva0035E5A0Link **)link;
    Rva0035E5A0Record *record=&source->records[(*slot)->index];
    Rva0035E5A0Entry *entry=record->first;
    if(record->count>(*slot)->extra) { int count=record->count-(*slot)->extra;do {--count;entry=entry->next;} while(count); }
    int *first=entry->child08;entry->child08=0;
    int *second=entry->child0C;entry->child0C=0;
    int index=((BfmeOwnerXQ *)self->table0C)->bfmeMoveXQ((BfmeOwnerXQ *)source->table0C,(*slot)->index);
    if(index!=-1) {
    (*slot)->index=index;(*slot)->extra=self->records[index].count;
    Rva0035E5A0Link *next=(*slot)->next;
    (*slot)->next=*(Rva0035E5A0Link **)what;*(Rva0035E5A0Link **)what=*slot;*slot=next;
    Rva0035E510::BfmeNodeEAT *receiver=(Rva0035E510::BfmeNodeEAT *)this;
    receiver->bfmeLinkEAT((Rva0035E510::BfmeNodeEAT *)source,(int *)&first,(int *)&entry->child08);
    if(first) { int **tail=&source->head04;while(*tail) tail=(int **)*tail;*tail=first; }
    receiver->bfmeRelinkEAT((Rva0035E510::BfmeNodeEAT *)source,(int *)&second,(int *)&entry->child0C);
    if(second) { int **tail=&source->head08;while(*tail) tail=(int **)*tail;*tail=second; }
    } else {
        entry->child08=first;
        entry->child0C=second;
    }
}
