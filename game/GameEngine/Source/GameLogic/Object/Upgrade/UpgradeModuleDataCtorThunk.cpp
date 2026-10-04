// cl: /DNDEBUG /MD /EHs-c-

extern "C" void UpgradeModuleModuleDataCtor();

extern "C" void UpgradeModuleDataCtorThunk()
{
	UpgradeModuleModuleDataCtor();
}
