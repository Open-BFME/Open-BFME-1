extern int g_bfmeDescriptor3C0600;
extern int g_bfmeDescriptor8C0600;
extern int g_bfmeDescriptor5C0600;

class Rva006C0600Registry
{
public:
	void bfmeResetC0600();
	void bfmeRegisterC0600(void *descriptor, int id);
	void registerDescriptors();
};

void Rva006C0600Registry::registerDescriptors()
{
	bfmeResetC0600();
	bfmeRegisterC0600(&g_bfmeDescriptor3C0600, 3);
	bfmeRegisterC0600(&g_bfmeDescriptor8C0600, 8);
	bfmeRegisterC0600(&g_bfmeDescriptor5C0600, 5);
}
