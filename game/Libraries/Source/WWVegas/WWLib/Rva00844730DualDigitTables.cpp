// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// The retail body dispatches two three-argument calls through slot +0x24;
// its distinct table ranges start at the independently read retail literals.
class Rva00844730TableSink
{
public:
	virtual void reserved00();
	virtual void reserved04();
	virtual void reserved08();
	virtual void reserved0c();
	virtual void reserved10();
	virtual void reserved14();
	virtual void reserved18();
	virtual void reserved1c();
	virtual void reserved20();
	virtual void accept(const char *first, const char *last, int value);
};

void rva00844730DispatchTables(int first, int second,
	Rva00844730TableSink *sink)
{
	static const char numbers[] = "0123456789";
	static const char letters[] = "aAbBcCdDeEfF";
	sink->accept(numbers, numbers + 10, first);
	sink->accept(letters, letters + 10, second);
}
