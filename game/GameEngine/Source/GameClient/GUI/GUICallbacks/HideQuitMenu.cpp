// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WindowManager;

// Retail tail-calls ILT 000290D2, whose body is the existing eight-byte
// Rva00465B80::apply in TinyByteFieldSetters.cpp. This address-qualified
// provider writes 1 at receiver+1AC; it does not establish a semantic owner.
class Rva00465B80
{
public:
	void apply();
	char m_lead[0x1AC];
	char m_flag;
};

// Globals filled by DIR32 from retail.
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;

// ?HideQuitMenu@@YAXXZ
void HideQuitMenu()
{
	if (reinterpret_cast<void * &>(g_obj12F4AD4))
		reinterpret_cast<Rva00465B80 *>(g_rva012F19E8WindowManager)->apply();
}
