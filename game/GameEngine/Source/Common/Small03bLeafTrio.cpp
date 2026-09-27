// Three small leaf bodies that share nothing but their size range.
// IDENTITY IS NOT RECOVERED: every name keeps its address token.
struct Rva0092D430Inner
{
	char m_pad[0x1C];
	signed char m_value;
};
class Rva0092D430Box
{
public:
	int get() const;
	char m_pad[0xC8];
	Rva0092D430Inner *m_ptr;
};
// mov eax,[ecx+0xC8] / test / movsx eax,byte ptr [eax+0x1C] / null on miss.
int Rva0092D430Box::get() const
{
	return m_ptr ? m_ptr->m_value : 0;
}
// shl eax,5 / add / indexed load off the ScreenTextureStageStates table.
extern unsigned int ScreenTextureStageStates[8][32];
int __cdecl Rva00945460Lookup(int a, int b)
{
	return ScreenTextureStageStates[a][b];
}
class Rva009339F0Box
{
public:
	short *at(int i);
	short *m_data;
	int m_pad4;
	unsigned int m_size;
};
// unsigned clamp: past-the-end index returns the base pointer.
short *Rva009339F0Box::at(int i)
{
	if ((unsigned int)i >= m_size)
		return m_data;
	return m_data + i;
}
