// cl: /DNDEBUG /MD /O2
// Width-selecting hexadecimal formatter at retail RVA 0x009D9990. (rev 2)
// Retail pushes the two format literals straight out of .rdata: 0x01144508 is
// "%i" (every width branch) and 0x01144500 is " [%s]" (ahead of the label).
// Neither VA has a datum row or a pin, so they are written as the literals
// they are; the byte check masks the pushed address and the string-ref check
// verifies the contents.
static const char g_bfmeRva01144508HexFormat[] = "%i";
static const char g_bfmeRva01144500LabelFormat[] = " [%s]";

extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

class Gen009D9990
{
public:
    Gen009D9990 *bfmeEmit(const char *label, const void *value, unsigned int width);

private:
    unsigned char m_pad[4];
    bool m_pending;
};

Gen009D9990 *Gen009D9990::bfmeEmit(const char *label, const void *value, unsigned int width)
{
    if (!m_pending)
        bfmeAppend(this, 0);
    switch (width)
    {
    case 1:
        bfmeAppend(this, g_bfmeRva01144508HexFormat, *static_cast<const unsigned char *>(value));
        break;
    case 2:
        bfmeAppend(this, g_bfmeRva01144508HexFormat, *static_cast<const unsigned short *>(value));
        break;
    case 3:
        bfmeAppend(this, g_bfmeRva01144508HexFormat, *static_cast<const unsigned int *>(value) & 0xffffff);
        break;
    case 4:
        bfmeAppend(this, g_bfmeRva01144508HexFormat, *static_cast<const unsigned int *>(value));
        break;
    }
    bfmeAppend(this, g_bfmeRva01144500LabelFormat, label);
    bfmeAppend(this, "\n");
    m_pending = false;
    return this;
}
