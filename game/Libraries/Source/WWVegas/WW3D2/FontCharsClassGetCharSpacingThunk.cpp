// cl: /DNDEBUG /MD /EHsc

struct Rva00941400CharRecord
{
    unsigned short Value;
    short Width;
    short ExtraSpacing;
};

class Rva00941400Font
{
public:
    const Rva00941400CharRecord *Get_Char_Data(unsigned short ch);
};

class FontCharsClass
{
public:
    int Get_Char_Spacing(unsigned short ch);

private:
    char Fields00[0x34];
    int CharOverhang;
    int PixelOverlap;
};

int FontCharsClass::Get_Char_Spacing(unsigned short ch)
{
    const Rva00941400CharRecord *data =
        reinterpret_cast<Rva00941400Font *>(this)->Get_Char_Data(ch);
    if (data != 0 && data->Width != 0) {
        if ((ch >= 0x0e01 && ch <= 0x0e3a)
            || (ch >= 0x0e3f && ch <= 0x0e5b)) {
            return data->Width + data->ExtraSpacing;
        }
        return data->Width - PixelOverlap - CharOverhang;
    }

    return 0;
}
