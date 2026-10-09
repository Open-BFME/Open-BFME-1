// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B73B0: vtable VA 011371F8; ret 8 and 37-entry switch table.
// Address-derived owner and callback identities; no semantic class is asserted.
struct Rva008B73B0Buffer { unsigned short refs, length; };
struct Rva008B73B0String { Rva008B73B0Buffer *data; };
struct R4Word { const char *name; int value; };
const R4Word *Rva008B60B0(const char *, unsigned);
void *Rva00897640(unsigned);
class Rva00897670HeaderedDelete {
public: static void operator delete(void *, unsigned);
};
class Rva00899FC0 : public Rva00897670HeaderedDelete {
public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    __declspec(noinline) Rva00899FC0(int callback);
    void *vtable;
    unsigned flags;
    char gap08[0x18];
    int callback;
};
struct Rva008B73B0Slot { virtual void slot00(); };
extern Rva00899FC0 *g_Va013383A4;
extern char Va00CB6B20[];
extern Rva00899FC0 *g_Va013383A8;
extern char Va00CB6B40[];
extern Rva00899FC0 *g_Va013383AC;
extern char Va00CB6B60[];
extern Rva00899FC0 *g_Va013383B0;
extern char Va00CB6B80[];
extern Rva00899FC0 *g_Va013383B4;
extern char Va00CB6BA0[];
extern Rva00899FC0 *g_Va013383B8;
extern char Va00CB6BC0[];
extern Rva00899FC0 *g_Va013383BC;
extern char Va00CB6BE0[];
extern Rva00899FC0 *g_Va013383C0;
extern char Va00CB6C00[];
extern Rva00899FC0 *g_Va013383C4;
extern char Va00CB6C20[];
extern Rva00899FC0 *g_Va013383C8;
extern char Va00CB6C30[];
extern Rva00899FC0 *g_Va013383CC;
extern char Va00CB6C50[];
extern Rva00899FC0 *g_Va013383D0;
extern char Va00CB6C70[];
extern Rva00899FC0 *g_Va013383D4;
extern char Va00CB6C90[];
extern Rva00899FC0 *g_Va013383D8;
extern char Va00CB6CB0[];
extern Rva00899FC0 *g_Va013383DC;
extern char Va00CB6CD0[];
extern Rva00899FC0 *g_Va013383E0;
extern char Va00CB6CF0[];
extern Rva00899FC0 *g_Va013383E4;
extern char Va00CB6D10[];
extern Rva00899FC0 *g_Va013383E8;
extern char Va00CB6D30[];
extern Rva00899FC0 *g_Va013383EC;
extern char Va00CB6D50[];
extern Rva00899FC0 *g_Va013383F0;
extern char Va00CB6D70[];
extern Rva00899FC0 *g_Va013383F4;
extern char Va00CB6DC0[];
extern Rva00899FC0 *g_Va013383F8;
extern char Va00CB6E50[];
extern Rva00899FC0 *g_Va013383FC;
extern char Va00CB6EA0[];
extern Rva00899FC0 *g_Va01338400;
extern char Va00CB6EF0[];
extern Rva00899FC0 *g_Va01338404;
extern char Va00CB6F40[];
extern Rva00899FC0 *g_Va01338408;
extern char Va00CB6F90[];
extern Rva00899FC0 *g_Va0133840C;
extern char Va00CB6FE0[];
extern Rva00899FC0 *g_Va01338410;
extern char Va00CB6FF0[];
extern Rva00899FC0 *g_Va01338414;
extern char Va00CB7040[];
extern Rva00899FC0 *g_Va01338418;
extern char Va00CB70D0[];
extern Rva00899FC0 *g_Va0133841C;
extern char Va00CB7120[];
extern Rva00899FC0 *g_Va01338420;
extern char Va00CB7170[];
extern Rva00899FC0 *g_Va01338424;
extern char Va00CB71C0[];
extern Rva00899FC0 *g_Va01338428;
extern char Va00CB7210[];
extern Rva00899FC0 *g_Va0133842C;
extern char Va00CB7260[];
extern Rva00899FC0 *g_Va01338430;
extern char Va00CB72B0[];
extern Rva00899FC0 *g_Va01338434;
extern char Va00CB6B10[];
Rva00899FC0 *__stdcall rva008B73B0(void *owner, const Rva008B73B0String *key)
{
    if (owner) {
        const R4Word *word = Rva008B60B0((const char *)key->data + 8, key->data->length);
        if (word) {
            switch (word->value) {
        case 1:
            if (!g_Va013383A4) {
                g_Va013383A4 = new Rva00899FC0((int)Va00CB6B20);
                g_Va013383A4->flags = (g_Va013383A4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383A4)->slot00();
            }
            return g_Va013383A4;
        case 2:
            if (!g_Va013383A8) {
                g_Va013383A8 = new Rva00899FC0((int)Va00CB6B40);
                g_Va013383A8->flags = (g_Va013383A8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383A8)->slot00();
            }
            return g_Va013383A8;
        case 3:
            if (!g_Va013383AC) {
                g_Va013383AC = new Rva00899FC0((int)Va00CB6B60);
                g_Va013383AC->flags = (g_Va013383AC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383AC)->slot00();
            }
            return g_Va013383AC;
        case 4:
            if (!g_Va013383B0) {
                g_Va013383B0 = new Rva00899FC0((int)Va00CB6B80);
                g_Va013383B0->flags = (g_Va013383B0->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383B0)->slot00();
            }
            return g_Va013383B0;
        case 5:
            if (!g_Va013383B4) {
                g_Va013383B4 = new Rva00899FC0((int)Va00CB6BA0);
                g_Va013383B4->flags = (g_Va013383B4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383B4)->slot00();
            }
            return g_Va013383B4;
        case 6:
            if (!g_Va013383B8) {
                g_Va013383B8 = new Rva00899FC0((int)Va00CB6BC0);
                g_Va013383B8->flags = (g_Va013383B8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383B8)->slot00();
            }
            return g_Va013383B8;
        case 7:
            if (!g_Va013383BC) {
                g_Va013383BC = new Rva00899FC0((int)Va00CB6BE0);
                g_Va013383BC->flags = (g_Va013383BC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383BC)->slot00();
            }
            return g_Va013383BC;
        case 8:
            if (!g_Va013383C0) {
                g_Va013383C0 = new Rva00899FC0((int)Va00CB6C00);
                g_Va013383C0->flags = (g_Va013383C0->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383C0)->slot00();
            }
            return g_Va013383C0;
        case 9:
            if (!g_Va013383C4) {
                g_Va013383C4 = new Rva00899FC0((int)Va00CB6C20);
                g_Va013383C4->flags = (g_Va013383C4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383C4)->slot00();
            }
            return g_Va013383C4;
        case 10:
            if (!g_Va013383C8) {
                g_Va013383C8 = new Rva00899FC0((int)Va00CB6C30);
                g_Va013383C8->flags = (g_Va013383C8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383C8)->slot00();
            }
            return g_Va013383C8;
        case 11:
            if (!g_Va013383CC) {
                g_Va013383CC = new Rva00899FC0((int)Va00CB6C50);
                g_Va013383CC->flags = (g_Va013383CC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383CC)->slot00();
            }
            return g_Va013383CC;
        case 12:
            if (!g_Va013383D0) {
                g_Va013383D0 = new Rva00899FC0((int)Va00CB6C70);
                g_Va013383D0->flags = (g_Va013383D0->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383D0)->slot00();
            }
            return g_Va013383D0;
        case 13:
            if (!g_Va013383D4) {
                g_Va013383D4 = new Rva00899FC0((int)Va00CB6C90);
                g_Va013383D4->flags = (g_Va013383D4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383D4)->slot00();
            }
            return g_Va013383D4;
        case 14:
            if (!g_Va013383D8) {
                g_Va013383D8 = new Rva00899FC0((int)Va00CB6CB0);
                g_Va013383D8->flags = (g_Va013383D8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383D8)->slot00();
            }
            return g_Va013383D8;
        case 15:
            if (!g_Va013383DC) {
                g_Va013383DC = new Rva00899FC0((int)Va00CB6CD0);
                g_Va013383DC->flags = (g_Va013383DC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383DC)->slot00();
            }
            return g_Va013383DC;
        case 16:
            if (!g_Va013383E0) {
                g_Va013383E0 = new Rva00899FC0((int)Va00CB6CF0);
                g_Va013383E0->flags = (g_Va013383E0->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383E0)->slot00();
            }
            return g_Va013383E0;
        case 17:
            if (!g_Va013383E4) {
                g_Va013383E4 = new Rva00899FC0((int)Va00CB6D10);
                g_Va013383E4->flags = (g_Va013383E4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383E4)->slot00();
            }
            return g_Va013383E4;
        case 18:
            if (!g_Va013383E8) {
                g_Va013383E8 = new Rva00899FC0((int)Va00CB6D30);
                g_Va013383E8->flags = (g_Va013383E8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383E8)->slot00();
            }
            return g_Va013383E8;
        case 19:
            if (!g_Va013383EC) {
                g_Va013383EC = new Rva00899FC0((int)Va00CB6D50);
                g_Va013383EC->flags = (g_Va013383EC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383EC)->slot00();
            }
            return g_Va013383EC;
        case 20:
            if (!g_Va013383F0) {
                g_Va013383F0 = new Rva00899FC0((int)Va00CB6D70);
                g_Va013383F0->flags = (g_Va013383F0->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383F0)->slot00();
            }
            return g_Va013383F0;
        case 21:
            if (!g_Va013383F4) {
                g_Va013383F4 = new Rva00899FC0((int)Va00CB6DC0);
                g_Va013383F4->flags = (g_Va013383F4->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383F4)->slot00();
            }
            return g_Va013383F4;
        case 22:
            if (!g_Va013383F8) {
                g_Va013383F8 = new Rva00899FC0((int)Va00CB6E50);
                g_Va013383F8->flags = (g_Va013383F8->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383F8)->slot00();
            }
            return g_Va013383F8;
        case 23:
            if (!g_Va013383FC) {
                g_Va013383FC = new Rva00899FC0((int)Va00CB6EA0);
                g_Va013383FC->flags = (g_Va013383FC->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va013383FC)->slot00();
            }
            return g_Va013383FC;
        case 24:
            if (!g_Va01338400) {
                g_Va01338400 = new Rva00899FC0((int)Va00CB6EF0);
                g_Va01338400->flags = (g_Va01338400->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338400)->slot00();
            }
            return g_Va01338400;
        case 25:
            if (!g_Va01338404) {
                g_Va01338404 = new Rva00899FC0((int)Va00CB6F40);
                g_Va01338404->flags = (g_Va01338404->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338404)->slot00();
            }
            return g_Va01338404;
        case 26:
            if (!g_Va01338408) {
                g_Va01338408 = new Rva00899FC0((int)Va00CB6F90);
                g_Va01338408->flags = (g_Va01338408->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338408)->slot00();
            }
            return g_Va01338408;
        case 27:
            if (!g_Va0133840C) {
                g_Va0133840C = new Rva00899FC0((int)Va00CB6FE0);
                g_Va0133840C->flags = (g_Va0133840C->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va0133840C)->slot00();
            }
            return g_Va0133840C;
        case 28:
            if (!g_Va01338410) {
                g_Va01338410 = new Rva00899FC0((int)Va00CB6FF0);
                g_Va01338410->flags = (g_Va01338410->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338410)->slot00();
            }
            return g_Va01338410;
        case 29:
            if (!g_Va01338414) {
                g_Va01338414 = new Rva00899FC0((int)Va00CB7040);
                g_Va01338414->flags = (g_Va01338414->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338414)->slot00();
            }
            return g_Va01338414;
        case 30:
            if (!g_Va01338418) {
                g_Va01338418 = new Rva00899FC0((int)Va00CB70D0);
                g_Va01338418->flags = (g_Va01338418->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338418)->slot00();
            }
            return g_Va01338418;
        case 31:
            if (!g_Va0133841C) {
                g_Va0133841C = new Rva00899FC0((int)Va00CB7120);
                g_Va0133841C->flags = (g_Va0133841C->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va0133841C)->slot00();
            }
            return g_Va0133841C;
        case 32:
            if (!g_Va01338420) {
                g_Va01338420 = new Rva00899FC0((int)Va00CB7170);
                g_Va01338420->flags = (g_Va01338420->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338420)->slot00();
            }
            return g_Va01338420;
        case 33:
            if (!g_Va01338424) {
                g_Va01338424 = new Rva00899FC0((int)Va00CB71C0);
                g_Va01338424->flags = (g_Va01338424->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338424)->slot00();
            }
            return g_Va01338424;
        case 34:
            if (!g_Va01338428) {
                g_Va01338428 = new Rva00899FC0((int)Va00CB7210);
                g_Va01338428->flags = (g_Va01338428->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338428)->slot00();
            }
            return g_Va01338428;
        case 35:
            if (!g_Va0133842C) {
                g_Va0133842C = new Rva00899FC0((int)Va00CB7260);
                g_Va0133842C->flags = (g_Va0133842C->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va0133842C)->slot00();
            }
            return g_Va0133842C;
        case 36:
            if (!g_Va01338430) {
                g_Va01338430 = new Rva00899FC0((int)Va00CB72B0);
                g_Va01338430->flags = (g_Va01338430->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338430)->slot00();
            }
            return g_Va01338430;
        case 37:
            if (!g_Va01338434) {
                g_Va01338434 = new Rva00899FC0((int)Va00CB6B10);
                g_Va01338434->flags = (g_Va01338434->flags & 0xffffc07f) | 0x40;
                ((Rva008B73B0Slot *)g_Va01338434)->slot00();
            }
            return g_Va01338434;
            }
        }
    }
    return 0;
}
