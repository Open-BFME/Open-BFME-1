// ?d_009f55d0@@YAXXZ
// partial score=0.72 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
struct S4SortElem24 { int m_key; int m_values[5]; };
struct S4Cmp009F4BF0 {
 bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const;
};
namespace _STL {
template <class Iter, class Compare>
void push_heap(Iter first, Iter last, Compare comp);
template <class Iter, class Distance, class Tp, class Compare>
void __push_heap_aux(Iter first, Iter last, Compare comp, Distance *, Tp *)
{
 push_heap(first, last, comp);
}
template void __push_heap_aux<S4SortElem24 *, int, S4SortElem24, S4Cmp009F4BF0>(
 S4SortElem24 *, S4SortElem24 *, S4Cmp009F4BF0, int *, S4SortElem24 *);
}
