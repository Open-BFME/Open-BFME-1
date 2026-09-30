// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// partial score=0.63 date=2026-09-29
// Shape lever: reuse the centre-tap subtraction for both the zero test and filter index.
extern const unsigned char g_bfmeClampTable[];

void Rva009B3180FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
    int p1 = ptr[1];
    int s = stride;
    const int *tbl = bounding;
    int p2 = ptr[2];
    int center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
        ptr += s;
    }

    p1 = ptr[1];
    p2 = ptr[2];
    center = p2 - p1;
    if (center != 0) {
        int p0 = ptr[0];
        int p3 = ptr[3];
        int a = p1 - p0;
        int b = p3 - p2;
        int t = 2 * center + 4;
        t -= a;
        t += b;
        int delta = tbl[t >> 3];
        ptr[1] = g_bfmeClampTable[p1 + delta];
        ptr[2] = g_bfmeClampTable[p2 - delta];
        int flag = (a | b) == 0;
        int half = delta >> 1;
        int adj = flag * half;
        ptr[0] = g_bfmeClampTable[p0 + adj];
        ptr[3] = g_bfmeClampTable[p3 - adj];
    }
}
