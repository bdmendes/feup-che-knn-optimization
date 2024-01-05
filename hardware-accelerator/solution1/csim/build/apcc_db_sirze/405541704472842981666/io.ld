#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/sirze/repos/CHE/hardware-accelerator/solution1/csim/build/apcc_db_sirze/405541704472842981666/io.ld.bc ${1+"$@"}
