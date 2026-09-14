// cl: /EHs-c-

#include <exception>

namespace _STL {

// The complete destructor at 0x0082AE60 is defined in STLBadAllocDtor.cpp.
// This focused declaration preserves that matched STLport hierarchy and lets
// MSVC emit the authentic scalar-deleting wrapper at 0x0082C040.
class bad_alloc : public std::exception
{
public:
	virtual ~bad_alloc();
};

class Rva0082AE60Exc : public bad_alloc
{
public:
	virtual ~Rva0082AE60Exc();
};

class Rva0082AE80Exc : public bad_alloc
{
public:
	virtual ~Rva0082AE80Exc();
};

class Rva0082AEA0Exc : public Rva0082AE60Exc
{
public:
	virtual ~Rva0082AEA0Exc();
};

class Rva0082AEC0Exc : public Rva0082AE60Exc
{
public:
	virtual ~Rva0082AEC0Exc();
};

class Rva0082AEE0Exc : public Rva0082AE60Exc
{
public:
	virtual ~Rva0082AEE0Exc();
};

class Rva0082AF00Exc : public Rva0082AE60Exc
{
public:
	virtual ~Rva0082AF00Exc();
};

class Rva0082AF20Exc : public Rva0082AE80Exc
{
public:
	virtual ~Rva0082AF20Exc();
};

class Rva0082AF40Exc : public Rva0082AE80Exc
{
public:
	virtual ~Rva0082AF40Exc();
};

class Rva0082AF60Exc : public Rva0082AE80Exc
{
public:
	virtual ~Rva0082AF60Exc();
};

void ForceRva0082AE60ExcDeletingDestructor()
{
	Rva0082AE60Exc value;
}

void ForceRva0082AE80ExcDeletingDestructor()
{
	Rva0082AE80Exc value;
}

void ForceRva0082AEA0ExcDeletingDestructor()
{
	Rva0082AEA0Exc value;
}

void ForceRva0082AEC0ExcDeletingDestructor()
{
	Rva0082AEC0Exc value;
}

void ForceRva0082AEE0ExcDeletingDestructor()
{
	Rva0082AEE0Exc value;
}

void ForceRva0082AF00ExcDeletingDestructor()
{
	Rva0082AF00Exc value;
}

void ForceRva0082AF20ExcDeletingDestructor()
{
	Rva0082AF20Exc value;
}

void ForceRva0082AF40ExcDeletingDestructor()
{
	Rva0082AF40Exc value;
}

void ForceRva0082AF60ExcDeletingDestructor()
{
	Rva0082AF60Exc value;
}

}
