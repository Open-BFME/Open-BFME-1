// Retail calls ILT 0x00028358, which the ledger defines as ?j_00028358@@YAXXZ.
extern void j_00028358();
typedef void (__cdecl *BfmeDoSixRCCall)(void *what, void *one, void *two, void *three, void *four, int flag);

void *bfmeCallSixRC(void *what, void *one, void *two, void *three, void *four)
{
	((BfmeDoSixRCCall)j_00028358)(what, one, two, three, four, 0);
	return what;
}
