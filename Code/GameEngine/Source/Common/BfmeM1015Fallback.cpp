// Open-BFME: BfmeM1015::bfmeFallback1015, retail 0x008A48A0.
// Named Apt lookup: strcmp of the string payload at m_data+8 against
// "registerClass", then a branchless select of the bound native.

extern "C" int __cdecl strcmp(const char *a, const char *b);

extern int g_bfmeRegisterClass1015;

class BfmeM1015
{
public:
	int bfmeFallback1015(int a, const char **b);
};

int BfmeM1015::bfmeFallback1015(int a, const char **b)
{
	return strcmp(*b + 8, "registerClass") == 0 ? g_bfmeRegisterClass1015 : 0;
}
