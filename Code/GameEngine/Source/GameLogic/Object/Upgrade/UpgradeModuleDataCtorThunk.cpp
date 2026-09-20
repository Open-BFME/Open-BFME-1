// cl: /DNDEBUG /MD /EHs-c-

#pragma comment(linker, "/alternatename:??0UpgradeModuleData@@QAE@XZ=_UpgradeModuleDataCtorThunk")

extern "C" void UpgradeModuleModuleDataCtor();
#pragma comment(linker, "/alternatename:_UpgradeModuleModuleDataCtor=??0UpgradeModuleModuleData@@QAE@XZ")

extern "C" void UpgradeModuleDataCtorThunk()
{
	UpgradeModuleModuleDataCtor();
}
