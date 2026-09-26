// cl: /MD
#include "lua.h"
#include "lobject.h"

struct Rva00997C60Value : TObject
{
	int truthy() const;
};

int Rva00997C60Value::truthy() const
{
	if (ttype == LUA_TNIL)
		return 0;
	if (ttype == 6)
		return value.b;
	return 1;
}
