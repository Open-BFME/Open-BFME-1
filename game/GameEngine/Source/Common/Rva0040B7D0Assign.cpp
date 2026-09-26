// cl: /O2 /Ob0

struct CloudEffect
{
	CloudEffect &operator=(const CloudEffect &);
};

CloudEffect g_rva0040b7d0_src;
CloudEffect g_rva0040b7d0_dst;

void rva0040b7d0()
{
	g_rva0040b7d0_dst = g_rva0040b7d0_src;
}
