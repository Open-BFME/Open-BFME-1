# Namespace include context for the ICoord2D adoption

PathfindGetRadiusAndCenterE30.cpp is compiled on its own and also textually
included inside RadiusContract003DEE30 in PathfinderAdjustDestination003F6090.cpp.
The normal commit header-dependent gate detected that including the canonical
ICoord2D header inside that namespace first suppressed its later global include
through pragma once. The standalone consumer gate did not cover this context.

Move the caller's existing ICoord2D include above the namespace wrapper. This
defines the established global8B data type once, and lets the included helper
refer to it. No data layout, signature, compiler flag, provider body or alias
is changed. The namespace is existing reconstruction/compiler context, not a
new claim about retail type ownership.

The dependent source was already task145 in batch8;
this repair is not counted again. Its retained1142B row and all43 ordinary
runtime sections/relocation roles remain identical in independent native
before/after objects. Both standalone helper and complete caller pass3/3
retail rows. No callable COMDAT is added, removed or changed. Original source
snapshots, normal objects and graph proof are preserved in batch9/namespace-context.

Separate frozen-census caller preview: before{'clean': False, 'bytes': 0}, after{'clean': False, 'bytes': 0}; no loss. The initial
commit refusal and successful ordinary checks are preserved. The combined
batch scope is rechecked including this extra dependent source. All of its
retained rows were separately leased before editing, and the lease trailers
travel with the batch. This is no new authored-byte or full-link claim.
