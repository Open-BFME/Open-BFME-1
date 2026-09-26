// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ emitter for the anonymous retail placement cleanup at
// 0x00C52AE0.  The owning FuncInfo is the real
// VectorClass<Vector3>::VectorClass(int, const Vector3 *) constructor at
// 0x007B9EE0; its vector.h body uses placement array construction when an
// external array is supplied.  The retail funclet calls the pinned placement
// delete target at 0x00033D3E.  Only the compiler-local .text$x label is
// claimed below, so this helper does not invent a retail parent identity.

struct Gen_uwt_00033d3e;
void *operator new[](unsigned int, Gen_uwt_00033d3e *);
void operator delete(void *, Gen_uwt_00033d3e *);

struct Gen_uwp_00033d3e
{
	Gen_uwp_00033d3e();
};

Gen_uwp_00033d3e *gen_uw_place_00c52ae0(int count, Gen_uwt_00033d3e *array)
{
	return new (array) Gen_uwp_00033d3e[count];
}
