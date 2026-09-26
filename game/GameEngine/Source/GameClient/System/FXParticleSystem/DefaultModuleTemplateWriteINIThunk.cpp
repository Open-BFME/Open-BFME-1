// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<6>::writeINI (ledger $05)

class File
{
};

namespace FXParticleSystem
{

void __cdecl writeINI_part1(const void *self, File *file, unsigned int *value);
void __cdecl writeINI_part2(File *file, unsigned int *value);

template <int Category>
class DefaultModuleTemplate
{
};

// MSVC mangles DefaultModuleTemplate<6> as @$05
template <>
class DefaultModuleTemplate<6>
{
public:
	virtual void writeINI(File &file, unsigned int value) const;
};

// ?writeINI@?$DefaultModuleTemplate@$05@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<6>::writeINI(File &file, unsigned int value) const
{
	writeINI_part1(this, &file, &value);
	writeINI_part2(&file, &value);
}

}
