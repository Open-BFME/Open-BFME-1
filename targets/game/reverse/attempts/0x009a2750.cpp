// ?merge@Rva009A2750Owner@@QAEXXZ
// partial score=0.428261 date=2026-09-28
// Address-preserving bottom-up endpoint-list merge at 0x009A2750.
struct Rva009A2750Endpoint {
    Rva009A2750Endpoint *prev, *next;
    void *field08;
    unsigned field0c;
    float value;
};
struct Rva009A2750Run {
    Rva009A2750Endpoint *head, *tail;
    unsigned count;
};
class Rva009A2750Owner {
public:
    char pad00[0xc];
    Rva009A2750Endpoint *heads[3];
    char pad18[0xc068-0x18];
    unsigned fieldc068;
    void merge();
};
void Rva009A2750Owner::merge()
{
    for (unsigned axis=0; axis<fieldc068; ++axis) {
        Rva009A2750Run runs[4];
        runs[1].count=0;
        runs[0].count=0;
        runs[0].head=0;
        unsigned slot=0;
        Rva009A2750Endpoint *p=heads[axis];
        while(p) {
            Rva009A2750Endpoint *next=p->next;
            p->next=runs[slot].head;
            runs[slot].head=p;
            ++runs[slot].count;
            slot ^= 1;
            p=next;
        }
        unsigned input=0;
        unsigned width=1;
        while(runs[input+1].count) {
            Rva009A2750Run *left=&runs[input];
            Rva009A2750Run *right=&runs[input+1];
            input ^= 2;
            runs[input+1].count=0;
            runs[input].count=0;
            unsigned out=input;
            while(left->count) {
                unsigned a=width,b=width;
                Rva009A2750Run *dest=&runs[out];
                for (;;) {
                    Rva009A2750Run *from;
                    if(a && left->count) {
                        if(b && right->count && left->head->value > right->head->value) {
                            from=right; --b;
                        } else {
                            from=left; --a;
                        }
                    } else if(b && right->count) {
                        from=right; --b;
                    } else break;
                    --from->count;
                    Rva009A2750Endpoint *node=from->head;
                    from->head=node->next;
                    if(!dest->count) {
                        dest->head=node; dest->tail=node; dest->count=1;
                    } else {
                        dest->tail->next=node; dest->tail=node; ++dest->count;
                    }
                }
                out ^= 1;
            }
            width <<= 1;
        }
        if(runs[input].count > 1) runs[input].tail->next=0;
        heads[axis]=runs[input].head;
        heads[axis]->prev=0;
        Rva009A2750Endpoint *node=heads[axis];
        Rva009A2750Endpoint *next;
        while ((next=node->next)!=0) {
            next->prev=node;
            node=node->next;
        }
    }
}
