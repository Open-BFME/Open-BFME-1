// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x00941450 is the FontCharsClass metric-sum body: it forwards the
// character to Get_Char_Data, tests the raw return, and adds the two
// halfword metrics at +4 and +2. The layout witness is the proven sibling
// Get_Char_Metric at 0x00941400 (same record, movsx pair, add). IDENTITY IS
// NOT RECOVERED: the record keeps its address token and the method name is
// a placeholder for the unproven semantic identity.
struct FontCharsClassCharDataStruct;

struct Rva00941450CharRecord
{
	unsigned short value;
	short metric;
	short extra_metric;
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short character);
	int Get_Char_Advance(unsigned short ch);
};

int FontCharsClass::Get_Char_Advance(unsigned short ch)
{
	const Rva00941450CharRecord *data =
		(const Rva00941450CharRecord *)Get_Char_Data(ch);
	if (data != 0)
	{
		return data->extra_metric + data->metric;
	}
	return 0;
}
