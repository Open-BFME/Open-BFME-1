// ?d_0089c900@@YAXXZ
// partial score=0.74 date=2026-09-04
typedef unsigned short UnsignedShort;

class BfmeOwnedSound {
public:
    virtual void unused();
    virtual void release();
};

struct BfmeStringBlock {
    UnsignedShort references;
};

extern BfmeStringBlock g_bfmeDefaultString1284;
extern void (__cdecl **g_bfmeStringPool1284)(void *block);
extern void (__cdecl *g_bfmeFreeDWF)(void *storage);

struct BfmeEvaSideSound {
    BfmeStringBlock *name;
    BfmeOwnedSound *sound;
};

class BfmeEvaSideSoundsArray {
public:
    ~BfmeEvaSideSoundsArray();

private:
    int m_count;
    BfmeEvaSideSound *m_elements;
    BfmeOwnedSound *m_owned1;
    BfmeOwnedSound *m_owned2;
};

BfmeEvaSideSoundsArray::~BfmeEvaSideSoundsArray()
{
    int i = 0;
    if (m_owned2 != (BfmeOwnedSound *)i && ((unsigned int)m_owned2 & 1) == 0) {
        m_owned2->release();
        m_owned2 = (BfmeOwnedSound *)i;
    }
    if (m_owned1 != (BfmeOwnedSound *)i && ((unsigned int)m_owned1 & 1) == 0) {
        m_owned1->release();
        m_owned1 = (BfmeOwnedSound *)i;
    }
    if (m_elements != (BfmeEvaSideSound *)i) {
        for (; i < m_count; ++i) {
            BfmeEvaSideSound &entry = m_elements[i];
            if (entry.name != 0) {
                if (entry.name != &g_bfmeDefaultString1284) {
                    BfmeOwnedSound *sound = (BfmeOwnedSound *)((unsigned int)entry.sound & ~1u);
                    if (sound != 0 && ((unsigned int)entry.sound & 1) == 0)
                        sound->release();
                }
                if (--entry.name->references == 0)
                    g_bfmeStringPool1284[1](entry.name);
                entry.name = 0;
            }
        }
        g_bfmeFreeDWF(m_elements);
        m_elements = (BfmeEvaSideSound *)0;
    }
}

// cl: /DNDEBUG /MD /GX- /O2 /Ob2
