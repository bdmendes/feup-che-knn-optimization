import sys
import os


if len(sys.argv) < 2:
    print("Usage: python3 collect-metrics.py target optimization samples")
    print("target: a1a, a1b, a1c, a2, a3")
    print("optimization: depending on target, see optimization_combinations.py or call with a target to see the options or all")
    print("samples: number of samples to collect")
    exit(1)

import optimization_combinations

if len(sys.argv) < 4:
    print("Usage: python3 collect-metrics.py target optimization samples")
    print("target: a1a, a1b, a1c, a2, a3")
    print("optimization: " + ", ".join([key for key in optimization_combinations.optimization_combinations.keys()]) + " or all")
    print("samples: number of samples to collect")
    exit(1)

if sys.argv[2] == "all":
    os.system(f'rm {sys.argv[1]}*.timing')

    executables = [filename for filename in os.listdir() if filename.startswith(sys.argv[1])]
    for executable in executables:
        timings_filename = executable.split(".")[0]
        for i in range(int(sys.argv[3])):
            os.system(f'./{executable} >> {timings_filename}.timing')

else:
    os.system(f'rm {sys.argv[1]}-{sys.argv[2]}.timing')

    for i in range(int(sys.argv[3])):
        os.system(f'./{sys.argv[1]}-{sys.argv[2]}.out >> {sys.argv[1]}-{sys.argv[2]}.timing')
