#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/sirze/repos/CHE/hardware-accelerator/solution1/csim/build/apcc_db_sirze/407411704472851677948/preprocess.ld.bc ${1+"$@"}
