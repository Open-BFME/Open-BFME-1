// ??_ELightningEmissionInfo@FXParticleSystem@@UAEPAXI@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: compiler-generated vector deleting destructor (87 B) for the
// 0x8c-byte FXParticleSystem::LightningEmissionInfo record (its destructor is
// the landed body reached through thunk 0x0000D7F6); emitted with the vtable
// by an array new/delete of the class.
void __cdecl operator delete[](void* block);
class FXParticleSystem {
public:
	struct LightningEmissionInfo {
		virtual ~LightningEmissionInfo();
		char m_body[0x8c - 4];
		static void operator delete[](void* block) { ::operator delete[](block); }
	};
};
__declspec(noinline) FXParticleSystem::LightningEmissionInfo::~LightningEmissionInfo()
{
}
// ?Rva005D6A60MakeArray@@YAPAULightningEmissionInfo@FXParticleSystem@@H@Z absent-from-retail
FXParticleSystem::LightningEmissionInfo* Rva005D6A60MakeArray(int count)
{
	return new FXParticleSystem::LightningEmissionInfo[count];
}
// ?Rva005D6A60DeleteArray@@YAXPAULightningEmissionInfo@FXParticleSystem@@@Z absent-from-retail
void Rva005D6A60DeleteArray(FXParticleSystem::LightningEmissionInfo* array)
{
	delete[] array;
}
