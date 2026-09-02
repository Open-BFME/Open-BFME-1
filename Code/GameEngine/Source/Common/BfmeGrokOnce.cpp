// cl: /O2

int g_bfmeCountWE;
void *g_bfmeObjWE;

void bfmeAssignSlotsVA();
void *bfmeTwoTB();

void bfmeOnceWE()
{
	if (g_bfmeCountWE <= 0)
	{
		bfmeAssignSlotsVA();
		g_bfmeObjWE = bfmeTwoTB();
		++g_bfmeCountWE;
	}
}
