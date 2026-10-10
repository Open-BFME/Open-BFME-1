unsigned char Rva0051A6D0GetFlag();
void showAptLivingWorldUI();

void bfmeGoBBC()
{
	if (!Rva0051A6D0GetFlag())
		showAptLivingWorldUI();
}
