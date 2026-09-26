// ?convertFlags008BAA60@@YAIE@Z
unsigned int convertFlags008BAA60(unsigned char cl)
{
	unsigned int eax = 0;
	if (cl & 8) eax = 0x800;
	if (cl & 4) eax |= 0x400;
	if (cl & 0x40) eax |= 0x1000;
	if (cl & 1) eax |= 0x2000;
	if (cl & 2) eax |= 0x4000;
	if (cl & 0x20) eax |= 0x8000;
	if (cl & 0x10) eax |= 0x10000;
	return eax;
}
