// Retail 0x0075B180 tests the status bits selected by mask 0x1D0.

bool Rva0075B180StatusMask(unsigned int status)
{
	return (status & 0x1d0) != 0;
}
