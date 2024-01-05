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
typedef struct l_struct_OC_BestPoint l_struct_OC_BestPoint;
typedef struct l_struct_OC_Point l_struct_OC_Point;

/* Structure contents */
struct l_struct_OC_BestPoint {
  unsigned char field0;
  double field1;
};

struct l_struct_OC_Point {
  double field0[43];
  unsigned char field1;
};


/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void copy_k_nearest_specific(l_struct_OC_BestPoint *llvm_cbe_dist_points, l_struct_OC_BestPoint *llvm_cbe_best_points);
void select_k_nearest_specific(l_struct_OC_BestPoint *llvm_cbe_dist_points);
void copy_k_nearest(l_struct_OC_BestPoint *llvm_cbe_dist_points, l_struct_OC_BestPoint *llvm_cbe_best_points);
void select_k_nearest(l_struct_OC_BestPoint *llvm_cbe_dist_points);
void get_k_NN(l_struct_OC_Point llvm_cbe_new_point, l_struct_OC_Point *llvm_cbe_known_points, l_struct_OC_BestPoint *llvm_cbe_best_points);
 char plurality_voting(l_struct_OC_BestPoint *llvm_cbe_best_points);
 char knn_classifyinstance(l_struct_OC_Point llvm_cbe_new_point, l_struct_OC_Point *llvm_cbe_known_points);


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

void copy_k_nearest_specific(l_struct_OC_BestPoint *llvm_cbe_dist_points, l_struct_OC_BestPoint *llvm_cbe_best_points) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
   char *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
   char *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @copy_k_nearest_specific\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds %%struct.BestPoint* %%best_points, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @copy_k_nearest_specific  --> \n", ++aesl_llvm_cbe_4_count);
  llvm_cbe_tmp__1 = ( char *)(&llvm_cbe_best_points->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 0, i32 0, !dbg !8 for 0x%llxth hint within @copy_k_nearest_specific  --> \n", ++aesl_llvm_cbe_6_count);
  llvm_cbe_tmp__2 = ( char *)(&llvm_cbe_dist_points->field0);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = call i8* @memcpy(i8* %%1, i8* %%2, i64 320 for 0x%llxth hint within @copy_k_nearest_specific  --> \n", ++aesl_llvm_cbe_7_count);
  ( char *)memcpy(( char *)llvm_cbe_tmp__1, ( char *)llvm_cbe_tmp__2, 320ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",320ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__3);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @copy_k_nearest_specific}\n");
  return;
}


void select_k_nearest_specific(l_struct_OC_BestPoint *llvm_cbe_dist_points) {
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge5_count = 0;
  unsigned int llvm_cbe_storemerge5;
  unsigned int llvm_cbe_storemerge5__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  unsigned long long llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  double *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  double llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge13_count = 0;
  unsigned int llvm_cbe_storemerge13;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge14_count = 0;
  unsigned int llvm_cbe_storemerge14;
  unsigned int llvm_cbe_storemerge14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  double llvm_cbe_tmp__7;
  double llvm_cbe_tmp__7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  unsigned int llvm_cbe_tmp__8;
  unsigned int llvm_cbe_tmp__8__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned long long llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  double *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_be_count = 0;
  unsigned int llvm_cbe__2e_be;
  static  unsigned long long aesl_llvm_cbe__2e_be2_count = 0;
  double llvm_cbe__2e_be2;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  unsigned long long llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
   char *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned char llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  double *llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  double llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
   char *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  unsigned char llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond6_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @select_k_nearest_specific\n");
  llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_thread;

  do {     /* Syntactic loop '.thread' to make GCC happy */
llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge5 = phi i32 [ 0, %%0 ], [ %%storemerge13, %%20 ], [ %%storemerge13, %%.thread  for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_storemerge5_count);
  llvm_cbe_storemerge5 = (unsigned int )llvm_cbe_storemerge5__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge5 = 0x%X",llvm_cbe_storemerge5);
printf("\n = 0x%X",0u);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge5 to i64, !dbg !7 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__4 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%1, i32 1, !dbg !7 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__5 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__4))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__4));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load double* %%2, align 8, !dbg !7 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__6 = (double )*llvm_cbe_tmp__5;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__6, *(long long*)(&llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge13 = add nsw i32 %%storemerge5, 1, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_storemerge13_count);
  llvm_cbe_storemerge13 = (unsigned int )((unsigned int )(llvm_cbe_storemerge5&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge13 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge13&4294967295ull)));
  if ((((signed int )llvm_cbe_storemerge13) < ((signed int )4336u))) {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    llvm_cbe_tmp__7__PHI_TEMPORARY = (double )llvm_cbe_tmp__6;   /* for PHI node */
    llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge5;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    goto llvm_cbe__2e_thread;
  }

llvm_cbe_tmp__19:
  if (((llvm_cbe_storemerge13&4294967295U) == (20u&4294967295U))) {
    goto llvm_cbe_tmp__20;
  } else {
    llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    goto llvm_cbe__2e_thread;
  }

llvm_cbe__2e__crit_edge:
  if (((llvm_cbe__2e_be&4294967295U) == (llvm_cbe_storemerge5&4294967295U))) {
    goto llvm_cbe_tmp__19;
  } else {
    goto llvm_cbe_tmp__21;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge14 = phi i32 [ %%storemerge1, %%.lr.ph ], [ %%storemerge13, %%.thread  for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_storemerge14_count);
  llvm_cbe_storemerge14 = (unsigned int )llvm_cbe_storemerge14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi double [ %%.be2, %%.lr.ph ], [ %%3, %%.thread  for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__7 = (double )llvm_cbe_tmp__7__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__7);
printf("\n.be2 = %lf",llvm_cbe__2e_be2);
printf("\n = %lf",llvm_cbe_tmp__6);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi i32 [ %%.be, %%.lr.ph ], [ %%storemerge5, %%.thread  for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__8 = (unsigned int )llvm_cbe_tmp__8__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__8);
printf("\n.be = 0x%X",llvm_cbe__2e_be);
printf("\nstoremerge5 = 0x%X",llvm_cbe_storemerge5);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%storemerge14 to i64, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__9 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%7, i32 1, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__10 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__9))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__9));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__11 = (double )*llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%.be = select i1 %%10, i32 %%storemerge14, i32 %%6, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe__2e_be_count);
  llvm_cbe__2e_be = (unsigned int )(((llvm_fcmp_olt(llvm_cbe_tmp__11, llvm_cbe_tmp__7))) ? ((unsigned int )llvm_cbe_storemerge14) : ((unsigned int )llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n.be = 0x%X\n", llvm_cbe__2e_be);
if (AESL_DEBUG_TRACE)
printf("\n  %%.be2 = select i1 %%10, double %%9, double %%5, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe__2e_be2_count);
  llvm_cbe__2e_be2 = (double )(((llvm_fcmp_olt(llvm_cbe_tmp__11, llvm_cbe_tmp__7))) ? ((double )llvm_cbe_tmp__11) : ((double )llvm_cbe_tmp__7));
if (AESL_DEBUG_TRACE)
printf("\n.be2 = %lf,  0x%llx\n", llvm_cbe__2e_be2, *(long long*)(&llvm_cbe__2e_be2));
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = add nsw i32 %%storemerge14, 1, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )((unsigned int )(llvm_cbe_storemerge14&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge1 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge1&4294967295ull)));
  if (((llvm_cbe_storemerge1&4294967295U) == (4336u&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge1;   /* for PHI node */
    llvm_cbe_tmp__7__PHI_TEMPORARY = (double )llvm_cbe__2e_be2;   /* for PHI node */
    llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe_tmp__21:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sext i32 %%.be to i64, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__12 = (unsigned long long )((signed long long )(signed int )llvm_cbe__2e_be);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%13, i32 0, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__13 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__12))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__12));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i8* %%14, align 1, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__14 = (unsigned char )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%13, i32 1, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__15 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__12))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__12));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load double* %%16, align 8, !dbg !8 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__16 = (double )*llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__16, *(long long*)(&llvm_cbe_tmp__16));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%1, i32 0, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__17 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__4))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__4));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load i8* %%18, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_tmp__18 = (unsigned char )*llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%19, i8* %%14, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_55_count);
  *llvm_cbe_tmp__13 = llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%3, double* %%16, align 8, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_56_count);
  *llvm_cbe_tmp__15 = llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%15, i8* %%18, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_57_count);
  *llvm_cbe_tmp__17 = llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%17, double* %%2, align 8, !dbg !9 for 0x%llxth hint within @select_k_nearest_specific  --> \n", ++aesl_llvm_cbe_58_count);
  *llvm_cbe_tmp__5 = llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__16);
  goto llvm_cbe_tmp__19;

  } while (1); /* end of syntactic loop '.thread' */
llvm_cbe_tmp__20:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @select_k_nearest_specific}\n");
  return;
}


void copy_k_nearest(l_struct_OC_BestPoint *llvm_cbe_dist_points, l_struct_OC_BestPoint *llvm_cbe_best_points) {
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  unsigned long long llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
   char *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  unsigned char llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
   char *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  double *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  double llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  double *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @copy_k_nearest\n");
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__30;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%0 ], [ %%9, %%1  for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__29);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sext i32 %%storemerge1 to i64, !dbg !7 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__22 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%2, i32 0, !dbg !7 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__23 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__22))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__22));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i8* %%3, align 1, !dbg !7 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__24 = (unsigned char )*llvm_cbe_tmp__23;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.BestPoint* %%best_points, i64 %%2, i32 0, !dbg !7 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__25 = ( char *)(&llvm_cbe_best_points[(((signed long long )llvm_cbe_tmp__22))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__22));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%4, i8* %%5, align 1, !dbg !7 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_80_count);
  *llvm_cbe_tmp__25 = llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%2, i32 1, !dbg !8 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__26 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__22))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__22));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load double* %%6, align 8, !dbg !8 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__27 = (double )*llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__27, *(long long*)(&llvm_cbe_tmp__27));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.BestPoint* %%best_points, i64 %%2, i32 1, !dbg !8 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__28 = (double *)(&llvm_cbe_best_points[(((signed long long )llvm_cbe_tmp__22))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__22));
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%7, double* %%8, align 8, !dbg !8 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_84_count);
  *llvm_cbe_tmp__28 = llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = add nsw i32 %%storemerge1, 1, !dbg !8 for 0x%llxth hint within @copy_k_nearest  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__29&4294967295ull)));
  if (((llvm_cbe_tmp__29&4294967295U) == (20u&4294967295U))) {
    goto llvm_cbe_tmp__31;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__29;   /* for PHI node */
    goto llvm_cbe_tmp__30;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__31:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @copy_k_nearest}\n");
  return;
}


void select_k_nearest(l_struct_OC_BestPoint *llvm_cbe_dist_points) {
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge5_count = 0;
  unsigned int llvm_cbe_storemerge5;
  unsigned int llvm_cbe_storemerge5__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  unsigned long long llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  double *llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  double llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge13_count = 0;
  unsigned int llvm_cbe_storemerge13;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge14_count = 0;
  unsigned int llvm_cbe_storemerge14;
  unsigned int llvm_cbe_storemerge14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  double llvm_cbe_tmp__35;
  double llvm_cbe_tmp__35__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  unsigned int llvm_cbe_tmp__36;
  unsigned int llvm_cbe_tmp__36__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned long long llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  double *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  double llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_be_count = 0;
  unsigned int llvm_cbe__2e_be;
  static  unsigned long long aesl_llvm_cbe__2e_be2_count = 0;
  double llvm_cbe__2e_be2;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned long long llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
   char *llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned char llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  double *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  double llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
   char *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned char llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond6_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @select_k_nearest\n");
  llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_thread;

  do {     /* Syntactic loop '.thread' to make GCC happy */
llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge5 = phi i32 [ 0, %%0 ], [ %%storemerge13, %%20 ], [ %%storemerge13, %%.thread  for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_storemerge5_count);
  llvm_cbe_storemerge5 = (unsigned int )llvm_cbe_storemerge5__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge5 = 0x%X",llvm_cbe_storemerge5);
printf("\n = 0x%X",0u);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge5 to i64, !dbg !7 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__32 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%1, i32 1, !dbg !7 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__33 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__32))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__32));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load double* %%2, align 8, !dbg !7 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__34 = (double )*llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__34, *(long long*)(&llvm_cbe_tmp__34));
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge13 = add nsw i32 %%storemerge5, 1, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_storemerge13_count);
  llvm_cbe_storemerge13 = (unsigned int )((unsigned int )(llvm_cbe_storemerge5&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge13 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge13&4294967295ull)));
  if ((((signed int )llvm_cbe_storemerge13) < ((signed int )4336u))) {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    llvm_cbe_tmp__35__PHI_TEMPORARY = (double )llvm_cbe_tmp__34;   /* for PHI node */
    llvm_cbe_tmp__36__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge5;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    goto llvm_cbe__2e_thread;
  }

llvm_cbe_tmp__47:
  if (((llvm_cbe_storemerge13&4294967295U) == (20u&4294967295U))) {
    goto llvm_cbe_tmp__48;
  } else {
    llvm_cbe_storemerge5__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    goto llvm_cbe__2e_thread;
  }

llvm_cbe__2e__crit_edge:
  if (((llvm_cbe__2e_be&4294967295U) == (llvm_cbe_storemerge5&4294967295U))) {
    goto llvm_cbe_tmp__47;
  } else {
    goto llvm_cbe_tmp__49;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge14 = phi i32 [ %%storemerge1, %%.lr.ph ], [ %%storemerge13, %%.thread  for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_storemerge14_count);
  llvm_cbe_storemerge14 = (unsigned int )llvm_cbe_storemerge14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge14 = 0x%X",llvm_cbe_storemerge14);
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi double [ %%.be2, %%.lr.ph ], [ %%3, %%.thread  for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__35 = (double )llvm_cbe_tmp__35__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__35);
printf("\n.be2 = %lf",llvm_cbe__2e_be2);
printf("\n = %lf",llvm_cbe_tmp__34);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi i32 [ %%.be, %%.lr.ph ], [ %%storemerge5, %%.thread  for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__36 = (unsigned int )llvm_cbe_tmp__36__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__36);
printf("\n.be = 0x%X",llvm_cbe__2e_be);
printf("\nstoremerge5 = 0x%X",llvm_cbe_storemerge5);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%storemerge14 to i64, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__37 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge14);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%7, i32 1, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__38 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__37))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__37));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__39 = (double )*llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__39, *(long long*)(&llvm_cbe_tmp__39));
if (AESL_DEBUG_TRACE)
printf("\n  %%.be = select i1 %%10, i32 %%storemerge14, i32 %%6, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe__2e_be_count);
  llvm_cbe__2e_be = (unsigned int )(((llvm_fcmp_olt(llvm_cbe_tmp__39, llvm_cbe_tmp__35))) ? ((unsigned int )llvm_cbe_storemerge14) : ((unsigned int )llvm_cbe_tmp__36));
if (AESL_DEBUG_TRACE)
printf("\n.be = 0x%X\n", llvm_cbe__2e_be);
if (AESL_DEBUG_TRACE)
printf("\n  %%.be2 = select i1 %%10, double %%9, double %%5, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe__2e_be2_count);
  llvm_cbe__2e_be2 = (double )(((llvm_fcmp_olt(llvm_cbe_tmp__39, llvm_cbe_tmp__35))) ? ((double )llvm_cbe_tmp__39) : ((double )llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n.be2 = %lf,  0x%llx\n", llvm_cbe__2e_be2, *(long long*)(&llvm_cbe__2e_be2));
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = add nsw i32 %%storemerge14, 1, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )((unsigned int )(llvm_cbe_storemerge14&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge1 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge1&4294967295ull)));
  if (((llvm_cbe_storemerge1&4294967295U) == (4336u&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge14__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge1;   /* for PHI node */
    llvm_cbe_tmp__35__PHI_TEMPORARY = (double )llvm_cbe__2e_be2;   /* for PHI node */
    llvm_cbe_tmp__36__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe_tmp__49:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sext i32 %%.be to i64, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__40 = (unsigned long long )((signed long long )(signed int )llvm_cbe__2e_be);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%13, i32 0, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__41 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__40))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__40));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i8* %%14, align 1, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__42 = (unsigned char )*llvm_cbe_tmp__41;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%13, i32 1, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__43 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__40))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__40));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load double* %%16, align 8, !dbg !8 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__44 = (double )*llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__44, *(long long*)(&llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = getelementptr inbounds %%struct.BestPoint* %%dist_points, i64 %%1, i32 0, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__45 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__32))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__32));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load i8* %%18, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__46 = (unsigned char )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%19, i8* %%14, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_141_count);
  *llvm_cbe_tmp__41 = llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%3, double* %%16, align 8, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_142_count);
  *llvm_cbe_tmp__43 = llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%15, i8* %%18, align 1, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_143_count);
  *llvm_cbe_tmp__45 = llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%17, double* %%2, align 8, !dbg !9 for 0x%llxth hint within @select_k_nearest  --> \n", ++aesl_llvm_cbe_144_count);
  *llvm_cbe_tmp__33 = llvm_cbe_tmp__44;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__44);
  goto llvm_cbe_tmp__47;

  } while (1); /* end of syntactic loop '.thread' */
llvm_cbe_tmp__48:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @select_k_nearest}\n");
  return;
}


void get_k_NN(l_struct_OC_Point llvm_cbe_new_point, l_struct_OC_Point *llvm_cbe_known_points, l_struct_OC_BestPoint *llvm_cbe_best_points) {
  static  unsigned long long aesl_llvm_cbe_dist_points_count = 0;
  l_struct_OC_BestPoint llvm_cbe_dist_points[4336];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  unsigned long long llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_count = 0;
  unsigned int llvm_cbe_storemerge12;
  unsigned int llvm_cbe_storemerge12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  double llvm_cbe_tmp__51;
  double llvm_cbe_tmp__51__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  double *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  double llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  double *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  double llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  double llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  double llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  double llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
   char *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  unsigned char llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
   char *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  double *llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond4_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  l_struct_OC_BestPoint *llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @get_k_NN\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%18, %%13  for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__65);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge3 to i64, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__50 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__50);
  llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__51__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
  goto llvm_cbe_tmp__67;

llvm_cbe_tmp__68:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%1, i32 1, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__61 = ( char *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__50))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__50));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i8* %%14, align 1, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__62 = (unsigned char )*llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds [4336 x %%struct.BestPoint]* %%dist_points, i64 0, i64 %%1, i32 0, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_193_count);
  llvm_cbe_tmp__63 = ( char *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__50))
#ifdef AESL_BC_SIM
 % 4336
#endif
].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__50));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__50) < 4336 && "Write access out of array 'dist_points' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%15, i8* %%16, align 16, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_194_count);
  *llvm_cbe_tmp__63 = llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds [4336 x %%struct.BestPoint]* %%dist_points, i64 0, i64 %%1, i32 1, !dbg !9 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__64 = (double *)(&llvm_cbe_dist_points[(((signed long long )llvm_cbe_tmp__50))
#ifdef AESL_BC_SIM
 % 4336
#endif
].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__50));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__50) < 4336 && "Write access out of array 'dist_points' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store double %%11, double* %%17, align 8, !dbg !9 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_196_count);
  *llvm_cbe_tmp__64 = llvm_cbe_tmp__59;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%storemerge3, 1, !dbg !9 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__65 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__65&4294967295ull)));
  if (((llvm_cbe_tmp__65&4294967295U) == (4336u&4294967295U))) {
    goto llvm_cbe_tmp__69;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__65;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__67:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12 = phi i32 [ 0, %%.preheader ], [ %%12, %%2  for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_storemerge12_count);
  llvm_cbe_storemerge12 = (unsigned int )llvm_cbe_storemerge12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12 = 0x%X",llvm_cbe_storemerge12);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__60);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = phi double [ 0.000000e+00, %%.preheader ], [ %%11, %%2  for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_169_count);
  llvm_cbe_tmp__51 = (double )llvm_cbe_tmp__51__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__51);
printf("\n = %lf",0x0p0);
printf("\n = %lf",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sext i32 %%storemerge12 to i64, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_170_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.Point* %%new_point, i64 0, i32 0, i64 %%4, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_171_count);
  llvm_cbe_tmp__53 = (double *)(&llvm_cbe_new_point.field0[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load double* %%5, align 8, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_172_count);
  llvm_cbe_tmp__54 = (double )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__54, *(long long*)(&llvm_cbe_tmp__54));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%1, i32 0, i64 %%4, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_173_count);
  llvm_cbe_tmp__55 = (double *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__50))].field0[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__50));
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load double* %%7, align 8, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__56 = (double )*llvm_cbe_tmp__55;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__56, *(long long*)(&llvm_cbe_tmp__56));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = fsub double %%6, %%8, !dbg !8 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_175_count);
  llvm_cbe_tmp__57 = (double )llvm_cbe_tmp__54 - llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__57, *(long long*)(&llvm_cbe_tmp__57));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fmul double %%9, %%9, !dbg !10 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__58 = (double )llvm_cbe_tmp__57 * llvm_cbe_tmp__57;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__58, *(long long*)(&llvm_cbe_tmp__58));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fadd double %%3, %%10, !dbg !10 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__59 = (double )llvm_cbe_tmp__51 + llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__59, *(long long*)(&llvm_cbe_tmp__59));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add nsw i32 %%storemerge12, 1, !dbg !10 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_184_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__60&4294967295ull)));
  if (((llvm_cbe_tmp__60&4294967295U) == (43u&4294967295U))) {
    goto llvm_cbe_tmp__68;
  } else {
    llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__60;   /* for PHI node */
    llvm_cbe_tmp__51__PHI_TEMPORARY = (double )llvm_cbe_tmp__59;   /* for PHI node */
    goto llvm_cbe_tmp__67;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__69:
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds [4336 x %%struct.BestPoint]* %%dist_points, i64 0, i64 0, !dbg !10 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_206_count);
  llvm_cbe_tmp__66 = (l_struct_OC_BestPoint *)(&llvm_cbe_dist_points[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 4336
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @select_k_nearest(%%struct.BestPoint* %%20), !dbg !10 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_207_count);
  select_k_nearest((l_struct_OC_BestPoint *)llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @copy_k_nearest(%%struct.BestPoint* %%20, %%struct.BestPoint* %%best_points), !dbg !9 for 0x%llxth hint within @get_k_NN  --> \n", ++aesl_llvm_cbe_208_count);
  copy_k_nearest((l_struct_OC_BestPoint *)llvm_cbe_tmp__66, (l_struct_OC_BestPoint *)llvm_cbe_best_points);
if (AESL_DEBUG_TRACE) {
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @get_k_NN}\n");
  return;
}


 char plurality_voting(l_struct_OC_BestPoint *llvm_cbe_best_points) {
  static  unsigned long long aesl_llvm_cbe_histogram_count = 0;
   char llvm_cbe_histogram[6];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
   char *llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
   char *llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
   char *llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
   char *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
   char *llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
   char *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
   char *llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  unsigned char llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  unsigned char llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe__2e_3_count = 0;
  unsigned char llvm_cbe__2e_3;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  unsigned char llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_1_count = 0;
  unsigned char llvm_cbe__2e__2e_1;
  static  unsigned long long aesl_llvm_cbe__2e_3_2e_1_count = 0;
  unsigned char llvm_cbe__2e_3_2e_1;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  unsigned char llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_2_count = 0;
  unsigned char llvm_cbe__2e__2e_2;
  static  unsigned long long aesl_llvm_cbe__2e_3_2e_2_count = 0;
  unsigned char llvm_cbe__2e_3_2e_2;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  unsigned char llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_3_count = 0;
  unsigned char llvm_cbe__2e__2e_3;
  static  unsigned long long aesl_llvm_cbe__2e_3_2e_3_count = 0;
  unsigned char llvm_cbe__2e_3_2e_3;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;
  static  unsigned long long aesl_llvm_cbe_305_count = 0;
  unsigned char llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_306_count = 0;
  static  unsigned long long aesl_llvm_cbe_307_count = 0;
  static  unsigned long long aesl_llvm_cbe_308_count = 0;
  static  unsigned long long aesl_llvm_cbe_309_count = 0;
  static  unsigned long long aesl_llvm_cbe_310_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_4_count = 0;
  unsigned char llvm_cbe__2e__2e_4;
  static  unsigned long long aesl_llvm_cbe__2e_3_2e_4_count = 0;
  unsigned char llvm_cbe__2e_3_2e_4;
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  unsigned char llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_5_count = 0;
  unsigned char llvm_cbe__2e__2e_5;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge16_count = 0;
  unsigned int llvm_cbe_storemerge16;
  unsigned int llvm_cbe_storemerge16__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  unsigned long long llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
   char *llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  unsigned char llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  unsigned long long llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
   char *llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  unsigned char llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  unsigned char llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  unsigned int llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond8_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @plurality_voting\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%0 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 0, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__70 = ( char *)(&llvm_cbe_histogram[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 1, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__71 = ( char *)(&llvm_cbe_histogram[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 2, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_227_count);
  llvm_cbe_tmp__72 = ( char *)(&llvm_cbe_histogram[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 3, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__73 = ( char *)(&llvm_cbe_histogram[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 4, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_237_count);
  llvm_cbe_tmp__74 = ( char *)(&llvm_cbe_histogram[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 5, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_242_count);
  llvm_cbe_tmp__75 = ( char *)(&llvm_cbe_histogram[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = call i8* @memset(i8* %%0, i32 0, i64 6 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_250_count);
  ( char *)memset(( char *)llvm_cbe_tmp__70, 0u, 6ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%llX",6ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__76);
}
  llvm_cbe_storemerge16__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__91;

llvm_cbe__2e_preheader:

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load i8* %%0, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_257_count);
  llvm_cbe_tmp__77 = (unsigned char )*llvm_cbe_tmp__70;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%8, i8 0, i8 -1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (unsigned char )((((( char )llvm_cbe_tmp__77) > (( char )((unsigned char )0)))) ? ((unsigned char )((unsigned char )0)) : ((unsigned char )((unsigned char )-1)));
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  %%.3 = select i1 %%8, i8 %%7, i8 0, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e_3_count);
  llvm_cbe__2e_3 = (unsigned char )((((( char )llvm_cbe_tmp__77) > (( char )((unsigned char )0)))) ? ((unsigned char )llvm_cbe_tmp__77) : ((unsigned char )((unsigned char )0)));
if (AESL_DEBUG_TRACE)
printf("\n.3 = 0x%X\n", llvm_cbe__2e_3);

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i8* %%1, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_269_count);
  llvm_cbe_tmp__78 = (unsigned char )*llvm_cbe_tmp__71;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n  %%..1 = select i1 %%10, i8 1, i8 %%., !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__2e_1_count);
  llvm_cbe__2e__2e_1 = (unsigned char )((((( char )llvm_cbe_tmp__78) > (( char )llvm_cbe__2e_3))) ? ((unsigned char )((unsigned char )1)) : ((unsigned char )llvm_cbe__2e_));
if (AESL_DEBUG_TRACE)
printf("\n..1 = 0x%X\n", llvm_cbe__2e__2e_1);
if (AESL_DEBUG_TRACE)
printf("\n  %%.3.1 = select i1 %%10, i8 %%9, i8 %%.3, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e_3_2e_1_count);
  llvm_cbe__2e_3_2e_1 = (unsigned char )((((( char )llvm_cbe_tmp__78) > (( char )llvm_cbe__2e_3))) ? ((unsigned char )llvm_cbe_tmp__78) : ((unsigned char )llvm_cbe__2e_3));
if (AESL_DEBUG_TRACE)
printf("\n.3.1 = 0x%X\n", llvm_cbe__2e_3_2e_1);

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i8* %%2, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_281_count);
  llvm_cbe_tmp__79 = (unsigned char )*llvm_cbe_tmp__72;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE)
printf("\n  %%..2 = select i1 %%12, i8 2, i8 %%..1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__2e_2_count);
  llvm_cbe__2e__2e_2 = (unsigned char )((((( char )llvm_cbe_tmp__79) > (( char )llvm_cbe__2e_3_2e_1))) ? ((unsigned char )((unsigned char )2)) : ((unsigned char )llvm_cbe__2e__2e_1));
if (AESL_DEBUG_TRACE)
printf("\n..2 = 0x%X\n", llvm_cbe__2e__2e_2);
if (AESL_DEBUG_TRACE)
printf("\n  %%.3.2 = select i1 %%12, i8 %%11, i8 %%.3.1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e_3_2e_2_count);
  llvm_cbe__2e_3_2e_2 = (unsigned char )((((( char )llvm_cbe_tmp__79) > (( char )llvm_cbe__2e_3_2e_1))) ? ((unsigned char )llvm_cbe_tmp__79) : ((unsigned char )llvm_cbe__2e_3_2e_1));
if (AESL_DEBUG_TRACE)
printf("\n.3.2 = 0x%X\n", llvm_cbe__2e_3_2e_2);

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load i8* %%3, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_293_count);
  llvm_cbe_tmp__80 = (unsigned char )*llvm_cbe_tmp__73;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%..3 = select i1 %%14, i8 3, i8 %%..2, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__2e_3_count);
  llvm_cbe__2e__2e_3 = (unsigned char )((((( char )llvm_cbe_tmp__80) > (( char )llvm_cbe__2e_3_2e_2))) ? ((unsigned char )((unsigned char )3)) : ((unsigned char )llvm_cbe__2e__2e_2));
if (AESL_DEBUG_TRACE)
printf("\n..3 = 0x%X\n", llvm_cbe__2e__2e_3);
if (AESL_DEBUG_TRACE)
printf("\n  %%.3.3 = select i1 %%14, i8 %%13, i8 %%.3.2, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e_3_2e_3_count);
  llvm_cbe__2e_3_2e_3 = (unsigned char )((((( char )llvm_cbe_tmp__80) > (( char )llvm_cbe__2e_3_2e_2))) ? ((unsigned char )llvm_cbe_tmp__80) : ((unsigned char )llvm_cbe__2e_3_2e_2));
if (AESL_DEBUG_TRACE)
printf("\n.3.3 = 0x%X\n", llvm_cbe__2e_3_2e_3);

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i8* %%4, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_305_count);
  llvm_cbe_tmp__81 = (unsigned char )*llvm_cbe_tmp__74;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE)
printf("\n  %%..4 = select i1 %%16, i8 4, i8 %%..3, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__2e_4_count);
  llvm_cbe__2e__2e_4 = (unsigned char )((((( char )llvm_cbe_tmp__81) > (( char )llvm_cbe__2e_3_2e_3))) ? ((unsigned char )((unsigned char )4)) : ((unsigned char )llvm_cbe__2e__2e_3));
if (AESL_DEBUG_TRACE)
printf("\n..4 = 0x%X\n", llvm_cbe__2e__2e_4);
if (AESL_DEBUG_TRACE)
printf("\n  %%.3.4 = select i1 %%16, i8 %%15, i8 %%.3.3, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e_3_2e_4_count);
  llvm_cbe__2e_3_2e_4 = (unsigned char )((((( char )llvm_cbe_tmp__81) > (( char )llvm_cbe__2e_3_2e_3))) ? ((unsigned char )llvm_cbe_tmp__81) : ((unsigned char )llvm_cbe__2e_3_2e_3));
if (AESL_DEBUG_TRACE)
printf("\n.3.4 = 0x%X\n", llvm_cbe__2e_3_2e_4);

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load i8* %%5, align 1, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_317_count);
  llvm_cbe_tmp__82 = (unsigned char )*llvm_cbe_tmp__75;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%..5 = select i1 %%18, i8 5, i8 %%..4, !dbg !10 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe__2e__2e_5_count);
  llvm_cbe__2e__2e_5 = (unsigned char )((((( char )llvm_cbe_tmp__82) > (( char )llvm_cbe__2e_3_2e_4))) ? ((unsigned char )((unsigned char )5)) : ((unsigned char )llvm_cbe__2e__2e_4));
if (AESL_DEBUG_TRACE)
printf("\n..5 = 0x%X\n", llvm_cbe__2e__2e_5);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @plurality_voting}\n");
  return llvm_cbe__2e__2e_5;
  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__91:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge16 = phi i32 [ 0, %%.preheader5 ], [ %%27, %%19  for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_storemerge16_count);
  llvm_cbe_storemerge16 = (unsigned int )llvm_cbe_storemerge16__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge16 = 0x%X",llvm_cbe_storemerge16);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__90);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = sext i32 %%storemerge16 to i64, !dbg !7 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_330_count);
  llvm_cbe_tmp__83 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge16);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__83);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds %%struct.BestPoint* %%best_points, i64 %%20, i32 0, !dbg !7 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_331_count);
  llvm_cbe_tmp__84 = ( char *)(&llvm_cbe_best_points[(((signed long long )llvm_cbe_tmp__83))].field0);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__83));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load i8* %%21, align 1, !dbg !7 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_332_count);
  llvm_cbe_tmp__85 = (unsigned char )*llvm_cbe_tmp__84;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = sext i8 %%22 to i64, !dbg !11 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_334_count);
  llvm_cbe_tmp__86 = (unsigned long long )((signed long long )( char )llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__86);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds [6 x i8]* %%histogram, i64 0, i64 %%23, !dbg !11 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_335_count);
  llvm_cbe_tmp__87 = ( char *)(&llvm_cbe_histogram[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 6
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__86) < 6)) fprintf(stderr, "%s:%d: warning: Read access out of array 'histogram' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load i8* %%24, align 1, !dbg !11 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_336_count);
  llvm_cbe_tmp__88 = (unsigned char )*llvm_cbe_tmp__87;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = add i8 %%25, 1, !dbg !11 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_337_count);
  llvm_cbe_tmp__89 = (unsigned char )((unsigned char )(((unsigned char )(llvm_cbe_tmp__88&255ull)) + ((unsigned char )(((unsigned char )1)&255ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )(llvm_cbe_tmp__89&255ull)));

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 6 && "Write access out of array 'histogram' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%26, i8* %%24, align 1, !dbg !11 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_338_count);
  *llvm_cbe_tmp__87 = llvm_cbe_tmp__89;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = add nsw i32 %%storemerge16, 1, !dbg !9 for 0x%llxth hint within @plurality_voting  --> \n", ++aesl_llvm_cbe_339_count);
  llvm_cbe_tmp__90 = (unsigned int )((unsigned int )(llvm_cbe_storemerge16&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__90&4294967295ull)));
  if (((llvm_cbe_tmp__90&4294967295U) == (20u&4294967295U))) {
    goto llvm_cbe__2e_preheader;
  } else {
    llvm_cbe_storemerge16__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__90;   /* for PHI node */
    goto llvm_cbe_tmp__91;
  }

  } while (1); /* end of syntactic loop '' */
}


 char knn_classifyinstance(l_struct_OC_Point llvm_cbe_new_point, l_struct_OC_Point *llvm_cbe_known_points) {
  static  unsigned long long aesl_llvm_cbe_best_points_count = 0;
  l_struct_OC_BestPoint llvm_cbe_best_points[20];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  l_struct_OC_BestPoint *llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  unsigned char llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @knn_classifyinstance\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [20 x %%struct.BestPoint]* %%best_points, i64 0, i64 0, !dbg !8 for 0x%llxth hint within @knn_classifyinstance  --> \n", ++aesl_llvm_cbe_349_count);
  llvm_cbe_tmp__92 = (l_struct_OC_BestPoint *)(&llvm_cbe_best_points[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 20
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @get_k_NN(%%struct.Point* byval align 8 %%new_point, %%struct.Point* %%known_points, %%struct.BestPoint* %%1), !dbg !8 for 0x%llxth hint within @knn_classifyinstance  --> \n", ++aesl_llvm_cbe_350_count);
  get_k_NN(llvm_cbe_new_point, (l_struct_OC_Point *)llvm_cbe_known_points, (l_struct_OC_BestPoint *)llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call signext i8 @plurality_voting(%%struct.BestPoint* %%1), !dbg !8 for 0x%llxth hint within @knn_classifyinstance  --> \n", ++aesl_llvm_cbe_351_count);
  llvm_cbe_tmp__93 = (unsigned char )plurality_voting((l_struct_OC_BestPoint *)llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__93);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @knn_classifyinstance}\n");
  return llvm_cbe_tmp__93;
}

