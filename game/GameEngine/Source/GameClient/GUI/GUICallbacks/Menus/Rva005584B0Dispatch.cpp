// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x005584B0.

extern "C" void j_0003b75a(int value, int *result);
extern "C" int j_0003b971(int value, int argument);

class LadderInfo;
class LadderList
{
public:
	const LadderInfo *findLadderByIndex(int index);
};
extern LadderList *TheLadderList;

class Rva005584B0Owner
{
public:
	void dispatch(void);

	unsigned char m_bfmeHead[0x6C];
	int m_value;
};

void Rva005584B0Owner::dispatch(void)
{
	int result;
	j_0003b75a(m_value, &result);
	TheLadderList->findLadderByIndex(j_0003b971(m_value, result));
}
