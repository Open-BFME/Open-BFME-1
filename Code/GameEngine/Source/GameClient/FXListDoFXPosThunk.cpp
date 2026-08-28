// readable body of ?doFXPos@FXList@@IBEXPBUCoord3D@@PBVMatrix3D@@M0M@Z: Code/GameEngine/Source/GameClient/FXList.cpp
// TU-scoped slice for FXList::doFXPos.  Retail splits this into an
// incremental-link thunk (0x0003E360) and the loop body (0x001D6770); the body
// is reached only through the thunk, so it is modelled here as a forwarding
// shim whose single method carries the body.  Nothing outside this file sees
// either declaration.
struct Coord3D;
class Matrix3D;

typedef float Real;

// ABI slice of FXNugget.  Slot 0 stands for the MemoryPoolObject virtual that
// FXNugget inherits; doFXPos is slot 1, which is the `call [eax+4]` retail
// makes on each element.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	virtual void slot0_memoryPoolObject() = 0;
	virtual void doFXPos(const Coord3D *, const Matrix3D *, Real, const Coord3D *, Real) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
protected:
	void doFXPos(const Coord3D *, const Matrix3D *, Real, const Coord3D *, Real) const;
};

// The nugget sequence is the first member of FXList (retail reads begin at
// [this+0] and end at [this+4], and reloads end after every call), so FXList
// carries no vptr in this build.
class FXListDoFXPosShim
{
public:
	// `secondary` is deliberately declared volatile.  Retail keeps the third
	// and fifth arguments in ebx/ebp across the loop and reloads the fourth
	// from its parameter slot every iteration; MSVC 7.1 otherwise ranks
	// enregistration candidates by descending stack slot and takes the fourth
	// and fifth.  The qualifier removes the fourth from the candidate set at
	// zero code cost and is the only spelling measured to do so -- it is a
	// codegen device local to this shim, not a claim about the retail
	// declaration, whose reconstructed name carries no such qualifier.
	void run(const Coord3D *, const Matrix3D *, Real, const Coord3D *volatile, Real) const;

private:
	FXNugget **m_begin;
	FXNugget **m_end;
};

// ?doFXPos@FXList@@IBEXPBUCoord3D@@PBVMatrix3D@@M0M@Z
void FXList::doFXPos(const Coord3D *pos, const Matrix3D *mtx, Real speed, const Coord3D *secondary, Real radius) const
{
	((const FXListDoFXPosShim *)this)->run(pos, mtx, speed, secondary, radius);
}

// ?run@FXListDoFXPosShim@@QBEXPBUCoord3D@@PBVMatrix3D@@MRBU2@M@Z
void FXListDoFXPosShim::run(const Coord3D *pos, const Matrix3D *mtx, Real speed, const Coord3D *volatile secondary, Real radius) const
{
	for (FXNugget **it = m_begin; it != m_end; ++it)
		(*it)->doFXPos(pos, mtx, speed, secondary, radius);
}
