// cl: /O2 /Ob0

class Rva005380A0
{
public:
	void *use_facet(const void *);
};

char g_rva005380a0_id;

void *rva005380a0(Rva005380A0 *obj)
{
	return obj->use_facet(&g_rva005380a0_id);
}
