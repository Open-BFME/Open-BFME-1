// cl: /O2 /Ob1 /MD /EHsc
// Retail 0x00150D80: 108 instruction bytes followed by a 24-byte destination
// table and a 24-byte message-index table. The complete compiler-produced
// range is 156 bytes; 0xCC padding starts at 0x00150E1C.
// GameLogic's dispatcher at 0x00398F4E calls this through 0x0003511B with
// (0, message, 0x0F). It walks the group's sentinel list at +4. This is shared
// by message 0x437 and 0x44B..0x44E, so it is not named groupCheer.
// Original class/method spelling remains unproven; the name records its RVA.
// BfmeItemRY is the existing object-call ABI view: 0x0002852E routes to the
// matched 0x001BE220 forwarding body, which adjusts this through member 0x1DC.
// Its void* parameters carry opaque 32-bit command operands, not dereferenced
// pointers. No new identity pins or raw instruction bytes are introduced.
class BfmeItemRY
{
public:
    void bfmeDoRY(void *, void *);
};

struct GroupNode150D80
{
    GroupNode150D80 *next;
    GroupNode150D80 *prev;
    BfmeItemRY *object;
};

class Rva00150D80Group
{
public:
    void dispatch(void *unused, int message, void *source);

private:
    unsigned unknown;
    GroupNode150D80 *sentinel;
};

void Rva00150D80Group::dispatch(void *, int message, void *source)
{
    for (GroupNode150D80 *node = sentinel->next;
         node != sentinel; node = node->next)
    {
        BfmeItemRY *object = node->object;
        switch (message)
        {
        case 0x437:
            object->bfmeDoRY((void *)0x6b, source);
            break;
        case 0x44b:
            object->bfmeDoRY((void *)0xae, source);
            break;
        case 0x44c:
            object->bfmeDoRY((void *)0xaf, source);
            break;
        case 0x44d:
            object->bfmeDoRY((void *)0xb0, source);
            break;
        case 0x44e:
            object->bfmeDoRY((void *)0xb1, source);
            break;
        }
    }
}
