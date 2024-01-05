#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/sirze/repos/CHE/hardware-accelerator/solution1/csim/build/apcc_db_sirze/408051704472854470887/timer.ld.bc ${1+"$@"}
