// ?Rva009B3180FilterVert@@YAXPAXPAEHPBH@Z
// partial score=0.1678 date=2026-10-08
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern unsigned char g_bfmeClampTable[];

struct Rva009B3180RowState
{
    int center;
    int p2;
    int p3;
};

// ?Rva009B3180FilterVert@@YAXPAXPAEHPBH@Z
void Rva009B3180FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
    int p0, p1, a, b, t, delta, flag, half, adj;
    Rva009B3180RowState row;
    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
        ptr += stride;
    }

    p1 = ptr[1];
    row.p2 = ptr[2];
    row.center = row.p2 - p1;
    if (row.center != 0) {
        p0 = ptr[0];
        row.p3 = ptr[3];
        a = p1 - p0;
        b = row.p3 - row.p2;
        t = 2 * row.center + 4;
        t -= a;
        t += b;
        delta = bounding[t >> 3];
        p1 = g_bfmeClampTable[p1 + delta + 256];
        ptr[1] = p1;
        row.p2 = g_bfmeClampTable[row.p2 - delta + 256];
        ptr[2] = row.p2;
        flag = (a | b) == 0;
        half = delta >> 1;
        adj = flag * half;
        p0 = g_bfmeClampTable[ptr[0] + adj + 256];
        ptr[0] = p0;
        row.p3 = g_bfmeClampTable[row.p3 - adj + 256];
        ptr[3] = row.p3;
    }
}
