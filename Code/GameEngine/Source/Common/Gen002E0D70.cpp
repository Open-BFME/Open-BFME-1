// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

struct Gen002E0D70Rec
{
	int a;
	AsciiString name;
	char flag;
};

void gen002E0BC0(void *a, Gen002E0D70Rec *p, Gen002E0D70Rec *q, Gen002E0D70Rec rec, void *c, int zero);

void gen002E0D70(void *a, Gen002E0D70Rec *last, int, void *c)
{
	void *arg4 = c;
	Gen002E0D70Rec *p = last;
	gen002E0BC0(a, p - 1, p - 1, p[-1], arg4, 0);
}
