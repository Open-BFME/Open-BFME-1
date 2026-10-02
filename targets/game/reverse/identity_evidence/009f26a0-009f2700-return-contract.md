# BFME 1.03 1050 query wrappers return the accepted object pointer

Retail proves that the `bfmeGo1050C` and `bfmeGo1050D` wrappers return a
pointer in EAX, so their MSVC decorations include the pointer return type.
This corrects the old `QAEX` (`void`) declarations to `QAEPAX` (`void *`); the
function identities, starts, extents, arguments, and call order are unchanged.

At RVA `0x009F2700`, the 36-byte wrapper pushes five arguments, calls
`0x009F5C00`, then immediately executes `ret 14h`. No instruction between the
call and return changes EAX. The callee at `0x009F5C00` loads the accepted
candidate into EAX before returning. The direct retail caller at `0x0014DEE1`
then compares EAX (`0x0014DEE6`) and moves it into ECX as the receiver of an
`Object` method call (`0x0014DEED`/`0x0014DEEF`).

At RVA `0x009F26A0`, the 33-byte wrapper similarly calls `0x009F5C00` and
immediately returns with `ret 10h`. Caller `0x003DCBA0` stores the returned
EAX at `0x003DCC0C`, tests it at `0x003DCC0E` and `0x003DCC9F`, and compares it
at `0x003DCCAB`. These are concrete return-value readers; this evidence makes
no claim about the other direct callers.

The inner result is a candidate object pointer, and the `0x009F2700` caller
uses it as an `Object *` receiver. The opaque return type `void *` preserves
that proven ABI without claiming a more specific object subtype.

Evidence was re-derived from the retail image with `tools/dis_retail.py` and
`tools/callees.py`; the affected translation unit passes the strict scoped
`tools/build.py` byte gate. The source provides the truthful type contract; it
does not redefine the retail identity from an unverified pin.
