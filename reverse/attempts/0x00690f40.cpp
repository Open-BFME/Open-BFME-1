// address-derived name; owning class unidentified
// partial score=0.35 date=2026-09-09
// C-style explicit-vtable object; printf format string at 0x0111B944 is
// "Removing %S\n" (read from retail .rdata). First 0x1a bytes byte-exact;
// remainder differs only in failure-block placement/tail-merging.
extern "C" __declspec(dllimport) int __cdecl printf(const char *fmt, ...);

struct Rva00690F40Iface;
struct Rva00690F40IfaceVtbl
{
	void *v00, *v04, *v08, *v0C, *v10, *v14, *v18, *v1C, *v20, *v24;
	void *v28, *v2C, *v30, *v34, *v38, *v3C, *v40, *v44, *v48, *v4C;
	int (__stdcall *v50)(Rva00690F40Iface *self, Rva00690F40Iface **out);
};

struct Rva00690F40Iface
{
	Rva00690F40IfaceVtbl *lpVtbl;
};

struct Rva00690F40LocalVtbl
{
	void *v00, *v04;
	void (__stdcall *release)(Rva00690F40Iface *self);
	void *v0C, *v10, *v14, *v18, *v1C, *v20;
	int (__stdcall *v24)(Rva00690F40Iface *self, void *ctx);
};

class Rva00690F40Owner
{
public:
	bool method();

	char m_pad00[4];
	unsigned short *m_name;
	char m_pad08[1];
	char m_flag;
	char m_pad0A[6];
	Rva00690F40Iface *m_iface;
};

bool Rva00690F40Owner::method()
{
	Rva00690F40Iface *local = 0;
	Rva00690F40Iface *iface = m_iface;
	int hr = ((Rva00690F40IfaceVtbl *)iface->lpVtbl)->v50(iface, &local);
	if (hr >= 0)
		goto step2;

fail:
	if (local)
		((Rva00690F40LocalVtbl *)local->lpVtbl)->release(local);
	return false;

step2:
	printf("Removing %S\n", m_name);
	{
		Rva00690F40LocalVtbl *vtbl = (Rva00690F40LocalVtbl *)local->lpVtbl;
		int hr2 = vtbl->v24(local, m_name);
		if (hr2 < 0)
			goto fail;
	}

	if (local)
		((Rva00690F40LocalVtbl *)local->lpVtbl)->release(local);
	m_flag = 0;
	return true;
}
