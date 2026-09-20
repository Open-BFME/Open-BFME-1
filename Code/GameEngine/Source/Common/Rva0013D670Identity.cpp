// Retail 0x0013D670 returns its receiver pointer unchanged.
// The carved boundary proves the three-byte identity body, but no evidence
// names its owning type.
// ?identity@Rva0013D670Identity@@QAEPAXXZ present-unmatched
class Rva0013D670Identity
{
public:
	void *identity();
};

void *Rva0013D670Identity::identity()
{
	return this;
}
