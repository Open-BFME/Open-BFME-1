#ifndef RVA0055AE10_MAP_PREDICATE_H
#define RVA0055AE10_MAP_PREDICATE_H

class MapMetaData;

// Read-only prefix witness, not a competing definition of MapMetaData.
// BFME inserts the scenario flag before the official flag found in ZH.
struct Rva00450B90MapFlags
{
    char m_beforeFlags[0x24];
    bool m_flag24;
    bool m_flag25;
    bool m_flag26;
};

// The four-byte value passed by fillMapMask at 0x0055AFB2. The address keeps
// the predicate's unproven original class name out of its native contract.
struct Rva0055AE10MapPredicate
{
    int value;
    Rva0055AE10MapPredicate(int v) : value(v) {}
    bool operator()(const MapMetaData *md) const
    {
        const Rva00450B90MapFlags *item =
            reinterpret_cast<const Rva00450B90MapFlags *>(md);
        if ((value & 0x01) != 0 && item->m_flag26)
            goto selected26;
        if ((value & 0x02) == 0 || item->m_flag26)
            return false;

    selected26:
        if ((item->m_flag24 && (value & 0x04) != 0)
                || (!item->m_flag24 && (value & 0x08) != 0))
            return false;

        return !((item->m_flag25 && (value & 0x10) != 0)
            || (!item->m_flag25 && (value & 0x20) != 0));
    }
};

#endif
