// Open-BFME5 conversions.

class BfmeO1146
{
public:
	virtual void bfmeV001146(void) = 0;
	virtual void bfmeV011146(void) = 0;
	virtual void bfmeV021146(void) = 0;
	virtual void bfmeV031146(void) = 0;
	virtual void bfmeV041146(void) = 0;
	virtual void bfmeV051146(void) = 0;
	virtual void bfmeV061146(void) = 0;
	virtual void bfmeV071146(void) = 0;
	virtual void bfmeV081146(void) = 0;
	virtual void bfmeV091146(void) = 0;
	virtual void bfmeV101146(void) = 0;
	virtual void bfmeV111146(void) = 0;
	virtual void bfmeV121146(void) = 0;
	virtual void bfmeV131146(void) = 0;
	virtual void bfmeV141146(void) = 0;
	virtual void bfmeV151146(void) = 0;
	virtual void bfmeV161146(void) = 0;
	virtual void bfmeV171146(void) = 0;
	virtual void bfmeV181146(void) = 0;
	virtual void bfmeV191146(void) = 0;
	virtual void bfmeV201146(void) = 0;
	virtual void bfmeV211146(void) = 0;
	virtual void bfmeV221146(void) = 0;
	virtual void bfmeV231146(void) = 0;
	virtual void bfmeV241146(void) = 0;
	virtual void bfmeV251146(void) = 0;
	virtual void bfmeV261146(void) = 0;
	virtual void bfmeV271146(void) = 0;
	virtual void bfmeV281146(void) = 0;
	virtual void bfmeV291146(void) = 0;
	virtual void bfmeV301146(void) = 0;
	virtual void bfmeV311146(void) = 0;
	virtual void bfmeV321146(void) = 0;
	virtual void bfmeV331146(void) = 0;
	virtual void bfmeV341146(void) = 0;
	virtual void bfmeV351146(void) = 0;
	virtual void bfmeV361146(void) = 0;
	virtual void bfmeV371146(void) = 0;
	virtual void bfmeV381146(void) = 0;
	virtual void bfmeV391146(void) = 0;
	virtual void bfmeV401146(void) = 0;
	virtual void bfmeV411146(void) = 0;
	virtual void bfmeV421146(void) = 0;
	virtual int bfmeVac1146(void) = 0;
	virtual void bfmeVb01146(int a) = 0;
	virtual void bfmeV451146(void) = 0;
	virtual void bfmeVb81146(int a) = 0;
	virtual void bfmeVbc1146(int a, int b) = 0;
};

extern "C" BfmeO1146 *volatile g_bfmeO1146;

void __stdcall bfmeGo1146(char a, int b)
{
	BfmeO1146 *o = g_bfmeO1146;

	if (a) {
		o->bfmeVb01146(1);
		g_bfmeO1146->bfmeVb81146(1);
		g_bfmeO1146->bfmeVbc1146(b, 1);
	} else if (o->bfmeVac1146() == 1) {
		g_bfmeO1146->bfmeVbc1146(b, -1);
	}
}

void __stdcall bfmeGo1146B(char a, int b)
{
	BfmeO1146 *o = g_bfmeO1146;

	if (a) {
		o->bfmeVb01146(1);
		g_bfmeO1146->bfmeVb81146(6);
		g_bfmeO1146->bfmeVbc1146(b, 1);
	} else {
		o->bfmeVb01146(1);
		g_bfmeO1146->bfmeVb81146(6);
		g_bfmeO1146->bfmeVbc1146(b, -1);
	}
}
