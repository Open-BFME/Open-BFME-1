// ?Rva005EEDA0WriteBase@@YAXPBXPAVFile@@PAI@Z
// Retail 0x005EEDA0 shares the stream-writing body at 0x005FCB60. Its
// category key is 1, while the matched helper uses category 8.

#include "Rva005FCB60WriteBase.cpp"

// The vtable and caller identify this as the DefaultModuleTemplate<0>
// stream writer. The address-derived function name keeps the remaining
// template ownership neutral.
void Rva005EEDA0WriteBase(const void *self, File *file, unsigned int *flags)
{
	OutputStream stream(0x10);
	const char *name = ((ModuleClassView *)((unsigned char *)self + 4))
		->getClass()->name;
	for (unsigned int indent = *flags; indent > 0; --indent)
		reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
	reinterpret_cast<StreamWriter *>(&stream)->append(
		FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)1));
	reinterpret_cast<StreamWriter *>(&stream)->append(g_u4Separator);
	reinterpret_cast<StreamWriter *>(&stream)->append(name);
	reinterpret_cast<StreamWriter *>(&stream)->separate('\n');
	writeStreamText(*file,
		reinterpret_cast<Rva005CB9F0StreamText *>(&stream)->getText());
	*flags += 2;
}
