# Gen-alias COMDAT homes replaced by real C++ instantiations (s553 batch a)

Each row below was a `?dup_` gen-alias home whose bytes came from a COMDAT
another TU emits under a different name. Retail was linked without
identical-COMDAT folding, so each address has exactly one identity.

Facts per row, from BFME 1 retail and this repo's build:

- the named matched C++ source emits a COMDAT of the row's size whose bytes
  equal retail outside relocation slots (fewer than a quarter of the bytes are
  relocation slots), and build.sh verifies it with its relocations;
- `tools/ilt_oracle.py check NAME RVA` CONFIRMS the decorated name at the
  address (exact thunk-table slot window; chance fit ~6e-4), and it is the
  only CONFIRMED byte-equal candidate across build/match objects;
- no symbols.csv pin gives the address a different real name.

Types in the names come from the sources' existing declarations (Zero Hour
headers or address-derived views).

| RVA | bytes | previous row | source | name |
|---|---|---|---|---|
| 0x62c660 | 22 | `?dup_0062c660@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??0?$pair@U?$_Rb_tree_iterator@PAVGameSpyStagingRoom@@U?$_Const_traits@PAVGameSpyStagingRoom@@@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@PAVGameSpyStagingRoom@@U?$_Const_traits@PAVGameSpyStagingRoom@@@_STL@@@1@AB_N@Z` |
| 0x62c810 | 22 | `?dup_0062c810@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??0?$pair@U?$_Rb_tree_iterator@PAVGameSpyStagingRoom@@U?$_Nonconst_traits@PAVGameSpyStagingRoom@@@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@PAVGameSpyStagingRoom@@U?$_Nonconst_traits@PAVGameSpyStagingRoom@@@_STL@@@1@AB_N@Z` |
| 0x63ab50 | 35 | `?dup_0063ab50@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??0?$_Deque_iterator@VBuddyRequest@@U?$_Nonconst_traits@VBuddyRequest@@@_STL@@@_STL@@QAE@ABU01@@Z` |
| 0x63aba0 | 35 | `?dup_0063aba0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??0?$_Deque_iterator@VBuddyResponse@@U?$_Nonconst_traits@VBuddyResponse@@@_STL@@@_STL@@QAE@ABU01@@Z` |
| 0x63aea0 | 22 | `?dup_0063aea0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$?9VBuddyRequest@@@_STL@@YA_NABU?$_Deque_iterator_base@VBuddyRequest@@@0@0@Z` |
| 0x63aec0 | 22 | `?dup_0063aec0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$?9VBuddyResponse@@@_STL@@YA_NABU?$_Deque_iterator_base@VBuddyResponse@@@0@0@Z` |
| 0x63af10 | 41 | `?dup_0063af10@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_ptrs@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63af50 | 38 | `?dup_0063af50@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_backward_ptrs@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63af90 | 41 | `?dup_0063af90@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_ptrs@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63afd0 | 38 | `?dup_0063afd0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_backward_ptrs@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63b670 | 41 | `?dup_0063b670@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_aux@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63b6b0 | 38 | `?dup_0063b6b0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_backward_aux@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63b6e0 | 41 | `?dup_0063b6e0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_aux@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63b720 | 38 | `?dup_0063b720@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$__copy_backward_aux@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x63bb10 | 41 | `?dup_0063bb10@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$copy@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00@Z` |
| 0x63bb50 | 38 | `?dup_0063bb50@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$copy_backward@PAPAVBuddyRequest@@PAPAV1@@_STL@@YAPAPAVBuddyRequest@@PAPAV1@00@Z` |
| 0x63bb80 | 41 | `?dup_0063bb80@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$copy@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00@Z` |
| 0x63bbc0 | 38 | `?dup_0063bbc0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `??$copy_backward@PAPAVBuddyResponse@@PAPAV1@@_STL@@YAPAPAVBuddyResponse@@PAPAV1@00@Z` |
| 0x63dfe0 | 55 | `?dup_0063dfe0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `?push_back@?$deque@VBuddyRequest@@V?$allocator@VBuddyRequest@@@_STL@@@_STL@@QAEXABVBuddyRequest@@@Z` |
| 0x63e030 | 55 | `?dup_0063e030@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `?push_back@?$deque@VBuddyResponse@@V?$allocator@VBuddyResponse@@@_STL@@@_STL@@QAEXABVBuddyResponse@@@Z` |
| 0x63e1a0 | 55 | `?dup_0063e1a0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `?push@?$queue@VBuddyRequest@@V?$deque@VBuddyRequest@@V?$allocator@VBuddyRequest@@@_STL@@@_STL@@@_STL@@QAEXABVBuddyRequest@@@Z` |
| 0x63e1f0 | 55 | `?dup_0063e1f0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp | `?push@?$queue@VBuddyResponse@@V?$deque@VBuddyResponse@@V?$allocator@VBuddyResponse@@@_STL@@@_STL@@@_STL@@QAEXABVBuddyResponse@@@Z` |
| 0x6405f0 | 41 | `?dup_006405f0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_ptrs@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x640630 | 38 | `?dup_00640630@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_ptrs@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x640c50 | 41 | `?dup_00640c50@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_aux@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x640c90 | 38 | `?dup_00640c90@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_aux@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x640df0 | 41 | `?dup_00640df0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00@Z` |
| 0x640e30 | 38 | `?dup_00640e30@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy_backward@PAPAVGameResultsRequest@@PAPAV1@@_STL@@YAPAPAVGameResultsRequest@@PAPAV1@00@Z` |
| 0x643ad0 | 41 | `?dup_00643ad0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_ptrs@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x643b10 | 38 | `?dup_00643b10@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_ptrs@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x644870 | 41 | `?dup_00644870@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_aux@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x6448b0 | 38 | `?dup_006448b0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_aux@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x645340 | 41 | `?dup_00645340@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00@Z` |
| 0x645380 | 38 | `?dup_00645380@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy_backward@PAPAVPeerResponse@@PAPAV1@@_STL@@YAPAPAVPeerResponse@@PAPAV1@00@Z` |
| 0x65eef0 | 41 | `?dup_0065eef0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_ptrs@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65ef30 | 38 | `?dup_0065ef30@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_ptrs@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65ef60 | 41 | `?dup_0065ef60@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_ptrs@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65efa0 | 38 | `?dup_0065efa0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_ptrs@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65f4b0 | 41 | `?dup_0065f4b0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_aux@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65f4f0 | 38 | `?dup_0065f4f0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_aux@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65f520 | 41 | `?dup_0065f520@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_aux@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65f560 | 38 | `?dup_0065f560@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$__copy_backward_aux@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x65f7b0 | 41 | `?dup_0065f7b0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00@Z` |
| 0x65f7f0 | 38 | `?dup_0065f7f0@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy_backward@PAPAVPingRequest@@PAPAV1@@_STL@@YAPAPAVPingRequest@@PAPAV1@00@Z` |
| 0x65f820 | 41 | `?dup_0065f820@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00@Z` |
| 0x65f860 | 38 | `?dup_0065f860@@YAXXZ` | game/GameEngine/Source/GameNetwork/GameSpy/GameSpyContainerBodies.cpp | `??$copy_backward@PAPAVPingResponse@@PAPAV1@@_STL@@YAPAPAVPingResponse@@PAPAV1@00@Z` |
