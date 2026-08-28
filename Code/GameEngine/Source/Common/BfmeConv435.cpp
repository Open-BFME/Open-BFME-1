bool bfmeAskBBC();
void bfmeElseBBC();

void bfmeGoBBC()
{
	if (!bfmeAskBBC())
		bfmeElseBBC();
}
