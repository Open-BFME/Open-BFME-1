// ?d_008314e0@@YAXXZ
// partial score=0.51 date=2026-09-17
// cl: /Od /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: address-derived reconstruction of the retail forward-range
// replace body at 0x008314E0.  The callers pass a fifth iterator-tag pointer.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int Bool;

struct BfmeRangeTag
{
    char m_pad;
    char m_value;
};

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
    void *destination, const void *source, UnsignedInt count);

class BfmeStrV44
{
public:
    void bfmeEraseV44(char *first, char *last);
};

void __stdcall bfmeInsertRangeV49(
    char *position, char *first, char *last, char *tag);

void __stdcall bfmeReplaceRangeV44(
    char *first, char *last, char *sourceFirst, char *sourceLast,
    Int tag);

class Rva008314E0String
{
public:
    void replaceRange(char *first, char *last, char *sourceFirst,
        char *sourceLast, char *tag);

    char *m_start;
    char *m_finish;
    char *m_endOfStorage;
};

void Rva008314E0String::replaceRange(
    char *first, char *last, char *sourceFirst, char *sourceLast,
    char *tag)
{
    char *source = sourceFirst;
    Bool sourceIsSelf = false;
    if (source >= m_start && source < m_finish)
        sourceIsSelf = true;

    if (!sourceIsSelf)
    {
        BfmeRangeTag rangeTag;
        rangeTag.m_value = 0;
        bfmeReplaceRangeV44(first, last, sourceFirst, sourceLast,
            (Int)&rangeTag);
        return;
    }

    Int sourceLength = sourceLast - sourceFirst;
    Int replacedLength = last - first;
    if (replacedLength >= sourceLength)
    {
        char *copyResult;
        if (sourceLength == 0)
            copyResult = first;
        else
            copyResult = (char *)BfmeMemMove(
                first, sourceFirst, sourceLength);
        ((BfmeStrV44 *)this)->bfmeEraseV44(first + sourceLength, last);
        return;
    }

    char *middle = sourceFirst + replacedLength;
    if (sourceLast <= first || sourceFirst >= last)
    {
        char *copyResult;
        if (replacedLength == 0)
            copyResult = first;
        else
            copyResult = (char *)BfmeMemMove(
                first, sourceFirst, replacedLength);
        BfmeRangeTag rangeTag;
        rangeTag.m_value = 0;
        bfmeInsertRangeV49(last, middle, sourceLast,
            (char *)&rangeTag);
        return;
    }

    BfmeRangeTag rangeTag;
    rangeTag.m_value = 0;
    bfmeInsertRangeV49(last, middle, sourceLast, (char *)&rangeTag);
    char *finalResult;
    if (sourceLength == 0)
        finalResult = first;
    else
        finalResult = (char *)BfmeMemMove(first + (sourceFirst - m_start),
            m_start + (sourceFirst - m_start), sourceLength);

}
