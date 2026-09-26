// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 0x009AF530: choose one of two bounding-table builders by mode.
struct Rva009AF490Context;
int *Rva009AF490SetupBounding(Rva009AF490Context *, int);

struct Rva009AF530Context
{
    int m_mode;
    unsigned char m_pad4[8];
    int m_limitIndex;
    unsigned char m_pad10[0x20];
    int *m_bounding;
};

extern int *g_bfmeFilterLimit;
typedef int *(__cdecl *Rva009AF530Builder)(Rva009AF530Context *, int);
extern Rva009AF530Builder g_rva01356e68SetupBounding;

void __cdecl Rva009AF530Setup(Rva009AF530Context *context)
{
    int limit = g_bfmeFilterLimit[context->m_limitIndex];
    if (context->m_mode >= 2)
        context->m_bounding = Rva009AF490SetupBounding(
            reinterpret_cast<Rva009AF490Context *>(context), limit);
    else
        context->m_bounding = g_rva01356e68SetupBounding(context, limit);
}
