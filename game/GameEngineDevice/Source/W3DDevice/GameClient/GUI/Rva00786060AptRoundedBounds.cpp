// cl: /EHs-c-
// Retail 0x00786060: get item through slot 2, copy affine transform,
// round its bounds, and pass them to the existing GUI helper.
struct Rva00784090Point { float x, y; };
struct Rva007845D0Transform { float m[6]; };
class Rva00785FD0Item {
public:
 void getRenderRegion(Rva00784090Point *, Rva00784090Point *);
 char m_prefix[0x10];
 Rva007845D0Transform m_xform;
};
class BoundsSource00786060 {
public:
 virtual void slot0();
 virtual void slot1();
 virtual Rva00785FD0Item *item();
};
class BfmeHub982 { public: void bfmeBegin982C(); void bfmeEnd982C(); };
class BfmeHostDO { public: void bfmeApplyDO(const char *, int, int, int, int); };
extern BfmeHub982 *g_bfmeHub982;
extern void *g_theWindowManager;
extern int g_Va012D7198;
extern Rva007845D0Transform g_Rva00F0692CTransform;
void rva00785FD0Flush();
int bfmeHelpWI(int);
void applyRoundedBounds00786060(const char *name, int first, BoundsSource00786060 *source, int fourth)
{
 if (!source) return;
 Rva00785FD0Item *item = source->item();
 if (!item) return;
 rva00785FD0Flush();
 int saved = g_Va012D7198;
 g_Va012D7198 = (int)&bfmeHelpWI;
 g_bfmeHub982->bfmeBegin982C();
 item->m_xform = g_Rva00F0692CTransform;
 Rva00784090Point minPt, extent;
 item->getRenderRegion(&minPt, &extent);
 minPt.x = (float)(int)(minPt.x + 0.5f);
 minPt.y = (float)(int)(minPt.y + 0.5f);
 extent.x = (float)(int)(extent.x + 0.5f);
 extent.y = (float)(int)(extent.y + 0.5f);
 ((BfmeHostDO *)g_theWindowManager)->bfmeApplyDO(name, (int)&minPt, (int)&extent, first, fourth);
 g_Va012D7198 = saved;
 g_bfmeHub982->bfmeEnd982C();
}

