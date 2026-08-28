// cl: /DNDEBUG /MD /EHsc

// FuncInfo for UpgradeCenter::getUpgradeNames at 0x0010B550 owns this cleanup;
// the pad preserves the two frame slots used by its vector return path.
struct Gen_uwt_0002aaa9;
void *operator new(unsigned int, Gen_uwt_0002aaa9 *);
void operator delete(void *, Gen_uwt_0002aaa9 *);

struct Gen_uwp_0002aaa9
{
	int value;
	Gen_uwp_0002aaa9(int);
};

Gen_uwt_0002aaa9 *upgrade_names_placement_tag();
void upgrade_names_placement_sink(void *);

Gen_uwp_0002aaa9 *gen_uw_upgrade_names_00bfd4b8()
{
	char pad[12];
	upgrade_names_placement_sink(pad);
	return new (upgrade_names_placement_tag()) Gen_uwp_0002aaa9(0);
}
