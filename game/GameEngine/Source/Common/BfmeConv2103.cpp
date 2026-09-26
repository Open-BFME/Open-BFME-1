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

StreamWriter *formatReal(StreamWriter *w, double v);
StreamWriter *bfmeFormatIntYS(StreamWriter *w, int v);

extern float g_bfmeScaleB3;
extern const float g_bfmeK1253;

StreamWriter *bfmeWriteYR(StreamWriter *w, Vector3 *v)
{
	w->append("X:");

	StreamWriter *wx = formatReal(w, v->X);

	wx->separate(0x20);
	w->append("Y:");

	StreamWriter *wy = formatReal(w, v->Y);

	wy->separate(0x20);

	w->append("Z:");
	formatReal(w, v->Z);

	return w;
}

StreamWriter *bfmeWriteYS(StreamWriter *w, Vector3 *v)
{
	w->append("R:");

	StreamWriter *wr = bfmeFormatIntYS(w, (int)(*(volatile float *)&v->X * g_bfmeScaleB3 + g_bfmeK1253));

	wr->separate(0x20);
	w->append("G:");

	StreamWriter *wg = bfmeFormatIntYS(w, (int)(*(volatile float *)&v->Y * g_bfmeScaleB3 + g_bfmeK1253));

	wg->separate(0x20);
	w->append("B:");
	bfmeFormatIntYS(w, (int)(*(volatile float *)&v->Z * g_bfmeScaleB3 + g_bfmeK1253));

	return w;
}
