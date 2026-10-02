// The pinned empty-string literal (symbols.csv ?g_Rva0107301CEmptyString@@3QBDB,
// RVA 0x00C7301C); the census alias _bfmeInfoDND was a placeholder for it.
extern const char g_Rva0107301CEmptyString[];

class BfmeOtherDND
{
public:
	void bfmeCallDND(void *info);
};

class BfmeThingDND
{
public:
	BfmeOtherDND *bfmeGoDND(BfmeOtherDND *other);
};

BfmeOtherDND *BfmeThingDND::bfmeGoDND(BfmeOtherDND *other)
{
	volatile int tmp = 0;
	other->bfmeCallDND((void *)g_Rva0107301CEmptyString);
	return other;
}
