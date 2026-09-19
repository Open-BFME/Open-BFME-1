// cl: /DNDEBUG /MD /G6 /EHsc

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short OffsetX;
	short Padding06;
	unsigned short *Buffer;
};

class FontCharsClass
{
public:
	virtual ~FontCharsClass();
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short ch);
	void Blit_Char(unsigned short ch, unsigned int *dest_ptr,
		int dest_stride, int x, int y);

private:
	char Fields04[0x28];
	int CharHeight;
};

void FontCharsClass::Blit_Char(unsigned short ch, unsigned int *dest_ptr,
	int dest_stride, int x, int y)
{
	const FontCharsClassCharDataStruct *data = Get_Char_Data(ch);
	if (data != 0 && data->Width != 0)
	{
		x += data->OffsetX;
		if (x < 0)
			x = 0;
		int dest_inc = dest_stride >> 2;
		dest_ptr += (dest_inc * y) + x;
		unsigned short *src_ptr = data->Buffer;

		for (int row = 0; row < CharHeight; row++)
		{
			for (int col = 0; col < data->Width; col++)
			{
				unsigned short pixel = *src_ptr;
				unsigned int curData = pixel;
				curData = (curData & 0xfffff000) << 4;
				curData |= pixel & 0x0f00;
				curData <<= 4;
				curData |= pixel & 0x00f0;
				curData <<= 4;
				curData |= pixel & 0x000f;
				curData <<= 4;
				curData |= dest_ptr[col];
				dest_ptr[col] = curData;
				src_ptr++;
			}
			dest_ptr += dest_inc;
		}
	}
}
