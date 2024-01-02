import sys
import os

if len(sys.argv) < 4:
    print("Usage: python3 collect-metrics.py target optimization samples")
    print("target: a1a, a1b, a1c, a2, a3")
    print("optimization: parallelization, parallel_reduction, soa_inverted, soa, memset, merge_distance_single, merge_distance_parallel, march_native, specific_voting")
    print("samples: number of samples to collect")
    exit(1)

os.system(f'rm {sys.argv[1]}-{sys.argv[2]}.timing')

for i in range(int(sys.argv[3])):
    os.system(f'./{sys.argv[1]}-{sys.argv[2]}.out >> {sys.argv[1]}-{sys.argv[2]}.timing')
