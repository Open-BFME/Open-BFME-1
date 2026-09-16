// Retail 0x00339120, 146 bytes.
//
// The body allocates a 0xd0-byte particle-system object from a template,
// registers it under a temporary retail AsciiString, and destroys that string
// before restoring the EH chain.  The owner is not identified by a named
// caller or vtable, so its class and method retain the retail address.

class BfmeTmplERD;

class BfmeSysERD
{
public:
	BfmeSysERD(BfmeTmplERD *tmpl);

	unsigned char m_bfmeBodyERD[0xd0];
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class BfmeStrEAU;
class BfmeThingEAU;

class ParticleSystemManager
{
public:
	void bfmeRegisterEAU(BfmeStrEAU *text, BfmeThingEAU *thing);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Rva00339120Owner
{
public:
	void rva00339120(const char *name, void *param);
};

// ?rva00339120@Rva00339120Owner@@QAEXPBDPAX@Z
void Rva00339120Owner::rva00339120(const char *name, void *param)
{
	BfmeSysERD *thing = new BfmeSysERD((BfmeTmplERD *)param);

	{
		BFMERetailAsciiString text(name);

		TheParticleSystemManager->bfmeRegisterEAU(
			(BfmeStrEAU *)&text, (BfmeThingEAU *)thing);
	}
}
