// Retail 0x008A4540:31B and 0x008A4560:6B; independent thiscall leaf entries.
// The generated 38B extent fused the predicate, INT3 padding, and accessor.
class Rva008A4540
{
public:
 char *m_00;
 unsigned int m_04;
 int method();
 char *method_008A4560();
};
int Rva008A4540::method()
{
 unsigned int flags=m_04;
 if ((flags & 0x3f) == 0x18 && ((unsigned char)~(flags >> 15) & 1) == 0) return 1;
 return 0;
}
char *Rva008A4540::method_008A4560()
{
 return m_00 + 8;
}
