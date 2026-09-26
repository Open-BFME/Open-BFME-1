// cl: /O2 /Ob0 /EHs-c-

class RenderObjClass
{
public:
	virtual void Delete_This();
	int m_refs;
};

class Rva006FE5A0Host
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual RenderObjClass *slot31(void *key, int flag);
};

void __cdecl Rva00739B30(RenderObjClass *item, bool flag);

extern const char g_bfmeEmptyAscii[];

class Rva006FE5A0Owner
{
public:
	void rva006FE5A0(RenderObjClass **out, void **in);

private:
	unsigned char m_pad[0x84];
	Rva006FE5A0Host *m_84;
};

void Rva006FE5A0Owner::rva006FE5A0(RenderObjClass **out, void **in)
{
	void *key = *in;
	if (key)
		key = (char *)key + 8;
	else
		key = (void *)g_bfmeEmptyAscii;
	*out = m_84->slot31(key, 0);
	if (*out)
	{
		Rva00739B30(*out, 0);
		RenderObjClass *obj = *out;
		if (--obj->m_refs == 0)
			obj->Delete_This();
	}
}
