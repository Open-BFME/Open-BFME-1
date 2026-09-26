// cl: /O2 /Ob0

class Rva005C0FD0
{
public:
	void *use_facet(const void *);
};

char g_rva005c0fd0_id;

void *rva005c0fd0(Rva005C0FD0 *obj)
{
	return obj->use_facet(&g_rva005c0fd0_id);
}
