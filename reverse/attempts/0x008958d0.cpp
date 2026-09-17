// ?find008958D0@Rva00893030Manager@@QAEXPAPAVBfmeDropObjectA@@PAVBfmeStrVKI@@@Z
// partial score=0.94 date=2026-09-08
// Identity correction: 0x00895A00 and 0x00895D30 both pass their
// Rva00893030Manager this pointer in ECX before calling this body.  The
// manager list and BfmeDropObjectA/string layout are witnessed by the
// matched manager remove/destructor sources.  The method name stays
// address-derived because no caller, vtable slot, or literal names it.
extern "C" int memcmp(const void *a, const void *b, unsigned int n);

#pragma intrinsic(memcmp)

struct BfmeStringData3AF0
{
public:
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    unsigned short m_flags;
    char m_data[1];
};

class BfmeStrVKI
{
public:
    BfmeStringData3AF0 *m_data;
};

class BfmeString3AF0
{
public:
    BfmeStringData3AF0 *m_data;
};

class BfmeDropObjectA
{
public:
    int m_refCount;
    BfmeString3AF0 m_string;
};

class Rva00893030Node
{
public:
    BfmeDropObjectA *m_object;
    Rva00893030Node *m_next;
};

__forceinline BfmeStringData3AF0 *loadStringData008958D0(
    BfmeStringData3AF0 *volatile *pp)
{
    return *pp;
}

class Rva00893030Manager
{
public:
    void find008958D0(BfmeDropObjectA **out, BfmeStrVKI *key);

private:
    Rva00893030Node *m_head;
};

void Rva00893030Manager::find008958D0(BfmeDropObjectA **out,
    BfmeStrVKI *key)
{
    Rva00893030Node *n = m_head;
    volatile int r = 0;

    if (n != 0)
    {
        BfmeStringData3AF0 *k = key->m_data;
        int len = k->m_length;

        do
        {
            BfmeStringData3AF0 *s = loadStringData008958D0(
                &n->m_object->m_string.m_data);

            if (len == s->m_length)
            {
                if (k == s || memcmp(k->m_data, s->m_data, len) == 0)
                {
                    BfmeDropObjectA *o = n->m_object;

                    *out = o;

                    if (o != 0)
                        ++o->m_refCount;

					return;
				}
			}

			n = n->m_next;
		}
		while (n != 0);
	}

	*out = 0;
}
