// ?Munge_Render_Obj_Name@@YAXPADHMPBDPAUStrView008FED30@@2H@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// BFME Munge_Render_Obj_Name — retail 0x008FED30
// Format "#%d!%g!%s#%s#%s!%d" with empty STLport-string sentinels.

extern "C" __declspec(dllimport) int sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) char *_strlwr(char *string);

struct StrView008FED30
{
	char *start;
	char *finish;
};

void Munge_Render_Obj_Name(
	char *newname,
	int color,
	float scale,
	const char *name,
	StrView008FED30 *texture,
	StrView008FED30 *subobj,
	int extra)
{
	char *sub_start = subobj->start;
	char *sub = sub_start;
	if (sub_start == subobj->finish)
		sub = "@NO_SUBOBJ&";
	char *tex_start = texture->start;
	char *tex = tex_start;
	if (tex_start == texture->finish)
		tex = "@NO_TEXTURE&";
	sprintf(newname, "#%d!%g!%s#%s#%s!%d", color, scale, name, tex, sub, extra);
	_strlwr(newname);
}
