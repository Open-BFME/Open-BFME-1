// Retail RVA 0x00872950: 29B; preceding INT3 starts at RVA 0x0087294A,
// RET at +0x14/+0x1C and trailing INT3 at +0x1D bound the body.
// No calls. All three absolute operands name VA 0x0130E8B4:
// read a dword, compare its low word, then store/increment only that word.
// The old dword remains in EAX on both exits. The unsigned source return
// records that physical result; no original declared return type or name
// is proved by a named caller. Both identities retain their addresses.
// This union describes the two witnessed access widths, not a semantic owner.

union Rva0130E8B4Storage
{
    unsigned int m_dword;
    unsigned short m_word;
};
extern Rva0130E8B4Storage g_Rva0130E8B4;

unsigned int Rva00872950()
{
    unsigned int value = g_Rva0130E8B4.m_dword;
    if ((unsigned short)value == 0xffff)
        g_Rva0130E8B4.m_word = 1;
    else
        ++g_Rva0130E8B4.m_word;
    return value;
}
