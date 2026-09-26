// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva003C61E0Obj
{
	char m_pad[0xA8];
	char m_flag;
};

void __stdcall rva003C61E0Set(Rva003C61E0Obj *obj, int unused)
{
	obj->m_flag = 1;
}
