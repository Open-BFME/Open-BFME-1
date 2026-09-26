extern "C" __declspec(dllimport) int __cdecl bfmeSprintfESP(char *buffer,
	const char *format, ...);

extern char g_bfmeFmtESP[];
extern const char g_bfmeEmptyESP[];

void bfmeApplyESP(const char *first, const char *second);
void bfmeRemoveESP(unsigned int index);

struct BfmeSlotESP
{
	unsigned char m_bfmeHeadESP[0x10];
	char m_bfmeFlagsESP;
	unsigned char m_bfmeTailESP[3];
};

class BfmeHostESP
{
public:
	char bfmeClearESP(unsigned int index);

	unsigned char m_bfmeHeadESP[0xa8];
	BfmeSlotESP m_bfmeSlotsESP[12];
};

char BfmeHostESP::bfmeClearESP(unsigned int index)
{
	if (index >= 0xc)
		return 0;

	BfmeSlotESP *slot = &m_bfmeSlotsESP[index];

	if ((slot->m_bfmeFlagsESP & 2) == 0)
		return 0;

	char name[32];

	bfmeSprintfESP(name, g_bfmeFmtESP, index);

	bfmeApplyESP(g_bfmeEmptyESP, name);

	slot->m_bfmeFlagsESP &= 0xf5;

	bfmeRemoveESP(index);

	return 1;
}
