# Do Zero Hour work packets convert better than a nameless dump?

Pre-registered before any packet was opened (design in build/sweepscan/prereg29.json,
scratch); rerun of an earlier 10-packet test that returned 5/10 INCONCLUSIVE at only
62% power, and which ran against packet metadata since found to be wrong.

## Design

29 addresses pinned by a rule independent of anything believed to predict success:
the lowest RVAs per size band, drawn only from packets nobody had attempted.
Allocation 10/10/6/2/1 across the bands, deliberately unequal because the scarce
bands hold 24/27/6/2/1 workable packets and equal allocation capped n at 15.

Baselines are tools/yield_model.py's fitted LAND_RATE_BY_SIZE: 0.140 / 0.273 /
0.413 / 0.206 / 0.088. The null is Poisson-binomial, not Binomial, because the
draw is stratified across five different rates.

    null mean 7.11        power vs a true 0.50 = 0.87
    REJECT   >= 12        (p = 0.0295)
    DEAD     <=  7        (at or below baseline)
    INCONCLUSIVE 8-11, and to be reported as inconclusive

## Result: 12 of 29 landed. p = 0.0295. REJECT — the lever is real.

    slice 1 (<64 B)      7 / 10
    slice 2 (64-127 B)   4 / 10
    slice 3 (larger)     1 /  9

Robust to the one contested classification: if 0x00647950 leaves the denominator
(its residual byte is a REL32 whose callee the ledger claims at the wrong address),
12 of 28 gives p = 0.0246. Still REJECT.

A "landed" body is byte-exact through ./build.sh at the pinned address, in clean
C++; a naked/__emit body byte-matches by construction and was counted not-landed.

## What the misses were, and why this is not a contradiction

The packets that pointed at the right place converted well above baseline. The
ones that did not, did not — and 19 of the 144 packets carry a banner saying their
address is not a function start. The exact partition, with no overlap:

      19  say "is not a function start"        13.2%   (6 in padding, 13 interior)
      93  say "is a confirmed function start"  64.6%
      32  assert neither                       22.2%
     ---
     144

  So the honest statement is a BOUND, not a rate: at least 13.2% are bad, at most
  35.4% could be, and 22.2% were never checked. Two earlier figures in this file
  were both wrong in different directions. 51 of 144 counted bad plus never-checked
  as if all were bad, because the grep behind it also matched the size line
  "measured from the int3 padding at 0xNNNN" -- which is the provenance of a CORRECT
  end measurement, not a defect. Then 19 of 144 was published as if it were the rate
  when it is only the lower bound.

  Per-band lower bounds, measured over all 144, and only the first three are worth
  banding: 5/81 (6.2%), 6/38 (15.8%), 4/14 (28.6%) across <64, 64-127, 128-255.
  That climb is identical under every cut tried.

  ABOVE 256 BYTES, DO NOT BAND IT. Report 4 of 11 = 36.4% pooled and say the sample
  cannot resolve a trend inside it. The whole population over 256 B is

      265*  286  293*  303  338*  434  453  793  837  1753  4057*      (* = bad)

  -- every bad address but one sits in 265-338, then five consecutive clean packets
  to 1753, then one bad at 4057. Splitting that at 512 gives 42.9% then 25.0%
  (falling); splitting at 1024 gives 33.3% then 50.0% (rising). Nothing changes but
  the cut: moving it shifts the 793 and 837 packets across. Both readings are four
  events, and "50% in the largest band" is one packet out of two. An earlier claim of
  75% there does not survive either.

  The size association itself is real and does not depend on binning: point-biserial
  r(size, is-bad) = +0.227 over all 144, Spearman +0.281 with average ranks, median
  size 109 bytes for bad addresses against 48 for the rest. Bigger bodies are
  likelier to be mis-addressed, which is what the derivation predicts — a longer body
  gives the unverified length more room to be wrong.

  One slice is NOT representative and must not be used to characterise the packet
  set: it drew all four band-2 bad addresses in the entire population plus the only
  bad address in band 4, against an expectation of 2.8 bad in its nine. Its 1-of-9
  strict tally is the worst-case draw of the three, and its "7 of 9 carried a
  metadata defect" is a fact about those nine, not a population estimate. That agent
  reported this against its own result.

- Start addresses: in the bad cases the END is correct and only the START is
  derived, from a length the sweep never verified. Packets whose extent came from
  targets/game/reverse/ghidra_functions.csv had a correct address 3 for 3; those whose extent
  came from the Zero Hour candidate's own length were wrong 6 for 6. Fix: keep the
  end, snap the start to the enclosing ghidra start, recompute size.
  NOT universal — slice 1 re-derived all ten of its boundaries from the PE and
  found delta +0 on every one. Reconcile before treating the rule as general.

  DO NOT implement this as "snap past the leading int3 run". Commit 1c78906e5
  records that mechanism from a two-packet sample where the candidate overshoot
  happened to equal the padding. It does not generalise: of three early-anchored
  packets in another slice the deltas are 2, 1, 13 against int3 runs of 36, 4, 13,
  so snapping to the start of the run would have placed 0x001DC59E thirty-six
  bytes early instead of two — worse than the bug. The slide is (candidate length
  - real length), not the pad.

  The slice that proposed the int3 mechanism then measured it against retail and
  refuted itself: the true runs before its own two addresses are 18 and 21 bytes
  against deltas of 4 and 2, so its starts sit INSIDE those runs. It had seen only
  the 4 and 2 leading 0xCC bytes its packets' quoted ranges happen to begin with,
  and generalised from truncated evidence. Its practice was right — it looked both
  real starts up in the ghidra inventory — and only its write-up was wrong.
  Retracted in fb3c6a70f, which supersedes the record in af52c2d6f.

  DO NOT implement it as a size formula either. Half the bad cases go the other
  way, starting INSIDE the body, where packet_size = real_size MINUS delta
  (0x00747493 245 vs 248, 0x0070F97D 293 vs 306, one of them landing
  mid-instruction inside an 0f 84 displacement). A size rule derived from the
  early cases would silently no-op on those.

  The end-invariance is the only thing true in both directions: keep the end and
  recover the start from targets/game/reverse/ghidra_functions.csv. But "snap to the enclosing
  start" is UNDER-SPECIFIED and ships at 3 of 6. Back-snapping and forward-snapping
  each fix one class and fail SILENTLY on the other, returning a real, plausible
  function start that is simply the wrong body -- the previous function for the
  padding class, the next function for the interior class. That is worse than
  today's banner, which at least announces that it does not know.

  The directional test is 6 of 6 (verified here against the live inventory):

      P = greatest ghidra start <= A
      if P + size(P) > A:  body = P                        # inside a function
      else:                body = least ghidra start >= A  # in padding
      size = packet_end - body

  The coverage test decides the class without trusting the packet's size line.
  The inventory has a start for all six bad addresses with sizes matching retail
  exactly (191, 207, 4042, 248, 306, 11), including the mid-instruction case, so
  no missing-start fallback is needed.

  Validated over the whole banner population, not a hand-picked sample: the rule
  returns a real ghidra start 19 of 19, and the direction it picks agrees with the
  packet's own label in all 19 — the 6 padding packets snap forward, the 13 interior
  ones snap back. Two independent signals, no disagreement, so an implementer can use
  the coverage test and treat the label as a free assertion. Note the majority is
  BACK-snap, 13 of 19: a forward-only rule would have been wrong for 13, not 3.

  Extent is a separate problem from address. Derived size is correct for 11 of the 12
  packets whose end does not span a later start; the miss is 0x0092A6C3, where
  ghidra's own extent is 2 bytes short (found independently by two slices).

  KEEP the existing "spans N function start(s)" check. Snapping fixes the address;
  it does not make a packet convertible. 0x00C0A3CE snaps correctly to 0xC0A3CB and
  is still an 11-byte gen_uw funclet whose packet end would claim 155 bytes across
  9 starts.
- Identity: eight independent packets named the wrong function, one of them a
  function already landed at another address. Identity fails hardest where the
  sweep reports a TIE between candidates.
- Callee pins: a pin marked "(already in the ledger)" is matched by NAME and not
  followed, so it can name a different copy of the symbol than the one retail
  calls. docs/lessons.md already documents this trap at another address.

So the lever is real and the metadata is still broken. Fixing the derivation should
raise the rate further; that is now a funded change rather than a guess.

## Run artifacts, excluded from the tally by rule

Three agents shared one working tree and one index, which is a dispatching error,
not a property of the packets: sibling reverts, contention, and a mid-flight
tools/build.py edit could each have produced a false not-landed. The fix for a
future fan-out is a per-agent `git worktree add --detach`, which one agent verified
by landing seven bodies through one while the shared index was contended.

Ledger blame is fragile: tools/dedup_csv.py rewrites the whole file, and `git log -S`
on an RVA returns the original dump commit because the address string has been there
since the gen_asm dump. Attribute with `git show <sha> -- targets/game/reverse/functions.csv` and
read the -gen_asm/+real-name pair. Reading it wrong is what made an earlier draft of
this file say INCONCLUSIVE.
