extern int g_bfmeCountBBD;

void bfmeElseBBD();

void bfmeGoBBD()
{
	if (g_bfmeCountBBD > 0)
		bfmeElseBBD();
}
