# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
# Tool Version Limit: 2023.10
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__SIM_MATHHLS__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../src/hardware-accelerator/hw_testbench.c ../../../../src/io.c ../../../../src/knn.c ../../../../src/hardware-accelerator/knn_hw_accel.c ../../../../src/preprocess.c ../../../../src/timer.c ../../../../src/utils.c

override TARGET := csim.exe

AUTOPILOT_ROOT := /tools/Xilinx/Vitis_HLS/2023.2
AUTOPILOT_MACH := lnx64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
IFLAG += -fPIC
ifndef AP_GCC_PATH
  AP_GCC_PATH := /tools/Xilinx/Vitis_HLS/2023.2/tps/lnx64/gcc-8.3.0/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_TOOL}/clang-3.9/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -I "/usr/include/x86_64-linux-gnu"
IFLAG += -D__HLS_COSIM__

IFLAG += -D__HLS_CSIM__

IFLAG += -D__VITIS_HLS__

IFLAG += -D__SIM_FPO__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E1__
IFLAG += -g
DFLAG += -DAUTOCC
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += -Werror=return-type
CCFLAG += -Wno-abi
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



AUTOCC := apcc 

$(ObjDir)/hw_testbench.o: ../../../../src/hardware-accelerator/hw_testbench.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/hardware-accelerator/hw_testbench.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD -Wno-unknown-pragmas -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/hw_testbench.d

$(ObjDir)/io.o: ../../../../src/io.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/io.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/io.d

$(ObjDir)/knn.o: ../../../../src/knn.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/knn.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/knn.d

$(ObjDir)/knn_hw_accel.o: ../../../../src/hardware-accelerator/knn_hw_accel.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/hardware-accelerator/knn_hw_accel.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/knn_hw_accel.d

$(ObjDir)/preprocess.o: ../../../../src/preprocess.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/preprocess.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/preprocess.d

$(ObjDir)/timer.o: ../../../../src/timer.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/timer.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/timer.d

$(ObjDir)/utils.o: ../../../../src/utils.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../src/utils.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/utils.d
