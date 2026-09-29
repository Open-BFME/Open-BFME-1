// ?setFlipRecursive@W3DTerrainBackground@@IAEXHHHH@Z
// partial score=0.1766 date=2026-09-28
// Scratch reconstruction for retail 0x007282A0..0x007285D5 (821 bytes).
// Caller, pin, and matched source establish the W3D member identity.
//
// MEASURED 2026-09-28 (tools/probe.py, MSVC 7.1 /O2): 842 B compiled vs 821 B
// retail, 634 non-relocation byte differences, first at +0x11, shape 0.922 with
// 23 structural differences (the previous bank measured 827 B / 437 diffs /
// shape 0.833 / 35 structural differences).
//
// THIS BANK IS STRUCTURALLY RIGHT AND THE PREVIOUS ONE WAS NOT, even though the
// old body has fewer differing bytes.  Everything below is measured, not argued:
//
//  * `sub esp,0x34` -- retail's frame size -- and exactly retail's TWELVE frame
//    objects (see the /FAsc table below).  The old bank sat at 0x30 with eleven.
//  * Prologue 0x00..0x0f is BYTE-EXACT: `sub esp,0x34; push ebx; push ebp;
//    push esi; mov ebp,ecx; push edi; mov [esp+0x40],ebp; lea ecx,[ecx]`.
//    `this` is in EBP and spilled to [esp+0x40], as in retail.  The old bank
//    had `this` in memory and EBP holding minX.
//  * The inner loop head now matches retail's shape.  Retail stores the
//    loop-invariant `minX + i` once per OUTER iteration to [esp+0x3c] and
//    RELOADS AND CLAMPS k at the INNER head (retail +0x113 `mov edi,[esp+0x3c];
//    cmp edi,ebx; jl; mov edi,ebx`), with the inner back edge at +0x1ed
//    jumping to that reload.  That is what `int k = xOrigin() + xOffset + i;`
//    INSIDE the inner loop produces: VC7.1 hoists the invariant into a $T with
//    a frame home, exactly as retail does.  With `int k = minX + i;` hoisted to
//    the outer loop -- what every earlier bank and ~150 earlier variants wrote
//    -- the clamp lands outside the inner loop and cannot match.  This is the
//    single largest structural fact discovered for this body and it is settled.
//
// /FAsc frame table for THIS bank (12 dwords, retail's set):
//   0x14 minX($T) 0x18 i 0x1c k($T) 0x20 C 0x24 D 0x28 B 0x2c u 0x30 A
//   0x34 j/$T 0x38 limitX 0x3c limitY 0x40 this          (0x13 match byte)
// retail: 0x14 minX 0x18 i 0x1c minY 0x20 C 0x24 D 0x28 B 0x2c u 0x30 A
//         0x34 j/$T 0x38 limitY 0x3c k 0x40 this
//
// THE ONE RESIDUE: retail puts limitX in EBX and HOMES minY; this build homes
// limitX and puts minY in EBX.  Both live ranges span the whole loop nest, so
// they are the allocator's fourth-callee-saved-register decision, and it is the
// only thing still wrong.  Everything after it -- the corner reads, the cliff
// block, the two-triangle x87 schedule, the tolerance test, the break edges and
// the three-calls-plus-tail-jump tail -- is already in retail's shape.
//
// ALREADY TRIED, do not redo (all measured this session unless noted):
//  * the two clamp spellings (if / ternary / separate clamped temp), the two
//    clamp orders, `const` and `register` on minY and limitX, two-step
//    `minY = yOrigin(); minY += yOffset;` and `limitX = width(); --limitX;`
//    definitions, 120 permutations of the five prologue declarations, all 24
//    corner-read orders (A,D,B,C is the best at 634; retail's own A,B,C,D costs
//    693), a cached `Rva007282A0Map *m` (+1 object, frame 0x38), a cached
//    `stride`, named `width`/`yOffset`/`xOrigin` locals, a float `tolerance`
//    local, `int match` instead of `bool`, and a tools/shape_search.py run over
//    the 64 combinations that tools/shape_family_levers.py generates for the
//    sib/register/bool/test/copy/store/loop/branch/constant/frame families
//    (13 trials, no improvement).
//  * Earlier sessions, still true: prologue order, loop-counter roles and
//    scopes, k/l hoisted to function scope, block-scoped locals, if vs ternary,
//    pre/post increment, `m_map` member vs `map()` accessor, upstream-shaped
//    WorldHeightMap/BfmeMaskAX classes, extern 1.0f, UnsignedShort corners,
//    currentHeight-first, /G3../Ga.  None of those reach the current base.
//  * Re-expressing minY as `yOrigin() + yOffset + j` (i.e. deleting the minY
//    local) also gives `this` a callee-saved register, but it costs a 13th
//    object (frame 0x38) because the hoisted sum becomes its own $T, and the
//    loop body re-reads both members per iteration.  Same for re-expressing
//    minX: `all` reaches 0x34 with a byte-exact prologue but 858 B / 722 diffs.
//  * The 4th parameter must stay `int`: the pinned thunk is HHHH and a Real
//    parameter mangles to HHHF@Z.
//
// NEXT WORKER: attack only the limitX-versus-minY register choice.  The
// generator that produced this bank is build/scratch/282a0/gen11.py
// (kForm x lForm matrix) and the best measured variant is
// build/scratch/282a0/wb/co_ADBC.cpp.  Frame tables come from adding
// `/FAsc /Fa<path>.cod` to the `// cl:` line below; the byte loop is
// `python3 build/scratch/loop.py <file.cpp>` (~0.6 s per variant).
//
// 2026-09-28 follow-up (60 variants): tested prologue permutations with
// cached width/height/xOrigin/yOrigin locals (709 diffs), heightAt/cliffAt
// cached vs direct (634), for-scoped loops (634), halfWidth shift/div (640),
// int vs bool match (711), tolerance float local (634), commuted adds
// (634), 80-trial random prologue+corner+KL brute (best 623 diffs but shape
// 0.898 vs 0.922 here, so structurally worse), and barrier/volatile trials
// (compile fail or 727).  No variant moves limitX into EBX; 634/0.922 remains
// best structural.  See build/scratch/best_623.cpp (623 diffs, 0.898) and
// build/scratch/282a0/wc/swapclamp.cpp (627 diffs) as evidence.
//
// cl: /DNDEBUG /MD /EHsc

class BfmeMaskAX
{
public:
    void bfmeMarkAX(int x, int y, unsigned char value);
};

class Rva007282A0Map
{
public:
    int width(void) const
    {
        return *(const int *)((const char *)this + 0x08);
    }

    int height(void) const
    {
        return *(const int *)((const char *)this + 0x0c);
    }

    int count(void) const
    {
        return *(const int *)((const char *)this + 0x20);
    }

    unsigned short *heights(void) const
    {
        return *(unsigned short * const *)((const char *)this + 0x24);
    }

    int *cliffArray(void) const
    {
        return *(int * const *)((const char *)this + 0x94);
    }

    int drawOriginX(void) const
    {
        return *(const int *)((const char *)this + 0x120E0);
    }

    int drawOriginY(void) const
    {
        return *(const int *)((const char *)this + 0x120E4);
    }

    unsigned short heightAt(int x, int y) const
    {
        int index = y * width() + x;
        if (index < 0 || index >= count())
            return 0;
        unsigned short *data = heights();
        if (data == 0)
            return 0;
        return data[index];
    }

    bool cliffAt(int x, int y) const
    {
        int index = (drawOriginY() + y) * width() + drawOriginX() + x;
        if (index < 0)
            return false;
        if (index >= count())
            return false;
        return cliffArray()[index] != 0;
    }
};

class W3DTerrainBackground
{
protected:
    void setFlipRecursive(int xOffset, int yOffset, int width,
        int errorToleranceBits);

private:
    int xOrigin(void) const
    {
        return *(const int *)((const char *)this + 0x40);
    }

    int yOrigin(void) const
    {
        return *(const int *)((const char *)this + 0x44);
    }

    Rva007282A0Map *map(void) const
    {
        return *(Rva007282A0Map * const *)((const char *)this + 0x4c);
    }
};

// ?setFlipRecursive@W3DTerrainBackground@@IAEXHHHH@Z
void W3DTerrainBackground::setFlipRecursive(int xOffset, int yOffset, int width,
    int errorToleranceBits)
{

    int limitX = map()->width() - 1;
    int limitY = map()->height() - 1;
    bool match = true;
    int minX = xOrigin() + xOffset;
    int minY = yOrigin() + yOffset;
    int maxX = minX + width;
    if (maxX >= limitX)
        maxX = limitX;
    int maxY = minY + width;
    if (maxY >= limitY)
        maxY = limitY;

    // The four corner reads are independent and side-effect free.  Retail emits
    // them A,B,C,D; declaring them A,D,B,C is what drops this body from 27
    // structural differences to 23.
    int cornerA = map()->heightAt(minX, minY);
    int cornerD = map()->heightAt(minX, maxY);
    int cornerB = map()->heightAt(maxX, minY);
    int cornerC = map()->heightAt(maxX, maxY);

    int i;
    int j;
    for (i = 0; i <= width; ++i)
    {
        for (j = 0; j <= width; ++j)
        {
            // k is written from the loop-invariant sum so that MSVC hoists it
            // into a $T with a frame home, reloaded and clamped at the inner
            // head exactly as retail does.  Writing `minX + i` here instead
            // gives the same bytes without the $T and cannot match.
            int k = xOrigin() + xOffset + i;
            if (k >= limitX)
                k = limitX;
            int l = minY + j;
            if (l >= limitY)
                l = limitY;

            if (map()->cliffAt(k, l))
            {
                match = false;
                break;
            }

            float u = (float)i / (float)width;
            float v = (float)j / (float)width;
            float predicted;
            if (v > (1.0f - u))
            {
                predicted = ((cornerB - cornerC) *
                    (1.0f - v) +
                    (cornerD - cornerC) *
                    (1.0f - u) + cornerC) *
                    0.0390625f;
            }
            else
            {
                predicted = ((cornerD - cornerA) * v +
                    (cornerB - cornerA) * u + cornerA) *
                    0.0390625f;
            }

            int currentHeight = map()->heightAt(k, l);
            float delta = predicted - currentHeight * 0.0390625f;
            if (delta < 0.0f)
                delta = -delta;
            if (delta > *(const float *)&errorToleranceBits)
            {
                match = false;
                break;
            }
        }
    }

    if (width == 1 || match)
    {
        int cornerMaxX = minX + width;
        if (cornerMaxX >= limitX)
            cornerMaxX = limitX;
        int cornerMaxY = minY + width;
        if (cornerMaxY >= limitY)
            cornerMaxY = limitY;

        ((BfmeMaskAX *)map())->bfmeMarkAX(minX, minY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(cornerMaxX, minY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(cornerMaxX, cornerMaxY, 1);
        ((BfmeMaskAX *)map())->bfmeMarkAX(minX, cornerMaxY, 1);
        return;
    }

    int halfWidth = width / 2;
    setFlipRecursive(xOffset, yOffset, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset, yOffset + halfWidth, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset + halfWidth, yOffset, halfWidth, errorToleranceBits);
    setFlipRecursive(xOffset + halfWidth, yOffset + halfWidth, halfWidth,
        errorToleranceBits);
}
