// cl: /EHsc
//
// Anonymous MSVC 7.1 multiple-inheritance destructor unwind bodies.
// Retail labels them Unwind@; no parent identity survives. The second
// base destructor is the already-pinned Gen_uw_00001c80 thunk.

struct Gen_uw_00001c80 {
	virtual void f() = 0;
	~Gen_uw_00001c80();
};

struct SnapshotMiUnwindBase8 {
	virtual void f() = 0;
	int x;
	~SnapshotMiUnwindBase8();
};

struct SnapshotMiUnwindObj8 : SnapshotMiUnwindBase8, Gen_uw_00001c80 {
	~SnapshotMiUnwindObj8();
};

struct SnapshotMiUnwindObj8p : SnapshotMiUnwindBase8, Gen_uw_00001c80 {
	~SnapshotMiUnwindObj8p();
};

extern void snapshot_mi_unwind_ext();
extern void snapshot_mi_unwind_sink(void *);

// ??1SnapshotMiUnwindObj8@@QAE@XZ absent-from-retail
SnapshotMiUnwindObj8::~SnapshotMiUnwindObj8()
{
	snapshot_mi_unwind_ext();
}

// ??1SnapshotMiUnwindObj8p@@QAE@XZ absent-from-retail
SnapshotMiUnwindObj8p::~SnapshotMiUnwindObj8p()
{
	char pad[12];
	snapshot_mi_unwind_sink(pad);
	snapshot_mi_unwind_ext();
}
