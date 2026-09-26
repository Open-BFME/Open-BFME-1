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

	char fields_00[0x34];
	int char_overhang;
	int pixel_overlap;
};

class BfmeSubAA
{
public:
	void bfmeLookupAA(float *out, const char *text);

private:
	char fields_00[0x4c];
	Rva00941400Font *font;
};

struct BfmeLookupAAResult
{
	float width;
	float height;
};

void BfmeSubAA::bfmeLookupAA(float *out, const char *text)
{
	BfmeLookupAAResult result;
	result.height = static_cast<float>(*reinterpret_cast<int *>(
		reinterpret_cast<char *>(font) + 0x2c));
	result.width = 0.0f;
	unsigned short ch = *reinterpret_cast<const unsigned short *>(text);

	if (ch != 0)
	{
		do
		{
			text += 2;
			if (ch != 0x000a)
			{
				Rva00941400Font *font = this->font;
				Rva00941400CharRecord const *data = font->Get_Char_Data(ch);
				int spacing;
				if (data != 0 && data->metric != 0)
				{
					if ((ch >= 0x0e01 && ch <= 0x0e3a) ||
						(ch >= 0x0e3f && ch <= 0x0e5b))
						spacing = data->extra_metric + data->metric;
					else
						spacing = data->metric - font->pixel_overlap - font->char_overhang;
				}
				else
					spacing = 0;

				result.width += static_cast<float>(spacing);
			}

			ch = *reinterpret_cast<const unsigned short *>(text);
		}
		while (ch != 0);
	}

	BfmeLookupAAResult *destination = reinterpret_cast<BfmeLookupAAResult *>(out);
	destination->width = result.width;
	destination->height = result.height;
}
