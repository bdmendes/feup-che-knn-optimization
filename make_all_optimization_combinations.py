import os
import sys


if len(sys.argv) < 2:
    print("Usage: python3 make-all.py target")
    print("target: a1a, a1b, a1c, a2, a3")
    exit(1)

import optimization_combinations

# make scenario without optimizations in all compiler optimization levels
for opt in optimization_combinations.compiler_optimization:
    os.system("make " + sys.argv[1] + " COPT=-" + opt + " OPTFLAGS=\"-DMETRICS\""+ " PROG=" + sys.argv[1] + "-"+opt+".out")
    # print("make " + sys.argv[1] + " COPT=-" + opt + " OPTFLAGS=\"-DMETRICS\""+ " PROG=" + sys.argv[1] + "-"+opt+".out")

# make comparison between data types with and without march native
for dt in optimization_combinations.data_type:
    for native in [True, False]:
        os.system("make " + sys.argv[1] + " COPT=\"-O3" + (" -march=native" if native else "") + "\" DT=\"" + str(dt) +"\" OPTFLAGS=\"-DMETRICS\""+ " PROG="+ sys.argv[1]+"-dt"+str(dt)+("_native" if native else "")+".out") 
        # print("make " + sys.argv[1] + " COPT=\"-O3" + (" -march=native" if native else "") + "\" DT=\"" + str(dt) +"\" OPTFLAGS=\"-DMETRICS\""+ " PROG="+ sys.argv[1]+"-dt"+str(dt)+("_native" if native else "")+".out")

# make scenario with optimizations and -O3 compiler optimization level
for key, value in optimization_combinations.optimization_combinations.items():
    if "march_native" in key:
        os.system("make " + sys.argv[1] + " COPT=\"-O3 -march=native\"" + " OPTFLAGS=\"" + " ".join(["-D"+flag for flag in value]) + "\" PROG=\"" + sys.argv[1]+ '-' +  key + ".out\"")
        # print("make " + sys.argv[1] + " COPT=\"-O3 -march=native\"" + " OPTFLAGS=\"" + " ".join(["-D"+flag for flag in value]) + "\" PROG=\"" + sys.argv[1]+ '-' +  key + ".out\"")
    else:
        os.system("make " + sys.argv[1] + " COPT=\"-O3\"" + " OPTFLAGS=\"" + " ".join(["-D"+flag for flag in value]) + "\" PROG=\""+ sys.argv[1]+ '-' + key + ".out\"")
        # print("make " + sys.argv[1] + " COPT=\"-O3\"" + " OPTFLAGS=\"" + " ".join(["-D"+flag for flag in value]) + "\" PROG=\""+ sys.argv[1]+ '-' + key + ".out\"")
