// cl: /DNDEBUG /MD /G6 /EHsc

struct Rva00941400CharRecord
{
	unsigned short Value;
	short Width;
	char Padding04[4];
	unsigned short *Buffer;
};

class Rva00941400Font
{
public:
	Rva00941400CharRecord const *Get_Char_Data(unsigned short ch);
};

class FontCharsClass
{
	public:
	virtual ~FontCharsClass();
	void Blit_Char(unsigned short ch, unsigned short *dest_ptr,
		int dest_stride, int x, int y);

	private:
	char Fields04[0x28];
	int CharHeight;
	char Fields30[8];
	int PixelOverlap;
};

void FontCharsClass::Blit_Char(unsigned short ch, unsigned short *dest_ptr,
	int dest_stride, int x, int y)
{
	unsigned int *dest = reinterpret_cast<unsigned int *>(dest_ptr);
	Rva00941400CharRecord const *data;
	data = reinterpret_cast<Rva00941400Font *>(this)->Get_Char_Data(ch);
	if (data != 0 && data->Width != 0)
	{
		int dest_inc = dest_stride >> 2;
		unsigned short *src_ptr = data->Buffer;
		dest += (dest_inc * y) + x;

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
				if (col < PixelOverlap)
					curData |= dest[col];
				dest[col] = curData;
				src_ptr++;
			}
			dest += dest_inc;
		}
	}
}
