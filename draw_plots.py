import sys
import os
import matplotlib.pyplot as plt


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 draw_plots.py <scenario>")
        sys.exit(1)

    scenario = sys.argv[1]
    if scenario not in ["a1a", "a1b", "a1c", "a2"]:
        print("Available scenarios: a1a, a1b, a1c, a2")
        sys.exit(1)

    files = [f for f in os.listdir(".") if os.path.isfile(f)]
    global_timings = []
    global_power = []
    flags = []

    for f in files:
        if f.startswith(scenario) and f.endswith(".timing"):
            with open(f, "r") as f:
                flag = f.name.replace(".timing", "").replace(scenario + "-", "")
                if (
                    flag != "parallel_reduction"
                    and flag != "dt1_native"
                    and flag != "dt1"
                    and flag != "dt2"
                    and flag != "dt2_native"
                    and flag != "march_native"
                ):
                    timings = [float(line.rstrip()) for line in f.readlines()]
                    if timings != []:
                        global_timings.append(timings)
                        flags.append(flag)

        if f.startswith(scenario) and f.endswith(".power"):
            with open(f, "r") as f:
                flag = f.name.replace(".timing", "").replace(scenario + "-", "")
                if (
                    flag != "parallel_reduction"
                    and flag != "dt1_native"
                    and flag != "dt1"
                    and flag != "dt2"
                    and flag != "dt2_native"
                    and flag != "march_native"
                ):
                    powers = [float(line.rstrip()) for line in f.readlines()]
                    if powers != []:
                        global_power.append(timings)

    # timings
    plt.figure(figsize=(25, 10))
    ax = plt.subplot(111)
    ax.boxplot(global_timings, showfliers=False)
    ax.set_xticklabels(flags)
    ax.set_ylabel("Time (s)")
    ax.set_title("Timings for scenario " + scenario)
    plt.savefig("plots/" + scenario + ".timings.png")

    # power
    plt.figure(figsize=(25, 10))
    ax = plt.subplot(111)
    ax.boxplot(global_power, showfliers=False)
    ax.set_xticklabels(flags)
    ax.set_ylabel("Power (W)")
    ax.set_title("Power for scenario " + scenario)
    plt.savefig("plots/" + scenario + ".power.png")


if __name__ == "__main__":
    main()
