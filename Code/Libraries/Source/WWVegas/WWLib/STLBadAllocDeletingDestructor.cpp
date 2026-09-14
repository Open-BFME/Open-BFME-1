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

}
