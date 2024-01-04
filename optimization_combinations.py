import sys

compiler_optimization = ["O0", "O1", "O2", "O3"]
data_type = [1, 2] # 1: Double 2: Float 
optimization_combinations={"parallelization": ["PARALLELIZATION"],
               "parallel_reduction":["PARALLELIZATION", "PARALLEL_REDUCTION"],
               "soa_inverted": ["PARALLELIZATION", "SOA", "INVERTED"],
               "soa": ["PARALLELIZATION", "SOA"],
               "memset": ["PARALLELIZATION", "SOA", "MEMSET"],
               "merge_distance_single": ["PARALLELIZATION", "SOA", "MEMSET", "MERGE_DISTANCE_SELECT", "MERGE_SINGLE"],
               "merge_distance_parallel": ["PARALLELIZATION", "SOA", "MEMSET", "MERGE_DISTANCE_SELECT"]}

optimization_combinations["march_native"] = optimization_combinations["merge_distance_parallel"].copy()

if sys.argv[1] == "a1a" or sys.argv[1] == "a1c":
    optimization_combinations["specific_voting"] = ["PARALLELIZATION", "SOA", "MEMSET", "SPECIFIC_VOTING"]
    optimization_combinations["merge_distance_single"].append("SPECIFIC_VOTING")
    optimization_combinations["merge_distance_parallel"].append("SPECIFIC_VOTING")
    optimization_combinations["march_native"].append("SPECIFIC_VOTING")

for flags in optimization_combinations.values():
    flags.append("METRICS")
