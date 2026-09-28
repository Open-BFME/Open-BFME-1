// Query every non-thunk function of the open program against BSim databases built with one
// template, writing each function's nearest matches (tools/ea_evidence.py --bsim reads them):
//   -postScript bsim_query.java <max> <threshold> <bsimURL> <out.tsv> [<bsimURL> <out.tsv> ...]
// Build a database per WorldBuilder first: bsim createdatabase file:/dir/wb1 medium_nosize, then
// bsim generatesigs ghidra:/dir/project --bsim file:/dir/wb1. Each batch is decompiled once and
// queried against every database.
//@category BSim
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.features.bsim.query.BSimClientFactory;
import ghidra.features.bsim.query.FunctionDatabase;
import ghidra.features.bsim.query.GenSignatures;
import ghidra.features.bsim.query.description.FunctionDescription;
import ghidra.features.bsim.query.protocol.QueryNearest;
import ghidra.features.bsim.query.protocol.ResponseNearest;
import ghidra.features.bsim.query.protocol.SimilarityNote;
import ghidra.features.bsim.query.protocol.SimilarityResult;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class bsim_query extends GhidraScript {
	private static final int BATCH = 1000;

	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 4 || args.length % 2 != 0) {
			throw new IllegalArgumentException("usage: <max> <threshold> <bsimURL> <out.tsv> [...]");
		}
		int max = Integer.parseInt(args[0]);
		double thresh = Double.parseDouble(args[1]);
		int ndb = (args.length - 2) / 2;
		long base = currentProgram.getImageBase().getOffset();
		List<Function> funcs = new ArrayList<>();
		FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
		while (it.hasNext()) {
			Function f = it.next();
			if (!f.isThunk() && !f.isExternal()) {
				funcs.add(f);
			}
		}
		FunctionDatabase[] dbs = new FunctionDatabase[ndb];
		PrintWriter[] outs = new PrintWriter[ndb];
		try {
			for (int d = 0; d < ndb; d++) {
				dbs[d] = BSimClientFactory.buildClient(BSimClientFactory.deriveBSimURL(args[2 + 2 * d]), false);
				if (!dbs[d].initialize()) {
					throw new IllegalStateException(args[2 + 2 * d] + ": " + dbs[d].getLastError().message);
				}
				outs[d] = new PrintWriter(new FileWriter(args[3 + 2 * d]));
				outs[d].println("game_rva\tmatch_md5\tmatch_va\tsimilarity\tsignificance");
			}
			FunctionDatabase db = dbs[0];
			for (int i = 0; i < funcs.size(); i += BATCH) {
				monitor.checkCancelled();
				List<Function> batch = funcs.subList(i, Math.min(i + BATCH, funcs.size()));
				GenSignatures gensig = new GenSignatures(false);
				try {
					gensig.setVectorFactory(db.getLSHVectorFactory());
					gensig.openProgram(currentProgram, null, null, null, null, null);
					gensig.scanFunctions(batch.iterator(), batch.size(), monitor);
					for (int d = 0; d < ndb; d++) {
						PrintWriter out = outs[d];
						QueryNearest query = new QueryNearest();
						query.manage = gensig.getDescriptionManager();
						query.max = max;
						query.thresh = thresh;
						query.signifthresh = 0.0;
						ResponseNearest response = query.execute(dbs[d]);
						if (response == null) {
							throw new IllegalStateException(dbs[d].getLastError().message);
						}
						for (SimilarityResult result : response.result) {
							long rva = result.getBase().getAddress() - base;
							Iterator<SimilarityNote> notes = result.iterator();
							while (notes.hasNext()) {
								SimilarityNote note = notes.next();
								FunctionDescription match = note.getFunctionDescription();
								out.printf("0x%X\t%s\t0x%X\t%.4f\t%.2f%n", rva,
									match.getExecutableRecord().getMd5(), match.getAddress(),
									note.getSimilarity(), note.getSignificance());
							}
						}
					}
				}
				finally {
					gensig.dispose();
				}
				if ((i / BATCH) % 10 == 0) {
					println("queried " + Math.min(i + BATCH, funcs.size()) + " / " + funcs.size());
				}
			}
		}
		finally {
			for (int d = 0; d < ndb; d++) {
				if (outs[d] != null) {
					outs[d].close();
				}
				if (dbs[d] != null) {
					dbs[d].close();
				}
			}
		}
	}
}
