// cl: /DNDEBUG /MD /G6 /EHsc

struct Rva00941400CharRecord
{
	unsigned short value;
	short metric;
	short extra_metric;
};

// Keep the retail callee's address-qualified declaration: its call target is
// pinned at 0x009412F0, distinct from the proven FontCharsClass::Get_Char_Data
// body at 0x00941290.
class Rva00941400Font
{
public:
	Rva00941400CharRecord const *Get_Char_Data(unsigned short ch);
	};

// The upstream FontCharsClass owns the adjacent character metric APIs; this
// witness uses that same character-record layout.
class FontCharsClass
{
	public:
	int Get_Char_Metric(unsigned short ch);
};

int FontCharsClass::Get_Char_Metric(unsigned short ch)
{
	Rva00941400CharRecord const *data =
		reinterpret_cast<Rva00941400Font *>(this)->Get_Char_Data(ch);
	if (data != 0)
	{
		if ((ch >= 0x0e01 && ch <= 0x0e3a) ||
			(ch >= 0x0e3f && ch <= 0x0e5b))
			return data->extra_metric + data->metric;
		return data->metric;
	}
	return 0;
}
