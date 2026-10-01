// ?rva003504e0@@YAPAURva003504E0Node@@PAU1@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct Rva003504E0Node { Rva003504E0Node *next; };
static __declspec(noinline) Rva003504E0Node *rva003504e0(Rva003504E0Node *node)
{
    if (node) {
        Rva003504E0Node *next = node->next;
        if (next) {
            do { node = next; next = next->next; } while (next);
        }
    }
    return node;
}
Rva003504E0Node *rva003504e0Caller(Rva003504E0Node *node) { return rva003504e0(node); }
