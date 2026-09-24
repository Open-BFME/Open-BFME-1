"""The layout witness CLI must parse before dispatching any work."""
import contextlib
import io
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import layout_witness  # noqa: E402


class LayoutWitnessCliTests(unittest.TestCase):
    def test_no_arguments_run_the_witness(self):
        with patch.object(layout_witness, "run_witness") as run, \
                patch.object(layout_witness, "compile_reference") as compile_ref:
            layout_witness.main([])
        run.assert_called_once_with()
        compile_ref.assert_not_called()

    def test_compile_prefixes_are_dispatched_without_compiling(self):
        prefixes = ["GameEngine/Source/Common", "GameEngineDevice/Source"]
        with patch.object(layout_witness, "run_witness") as run, \
                patch.object(layout_witness, "compile_reference") as compile_ref:
            layout_witness.main(["--compile", *prefixes])
        compile_ref.assert_called_once_with(prefixes)
        run.assert_not_called()

    def test_compile_without_prefixes_means_all_reference_sources(self):
        with patch.object(layout_witness, "compile_reference") as compile_ref:
            layout_witness.main(["--compile"])
        compile_ref.assert_called_once_with(None)

    def test_help_exits_before_dispatch(self):
        stdout = io.StringIO()
        with patch.object(layout_witness, "run_witness") as run, \
                patch.object(layout_witness, "compile_reference") as compile_ref, \
                contextlib.redirect_stdout(stdout), \
                self.assertRaises(SystemExit) as exc:
            layout_witness.main(["--help"])
        self.assertEqual(exc.exception.code, 0)
        self.assertIn("--compile", stdout.getvalue())
        run.assert_not_called()
        compile_ref.assert_not_called()

    def test_unknown_arguments_fail_before_dispatch(self):
        stderr = io.StringIO()
        with patch.object(layout_witness, "run_witness") as run, \
                patch.object(layout_witness, "compile_reference") as compile_ref, \
                contextlib.redirect_stderr(stderr), \
                self.assertRaises(SystemExit) as exc:
            layout_witness.main(["--compiel"])
        self.assertEqual(exc.exception.code, 2)
        self.assertIn("unrecognized arguments", stderr.getvalue())
        run.assert_not_called()
        compile_ref.assert_not_called()
