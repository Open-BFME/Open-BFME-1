// cl: /DNDEBUG /MD /EHsc
// BFME keeps a floating point font size and one additional integer setting.

class StringClass
{
public:
	void Format(const char *format, ...);
	StringClass &operator=(const char *text);

private:
	char *data;
};

class FontCharsClass
{
public:
	void Initialize_GDI_Font(const char *font_name, float point_size,
		bool is_bold, int extra_setting);

private:
	void Create_GDI_Font(const char *font_name);

	unsigned char pad_to_name[0x0c];
	StringClass name;
	unsigned char pad_to_point_size[0x2c];
	float point_size;
	int extra_setting;
	StringClass gdi_font_name;
	unsigned char pad_to_is_bold[0x418];
	bool is_bold;
};

// ?Initialize_GDI_Font@FontCharsClass@@QAEXPBDM_NH@Z
void FontCharsClass::Initialize_GDI_Font(const char *font_name,
	float new_point_size, bool new_is_bold, int new_extra_setting)
{
	name.Format("%s%f", font_name, new_point_size);
	gdi_font_name = font_name;
	point_size = new_point_size;
	is_bold = new_is_bold;
	extra_setting = new_extra_setting;
	Create_GDI_Font(font_name);
}
