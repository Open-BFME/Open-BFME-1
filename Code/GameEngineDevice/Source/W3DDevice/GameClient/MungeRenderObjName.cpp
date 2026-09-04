// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail 0x008FED30. Build the render-object cache key and
// normalize it to lower case. Empty texture and subobject views use the
// retail sentinel strings.

extern "C" __declspec(dllimport) int sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) char *_strlwr(char *string);

struct StrView008FED30
{
	char *start;
	char *finish;
};

void Munge_Render_Obj_Name(
	char *newname,
	const char *name,
	float scale,
	int color,
	StrView008FED30 *texture,
	StrView008FED30 *subobj,
	int extra)
{
	StrView008FED30 *sub_view = subobj;
	char *sub_start = sub_view->start;
	char *sub = sub_start != sub_view->finish ? sub_start : "@NO_SUBOBJ&";
	StrView008FED30 *tex_view = texture;
	char *tex_start = tex_view->start;
	char *tex = tex_start != tex_view->finish ? tex_start : "@NO_TEXTURE&";
	sprintf(newname, "#%d!%g!%s#%s#%s!%d", color, scale, tex, name, sub, extra);
	_strlwr(newname);
}
