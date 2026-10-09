# Creation helper retry at RVA 0x001D9630

The target remains a generated dump. This run banks a complete C++ attempt and claims no exact recovery. The tested base is `46ef98977030087894f131cdf0448d17d1f980c4`; the model is `gpt-6.1-sol`. Source snapshots, scripts, complete decodes and unedited probe output are retained under `build/001d9630-retry/`. The measured score uses `tools/finish_measure.py`, including its penalty for size differences; it is distinct from probe's normalized instruction score.

## New evidence and hypothesis

The previous bank omitted force and ownership paths and declared several indirect calls as ordinary members. The current landed nugget constructor, animation copy helper, AI command constructor, particle creation helper and intrusive handle detach body supply independently inspectable field and receiver evidence. A complete reconstruction using those declarations should reproduce the missing branches and improve on the bank. An unchanged or worse measured complete body would refute that experiment. The new body improves the tool's measured comparison, so the initial hypothesis was supported.

The final productive experiment makes the compiler see the already landed `calcRandomForce` source body. Its definition is static in the original `ObjectCreationList.cpp`, and its decoded output writes three consecutive floats. A declaration-only callee leaves an additional force local in the frame. A static noinline copy restores the frame but produces a private register convention absent from retail. An inline noinline copy restores the frame while retaining the decoded cdecl argument convention. These are separately measured trials, not an inferred pin. The copied helper is not itself byte exact in this smaller translation unit. Its source is preserved and that context difference remains a blocker.

## Boundary and caller ABI

`retail.txt` decodes the complete target. Its final instruction is `ret 0x20`; the conditional early exits reach its shared epilogue, and no target branch or tail jump leaves the extent. `checked-target.log` records the direct callee inventory. The complete caller at RVA 0x001D88C0 has two instruction-aligned calls through ILT 0x0002C660, at offsets +0x663 and +0x99C. Both push eight slots and place the nugget receiver in ECX. The second supplies the empty AsciiString object. The argument interpretation remains Object pointer, string reference, position pointer, matrix pointer, float orientation, source Object pointer, unsigned lifetime and signed formation index. The main method's inherited bank name is retained; a matched named caller proving that spelling has not been found.

## Value layout and cleanup evidence

The animation payload is three AsciiString values, rather than a scalar inferred from its allocation size. The actual target loads the three fields at offsets 0, 4 and 8 and calls StringBase copy construction for each. The complete copy helper at RVA 0x001D6B80 independently constructs all three fields through RVA 0x00887B60 and returns with `ret 4`. Both helpers are fully decoded and have checked-callee logs. No unexamined payload field was substituted with padding.

The AI command constructor at RVA 0x00185910 and the landed command declarations establish its position, Object pointers, vector storage, integer payload and damage block. The busy command stores its integer at +0x34, invokes the interface at AI receiver +0x20, and destroys the vector at command +0x20. The complete destructor at RVA 0x000D7330 frees that member alone. The bank retains an opaque tail for members this target does not access; the total block extent is checked at compile time.

Particle creation at RVA 0x005C3A30 uses hidden return storage and returns the storage pointer in EAX. It initializes all three handle fields. Creation, attach, detach and the complete cleanup at RVA 0x001DA440 establish the system pointer and both intrusive links, including the owner's +0x98 and +0x9C endpoints. The handle is temporary owning storage, rather than the raw ParticleSystem pointer proposed by the old bank.

`target-eh.log` records the retail unwind map. `bank-unwind.log` verifies matching predecessor states and all four receiver or saved-stack adjustments in the candidate. The two string actions call AsciiString destruction, the command action destroys the whole command, and the handle action destroys the whole handle. String destruction tail-jumps to releaseBuffer; `release-complete.log` and `release-callees.log` cover its complete decrement, free and critical-section paths. The candidate cleanup bodies still need canonical relocation bindings and helper byte verification before an exact claim.

The virtual health call was checked separately. The ActiveBody constructor installs its body interface at +0x10, and `body-vtable.log` identifies slot +0x54 through ILT 0x000498D7. The complete target at RVA 0x00212610 reads a float first argument and the low byte of the second stack slot, then returns with `ret 8` on both paths. The position, force, slaved-update, debris and containment virtual declarations remain partly based on call-site evidence; complete concrete virtual target verification is still required.

## Rejected shapes and remaining work

The AI command native-vector trial adds inline deallocation instructions. Moving force storage across all branches or only the outgoing and flying branches does not reduce the frame. Moving the flying branch's results into scalar carriers increases it. A proper multiple-inheritance behavior view does not change the emitted target. Canonical AsciiString, Coord3D and Object header adoption preserves the relevant bytes. The native mask accessor restores retail's mask materialization. Caching radial intensity, using double math entry points, and restoring the donor-style two-stage rotation remove the radial x87 structure differences. The static helper's private convention is rejected because retail pushes all arguments. Adding the donor's platform flags and commuting the final additions produce unchanged target bytes, so those experiments are closed.

The fresh EH search is retained under `build/shape_search/173736ca15ef4c298fd1ac388191ed84/`; its raw per-trial probes are `eh-trial-*-probe.log`. The bounded family search is under `build/shape_search/88047eeb2333451e9a4fb47f2048e2e0/`, with raw `family-trial-*-probe.log` output. These searches used the new reconstructed body rather than repeating the old bank unchanged.

The bank still differs in animation address arithmetic, force accumulation and subsequent instruction offsets. The first raw mismatch is the entry branch displacement after the now matching frame and receiver setup. The first normalized structure mismatch is in outgoing-force accumulation. The copied helper's matrix construction context differs from the independently exact donor probe. Reopening is justified by evidence for that constructor visibility or for the accumulation helper's source form, or by canonical declarations that resolve the documented callee spellings. Additional unchanged register or x87 spelling searches are not justified.

No functions.csv row, symbols.csv pin or shared header was changed. The paused STL family was not extended. A later landing would need the existing Coord3D vector destructor binding, plus resolution of the other declared calls; this run adds no STL name or pin. The inherited field names are retained, including names whose semantic interpretation still needs confirmation.

## Checks

`bank-byte-gate.log` is the strict repository verifier run with one in-memory candidate row. It fails byte comparison and lists unresolved declarations. The ledger was never changed to run it. `check-csv-final.log`, `pin-consistency.log`, `bank-class.log` and `bank-names.log` pass. The file-based name check calls the repository's comparison implementation because the current name_regression CLI accepts revisions rather than paths. `declared-unmatched.log` refuses an unclaimed scratch source; no whitelist was added. No full gate is required for this bank-only evidence change, and no landing is reported.

## Compiler measurements

Each row below comes directly from its preserved probe output. The JSON measurements are saved beside those logs. These comparisons do not certify identity, ABI or runtime behavior.

| Raw log | Candidate bytes | Differing bytes | First difference | Measured quality | Normalized instruction score |
| --- | ---: | ---: | ---: | ---: | ---: |
| `build/001d9630-retry/bank-probe.log` | 2717 | 517 | +0x2C | 0.8044 | 0.992 |
| `build/001d9630-retry/baseline-raw-probe.log` | 2057 | 1463 | +0x1C | 0.0000 | 0.614 |
| `build/001d9630-retry/candidate01b-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/candidate02-probe.log` | 2792 | 2122 | +0x15 | 0.1721 | 0.941 |
| `build/001d9630-retry/candidate03-probe.log` | 2725 | 1661 | +0x17 | 0.3905 | 0.961 |
| `build/001d9630-retry/candidate04-probe.log` | 2725 | 1660 | +0x17 | 0.3908 | 0.962 |
| `build/001d9630-retry/candidate05-probe.log` | 2725 | 1660 | +0x17 | 0.3908 | 0.962 |
| `build/001d9630-retry/candidate06-probe.log` | 2745 | 1825 | +0x17 | 0.3156 | 0.949 |
| `build/001d9630-retry/candidate07-probe.log` | 2725 | 1663 | +0x17 | 0.3897 | 0.958 |
| `build/001d9630-retry/candidate08-probe.log` | 2726 | 1543 | +0x17 | 0.4330 | 0.967 |
| `build/001d9630-retry/candidate09-probe.log` | 2725 | 1512 | +0x17 | 0.4451 | 0.97 |
| `build/001d9630-retry/candidate10-probe.log` | 2725 | 1512 | +0x17 | 0.4451 | 0.97 |
| `build/001d9630-retry/candidate11-probe.log` | 2726 | 1512 | +0x17 | 0.4444 | 0.971 |
| `build/001d9630-retry/candidate12-probe.log` | 2719 | 1689 | +0x17 | 0.3758 | 0.976 |
| `build/001d9630-retry/candidate13-probe.log` | 2722 | 1718 | +0x17 | 0.3673 | 0.982 |
| `build/001d9630-retry/candidate14-probe.log` | 2724 | 1724 | +0x17 | 0.3666 | 0.987 |
| `build/001d9630-retry/candidate15-probe.log` | 2764 | 1774 | +0x17 | 0.3204 | 0.973 |
| `build/001d9630-retry/candidate16-probe.log` | 2740 | 1746 | +0x17 | 0.3483 | 0.986 |
| `build/001d9630-retry/candidate17-probe.log` | 2724 | 1724 | +0x17 | 0.3666 | 0.987 |
| `build/001d9630-retry/candidate18-probe.log` | 2737 | 1738 | +0x17 | 0.3534 | 0.987 |
| `build/001d9630-retry/candidate19-probe.log` | 2732 | 1739 | +0x17 | 0.3567 | 0.99 |
| `build/001d9630-retry/candidate20-probe.log` | 2730 | 1736 | +0x17 | 0.3593 | 0.992 |
| `build/001d9630-retry/candidate23-probe.log` | 2728 | 621 | +0x29 | 0.7699 | 0.985 |
| `build/001d9630-retry/candidate24-probe.log` | 2728 | 621 | +0x29 | 0.7699 | 0.985 |
| `build/001d9630-retry/candidate25-probe.log` | 2717 | 517 | +0x2C | 0.8044 | 0.992 |
| `build/001d9630-retry/candidate26-probe.log` | 2717 | 517 | +0x2C | 0.8044 | 0.992 |
| `build/001d9630-retry/candidate27-probe.log` | 2717 | 517 | +0x2C | 0.8044 | 0.992 |
| `build/001d9630-retry/eh-trial-00-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-01-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-02-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-03-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-04-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-05-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-06-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-07-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/eh-trial-08-probe.log` | 2742 | 1894 | +0x17 | 0.2925 | 0.956 |
| `build/001d9630-retry/family-trial-00-probe.log` | 2724 | 1724 | +0x17 | 0.3666 | 0.987 |
| `build/001d9630-retry/family-trial-01-probe.log` | 2726 | 1708 | +0x17 | 0.3725 | 0.985 |
| `build/001d9630-retry/family-trial-02-probe.log` | 2724 | 1724 | +0x17 | 0.3666 | 0.987 |
| `build/001d9630-retry/final-probe.log` | 2726 | 1708 | +0x17 | 0.3725 | 0.985 |
