// cl: /Od /GZ
// DirtySock transport shutdown callback at retail RVA 0x0081B9B0.
extern "C" int Rva0081B830(void *comm);

extern "C" void Rva0081B9B0(void *comm)
{
	Rva0081B830(comm);
}
