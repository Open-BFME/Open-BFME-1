extern "C" __declspec(dllimport) void bfmeCIpowImport();

extern "C" void __CIpow()
{
	bfmeCIpowImport();
}
