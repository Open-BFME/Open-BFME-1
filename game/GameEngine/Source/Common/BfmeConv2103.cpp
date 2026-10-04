class StreamWriter
{
public:
	void append(const char *s);
	void separate(int ch);
};

struct Vector3
{
	float X;
	float Y;
	float Z;
};

// Retail .data 0x01084068 is the compiler literal __real@437f0000 (255.0f).
// MSVC mints that assembler name itself for the literal, and C++ cannot spell
// it: under `extern "C"` the object symbol gains a leading underscore
// (___real@437f0000, which nothing defines), and `__identifier` without
// extern "C" mangles to ?__real@437f0000@@3QBDB.  Writing the literal is this
// repo's convention (W3DWater.cpp, WaterTracksObjRender.cpp, W3DWaterTracks.cpp)
// and emits the same retail-verified COMDAT copy eight objects already carry.
extern const float g_rva0107533C;

// The four StreamWriter calls this file makes land on retail ILT thunks
// (VA 0x0002DFEC append, 0x0002408C separate, 0x0002CE5D bfmeFormatIntYS and
// 0x0000F376 formatReal) whose ledger owners are the ?j_XXXXXXXX@@YAXXZ
// gen-thunks, so each is reached through a call cast exactly as
// GiantBirdGuardReturnState_update.cpp does.  append and separate are members
// (ecx = writer); formatReal and bfmeFormatIntYS are free functions that take
// the writer as their first argument.
extern void j_0002dfec();
extern void j_0002408c();
extern void j_0002ce5d();
extern void j_0000f376();

typedef const char *(StreamWriter::*AppendCall)(const char *);
typedef void (StreamWriter::*SeparateCall)(int);
typedef StreamWriter *(*FormatIntCall)(StreamWriter *, int);
typedef StreamWriter *(*FormatRealCall)(StreamWriter *, double);

StreamWriter *bfmeWriteYR(StreamWriter *w, Vector3 *v)
{
	union { void *asVoid; AppendCall asMember; } appendCast;
	union { void *asVoid; SeparateCall asMember; } separateCast;
	union { void *asVoid; FormatRealCall asFunction; } formatRealCast;
	appendCast.asVoid = (void *)j_0002dfec;
	separateCast.asVoid = (void *)j_0002408c;
	formatRealCast.asVoid = (void *)j_0000f376;

	(w->*appendCast.asMember)("X:");

	StreamWriter *wx = formatRealCast.asFunction(w, v->X);

	(wx->*separateCast.asMember)(0x20);
	(w->*appendCast.asMember)("Y:");

	StreamWriter *wy = formatRealCast.asFunction(w, v->Y);

	(wy->*separateCast.asMember)(0x20);

	(w->*appendCast.asMember)("Z:");
	formatRealCast.asFunction(w, v->Z);

	return w;
}

StreamWriter *bfmeWriteYS(StreamWriter *w, Vector3 *v)
{
	union { void *asVoid; AppendCall asMember; } appendCast;
	union { void *asVoid; SeparateCall asMember; } separateCast;
	union { void *asVoid; FormatIntCall asFunction; } formatIntCast;
	appendCast.asVoid = (void *)j_0002dfec;
	separateCast.asVoid = (void *)j_0002408c;
	formatIntCast.asVoid = (void *)j_0002ce5d;

	(w->*appendCast.asMember)("R:");

	StreamWriter *wr = formatIntCast.asFunction(w, (int)(*(volatile float *)&v->X * 255.0f + g_rva0107533C));

	(wr->*separateCast.asMember)(0x20);
	(w->*appendCast.asMember)("G:");

	StreamWriter *wg = formatIntCast.asFunction(w, (int)(*(volatile float *)&v->Y * 255.0f + g_rva0107533C));

	(wg->*separateCast.asMember)(0x20);
	(w->*appendCast.asMember)("B:");
	formatIntCast.asFunction(w, (int)(*(volatile float *)&v->Z * 255.0f + g_rva0107533C));

	return w;
}