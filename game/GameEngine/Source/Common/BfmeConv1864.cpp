extern const float g_bfmeZeroYS;

struct BfmeVec3YS
{
	float m_bfmeXYS;
	float m_bfmeYYS;
	float m_bfmeZYS;
};

class BfmeSourceYS
{
public:
	virtual void bfmeS000YS();
	virtual void bfmeS001YS();
	virtual void bfmeS002YS();
	virtual void bfmeS003YS();
	virtual void bfmeS004YS();
	virtual void bfmeS005YS();
	virtual void bfmeS006YS();
	virtual void bfmeS007YS();
	virtual void bfmeS008YS();
	virtual void bfmeS009YS();
	virtual void bfmeS010YS();
	virtual void bfmeS011YS();
	virtual void bfmeS012YS();
	virtual void bfmeS013YS();
	virtual void bfmeS014YS();
	virtual void bfmeS015YS();
	virtual void bfmeS016YS();
	virtual void bfmeS017YS();
	virtual void bfmeS018YS();
	virtual void bfmeS019YS();
	virtual void bfmeS020YS();
	virtual void bfmeS021YS();
	virtual void bfmeS022YS();
	virtual void bfmeS023YS();
	virtual void bfmeS024YS();
	virtual void bfmeS025YS();
	virtual void bfmeS026YS();
	virtual void bfmeS027YS();
	virtual void bfmeS028YS();
	virtual void bfmeS029YS();
	virtual void bfmeS030YS();
	virtual void bfmeS031YS();
	virtual void bfmeS032YS();
	virtual void bfmeS033YS();
	virtual void bfmeS034YS();
	virtual void bfmeS035YS();
	virtual void bfmeS036YS();
	virtual void bfmeS037YS();
	virtual void bfmeS038YS();
	virtual void bfmeS039YS();
	virtual void bfmeS040YS();
	virtual void bfmeS041YS();
	virtual void bfmeS042YS();
	virtual void bfmeS043YS();
	virtual void bfmeS044YS();
	virtual void bfmeS045YS();
	virtual void bfmeS046YS();
	virtual void bfmeS047YS();
	virtual void bfmeS048YS();
	virtual void bfmeS049YS();
	virtual void bfmeS050YS();
	virtual void bfmeS051YS();
	virtual void bfmeS052YS();
	virtual void bfmeS053YS();
	virtual void bfmeS054YS();
	virtual void bfmeS055YS();
	virtual void bfmeS056YS();
	virtual void bfmeS057YS();
	virtual void bfmeS058YS();
	virtual void bfmeS059YS();
	virtual void bfmeS060YS();
	virtual void bfmeS061YS();
	virtual void bfmeS062YS();
	virtual void bfmeS063YS();
	virtual void bfmeS064YS();
	virtual void bfmeS065YS();
	virtual void bfmeS066YS();
	virtual void bfmeS067YS();
	virtual void bfmeS068YS();
	virtual void bfmeS069YS();
	virtual void bfmeS070YS();
	virtual void bfmeS071YS();
	virtual void bfmeS072YS();
	virtual void bfmeS073YS();
	virtual void bfmeS074YS();
	virtual void bfmeS075YS();
	virtual void bfmeS076YS();
	virtual void bfmeS077YS();
	virtual void bfmeS078YS();
	virtual void bfmeS079YS();
	virtual void bfmeS080YS();
	virtual void bfmeS081YS();
	virtual void bfmeS082YS();
	virtual void bfmeS083YS();
	virtual void bfmeS084YS();
	virtual void bfmeS085YS();
	virtual void bfmeS086YS();
	virtual void bfmeS087YS();
	virtual void bfmeS088YS();
	virtual void bfmeS089YS();
	virtual void bfmeS090YS();
	virtual void bfmeS091YS();
	virtual void bfmeS092YS();
	virtual void bfmeS093YS();
	virtual void bfmeS094YS();
	virtual void bfmeS095YS();
	virtual void bfmeS096YS();
	virtual void bfmeS097YS();
	virtual void bfmeS098YS();
	virtual void bfmeS099YS();
	virtual void bfmeS100YS();
	virtual void bfmeS101YS();
	virtual void bfmeS102YS();
	virtual void bfmeS103YS();
	virtual void bfmeS104YS();
	virtual void bfmeS105YS();
	virtual void bfmeS106YS();
	virtual void bfmeS107YS();
	virtual void bfmeS108YS();
	virtual void bfmeS109YS();
	virtual void bfmeS110YS();
	virtual void bfmeS111YS();
	virtual void bfmeS112YS();
	virtual void bfmeS113YS();
	virtual void bfmeS114YS();
	virtual void bfmeS115YS();
	virtual void bfmeS116YS();
	virtual void bfmeS117YS();
	virtual void bfmeS118YS();
	virtual void bfmeS119YS();
	virtual void bfmeS120YS();
	virtual void bfmeS121YS();
	virtual void bfmeS122YS();
	virtual void bfmeS123YS();
	virtual void bfmeS124YS();
	virtual void bfmeS125YS();
	virtual void bfmeS126YS();
	virtual void bfmeS127YS();
	virtual void bfmeS128YS();
	virtual void bfmeS129YS();
	virtual void bfmeS130YS();
	virtual void bfmeS131YS();
	virtual void bfmeS132YS();
	virtual void bfmeS133YS();
	virtual void bfmeS134YS();
	virtual void bfmeS135YS();
	virtual void bfmeS136YS();
	virtual void bfmeS137YS();
	virtual void bfmeS138YS();
	virtual void bfmeS139YS();
	virtual void bfmeS140YS();
	virtual void bfmeS141YS();
	virtual void bfmeS142YS();
	virtual void bfmeS143YS();
	virtual void bfmeS144YS();
	virtual void bfmeS145YS();
	virtual float bfmeCallYS(void *a, void *b, BfmeVec3YS *out);
};

extern BfmeSourceYS *g_bfmeSourceYS;

float __stdcall bfmeGetYS(void *a, void *b, BfmeVec3YS *out)
{
	if (out != 0)
	{
		out->m_bfmeXYS = 0.0f;
		out->m_bfmeYYS = 0.0f;
		out->m_bfmeZYS = 1.0f;
	}

	if (g_bfmeSourceYS != 0)
	{
		return g_bfmeSourceYS->bfmeCallYS(a, b, out);
	}

	return g_bfmeZeroYS;
}
