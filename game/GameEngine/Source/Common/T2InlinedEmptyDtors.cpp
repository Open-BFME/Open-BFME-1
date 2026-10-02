// cl: /DNDEBUG /MD /EHsc
// Scalar deleting destructors whose class destructor is empty and whose class
// holds nothing that needs destroying, so the destructor inlined into the stub
// and all that is left of it is the vptr store the compiler inserts.  Each row
// installs a different vftable address, which is what says these are different
// classes; the addresses themselves are DIR32 the patcher fills from retail.

struct T2EmptyDtor_008018a0 { virtual ~T2EmptyDtor_008018a0(); };
// ??1T2EmptyDtor_008018a0@@UAE@XZ absent-from-retail
T2EmptyDtor_008018a0::~T2EmptyDtor_008018a0() {}

struct T2EmptyDtor_00802360 { virtual ~T2EmptyDtor_00802360(); };
// ??1T2EmptyDtor_00802360@@UAE@XZ absent-from-retail
T2EmptyDtor_00802360::~T2EmptyDtor_00802360() {}

struct T2EmptyDtor_00802450 { virtual ~T2EmptyDtor_00802450(); };
// ??1T2EmptyDtor_00802450@@UAE@XZ absent-from-retail
T2EmptyDtor_00802450::~T2EmptyDtor_00802450() {}

struct T2EmptyDtor_00802a70 { virtual ~T2EmptyDtor_00802a70(); };
// ??1T2EmptyDtor_00802a70@@UAE@XZ absent-from-retail
T2EmptyDtor_00802a70::~T2EmptyDtor_00802a70() {}

struct T2EmptyDtor_00802ea0 { virtual ~T2EmptyDtor_00802ea0(); };
// ??1T2EmptyDtor_00802ea0@@UAE@XZ absent-from-retail
T2EmptyDtor_00802ea0::~T2EmptyDtor_00802ea0() {}

struct T2EmptyDtor_00806460 { virtual ~T2EmptyDtor_00806460(); };
// ??1T2EmptyDtor_00806460@@UAE@XZ absent-from-retail
T2EmptyDtor_00806460::~T2EmptyDtor_00806460() {}

struct T2EmptyDtor_00832560 { virtual ~T2EmptyDtor_00832560(); };
// ??1T2EmptyDtor_00832560@@UAE@XZ absent-from-retail
T2EmptyDtor_00832560::~T2EmptyDtor_00832560() {}

