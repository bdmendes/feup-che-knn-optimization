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
typedef struct l_struct_OC_Point l_struct_OC_Point;

/* Structure contents */
struct l_struct_OC_Point {
  double field0[43];
  unsigned char field1;
};


/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
 char get_class_name( char llvm_cbe_class_id);
signed int verify_results(signed int llvm_cbe_num_new_points, l_struct_OC_Point *llvm_cbe_new_points,  char *llvm_cbe_key);
signed int get_reference_score(double llvm_cbe_time_s, signed int llvm_cbe_num_points);
void initialize_known_points(signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_known_points, signed int llvm_cbe_num_classes, signed int llvm_cbe_num_features);
static signed int aesl_internal_rand_int(signed int llvm_cbe_max);
void initialize_new_points(signed int llvm_cbe_num_new_points, l_struct_OC_Point *llvm_cbe_new_points, signed int llvm_cbe_num_features);
void show_point(l_struct_OC_Point llvm_cbe_point, signed int llvm_cbe_num_features);
void minmax(double *llvm_cbe_min, double *llvm_cbe_max, signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_known_points, signed int llvm_cbe_num_features);
void minmax_normalize(double *llvm_cbe_min, double *llvm_cbe_max, signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_points, signed int llvm_cbe_num_features);
void minmax_normalize_point(double *llvm_cbe_min, double *llvm_cbe_max, l_struct_OC_Point *llvm_cbe_point, signed int llvm_cbe_num_features);
static double aesl_internal_get_rand_feature_value(void);
static double aesl_internal_rand_double(void);


/* Global Variable Definitions and Initialization */
static  char aesl_internal_str3[8] = "Failed!";
static  char aesl_internal__OC_str8[6] = ",%.3f";
static  char aesl_internal__OC_str9[14] = ", class = %d\n";
static  char aesl_internal_str[23] = "Skipping verification.";
static  char aesl_internal__OC_str7[5] = "%.3f";
static  char aesl_internal_str1[21] = "Verifying results...";
static  char aesl_internal_str2[8] = "Passed!";
static  char aesl_internal__OC_str4[27] = "Verification is complete: ";
static  char aesl_internal__OC_str3[3] = "!=";
static  char aesl_internal__OC_str2[11] = " %c %s %c\n";


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

 char get_class_name( char llvm_cbe_class_id) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  unsigned char llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @get_class_name\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = add i8 %%class_id, 65, !dbg !12 for 0x%llxth hint within @get_class_name  --> \n", ++aesl_llvm_cbe_3_count);
  llvm_cbe_tmp__1 = (unsigned char )((unsigned char )(((unsigned char )(llvm_cbe_class_id&255ull)) + ((unsigned char )(((unsigned char )65)&255ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )(llvm_cbe_tmp__1&255ull)));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @get_class_name}\n");
  return llvm_cbe_tmp__1;
}


signed int verify_results(signed int llvm_cbe_num_new_points, l_struct_OC_Point *llvm_cbe_new_points,  char *llvm_cbe_key) {
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts_count = 0;
  unsigned int llvm_cbe_puts;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts1_count = 0;
  unsigned int llvm_cbe_puts1;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge4_count = 0;
  unsigned int llvm_cbe_storemerge4;
  unsigned int llvm_cbe_storemerge4__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  unsigned int llvm_cbe_tmp__3;
  unsigned int llvm_cbe_tmp__3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  unsigned long long llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
   char *llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned char llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
   char *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  unsigned char llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  unsigned char llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  unsigned char llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned int llvm_cbe_tmp__14;
  unsigned int llvm_cbe_tmp__14__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts2_count = 0;
  unsigned int llvm_cbe_puts2;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts3_count = 0;
  unsigned int llvm_cbe_puts3;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  unsigned int llvm_cbe_tmp__17;
  unsigned int llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @verify_results\n");
  if (((llvm_cbe_key) == ((( char *)/*NULL*/0)))) {
    goto llvm_cbe_tmp__18;
  } else {
    goto llvm_cbe_tmp__19;
  }

llvm_cbe_tmp__18:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts = tail call i32 @puts(i8* getelementptr inbounds ([23 x i8]* @aesl_internal_str, i64 0, i64 0)), !dbg !13 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_puts_count);
   /*tail*/ puts(( char *)((&aesl_internal_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 23
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts = 0x%X",llvm_cbe_puts);
}
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )4294967295u;   /* for PHI node */
  goto llvm_cbe_tmp__20;

llvm_cbe_tmp__19:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts1 = tail call i32 @puts(i8* getelementptr inbounds ([21 x i8]* @aesl_internal_str1, i64 0, i64 0)), !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_puts1_count);
   /*tail*/ puts(( char *)((&aesl_internal_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 21
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts1 = 0x%X",llvm_cbe_puts1);
}
  if ((((signed int )llvm_cbe_num_new_points) > ((signed int )0u))) {
    llvm_cbe_storemerge4__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__3__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge_2e_thread;
  }

llvm_cbe__2e__crit_edge_2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @aesl_internal_.str4, i64 0, i64 0)) nounwind, !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_24_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 27
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
  goto llvm_cbe_tmp__21;

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge4 = phi i32 [ %%21, %%19 ], [ 0, %%3  for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_storemerge4_count);
  llvm_cbe_storemerge4 = (unsigned int )llvm_cbe_storemerge4__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge4 = 0x%X",llvm_cbe_storemerge4);
printf("\n = 0x%X",llvm_cbe_tmp__15);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi i32 [ %%20, %%19 ], [ 1, %%3  for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__3 = (unsigned int )llvm_cbe_tmp__3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__3);
printf("\n = 0x%X",llvm_cbe_tmp__14);
printf("\n = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%storemerge4 to i64, !dbg !12 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__4 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge4);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.Point* %%new_points, i64 %%7, i32 1, !dbg !12 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__5 = ( char *)(&llvm_cbe_new_points[(((signed long long )llvm_cbe_tmp__4))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__4));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i8* %%8, align 1, !dbg !12 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__6 = (unsigned char )*llvm_cbe_tmp__5;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds i8* %%key, i64 %%7, !dbg !13 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__7 = ( char *)(&llvm_cbe_key[(((signed long long )llvm_cbe_tmp__4))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__4));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i8* %%10, align 1, !dbg !13 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__8 = (unsigned char )*llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__8);
  if (((llvm_cbe_tmp__6&255U) == (llvm_cbe_tmp__8&255U))) {
    llvm_cbe_tmp__14__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__3;   /* for PHI node */
    goto llvm_cbe_tmp__22;
  } else {
    goto llvm_cbe_tmp__23;
  }

llvm_cbe_tmp__22:
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = phi i32 [ 0, %%13 ], [ %%6, %%.lr.ph  for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__14 = (unsigned int )llvm_cbe_tmp__14__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__14);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = add nsw i32 %%storemerge4, 1, !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_storemerge4&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
  if (((llvm_cbe_tmp__15&4294967295U) == (llvm_cbe_num_new_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge4__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__15;   /* for PHI node */
    llvm_cbe_tmp__3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__14;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe_tmp__23:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = tail call signext i8 @get_class_name(i8 signext %%9), !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__9 = (unsigned char ) /*tail*/ get_class_name(llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__6);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__9);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = sext i8 %%14 to i32, !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__10 = (unsigned int )((signed int )( char )llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = tail call signext i8 @get_class_name(i8 signext %%11), !dbg !15 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__11 = (unsigned char ) /*tail*/ get_class_name(llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__8);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__11);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = sext i8 %%16 to i32, !dbg !15 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__12 = (unsigned int )((signed int )( char )llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([11 x i8]* @aesl_internal_.str2, i64 0, i64 0), i32 %%15, i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str3, i64 0, i64 0), i32 %%17) nounwind, !dbg !15 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_44_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 11
#endif
])), llvm_cbe_tmp__10, ( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__10);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__12);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__13);
}
  llvm_cbe_tmp__14__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__22;

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @aesl_internal_.str4, i64 0, i64 0)) nounwind, !dbg !14 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_56_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 27
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__16);
}
  if (((llvm_cbe_tmp__14&4294967295U) == (1u&4294967295U))) {
    goto llvm_cbe_tmp__21;
  } else {
    goto llvm_cbe_tmp__24;
  }

llvm_cbe_tmp__21:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts2 = tail call i32 @puts(i8* getelementptr inbounds ([8 x i8]* @aesl_internal_str2, i64 0, i64 0)), !dbg !15 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_puts2_count);
   /*tail*/ puts(( char *)((&aesl_internal_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts2 = 0x%X",llvm_cbe_puts2);
}
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__20;

llvm_cbe_tmp__24:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts3 = tail call i32 @puts(i8* getelementptr inbounds ([8 x i8]* @aesl_internal_str3, i64 0, i64 0)), !dbg !15 for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_puts3_count);
   /*tail*/ puts(( char *)((&aesl_internal_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts3 = 0x%X",llvm_cbe_puts3);
}
  llvm_cbe_tmp__17__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe_tmp__20;

llvm_cbe_tmp__20:
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = phi i32 [ 1, %%25 ], [ 0, %%24 ], [ -1, %%2  for 0x%llxth hint within @verify_results  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__17 = (unsigned int )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__17);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",4294967295u);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @verify_results}\n");
  return llvm_cbe_tmp__17;
}


signed int get_reference_score(double llvm_cbe_time_s, signed int llvm_cbe_num_points) {
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  double llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  double llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  double llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  double llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  double llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  double llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__34;
  unsigned int llvm_cbe_tmp__34__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @get_reference_score\n");
  switch (((unsigned int )(llvm_cbe_num_points&4294967295ull))) {
  default:
    llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe_tmp__35;
;
  case ((unsigned int )(1000u&4294967295ull)):
    goto llvm_cbe_tmp__36;
    break;
  case ((unsigned int )(250000u&4294967295ull)):
    goto llvm_cbe_tmp__37;
  case ((unsigned int )(1000000u&4294967295ull)):
    goto llvm_cbe_tmp__38;
  }
llvm_cbe_tmp__36:
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = fdiv double 8.400000e-03, %%time_s, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__25 = (double )0x1.13404ea4a8c15p-7 / llvm_cbe_time_s;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__25, *(long long*)(&llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fmul double %%2, 1.000000e+02, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__26 = (double )llvm_cbe_tmp__25 * 0x1.9p6;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__26, *(long long*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = fptosi double %%3 to i32, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__27 = (unsigned int )((signed int )llvm_cbe_tmp__26&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__27);
  llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__27;   /* for PHI node */
  goto llvm_cbe_tmp__35;

llvm_cbe_tmp__37:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = fdiv double 8.221700e+00, %%time_s, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__28 = (double )0x1.07182a9930be1p3 / llvm_cbe_time_s;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__28, *(long long*)(&llvm_cbe_tmp__28));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fmul double %%6, 1.000000e+02, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__29 = (double )llvm_cbe_tmp__28 * 0x1.9p6;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__29, *(long long*)(&llvm_cbe_tmp__29));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = fptosi double %%7 to i32, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__30 = (unsigned int )((signed int )llvm_cbe_tmp__29&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
  llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
  goto llvm_cbe_tmp__35;

llvm_cbe_tmp__38:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fdiv double 6.435850e+01, %%time_s, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__31 = (double )0x1.016f1a9fbe76dp6 / llvm_cbe_time_s;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__31, *(long long*)(&llvm_cbe_tmp__31));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fmul double %%10, 1.000000e+02, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__32 = (double )llvm_cbe_tmp__31 * 0x1.9p6;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__32, *(long long*)(&llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = fptosi double %%11 to i32, !dbg !12 for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__33 = (unsigned int )((signed int )llvm_cbe_tmp__32&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
  llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__33;   /* for PHI node */
  goto llvm_cbe_tmp__35;

llvm_cbe_tmp__35:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = phi i32 [ %%12, %%9 ], [ %%8, %%5 ], [ %%4, %%1 ], [ 0, %%0  for 0x%llxth hint within @get_reference_score  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__34 = (unsigned int )llvm_cbe_tmp__34__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__34);
printf("\n = 0x%X",llvm_cbe_tmp__33);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n = 0x%X",llvm_cbe_tmp__27);
printf("\n = 0x%X",0u);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @get_reference_score}\n");
  return llvm_cbe_tmp__34;
}


void initialize_known_points(signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_known_points, signed int llvm_cbe_num_classes, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  unsigned int llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  unsigned char llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  unsigned long long llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
   char *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond5_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge12_2e_us;
  unsigned int llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  double llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned long long llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  double *llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge3_2e_us;
  unsigned int llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned long long llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned char llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
   char *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond6_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @initialize_known_points\n");
  if ((((signed int )llvm_cbe_num_points) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe_tmp__55;
  }

llvm_cbe__2e_preheader_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add nsw i32 %%num_classes, -1, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(llvm_cbe_num_classes&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__39&4294967295ull)));
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe_tmp__56;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3.us = phi i32 [ %%9, %%4 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_storemerge3_2e_us_count);
  llvm_cbe_storemerge3_2e_us = (unsigned int )llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3.us = 0x%X",llvm_cbe_storemerge3_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__44);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = sext i32 %%storemerge3.us to i64, !dbg !12 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__49 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__49);
  llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__57;

llvm_cbe_tmp__58:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call fastcc i32 @aesl_internal_rand_int(i32 %%3), !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__40 = (unsigned int ) /*tail*/ aesl_internal_rand_int(llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__39);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__40);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = trunc i32 %%5 to i8, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__41 = (unsigned char )((unsigned char )llvm_cbe_tmp__40&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%storemerge3.us to i64, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__42 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%7, i32 1, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__43 = ( char *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__42))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__42));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%6, i8* %%8, align 1, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_107_count);
  *llvm_cbe_tmp__43 = llvm_cbe_tmp__41;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = add nsw i32 %%storemerge3.us, 1, !dbg !14 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__44 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__44&4294967295ull)));
  if (((llvm_cbe_tmp__44&4294967295U) == (llvm_cbe_num_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge4;
  } else {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__44;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__57:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12.us = phi i32 [ 0, %%.lr.ph.us ], [ %%14, %%10  for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_storemerge12_2e_us_count);
  llvm_cbe_storemerge12_2e_us = (unsigned int )llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12.us = 0x%X",llvm_cbe_storemerge12_2e_us);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = tail call fastcc double @aesl_internal_get_rand_feature_value(), !dbg !12 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__45 = (double ) /*tail*/ aesl_internal_get_rand_feature_value();
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sext i32 %%storemerge12.us to i64, !dbg !12 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__46 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%15, i32 0, i64 %%12, !dbg !12 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__47 = (double *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__49))].field0[(((signed long long )llvm_cbe_tmp__46))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__49));
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__46));
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%11, double* %%13, align 8, !dbg !12 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_118_count);
  *llvm_cbe_tmp__47 = llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add nsw i32 %%storemerge12.us, 1, !dbg !14 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
  if (((llvm_cbe_tmp__48&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe_tmp__58;
  } else {
    llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__48;   /* for PHI node */
    goto llvm_cbe_tmp__57;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__56:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ %%21, %%16 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",llvm_cbe_tmp__54);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = tail call fastcc i32 @aesl_internal_rand_int(i32 %%3), !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__50 = (unsigned int ) /*tail*/ aesl_internal_rand_int(llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__39);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__50);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = trunc i32 %%17 to i8, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__51 = (unsigned char )((unsigned char )llvm_cbe_tmp__50&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = sext i32 %%storemerge3 to i64, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%19, i32 1, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__53 = ( char *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__52))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 %%18, i8* %%20, align 1, !dbg !13 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_137_count);
  *llvm_cbe_tmp__53 = llvm_cbe_tmp__51;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = add nsw i32 %%storemerge3, 1, !dbg !14 for 0x%llxth hint within @initialize_known_points  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
  if (((llvm_cbe_tmp__54&4294967295U) == (llvm_cbe_num_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge4;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__54;   /* for PHI node */
    goto llvm_cbe_tmp__56;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e__crit_edge4:
  goto llvm_cbe_tmp__55;

llvm_cbe_tmp__55:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @initialize_known_points}\n");
  return;
}


static signed int aesl_internal_rand_int(signed int llvm_cbe_max) {
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_rand_int\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call i32 @rand() nounwind, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_int  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__59 = (unsigned int ) /*tail*/ rand();
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add nsw i32 %%max, 1, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_int  --> \n", ++aesl_llvm_cbe_153_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(llvm_cbe_max&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__60&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sdiv i32 2147483647, %%2, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_int  --> \n", ++aesl_llvm_cbe_154_count);
  llvm_cbe_tmp__61 = (unsigned int )((signed int )(((signed int )2147483647u) / ((signed int )llvm_cbe_tmp__60)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__61));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%3, 1, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_int  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_tmp__61&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = sdiv i32 %%1, %%4, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_int  --> \n", ++aesl_llvm_cbe_156_count);
  llvm_cbe_tmp__63 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__59) / ((signed int )llvm_cbe_tmp__62)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__63));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @aesl_internal_rand_int}\n");
  return llvm_cbe_tmp__63;
}


void initialize_new_points(signed int llvm_cbe_num_new_points, l_struct_OC_Point *llvm_cbe_new_points, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  unsigned long long llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
   char *llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond5_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge12_2e_us;
  unsigned int llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  double llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  unsigned long long llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  double *llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  unsigned int llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge3_2e_us;
  unsigned int llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  unsigned long long llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  unsigned long long llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
   char *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned int llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond6_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @initialize_new_points\n");
  if ((((signed int )llvm_cbe_num_new_points) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe_tmp__75;
  }

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe_tmp__76;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3.us = phi i32 [ %%6, %%3 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_storemerge3_2e_us_count);
  llvm_cbe_storemerge3_2e_us = (unsigned int )llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3.us = 0x%X",llvm_cbe_storemerge3_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__66);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sext i32 %%storemerge3.us to i64, !dbg !12 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_199_count);
  llvm_cbe_tmp__71 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__71);
  llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__77;

llvm_cbe_tmp__78:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sext i32 %%storemerge3.us to i64, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__64 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds %%struct.Point* %%new_points, i64 %%4, i32 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_177_count);
  llvm_cbe_tmp__65 = ( char *)(&llvm_cbe_new_points[(((signed long long )llvm_cbe_tmp__64))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__64));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 -1, i8* %%5, align 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_178_count);
  *llvm_cbe_tmp__65 = ((unsigned char )-1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )-1));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%storemerge3.us, 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__66 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__66&4294967295ull)));
  if (((llvm_cbe_tmp__66&4294967295U) == (llvm_cbe_num_new_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge4;
  } else {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__66;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__77:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12.us = phi i32 [ 0, %%.lr.ph.us ], [ %%11, %%7  for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_storemerge12_2e_us_count);
  llvm_cbe_storemerge12_2e_us = (unsigned int )llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12.us = 0x%X",llvm_cbe_storemerge12_2e_us);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__70);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call fastcc double @aesl_internal_get_rand_feature_value(), !dbg !12 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_186_count);
  llvm_cbe_tmp__67 = (double ) /*tail*/ aesl_internal_get_rand_feature_value();
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__67);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sext i32 %%storemerge12.us to i64, !dbg !12 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__68 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__68);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.Point* %%new_points, i64 %%12, i32 0, i64 %%9, !dbg !12 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__69 = (double *)(&llvm_cbe_new_points[(((signed long long )llvm_cbe_tmp__71))].field0[(((signed long long )llvm_cbe_tmp__68))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__71));
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__68));
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%8, double* %%10, align 8, !dbg !12 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_189_count);
  *llvm_cbe_tmp__69 = llvm_cbe_tmp__67;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = add nsw i32 %%storemerge12.us, 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_190_count);
  llvm_cbe_tmp__70 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__70&4294967295ull)));
  if (((llvm_cbe_tmp__70&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe_tmp__78;
  } else {
    llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__70;   /* for PHI node */
    goto llvm_cbe_tmp__77;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__76:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ %%16, %%13 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",llvm_cbe_tmp__74);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sext i32 %%storemerge3 to i64, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__72 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.Point* %%new_points, i64 %%14, i32 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_205_count);
  llvm_cbe_tmp__73 = ( char *)(&llvm_cbe_new_points[(((signed long long )llvm_cbe_tmp__72))].field1);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__72));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8 -1, i8* %%15, align 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_206_count);
  *llvm_cbe_tmp__73 = ((unsigned char )-1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned char )-1));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = add nsw i32 %%storemerge3, 1, !dbg !13 for 0x%llxth hint within @initialize_new_points  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__74 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__74&4294967295ull)));
  if (((llvm_cbe_tmp__74&4294967295U) == (llvm_cbe_num_new_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge4;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__74;   /* for PHI node */
    goto llvm_cbe_tmp__76;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e__crit_edge4:
  goto llvm_cbe_tmp__75;

llvm_cbe_tmp__75:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @initialize_new_points}\n");
  return;
}


void show_point(l_struct_OC_Point llvm_cbe_point, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  double *llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  double llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  unsigned long long llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  double *llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  double llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned int llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  unsigned int llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
   char *llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  unsigned char llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  unsigned int llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  unsigned int llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @show_point\n");
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ %%13, %%12 ], [ 0, %%0  for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",llvm_cbe_tmp__86);
printf("\n = 0x%X",0u);
}
  if (((llvm_cbe_storemerge1&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__91;
  } else {
    goto llvm_cbe_tmp__92;
  }

llvm_cbe_tmp__93:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = add nsw i32 %%storemerge1, 1, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_238_count);
  llvm_cbe_tmp__86 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__86&4294967295ull)));
  if (((llvm_cbe_tmp__86&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__86;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe_tmp__91:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds %%struct.Point* %%point, i64 0, i32 0, i64 0, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_229_count);
  llvm_cbe_tmp__79 = (double *)(&llvm_cbe_point.field0[(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load double* %%4, align 8, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__80 = (double )*llvm_cbe_tmp__79;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__80, *(long long*)(&llvm_cbe_tmp__80));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([5 x i8]* @aesl_internal_.str7, i64 0, i64 0), double %%5) nounwind, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_231_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str7[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])), llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__80, *(long long*)(&llvm_cbe_tmp__80));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__81);
}
  goto llvm_cbe_tmp__93;

llvm_cbe_tmp__92:
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sext i32 %%storemerge1 to i64, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__82 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds %%struct.Point* %%point, i64 0, i32 0, i64 %%8, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__83 = (double *)(&llvm_cbe_point.field0[(((signed long long )llvm_cbe_tmp__82))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__82));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load double* %%9, align 8, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__84 = (double )*llvm_cbe_tmp__83;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__84, *(long long*)(&llvm_cbe_tmp__84));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([6 x i8]* @aesl_internal_.str8, i64 0, i64 0), double %%10) nounwind, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_236_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str8[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 6
#endif
])), llvm_cbe_tmp__84);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__84, *(long long*)(&llvm_cbe_tmp__84));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__85);
}
  goto llvm_cbe_tmp__93;

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds %%struct.Point* %%point, i64 0, i32 1, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_246_count);
  llvm_cbe_tmp__87 = ( char *)(&llvm_cbe_point.field1);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i8* %%14, align 8, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_247_count);
  llvm_cbe_tmp__88 = (unsigned char )*llvm_cbe_tmp__87;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = sext i8 %%15 to i32, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_248_count);
  llvm_cbe_tmp__89 = (unsigned int )((signed int )( char )llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @aesl_internal_.str9, i64 0, i64 0), i32 %%16) nounwind, !dbg !13 for 0x%llxth hint within @show_point  --> \n", ++aesl_llvm_cbe_249_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str9[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 14
#endif
])), llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__89);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__90);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @show_point}\n");
  return;
}


void minmax(double *llvm_cbe_min, double *llvm_cbe_max, signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_known_points, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  unsigned int llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond10_count = 0;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  unsigned int llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;
  static  unsigned long long aesl_llvm_cbe_305_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_306_count = 0;
  static  unsigned long long aesl_llvm_cbe_307_count = 0;
  static  unsigned long long aesl_llvm_cbe_308_count = 0;
  static  unsigned long long aesl_llvm_cbe_309_count = 0;
  double llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_310_count = 0;
  double *llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  double llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge23_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge23_2e_us;
  unsigned int llvm_cbe_storemerge23_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  unsigned long long llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  double *llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  double llvm_cbe_tmp__101;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  double *llvm_cbe_tmp__102;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  double llvm_cbe_tmp__103;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge15_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge15_2e_us;
  unsigned int llvm_cbe_storemerge15_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  unsigned long long llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge7_count = 0;
  unsigned int llvm_cbe_storemerge7;
  unsigned int llvm_cbe_storemerge7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
  unsigned long long llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  double *llvm_cbe_tmp__106;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  double *llvm_cbe_tmp__107;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  unsigned int llvm_cbe_tmp__108;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond12_count = 0;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @minmax\n");
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge7__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph9;
  } else {
    goto llvm_cbe__2e_preheader4;
  }

llvm_cbe__2e_preheader4:
  if ((((signed int )llvm_cbe_num_points) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe_tmp__109;
  }

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge15_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__crit_edge6;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge15.us = phi i32 [ %%4, %%3 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_storemerge15_2e_us_count);
  llvm_cbe_storemerge15_2e_us = (unsigned int )llvm_cbe_storemerge15_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge15.us = 0x%X",llvm_cbe_storemerge15_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__94);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = sext i32 %%storemerge15.us to i64, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_333_count);
  llvm_cbe_tmp__104 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge15_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__104);
  llvm_cbe_storemerge23_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__110;

llvm_cbe_tmp__111:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%storemerge15.us, 1, !dbg !15 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_285_count);
  llvm_cbe_tmp__94 = (unsigned int )((unsigned int )(llvm_cbe_storemerge15_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__94&4294967295ull)));
  if (((llvm_cbe_tmp__94&4294967295U) == (llvm_cbe_num_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge6;
  } else {
    llvm_cbe_storemerge15_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__94;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__110:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge23.us = phi i32 [ 0, %%.lr.ph.us ], [ %%6, %%5  for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_storemerge23_2e_us_count);
  llvm_cbe_storemerge23_2e_us = (unsigned int )llvm_cbe_storemerge23_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge23.us = 0x%X",llvm_cbe_storemerge23_2e_us);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__95);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sext i32 %%storemerge23.us to i64, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_314_count);
  llvm_cbe_tmp__99 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge23_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__99);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds %%struct.Point* %%known_points, i64 %%21, i32 0, i64 %%14, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_315_count);
  llvm_cbe_tmp__100 = (double *)(&llvm_cbe_known_points[(((signed long long )llvm_cbe_tmp__104))].field0[(((signed long long )llvm_cbe_tmp__99))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__104));
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__99));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load double* %%15, align 8, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_316_count);
  llvm_cbe_tmp__101 = (double )*llvm_cbe_tmp__100;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__101, *(long long*)(&llvm_cbe_tmp__101));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds double* %%min, i64 %%14, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_317_count);
  llvm_cbe_tmp__102 = (double *)(&llvm_cbe_min[(((signed long long )llvm_cbe_tmp__99))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__99));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load double* %%17, align 8, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_318_count);
  llvm_cbe_tmp__103 = (double )*llvm_cbe_tmp__102;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__103, *(long long*)(&llvm_cbe_tmp__103));
  if ((llvm_fcmp_olt(llvm_cbe_tmp__101, llvm_cbe_tmp__103))) {
    goto llvm_cbe_tmp__112;
  } else {
    goto llvm_cbe_tmp__113;
  }

llvm_cbe_tmp__114:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%storemerge23.us, 1, !dbg !15 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_294_count);
  llvm_cbe_tmp__95 = (unsigned int )((unsigned int )(llvm_cbe_storemerge23_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__95&4294967295ull)));
  if (((llvm_cbe_tmp__95&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe_tmp__111;
  } else {
    llvm_cbe_storemerge23_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__95;   /* for PHI node */
    goto llvm_cbe_tmp__110;
  }

llvm_cbe_tmp__115:
if (AESL_DEBUG_TRACE)
printf("\n  store double %%9, double* %%10, align 8, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_307_count);
  *llvm_cbe_tmp__97 = llvm_cbe_tmp__96;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__96);
  goto llvm_cbe_tmp__114;

llvm_cbe_tmp__113:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%15, align 8, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_309_count);
  llvm_cbe_tmp__96 = (double )*llvm_cbe_tmp__100;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__96, *(long long*)(&llvm_cbe_tmp__96));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds double* %%max, i64 %%14, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_310_count);
  llvm_cbe_tmp__97 = (double *)(&llvm_cbe_max[(((signed long long )llvm_cbe_tmp__99))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__99));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load double* %%10, align 8, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_311_count);
  llvm_cbe_tmp__98 = (double )*llvm_cbe_tmp__97;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__98, *(long long*)(&llvm_cbe_tmp__98));
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__96, llvm_cbe_tmp__98))) {
    goto llvm_cbe_tmp__115;
  } else {
    goto llvm_cbe_tmp__114;
  }

llvm_cbe_tmp__112:
if (AESL_DEBUG_TRACE)
printf("\n  store double %%16, double* %%17, align 8, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_321_count);
  *llvm_cbe_tmp__102 = llvm_cbe_tmp__101;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__101);
  goto llvm_cbe_tmp__113;

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
  do {     /* Syntactic loop '.lr.ph9' to make GCC happy */
llvm_cbe__2e_lr_2e_ph9:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge7 = phi i32 [ %%25, %%.lr.ph9 ], [ 0, %%0  for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_storemerge7_count);
  llvm_cbe_storemerge7 = (unsigned int )llvm_cbe_storemerge7__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge7 = 0x%X",llvm_cbe_storemerge7);
printf("\n = 0x%X",llvm_cbe_tmp__108);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = sext i32 %%storemerge7 to i64, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_335_count);
  llvm_cbe_tmp__105 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge7);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__105);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = getelementptr inbounds double* %%min, i64 %%22, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_336_count);
  llvm_cbe_tmp__106 = (double *)(&llvm_cbe_min[(((signed long long )llvm_cbe_tmp__105))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__105));
}
if (AESL_DEBUG_TRACE)
printf("\n  store double 0x7FEFFFFFFFFFFFFF, double* %%23, align 8, !dbg !12 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_337_count);
  *llvm_cbe_tmp__106 = 0x1.fffffffffffffp1023;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x1.fffffffffffffp1023);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds double* %%max, i64 %%22, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_338_count);
  llvm_cbe_tmp__107 = (double *)(&llvm_cbe_max[(((signed long long )llvm_cbe_tmp__105))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__105));
}
if (AESL_DEBUG_TRACE)
printf("\n  store double 0xFFEFFFFFFFFFFFFF, double* %%24, align 8, !dbg !13 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_339_count);
  *llvm_cbe_tmp__107 = -0x1.fffffffffffffp1023;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", -0x1.fffffffffffffp1023);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = add nsw i32 %%storemerge7, 1, !dbg !14 for 0x%llxth hint within @minmax  --> \n", ++aesl_llvm_cbe_340_count);
  llvm_cbe_tmp__108 = (unsigned int )((unsigned int )(llvm_cbe_storemerge7&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__108&4294967295ull)));
  if (((llvm_cbe_tmp__108&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe__2e_preheader4;
  } else {
    llvm_cbe_storemerge7__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__108;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph9;
  }

  } while (1); /* end of syntactic loop '.lr.ph9' */
llvm_cbe__2e__crit_edge6:
  goto llvm_cbe_tmp__109;

llvm_cbe_tmp__109:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @minmax}\n");
  return;
}


void minmax_normalize(double *llvm_cbe_min, double *llvm_cbe_max, signed int llvm_cbe_num_points, l_struct_OC_Point *llvm_cbe_points, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;
  static  unsigned long long aesl_llvm_cbe_355_count = 0;
  static  unsigned long long aesl_llvm_cbe_356_count = 0;
  static  unsigned long long aesl_llvm_cbe_357_count = 0;
  static  unsigned long long aesl_llvm_cbe_358_count = 0;
  static  unsigned long long aesl_llvm_cbe_359_count = 0;
  static  unsigned long long aesl_llvm_cbe_360_count = 0;
  static  unsigned long long aesl_llvm_cbe_361_count = 0;
  static  unsigned long long aesl_llvm_cbe_362_count = 0;
  static  unsigned long long aesl_llvm_cbe_363_count = 0;
  static  unsigned long long aesl_llvm_cbe_364_count = 0;
  static  unsigned long long aesl_llvm_cbe_365_count = 0;
  static  unsigned long long aesl_llvm_cbe_366_count = 0;
  static  unsigned long long aesl_llvm_cbe_367_count = 0;
  static  unsigned long long aesl_llvm_cbe_368_count = 0;
  static  unsigned long long aesl_llvm_cbe_369_count = 0;
  static  unsigned long long aesl_llvm_cbe_370_count = 0;
  unsigned int llvm_cbe_tmp__116;
  static  unsigned long long aesl_llvm_cbe_371_count = 0;
  static  unsigned long long aesl_llvm_cbe_372_count = 0;
  static  unsigned long long aesl_llvm_cbe_373_count = 0;
  static  unsigned long long aesl_llvm_cbe_374_count = 0;
  static  unsigned long long aesl_llvm_cbe_375_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond5_count = 0;
  static  unsigned long long aesl_llvm_cbe_376_count = 0;
  static  unsigned long long aesl_llvm_cbe_377_count = 0;
  double llvm_cbe_tmp__117;
  double llvm_cbe_tmp__117__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_378_count = 0;
  static  unsigned long long aesl_llvm_cbe_379_count = 0;
  unsigned int llvm_cbe_tmp__118;
  static  unsigned long long aesl_llvm_cbe_380_count = 0;
  static  unsigned long long aesl_llvm_cbe_381_count = 0;
  static  unsigned long long aesl_llvm_cbe_382_count = 0;
  static  unsigned long long aesl_llvm_cbe_383_count = 0;
  static  unsigned long long aesl_llvm_cbe_384_count = 0;
  static  unsigned long long aesl_llvm_cbe_385_count = 0;
  static  unsigned long long aesl_llvm_cbe_386_count = 0;
  static  unsigned long long aesl_llvm_cbe_387_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_388_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge12_2e_us;
  unsigned int llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_389_count = 0;
  unsigned long long llvm_cbe_tmp__119;
  static  unsigned long long aesl_llvm_cbe_390_count = 0;
  double *llvm_cbe_tmp__120;
  static  unsigned long long aesl_llvm_cbe_391_count = 0;
  double llvm_cbe_tmp__121;
  static  unsigned long long aesl_llvm_cbe_392_count = 0;
  double *llvm_cbe_tmp__122;
  static  unsigned long long aesl_llvm_cbe_393_count = 0;
  double llvm_cbe_tmp__123;
  static  unsigned long long aesl_llvm_cbe_394_count = 0;
  double llvm_cbe_tmp__124;
  static  unsigned long long aesl_llvm_cbe_395_count = 0;
  double *llvm_cbe_tmp__125;
  static  unsigned long long aesl_llvm_cbe_396_count = 0;
  double llvm_cbe_tmp__126;
  static  unsigned long long aesl_llvm_cbe_397_count = 0;
  double llvm_cbe_tmp__127;
  static  unsigned long long aesl_llvm_cbe_398_count = 0;
  double llvm_cbe_tmp__128;
  static  unsigned long long aesl_llvm_cbe_399_count = 0;
  static  unsigned long long aesl_llvm_cbe_400_count = 0;
  static  unsigned long long aesl_llvm_cbe_401_count = 0;
  static  unsigned long long aesl_llvm_cbe_402_count = 0;
  static  unsigned long long aesl_llvm_cbe_403_count = 0;
  unsigned int llvm_cbe_tmp__129;
  static  unsigned long long aesl_llvm_cbe_404_count = 0;
  static  unsigned long long aesl_llvm_cbe_405_count = 0;
  static  unsigned long long aesl_llvm_cbe_406_count = 0;
  unsigned int llvm_cbe_tmp__130;
  static  unsigned long long aesl_llvm_cbe_407_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__2e_us_count = 0;
  double llvm_cbe__2e__2e_us;
  static  unsigned long long aesl_llvm_cbe_408_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_2e_us_count = 0;
  unsigned int llvm_cbe_storemerge3_2e_us;
  unsigned int llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_409_count = 0;
  static  unsigned long long aesl_llvm_cbe_410_count = 0;
  static  unsigned long long aesl_llvm_cbe_411_count = 0;
  static  unsigned long long aesl_llvm_cbe_412_count = 0;
  static  unsigned long long aesl_llvm_cbe_413_count = 0;
  static  unsigned long long aesl_llvm_cbe_414_count = 0;
  static  unsigned long long aesl_llvm_cbe_415_count = 0;
  static  unsigned long long aesl_llvm_cbe_416_count = 0;
  unsigned long long llvm_cbe_tmp__131;
  static  unsigned long long aesl_llvm_cbe_417_count = 0;
  static  unsigned long long aesl_llvm_cbe_418_count = 0;
  static  unsigned long long aesl_llvm_cbe_419_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @minmax_normalize\n");
  if ((((signed int )llvm_cbe_num_points) > ((signed int )0u))) {
    goto llvm_cbe__2e_preheader_2e_lr_2e_ph;
  } else {
    goto llvm_cbe_tmp__132;
  }

llvm_cbe__2e_preheader_2e_lr_2e_ph:
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  } else {
    goto llvm_cbe__2e__crit_edge4;
  }

  do {     /* Syntactic loop '.lr.ph.us' to make GCC happy */
llvm_cbe__2e_lr_2e_ph_2e_us:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3.us = phi i32 [ %%4, %%3 ], [ 0, %%.preheader.lr.ph  for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_storemerge3_2e_us_count);
  llvm_cbe_storemerge3_2e_us = (unsigned int )llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3.us = 0x%X",llvm_cbe_storemerge3_2e_us);
printf("\n = 0x%X",llvm_cbe_tmp__116);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = sext i32 %%storemerge3.us to i64, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_416_count);
  llvm_cbe_tmp__131 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__131);
  llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__133;

llvm_cbe_tmp__134:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%storemerge3.us, 1, !dbg !14 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_370_count);
  llvm_cbe_tmp__116 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__116&4294967295ull)));
  if (((llvm_cbe_tmp__116&4294967295U) == (llvm_cbe_num_points&4294967295U))) {
    goto llvm_cbe__2e__crit_edge4;
  } else {
    llvm_cbe_storemerge3_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__116;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph_2e_us;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__133:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12.us = phi i32 [ 0, %%.lr.ph.us ], [ %%7, %%5  for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_storemerge12_2e_us_count);
  llvm_cbe_storemerge12_2e_us = (unsigned int )llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12.us = 0x%X",llvm_cbe_storemerge12_2e_us);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__118);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sext i32 %%storemerge12.us to i64, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_389_count);
  llvm_cbe_tmp__119 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12_2e_us);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__119);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds %%struct.Point* %%points, i64 %%24, i32 0, i64 %%9, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_390_count);
  llvm_cbe_tmp__120 = (double *)(&llvm_cbe_points[(((signed long long )llvm_cbe_tmp__131))].field0[(((signed long long )llvm_cbe_tmp__119))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__131));
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__119));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load double* %%10, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_391_count);
  llvm_cbe_tmp__121 = (double )*llvm_cbe_tmp__120;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__121, *(long long*)(&llvm_cbe_tmp__121));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds double* %%min, i64 %%9, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_392_count);
  llvm_cbe_tmp__122 = (double *)(&llvm_cbe_min[(((signed long long )llvm_cbe_tmp__119))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__119));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load double* %%12, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_393_count);
  llvm_cbe_tmp__123 = (double )*llvm_cbe_tmp__122;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__123, *(long long*)(&llvm_cbe_tmp__123));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fsub double %%11, %%13, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_394_count);
  llvm_cbe_tmp__124 = (double )llvm_cbe_tmp__121 - llvm_cbe_tmp__123;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__124, *(long long*)(&llvm_cbe_tmp__124));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds double* %%max, i64 %%9, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_395_count);
  llvm_cbe_tmp__125 = (double *)(&llvm_cbe_max[(((signed long long )llvm_cbe_tmp__119))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__119));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load double* %%15, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_396_count);
  llvm_cbe_tmp__126 = (double )*llvm_cbe_tmp__125;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__126, *(long long*)(&llvm_cbe_tmp__126));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fsub double %%16, %%13, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_397_count);
  llvm_cbe_tmp__127 = (double )llvm_cbe_tmp__126 - llvm_cbe_tmp__123;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__127, *(long long*)(&llvm_cbe_tmp__127));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fdiv double %%14, %%17, !dbg !12 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_398_count);
  llvm_cbe_tmp__128 = (double )llvm_cbe_tmp__124 / llvm_cbe_tmp__127;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__128, *(long long*)(&llvm_cbe_tmp__128));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = tail call i32 (...)* @__isnan(double %%18) nounwind, !dbg !14 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_403_count);
  llvm_cbe_tmp__129 = (unsigned int ) /*tail*/ __isnan(llvm_cbe_tmp__128);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__128, *(long long*)(&llvm_cbe_tmp__128));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__129);
}
  if (((llvm_cbe_tmp__129&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__135;
  } else {
    llvm_cbe_tmp__117__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe_tmp__136;
  }

llvm_cbe_tmp__136:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi double [ 0.000000e+00, %%8 ], [ %%..us, %%21  for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_377_count);
  llvm_cbe_tmp__117 = (double )llvm_cbe_tmp__117__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__117);
printf("\n = %lf",0x0p0);
printf("\n..us = %lf",llvm_cbe__2e__2e_us);
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%6, double* %%10, align 8, !dbg !13 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_378_count);
  *llvm_cbe_tmp__120 = llvm_cbe_tmp__117;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__117);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = add nsw i32 %%storemerge12.us, 1, !dbg !14 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_379_count);
  llvm_cbe_tmp__118 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12_2e_us&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__118&4294967295ull)));
  if (((llvm_cbe_tmp__118&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe_tmp__134;
  } else {
    llvm_cbe_storemerge12_2e_us__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__118;   /* for PHI node */
    goto llvm_cbe_tmp__133;
  }

llvm_cbe_tmp__135:
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = tail call i32 @__isinf(double %%18) nounwind readnone, !dbg !14 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe_406_count);
  llvm_cbe_tmp__130 = (unsigned int ) /*tail*/ __isinf(llvm_cbe_tmp__128);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__128, *(long long*)(&llvm_cbe_tmp__128));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__130);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%..us = select i1 %%23, double %%18, double 1.000000e+00, !dbg !14 for 0x%llxth hint within @minmax_normalize  --> \n", ++aesl_llvm_cbe__2e__2e_us_count);
  llvm_cbe__2e__2e_us = (double )((((llvm_cbe_tmp__130&4294967295U) == (0u&4294967295U))) ? ((double )llvm_cbe_tmp__128) : ((double )0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n..us = %lf,  0x%llx\n", llvm_cbe__2e__2e_us, *(long long*)(&llvm_cbe__2e__2e_us));
  llvm_cbe_tmp__117__PHI_TEMPORARY = (double )llvm_cbe__2e__2e_us;   /* for PHI node */
  goto llvm_cbe_tmp__136;

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.lr.ph.us' */
llvm_cbe__2e__crit_edge4:
  goto llvm_cbe_tmp__132;

llvm_cbe_tmp__132:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @minmax_normalize}\n");
  return;
}


void minmax_normalize_point(double *llvm_cbe_min, double *llvm_cbe_max, l_struct_OC_Point *llvm_cbe_point, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_420_count = 0;
  static  unsigned long long aesl_llvm_cbe_421_count = 0;
  static  unsigned long long aesl_llvm_cbe_422_count = 0;
  static  unsigned long long aesl_llvm_cbe_423_count = 0;
  static  unsigned long long aesl_llvm_cbe_424_count = 0;
  static  unsigned long long aesl_llvm_cbe_425_count = 0;
  static  unsigned long long aesl_llvm_cbe_426_count = 0;
  static  unsigned long long aesl_llvm_cbe_427_count = 0;
  static  unsigned long long aesl_llvm_cbe_428_count = 0;
  static  unsigned long long aesl_llvm_cbe_429_count = 0;
  static  unsigned long long aesl_llvm_cbe_430_count = 0;
  static  unsigned long long aesl_llvm_cbe_431_count = 0;
  static  unsigned long long aesl_llvm_cbe_432_count = 0;
  static  unsigned long long aesl_llvm_cbe_433_count = 0;
  static  unsigned long long aesl_llvm_cbe_434_count = 0;
  static  unsigned long long aesl_llvm_cbe_435_count = 0;
  static  unsigned long long aesl_llvm_cbe_436_count = 0;
  static  unsigned long long aesl_llvm_cbe_437_count = 0;
  static  unsigned long long aesl_llvm_cbe_438_count = 0;
  static  unsigned long long aesl_llvm_cbe_439_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_440_count = 0;
  unsigned long long llvm_cbe_tmp__137;
  static  unsigned long long aesl_llvm_cbe_441_count = 0;
  double *llvm_cbe_tmp__138;
  static  unsigned long long aesl_llvm_cbe_442_count = 0;
  double llvm_cbe_tmp__139;
  static  unsigned long long aesl_llvm_cbe_443_count = 0;
  double *llvm_cbe_tmp__140;
  static  unsigned long long aesl_llvm_cbe_444_count = 0;
  double llvm_cbe_tmp__141;
  static  unsigned long long aesl_llvm_cbe_445_count = 0;
  double llvm_cbe_tmp__142;
  static  unsigned long long aesl_llvm_cbe_446_count = 0;
  double *llvm_cbe_tmp__143;
  static  unsigned long long aesl_llvm_cbe_447_count = 0;
  double llvm_cbe_tmp__144;
  static  unsigned long long aesl_llvm_cbe_448_count = 0;
  double llvm_cbe_tmp__145;
  static  unsigned long long aesl_llvm_cbe_449_count = 0;
  double llvm_cbe_tmp__146;
  static  unsigned long long aesl_llvm_cbe_450_count = 0;
  static  unsigned long long aesl_llvm_cbe_451_count = 0;
  static  unsigned long long aesl_llvm_cbe_452_count = 0;
  static  unsigned long long aesl_llvm_cbe_453_count = 0;
  static  unsigned long long aesl_llvm_cbe_454_count = 0;
  unsigned int llvm_cbe_tmp__147;
  static  unsigned long long aesl_llvm_cbe_455_count = 0;
  static  unsigned long long aesl_llvm_cbe_456_count = 0;
  static  unsigned long long aesl_llvm_cbe_457_count = 0;
  unsigned int llvm_cbe_tmp__148;
  static  unsigned long long aesl_llvm_cbe_458_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  double llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_459_count = 0;
  static  unsigned long long aesl_llvm_cbe_460_count = 0;
  double llvm_cbe_tmp__149;
  double llvm_cbe_tmp__149__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_461_count = 0;
  static  unsigned long long aesl_llvm_cbe_462_count = 0;
  unsigned int llvm_cbe_tmp__150;
  static  unsigned long long aesl_llvm_cbe_463_count = 0;
  static  unsigned long long aesl_llvm_cbe_464_count = 0;
  static  unsigned long long aesl_llvm_cbe_465_count = 0;
  static  unsigned long long aesl_llvm_cbe_466_count = 0;
  static  unsigned long long aesl_llvm_cbe_467_count = 0;
  static  unsigned long long aesl_llvm_cbe_468_count = 0;
  static  unsigned long long aesl_llvm_cbe_469_count = 0;
  static  unsigned long long aesl_llvm_cbe_470_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_471_count = 0;
  static  unsigned long long aesl_llvm_cbe_472_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @minmax_normalize_point\n");
  if ((((signed int )llvm_cbe_num_features) > ((signed int )0u))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ %%19, %%17 ], [ 0, %%0  for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",llvm_cbe_tmp__150);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sext i32 %%storemerge1 to i64, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_440_count);
  llvm_cbe_tmp__137 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__137);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds %%struct.Point* %%point, i64 0, i32 0, i64 %%2, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_441_count);
  llvm_cbe_tmp__138 = (double *)(&llvm_cbe_point->field0[(((signed long long )llvm_cbe_tmp__137))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__137));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load double* %%3, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_442_count);
  llvm_cbe_tmp__139 = (double )*llvm_cbe_tmp__138;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__139, *(long long*)(&llvm_cbe_tmp__139));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds double* %%min, i64 %%2, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_443_count);
  llvm_cbe_tmp__140 = (double *)(&llvm_cbe_min[(((signed long long )llvm_cbe_tmp__137))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__137));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = load double* %%5, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_444_count);
  llvm_cbe_tmp__141 = (double )*llvm_cbe_tmp__140;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__141, *(long long*)(&llvm_cbe_tmp__141));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = fsub double %%4, %%6, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_445_count);
  llvm_cbe_tmp__142 = (double )llvm_cbe_tmp__139 - llvm_cbe_tmp__141;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__142, *(long long*)(&llvm_cbe_tmp__142));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds double* %%max, i64 %%2, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_446_count);
  llvm_cbe_tmp__143 = (double *)(&llvm_cbe_max[(((signed long long )llvm_cbe_tmp__137))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%llX",((signed long long )llvm_cbe_tmp__137));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_447_count);
  llvm_cbe_tmp__144 = (double )*llvm_cbe_tmp__143;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__144, *(long long*)(&llvm_cbe_tmp__144));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = fsub double %%9, %%6, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_448_count);
  llvm_cbe_tmp__145 = (double )llvm_cbe_tmp__144 - llvm_cbe_tmp__141;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__145, *(long long*)(&llvm_cbe_tmp__145));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fdiv double %%7, %%10, !dbg !12 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_449_count);
  llvm_cbe_tmp__146 = (double )llvm_cbe_tmp__142 / llvm_cbe_tmp__145;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__146, *(long long*)(&llvm_cbe_tmp__146));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = tail call i32 (...)* @__isnan(double %%11) nounwind, !dbg !13 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_454_count);
  llvm_cbe_tmp__147 = (unsigned int ) /*tail*/ __isnan(llvm_cbe_tmp__146);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__146, *(long long*)(&llvm_cbe_tmp__146));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__147);
}
  if (((llvm_cbe_tmp__147&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__151;
  } else {
    llvm_cbe_tmp__149__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe_tmp__152;
  }

llvm_cbe_tmp__152:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = phi double [ 0.000000e+00, %%.lr.ph ], [ %%., %%14  for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_460_count);
  llvm_cbe_tmp__149 = (double )llvm_cbe_tmp__149__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__149);
printf("\n = %lf",0x0p0);
printf("\n. = %lf",llvm_cbe__2e_);
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%18, double* %%3, align 8, !dbg !13 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_461_count);
  *llvm_cbe_tmp__138 = llvm_cbe_tmp__149;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__149);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = add nsw i32 %%storemerge1, 1, !dbg !13 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_462_count);
  llvm_cbe_tmp__150 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__150&4294967295ull)));
  if (((llvm_cbe_tmp__150&4294967295U) == (llvm_cbe_num_features&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__150;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe_tmp__151:
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call i32 @__isinf(double %%11) nounwind readnone, !dbg !14 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe_457_count);
  llvm_cbe_tmp__148 = (unsigned int ) /*tail*/ __isinf(llvm_cbe_tmp__146);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__146, *(long long*)(&llvm_cbe_tmp__146));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__148);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%16, double %%11, double 1.000000e+00, !dbg !14 for 0x%llxth hint within @minmax_normalize_point  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (double )((((llvm_cbe_tmp__148&4294967295U) == (0u&4294967295U))) ? ((double )llvm_cbe_tmp__146) : ((double )0x1p0));
if (AESL_DEBUG_TRACE)
printf("\n. = %lf,  0x%llx\n", llvm_cbe__2e_, *(long long*)(&llvm_cbe__2e_));
  llvm_cbe_tmp__149__PHI_TEMPORARY = (double )llvm_cbe__2e_;   /* for PHI node */
  goto llvm_cbe_tmp__152;

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @minmax_normalize_point}\n");
  return;
}


static double aesl_internal_get_rand_feature_value(void) {
  static  unsigned long long aesl_llvm_cbe_473_count = 0;
  double llvm_cbe_tmp__153;
  static  unsigned long long aesl_llvm_cbe_474_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_get_rand_feature_value\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call fastcc double @aesl_internal_rand_double(), !dbg !12 for 0x%llxth hint within @aesl_internal_get_rand_feature_value  --> \n", ++aesl_llvm_cbe_473_count);
  llvm_cbe_tmp__153 = (double ) /*tail*/ aesl_internal_rand_double();
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = %lf",llvm_cbe_tmp__153);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @aesl_internal_get_rand_feature_value}\n");
  return llvm_cbe_tmp__153;
}


static double aesl_internal_rand_double(void) {
  static  unsigned long long aesl_llvm_cbe_475_count = 0;
  static  unsigned long long aesl_llvm_cbe_476_count = 0;
  static  unsigned long long aesl_llvm_cbe_477_count = 0;
  static  unsigned long long aesl_llvm_cbe_478_count = 0;
  static  unsigned long long aesl_llvm_cbe_479_count = 0;
  static  unsigned long long aesl_llvm_cbe_480_count = 0;
  unsigned int llvm_cbe_tmp__154;
  static  unsigned long long aesl_llvm_cbe_481_count = 0;
  double llvm_cbe_tmp__155;
  static  unsigned long long aesl_llvm_cbe_482_count = 0;
  double llvm_cbe_tmp__156;
  static  unsigned long long aesl_llvm_cbe_483_count = 0;
  double llvm_cbe_tmp__157;
  static  unsigned long long aesl_llvm_cbe_484_count = 0;
  static  unsigned long long aesl_llvm_cbe_485_count = 0;
  static  unsigned long long aesl_llvm_cbe_486_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @aesl_internal_rand_double\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call i32 @rand() nounwind, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_double  --> \n", ++aesl_llvm_cbe_480_count);
  llvm_cbe_tmp__154 = (unsigned int ) /*tail*/ rand();
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__154);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sitofp i32 %%1 to double, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_double  --> \n", ++aesl_llvm_cbe_481_count);
  llvm_cbe_tmp__155 = (double )((double )(signed int )llvm_cbe_tmp__154);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__155, *(long long*)(&llvm_cbe_tmp__155));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = fdiv double %%2, 0x41D0000000200000, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_double  --> \n", ++aesl_llvm_cbe_482_count);
  llvm_cbe_tmp__156 = (double )llvm_cbe_tmp__155 / 0x1.00000002p30;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__156, *(long long*)(&llvm_cbe_tmp__156));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = fadd double %%3, 0.000000e+00, !dbg !12 for 0x%llxth hint within @aesl_internal_rand_double  --> \n", ++aesl_llvm_cbe_483_count);
  llvm_cbe_tmp__157 = (double )llvm_cbe_tmp__156 + 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__157, *(long long*)(&llvm_cbe_tmp__157));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @aesl_internal_rand_double}\n");
  return llvm_cbe_tmp__157;
}

