// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Legacy window-data template selector.  This is the two-argument variant
// reached by the older parseWindow path; the second argument receives the
// selected record size.

#include <string.h>

static unsigned char s_verticalSlider[0x10];
static unsigned char s_scrollListbox[0x4c];
static unsigned char s_tabControl[0x54];
static unsigned char s_entryField[0x28];
static unsigned char s_staticText[8];
static unsigned char s_radioButton[8];
static unsigned char s_comboBox[0x34];

extern "C" void *Rva00484F60GetDataTemplate(char *type, unsigned int *size)
{
	void *data;
	unsigned int dataSize;

	if (!strcmp(type, "VERTSLIDER") || !strcmp(type, "HORZSLIDER"))
	{
		dataSize = 0x10;
		data = s_verticalSlider;
	}
	else if (!strcmp(type, "SCROLLLISTBOX"))
	{
		dataSize = 0x4c;
		data = s_scrollListbox;
	}
	else if (!strcmp(type, "TABCONTROL"))
	{
		dataSize = 0x54;
		data = s_tabControl;
	}
	else if (!strcmp(type, "ENTRYFIELD"))
	{
		dataSize = 0x28;
		data = s_entryField;
	}
	else if (!strcmp(type, "STATICTEXT"))
	{
		dataSize = 8;
		data = s_staticText;
	}
	else if (!strcmp(type, "RADIOBUTTON"))
	{
		dataSize = 8;
		data = s_radioButton;
	}
	else if (!strcmp(type, "COMBOBOX"))
	{
		dataSize = 0x34;
		data = s_comboBox;
	}
	else
		return 0;

	if (size != 0)
		*size = dataSize;
	*(unsigned int *)data = 0;
	return data;
}
