"""The stale-annotation complaint must not claim a byte comparison it did not do.

`matched_sources` is the ledger's status column. merge_cluster --apply sets that
status without building, so right after an apply this check can fire on a row
nothing has verified. Worded as "byte-verified", it once had an agent believe a
repointed row was proven and nearly write an overturned verdict into a source
comment -- the build disagreed.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

SRC = (Path(__file__).resolve().parents[1] / "build.py").read_text()
BLOCK = re.search(r"if rel in matched_sources\.get\(label, \(\)\):.*?\)\n",
                  SRC, re.S).group(0)


def test_the_complaint_does_not_claim_byte_verification():
    message = "".join(re.findall(r'f"([^"]*)"', BLOCK))
    assert "byte-verified matched" not in message, BLOCK


def test_it_names_the_ledger_as_the_source_of_the_claim():
    assert "LEDGER" in BLOCK or "ledger" in BLOCK


def test_it_offers_the_check_that_would_settle_it():
    assert "build.sh" in BLOCK
