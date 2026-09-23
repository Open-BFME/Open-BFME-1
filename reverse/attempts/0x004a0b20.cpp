// ?Rva004A0B20Query@@YGHHH@Z
// partial score=0.7901 date=2026-09-23
// ?Rva004A0B20Query@@YGHHH@Z
// Retail 0x004A0B20, 81 bytes. The caller reaches this wrapper via an ILT;
// no named owner is proven. It calls the matched purchase-science query,
// reuses both input parameter slots as byte out-parameters, and reserves an
// eight-byte local area. Only the call-argument register schedule differs.
void __stdcall bfmeQueryWD(int first, int second, bool *fourth,
                            bool *secondOut, bool *firstOut, bool *third);

int __stdcall Rva004A0B20Query(int first, int second)
{
    bool local[8];
    bfmeQueryWD(first, second, &local[4],
                reinterpret_cast<bool *>(&second),
                reinterpret_cast<bool *>(&first), &local[3]);
    if (*reinterpret_cast<bool *>(&second) &&
        *reinterpret_cast<bool *>(&first) && !local[3])
        return 1;
    return 0;
}
