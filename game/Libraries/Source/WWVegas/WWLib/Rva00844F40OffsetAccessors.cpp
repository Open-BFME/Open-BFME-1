// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

struct Rva00844F40Offset
{
    int first;
    int displacement;
};

struct Rva00844F40Owner
{
    Rva00844F40Offset *offset;
};

int Rva00844F40GetRelative(const Rva00844F40Owner *owner)
{
    return *(const int *)((const char *)owner + owner->offset->displacement + 0x58);
}

int Rva00844F50GetRelative(const Rva00844F40Owner *owner)
{
    return *(const int *)((const char *)owner + owner->offset->displacement + 0x58);
}
