import sys

compiler_optimization = ["O0", "O1", "O2", "O3"]
data_type = [1, 2] # 1: Double 2: Float 
optimizations={"parallelization": ["PARALLELIZATION"],
               "parallel_reduction":["PARALLELIZATION", "PARALLEL_REDUCTION"],
               "soa_inverted": ["PARALLELIZATION", "SOA", "INVERTED"],
               "soa": ["PARALLELIZATION", "SOA"],
               "memset": ["PARALLELIZATION", "SOA", "MEMSET"],
               "merge_distance_single": ["PARALLELIZATION", "SOA", "MEMSET", "MERGE_DISTANCE_SELECT", "MERGE_SINGLE"],
               "merge_distance_parallel": ["PARALLELIZATION", "SOA", "MEMSET", "MERGE_DISTANCE_SELECT"]}

optimizations["march_native"] = optimizations["merge_distance_parallel"].copy()

if sys.argv[1] == "a1a" or sys.argv[1] == "a1c":
    optimizations["specific_voting"] = ["PARALLELIZATION", "SOA", "MEMSET", "SPECIFIC_VOTING"]
    optimizations["merge_distance_single"].append("SPECIFIC_VOTING")
    optimizations["merge_distance_parallel"].append("SPECIFIC_VOTING")
    optimizations["march_native"].append("SPECIFIC_VOTING")

for flags in optimizations.values():
    flags.append("METRICS")