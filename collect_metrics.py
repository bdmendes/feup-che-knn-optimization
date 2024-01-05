import sys
import os
import time


if len(sys.argv) < 2:
    print("Usage: python3 collect-metrics.py target optimization samples")
    print("target: a1a, a1b, a1c, a2, a3")
    print(
        "optimization: depending on target, see optimization_combinations.py or call with a target to see the options or all"
    )
    print("samples: number of samples to collect")
    exit(1)

import optimization_combinations

if len(sys.argv) < 4:
    print("Usage: python3 collect-metrics.py target optimization samples")
    print("target: a1a, a1b, a1c, a2, a3")
    print(
        "optimization: "
        + ", ".join(
            [key for key in optimization_combinations.optimization_combinations.keys()]
        )
        + " or all"
    )
    print("samples: number of samples to collect")
    exit(1)

if sys.argv[2] == "all":
    os.system(f"rm {sys.argv[1]}*.timing")

    executables = [
        filename for filename in os.listdir() if filename.startswith(sys.argv[1])
    ]
    for executable in executables:
        timings_filename = executable.split(".")[0]
        for i in range(int(sys.argv[3])):
            os.system(f"./{executable} >> {timings_filename}.timing")
            time.sleep(1)
            os.system(
                f"pcm -csv={timings_filename}.powertmp{i} -- ./{executable} > /dev/null"
            )

        # remove powertmp and append to power
        os.system(f"rm {timings_filename}.power")
        os.system(f"touch {timings_filename}.power")
        for i in range(int(sys.argv[3])):
            os.system(f"cat {timings_filename}.powertmp{i} >> {timings_filename}.power")
            os.system(f"echo '' >> {timings_filename}.power")
            os.system(f"rm {timings_filename}.powertmp{i}")

else:
    filename = f"{sys.argv[1]}-{sys.argv[2]}"
    os.system(f"rm {filename}.timing")

    for i in range(int(sys.argv[3])):
        os.system(f"./{filename}.out >> {filename}.timing")
        time.sleep(1)
        os.system(f"pcm -csv={filename}.powertmp{i} -- ./{filename}.out > /dev/null")

    # remove powertmp and append to power
    os.system(f"rm {filename}.power")
    os.system(f"touch {filename}.power")
    for i in range(int(sys.argv[3])):
        os.system(f"cat {filename}.powertmp{i} >> {filename}.power")
        os.system(f"echo '' >> {filename}.power")
        os.system(f"rm {filename}.powertmp{i}")
