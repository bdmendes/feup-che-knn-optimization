/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;
/* Structure forward decls */
typedef struct l_struct_OC_Timer l_struct_OC_Timer;
typedef struct l_struct_OC_timespec l_struct_OC_timespec;

/* Structure contents */
struct l_struct_OC_Timer {
  unsigned char field0;
  l_struct_OC_timespec *field1;
  double field2;
};

struct l_struct_OC_timespec {
  unsigned long long field0;
  unsigned long long field1;
};


/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
l_struct_OC_Timer *timer_init(void);
l_struct_OC_Timer *timer_destroy(l_struct_OC_Timer *llvm_cbe_timer);
void timer_start(l_struct_OC_Timer *llvm_cbe_timer);
void timer_pause(l_struct_OC_Timer *llvm_cbe_timer);
static double aesl_internal_calc_delta_ms(l_struct_OC_timespec *llvm_cbe_this_instant, l_struct_OC_timespec *llvm_cbe_start_instant);
void timer_stop(l_struct_OC_Timer *llvm_cbe_timer);
double timer_get_ms(l_struct_OC_Timer *llvm_cbe_timer);
double timer_get_s(l_struct_OC_Timer *llvm_cbe_timer);
double timer_get_us(l_struct_OC_Timer *llvm_cbe_timer);


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

l_struct_OC_Timer *timer_init(void) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  l_struct_OC_Timer *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
   char *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
   char *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  l_struct_OC_Timer *llvm_cbe_tmp__7;
  l_struct_OC_Timer *llvm_cbe_tmp__7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_init\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call noalias i8* @malloc(i64 24) nounwind, !dbg !8 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_1_count);
  llvm_cbe_tmp__1 = ( char *) /*tail*/ ( char *)malloc(24ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",24ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = bitcast i8* %%1 to %%struct.Timer*, !dbg !8 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_2_count);
  llvm_cbe_tmp__2 = (l_struct_OC_Timer *)((l_struct_OC_Timer *)llvm_cbe_tmp__1);
  if (((llvm_cbe_tmp__1) == ((( char *)/*NULL*/0)))) {
    llvm_cbe_tmp__7__PHI_TEMPORARY = (l_struct_OC_Timer *)((l_struct_OC_Timer *)/*NULL*/0);   /* for PHI node */
    goto llvm_cbe_tmp__8;
  } else {
    goto llvm_cbe_tmp__9;
  }

llvm_cbe_tmp__9:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call noalias i8* @malloc(i64 16) nounwind, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_11_count);
  llvm_cbe_tmp__3 = ( char *) /*tail*/ ( char *)malloc(16ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",16ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = bitcast i8* %%5 to %%struct.timespec*, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_12_count);
  llvm_cbe_tmp__4 = (l_struct_OC_timespec *)((l_struct_OC_timespec *)llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.Timer* %%2, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_13_count);
  llvm_cbe_tmp__5 = (l_struct_OC_timespec **)(&llvm_cbe_tmp__2->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store %%struct.timespec* %%6, %%struct.timespec** %%7, align 8, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_14_count);
  *llvm_cbe_tmp__5 = (l_struct_OC_timespec *)llvm_cbe_tmp__4;
  if (((llvm_cbe_tmp__3) == ((( char *)/*NULL*/0)))) {
    llvm_cbe_tmp__7__PHI_TEMPORARY = (l_struct_OC_Timer *)((l_struct_OC_Timer *)/*NULL*/0);   /* for PHI node */
    goto llvm_cbe_tmp__8;
  } else {
    goto llvm_cbe_tmp__10;
  }

llvm_cbe_tmp__10:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = bitcast i8* %%1 to i2*, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__6 = ( char *)(( char *)llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE)
printf("\n  store i2 1, i2* %%10, align 1, !dbg !9 for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_18_count);
  *llvm_cbe_tmp__6 = ((((unsigned char )1)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )1));
  llvm_cbe_tmp__7__PHI_TEMPORARY = (l_struct_OC_Timer *)llvm_cbe_tmp__2;   /* for PHI node */
  goto llvm_cbe_tmp__8;

llvm_cbe_tmp__8:
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = phi %%struct.Timer* [ %%2, %%9 ], [ null, %%0 ], [ null, %%4  for 0x%llxth hint within @timer_init  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__7 = (l_struct_OC_Timer *)llvm_cbe_tmp__7__PHI_TEMPORARY;
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_init}\n");
  return llvm_cbe_tmp__7;
}


l_struct_OC_Timer *timer_destroy(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
   char *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
   char *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_destroy\n");
  if (((llvm_cbe_timer) == (((l_struct_OC_Timer *)/*NULL*/0)))) {
    goto llvm_cbe_tmp__15;
  } else {
    goto llvm_cbe_tmp__16;
  }

llvm_cbe_tmp__16:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__11 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load %%struct.timespec** %%3, align 8, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__12 = (l_struct_OC_timespec *)*llvm_cbe_tmp__11;
  if (((llvm_cbe_tmp__12) == (((l_struct_OC_timespec *)/*NULL*/0)))) {
    goto llvm_cbe_tmp__17;
  } else {
    goto llvm_cbe_tmp__18;
  }

llvm_cbe_tmp__18:
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = bitcast %%struct.timespec* %%4 to i8*, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__13 = ( char *)(( char *)llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @free(i8* %%7) nounwind, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_34_count);
   /*tail*/ free(( char *)llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE) {
}
  goto llvm_cbe_tmp__17;

llvm_cbe_tmp__17:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = bitcast %%struct.Timer* %%timer to i8*, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__14 = ( char *)(( char *)llvm_cbe_timer);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @free(i8* %%9) nounwind, !dbg !9 for 0x%llxth hint within @timer_destroy  --> \n", ++aesl_llvm_cbe_37_count);
   /*tail*/ free(( char *)llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE) {
}
  goto llvm_cbe_tmp__15;

llvm_cbe_tmp__15:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_destroy}\n");
  return ((l_struct_OC_Timer *)/*NULL*/0);
}


void timer_start(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
   char *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned char llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  double *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  unsigned int llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_start\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__19 = ( char *)(&llvm_cbe_timer->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load i2* %%1, align 1, !dbg !8 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__20 = (unsigned char )*llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = zext i2 %%2 to i32, !dbg !8 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__21 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__20&3U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__21);
  switch (((unsigned int )(llvm_cbe_tmp__21&4294967295ull))) {
  default:
    goto llvm_cbe_tmp__29;
;
  case ((unsigned int )(1u&4294967295ull)):
    goto llvm_cbe_tmp__30;
    break;
  case ((unsigned int )(2u&4294967295ull)):
    goto llvm_cbe_tmp__31;
  }
llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__22 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store double 0.000000e+00, double* %%5, align 8, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_52_count);
  *llvm_cbe_tmp__22 = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store i2 0, i2* %%1, align 1, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_53_count);
  *llvm_cbe_tmp__19 = ((((unsigned char )0)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )0));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_tmp__23 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load %%struct.timespec** %%6, align 8, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__24 = (l_struct_OC_timespec *)*llvm_cbe_tmp__23;
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call i32 @clock_gettime(i32 1, %%struct.timespec* %%7) nounwind, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_56_count);
   /*tail*/ clock_gettime(1u, (l_struct_OC_timespec *)llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__25);
}
  goto llvm_cbe_tmp__29;

llvm_cbe_tmp__31:
if (AESL_DEBUG_TRACE)
printf("\n  store i2 0, i2* %%1, align 1, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_58_count);
  *llvm_cbe_tmp__19 = ((((unsigned char )0)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )0));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__26 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load %%struct.timespec** %%10, align 8, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__27 = (l_struct_OC_timespec *)*llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = tail call i32 @clock_gettime(i32 1, %%struct.timespec* %%11) nounwind, !dbg !9 for 0x%llxth hint within @timer_start  --> \n", ++aesl_llvm_cbe_61_count);
   /*tail*/ clock_gettime(1u, (l_struct_OC_timespec *)llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__28);
}
  goto llvm_cbe_tmp__29;

llvm_cbe_tmp__29:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_start}\n");
  return;
}


void timer_pause(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_this_instant_count = 0;
  l_struct_OC_timespec llvm_cbe_this_instant;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
   char *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned char llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_cond_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  double llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  double *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  double llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  double llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_pause\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__32 = ( char *)(&llvm_cbe_timer->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load i2* %%1, align 1, !dbg !8 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__33 = (unsigned char )*llvm_cbe_tmp__32;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
  if (((llvm_cbe_tmp__33&3U) == (((unsigned char )0)&3U))) {
    goto llvm_cbe_tmp__41;
  } else {
    goto llvm_cbe_tmp__42;
  }

llvm_cbe_tmp__41:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = call i32 @clock_gettime(i32 1, %%struct.timespec* %%this_instant) nounwind, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_73_count);
  clock_gettime(1u, (l_struct_OC_timespec *)(&llvm_cbe_this_instant));
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__34);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__35 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load %%struct.timespec** %%5, align 8, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__36 = (l_struct_OC_timespec *)*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = call fastcc double @aesl_internal_calc_delta_ms(%%struct.timespec* %%this_instant, %%struct.timespec* %%6), !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__37 = (double )aesl_internal_calc_delta_ms((l_struct_OC_timespec *)(&llvm_cbe_this_instant), (l_struct_OC_timespec *)llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__37);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__38 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__39 = (double )*llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__39, *(long long*)(&llvm_cbe_tmp__39));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fadd double %%9, %%7, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__40 = (double )llvm_cbe_tmp__39 + llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__40, *(long long*)(&llvm_cbe_tmp__40));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%10, double* %%8, align 8, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_82_count);
  *llvm_cbe_tmp__38 = llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  store i2 -2, i2* %%1, align 1, !dbg !9 for 0x%llxth hint within @timer_pause  --> \n", ++aesl_llvm_cbe_83_count);
  *llvm_cbe_tmp__32 = ((((unsigned char )2u)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )2u));
  goto llvm_cbe_tmp__42;

llvm_cbe_tmp__42:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_pause}\n");
  return;
}


static double aesl_internal_calc_delta_ms(l_struct_OC_timespec *llvm_cbe_this_instant, l_struct_OC_timespec *llvm_cbe_start_instant) {
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  signed long long *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  signed long long *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  unsigned long long llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  unsigned long long llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  double llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  double llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  signed long long *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  unsigned long long llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  signed long long *llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned long long llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  unsigned long long llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  double llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  double llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  double llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_calc_delta_ms\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.timespec* %%this_instant, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__43 = (signed long long *)(&llvm_cbe_this_instant->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load i64* %%1, align 8, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_93_count);
  llvm_cbe_tmp__44 = (unsigned long long )*llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.timespec* %%start_instant, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_94_count);
  llvm_cbe_tmp__45 = (signed long long *)(&llvm_cbe_start_instant->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i64* %%3, align 8, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__46 = (unsigned long long )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = sub nsw i64 %%2, %%4, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__47 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__44&18446744073709551615ull)) - ((unsigned long long )(llvm_cbe_tmp__46&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__47&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sitofp i64 %%5 to double, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__48 = (double )((double )(signed long long )llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__48, *(long long*)(&llvm_cbe_tmp__48));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fmul double %%6, 1.000000e+03, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__49 = (double )llvm_cbe_tmp__48 * 0x1.f4p9;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__49, *(long long*)(&llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.timespec* %%this_instant, i64 0, i32 1, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_tmp__50 = (signed long long *)(&llvm_cbe_this_instant->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i64* %%8, align 8, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__51 = (unsigned long long )*llvm_cbe_tmp__50;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.timespec* %%start_instant, i64 0, i32 1, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__52 = (signed long long *)(&llvm_cbe_start_instant->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i64* %%10, align 8, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__53 = (unsigned long long )*llvm_cbe_tmp__52;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sub nsw i64 %%9, %%11, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__54 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__51&18446744073709551615ull)) - ((unsigned long long )(llvm_cbe_tmp__53&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__54&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sitofp i64 %%12 to double, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__55 = (double )((double )(signed long long )llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__55, *(long long*)(&llvm_cbe_tmp__55));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fmul double %%13, 1.000000e-06, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__56 = (double )llvm_cbe_tmp__55 * 0x1.0c6f7a0b5ed8dp-20;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__56, *(long long*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fadd double %%7, %%14, !dbg !8 for 0x%llxth hint within @aesl_internal_calc_delta_ms  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__57 = (double )llvm_cbe_tmp__49 + llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__57, *(long long*)(&llvm_cbe_tmp__57));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @aesl_internal_calc_delta_ms}\n");
  return llvm_cbe_tmp__57;
}


void timer_stop(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_this_instant_count = 0;
  l_struct_OC_timespec llvm_cbe_this_instant;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
   char *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned char llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  double llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  double *llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  double llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  double llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_stop\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__58 = ( char *)(&llvm_cbe_timer->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load i2* %%1, align 1, !dbg !8 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__59 = (unsigned char )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = zext i2 %%2 to i32, !dbg !8 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__59&3U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
  switch (((unsigned int )(llvm_cbe_tmp__60&4294967295ull))) {
  default:
    goto llvm_cbe_tmp__68;
;
  case ((unsigned int )(0u&4294967295ull)):
    goto llvm_cbe_tmp__69;
    break;
  case ((unsigned int )(2u&4294967295ull)):
    goto llvm_cbe_tmp__70;
  }
llvm_cbe_tmp__69:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = call i32 @clock_gettime(i32 1, %%struct.timespec* %%this_instant) nounwind, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_119_count);
  clock_gettime(1u, (l_struct_OC_timespec *)(&llvm_cbe_this_instant));
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__61);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__62 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load %%struct.timespec** %%6, align 8, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__63 = (l_struct_OC_timespec *)*llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = call fastcc double @aesl_internal_calc_delta_ms(%%struct.timespec* %%this_instant, %%struct.timespec* %%7), !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__64 = (double )aesl_internal_calc_delta_ms((l_struct_OC_timespec *)(&llvm_cbe_this_instant), (l_struct_OC_timespec *)llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__64);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__65 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load double* %%9, align 8, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__66 = (double )*llvm_cbe_tmp__65;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__66, *(long long*)(&llvm_cbe_tmp__66));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fadd double %%10, %%8, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__67 = (double )llvm_cbe_tmp__66 + llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__67, *(long long*)(&llvm_cbe_tmp__67));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%11, double* %%9, align 8, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_128_count);
  *llvm_cbe_tmp__65 = llvm_cbe_tmp__67;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  store i2 1, i2* %%1, align 1, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_129_count);
  *llvm_cbe_tmp__58 = ((((unsigned char )1)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )1));
  goto llvm_cbe_tmp__68;

llvm_cbe_tmp__70:
if (AESL_DEBUG_TRACE)
printf("\n  store i2 1, i2* %%1, align 1, !dbg !9 for 0x%llxth hint within @timer_stop  --> \n", ++aesl_llvm_cbe_131_count);
  *llvm_cbe_tmp__58 = ((((unsigned char )1)) & 3ull);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )1));
  goto llvm_cbe_tmp__68;

llvm_cbe_tmp__68:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_stop}\n");
  return;
}


double timer_get_ms(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_this_instant_count = 0;
  l_struct_OC_timespec llvm_cbe_this_instant;    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
   char *llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  unsigned char llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  unsigned int llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  l_struct_OC_timespec **llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  l_struct_OC_timespec *llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  double llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  double *llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  double llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  double llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  double *llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  double llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  double *llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  double llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  double llvm_cbe_tmp__85;
  double llvm_cbe_tmp__85__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_get_ms\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__71 = ( char *)(&llvm_cbe_timer->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load i2* %%1, align 1, !dbg !8 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__72 = (unsigned char )*llvm_cbe_tmp__71;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = zext i2 %%2 to i32, !dbg !8 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__73 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__72&3U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__73);
  switch (((unsigned int )(llvm_cbe_tmp__73&4294967295ull))) {
  default:
    llvm_cbe_tmp__85__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe_tmp__86;
;
  case ((unsigned int )(0u&4294967295ull)):
    goto llvm_cbe_tmp__87;
    break;
  case ((unsigned int )(1u&4294967295ull)):
    goto llvm_cbe_tmp__88;
  case ((unsigned int )(2u&4294967295ull)):
    goto llvm_cbe_tmp__89;
  }
llvm_cbe_tmp__87:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = call i32 @clock_gettime(i32 1, %%struct.timespec* %%this_instant) nounwind, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_145_count);
  clock_gettime(1u, (l_struct_OC_timespec *)(&llvm_cbe_this_instant));
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__74);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 1, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__75 = (l_struct_OC_timespec **)(&llvm_cbe_timer->field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load %%struct.timespec** %%6, align 8, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__76 = (l_struct_OC_timespec *)*llvm_cbe_tmp__75;
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = call fastcc double @aesl_internal_calc_delta_ms(%%struct.timespec* %%this_instant, %%struct.timespec* %%7), !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__77 = (double )aesl_internal_calc_delta_ms((l_struct_OC_timespec *)(&llvm_cbe_this_instant), (l_struct_OC_timespec *)llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__77);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__78 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load double* %%9, align 8, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__79 = (double )*llvm_cbe_tmp__78;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__79, *(long long*)(&llvm_cbe_tmp__79));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fadd double %%10, %%8, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_153_count);
  llvm_cbe_tmp__80 = (double )llvm_cbe_tmp__79 + llvm_cbe_tmp__77;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__80, *(long long*)(&llvm_cbe_tmp__80));
  llvm_cbe_tmp__85__PHI_TEMPORARY = (double )llvm_cbe_tmp__80;   /* for PHI node */
  goto llvm_cbe_tmp__86;

llvm_cbe_tmp__88:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__81 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load double* %%13, align 8, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_156_count);
  llvm_cbe_tmp__82 = (double )*llvm_cbe_tmp__81;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__82, *(long long*)(&llvm_cbe_tmp__82));
  llvm_cbe_tmp__85__PHI_TEMPORARY = (double )llvm_cbe_tmp__82;   /* for PHI node */
  goto llvm_cbe_tmp__86;

llvm_cbe_tmp__89:
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.Timer* %%timer, i64 0, i32 2, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__83 = (double *)(&llvm_cbe_timer->field2);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load double* %%16, align 8, !dbg !9 for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__84 = (double )*llvm_cbe_tmp__83;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__84, *(long long*)(&llvm_cbe_tmp__84));
  llvm_cbe_tmp__85__PHI_TEMPORARY = (double )llvm_cbe_tmp__84;   /* for PHI node */
  goto llvm_cbe_tmp__86;

llvm_cbe_tmp__86:
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = phi double [ %%17, %%15 ], [ %%14, %%12 ], [ %%11, %%4 ], [ 0.000000e+00, %%0  for 0x%llxth hint within @timer_get_ms  --> \n", ++aesl_llvm_cbe_161_count);
  llvm_cbe_tmp__85 = (double )llvm_cbe_tmp__85__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__85);
printf("\n = %lf",llvm_cbe_tmp__84);
printf("\n = %lf",llvm_cbe_tmp__82);
printf("\n = %lf",llvm_cbe_tmp__80);
printf("\n = %lf",0x0p0);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_get_ms}\n");
  return llvm_cbe_tmp__85;
}


double timer_get_s(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  double llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  double llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_get_s\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call double @timer_get_ms(%%struct.Timer* %%timer), !dbg !9 for 0x%llxth hint within @timer_get_s  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__90 = (double ) /*tail*/ timer_get_ms((l_struct_OC_Timer *)llvm_cbe_timer);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__90);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = fmul double %%1, 1.000000e-03, !dbg !9 for 0x%llxth hint within @timer_get_s  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__91 = (double )llvm_cbe_tmp__90 * 0x1.0624dd2f1a9fcp-10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__91, *(long long*)(&llvm_cbe_tmp__91));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_get_s}\n");
  return llvm_cbe_tmp__91;
}


double timer_get_us(l_struct_OC_Timer *llvm_cbe_timer) {
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  double llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  double llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @timer_get_us\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call double @timer_get_ms(%%struct.Timer* %%timer), !dbg !9 for 0x%llxth hint within @timer_get_us  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__92 = (double ) /*tail*/ timer_get_ms((l_struct_OC_Timer *)llvm_cbe_timer);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__92);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = fmul double %%1, 1.000000e+03, !dbg !9 for 0x%llxth hint within @timer_get_us  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__93 = (double )llvm_cbe_tmp__92 * 0x1.f4p9;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__93, *(long long*)(&llvm_cbe_tmp__93));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @timer_get_us}\n");
  return llvm_cbe_tmp__93;
}

