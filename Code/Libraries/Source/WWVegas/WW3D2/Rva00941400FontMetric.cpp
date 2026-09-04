// cl: /DNDEBUG /MD /G6 /EHsc

struct Rva00941400CharRecord
{
	unsigned short value;
	short metric;
	short extra_metric;
};

class Rva00941400Font
{
public:
	Rva00941400CharRecord const *Get_Char_Data(unsigned short ch);
	int Get_Char_Metric(unsigned short ch);
};

int Rva00941400Font::Get_Char_Metric(unsigned short ch)
{
	Rva00941400CharRecord const *data = Get_Char_Data(ch);
	if (data != 0)
	{
		if ((ch >= 0x0e01 && ch <= 0x0e3a) ||
			(ch >= 0x0e3f && ch <= 0x0e5b))
			return data->extra_metric + data->metric;
		return data->metric;
	}
	return 0;
}
