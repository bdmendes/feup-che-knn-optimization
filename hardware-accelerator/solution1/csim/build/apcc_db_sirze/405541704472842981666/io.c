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
typedef struct l_struct_OC__IO_FILE l_struct_OC__IO_FILE;

/* Structure contents */
struct l_struct_OC_Point {
  double field0[43];
  unsigned char field1;
};

struct l_struct_OC__IO_FILE {
  unsigned int field0;
   char *field1;
   char *field2;
   char *field3;
   char *field4;
   char *field5;
   char *field6;
   char *field7;
   char *field8;
   char *field9;
   char *field10;
   char *field11;
  l_struct_OC_Point *field12;
  l_struct_OC__IO_FILE *field13;
  unsigned int field14;
  unsigned int field15;
  unsigned long long field16;
  unsigned short field17;
  unsigned char field18;
   char field19[1];
   char *field20;
  unsigned long long field21;
  l_struct_OC_Point *field22;
  l_struct_OC_Point *field23;
  l_struct_OC__IO_FILE *field24;
   char *field25;
  unsigned long long field26;
  unsigned int field27;
   char field28[20];
};


/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void read_data(signed int llvm_cbe_argc,  char **llvm_cbe_argv, signed int *llvm_cbe_num_points, signed int *llvm_cbe_num_classes, signed int *llvm_cbe_num_new_points, signed int *llvm_cbe_k, l_struct_OC_Point **llvm_cbe_known_points, l_struct_OC_Point **llvm_cbe_new_points,  char **llvm_cbe_key, signed int llvm_cbe_num_features);
void generate_random_data(signed int llvm_cbe_argc,  char **llvm_cbe_argv, signed int *llvm_cbe_num_points, signed int *llvm_cbe_num_classes, signed int *llvm_cbe_num_new_points, signed int *llvm_cbe_k, l_struct_OC_Point **llvm_cbe_known_points, l_struct_OC_Point **llvm_cbe_new_points,  char **llvm_cbe_key, signed int llvm_cbe_num_features);
void initialize_known_points(signed int , l_struct_OC_Point *, signed int , signed int );
void initialize_new_points(signed int , l_struct_OC_Point *, signed int );


/* Global Variable Definitions and Initialization */
static  char aesl_internal__OC_str17[3] = "d3";
static  char aesl_internal__OC_str18[41] = "Could not recognize dataset version %s.\n";
static  char aesl_internal__OC_str19[25] = "Generating data for %s.\n";
static  char aesl_internal__OC_str3[2] = "r";
static  char aesl_internal__OC_str4[25] = "Could not open file %s.\n";
static  char aesl_internal__OC_str5[41] = "Could not read num_points data from %s.\n";
static  char aesl_internal__OC_str15[3] = "d1";
static  char aesl_internal__OC_str16[3] = "d2";
static  char aesl_internal__OC_str6[42] = "Could not read num_classes data from %s.\n";
static  char aesl_internal__OC_str7[45] = "Could not read num_new_points data from %s.\n";
static  char aesl_internal__OC_str8[32] = "Could not read k data from %s.\n";
static  char aesl_internal__OC_str9[43] = "Could not read known_points data from %s.\n";
static  char aesl_internal_str[48] = "Need exactly 1 argument, the input file. Usage:";
static  char aesl_internal_str1[60] = "Need exactly 1 argument, the dataset random version. Usage:";
static  char aesl_internal__OC_str12[69] = "%d-NN, %d classes, %d instances, %d features, %d points to classify\n";
static  char aesl_internal__OC_str14[20] = "\t%s <d1 | d2 | d3>\n";
static  char aesl_internal__OC_str2[23] = "Reading data from %s.\n";
static  char aesl_internal__OC_str10[41] = "Could not read new_points data from %s.\n";
static  char aesl_internal__OC_str11[34] = "Could not read key data from %s.\n";
static  char aesl_internal__OC_str1[18] = "\t%s <input_file>\n";


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

void read_data(signed int llvm_cbe_argc,  char **llvm_cbe_argv, signed int *llvm_cbe_num_points, signed int *llvm_cbe_num_classes, signed int *llvm_cbe_num_new_points, signed int *llvm_cbe_k, l_struct_OC_Point **llvm_cbe_known_points, l_struct_OC_Point **llvm_cbe_new_points,  char **llvm_cbe_key, signed int llvm_cbe_num_features) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts_count = 0;
  unsigned int llvm_cbe_puts;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
   char **llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
   char *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  l_struct_OC__IO_FILE *llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
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
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
   char *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  unsigned long long llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
   char *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned long long llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
   char *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  unsigned long long llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
   char *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned long long llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  unsigned long long llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  unsigned long long llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
   char *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  l_struct_OC_Point *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned long long llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned long long llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  unsigned int llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  unsigned long long llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  unsigned long long llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  unsigned long long llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
   char *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  l_struct_OC_Point *llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  unsigned long long llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  unsigned long long llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned long long llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
   char *llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned long long llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  unsigned long long llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  unsigned int llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @read_data\n");
  if (((llvm_cbe_argc&4294967295U) == (2u&4294967295U))) {
    goto llvm_cbe_tmp__54;
  } else {
    goto llvm_cbe_tmp__55;
  }

llvm_cbe_tmp__55:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts = tail call i32 @puts(i8* getelementptr inbounds ([48 x i8]* @aesl_internal_str, i64 0, i64 0)), !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_puts_count);
   /*tail*/ puts(( char *)((&aesl_internal_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 48
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts = 0x%X",llvm_cbe_puts);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i8** %%argv, align 8, !dbg !10 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__1 = ( char *)*llvm_cbe_argv;
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([18 x i8]* @aesl_internal_.str1, i64 0, i64 0), i8* %%3) nounwind, !dbg !10 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_41_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 18
#endif
])), ( char *)llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_42_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__54:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds i8** %%argv, i64 1, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__3 = ( char **)(&llvm_cbe_argv[(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load i8** %%6, align 8, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_45_count);
  llvm_cbe_tmp__4 = ( char *)*llvm_cbe_tmp__3;
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @aesl_internal_.str2, i64 0, i64 0), i8* %%7) nounwind, !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_57_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 23
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__5);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = tail call %%struct._IO_FILE* @fopen(i8* %%7, i8* getelementptr inbounds ([2 x i8]* @aesl_internal_.str3, i64 0, i64 0)) nounwind, !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__6 = (l_struct_OC__IO_FILE *) /*tail*/ aesl_fopen(( char *)llvm_cbe_tmp__4, ( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 2
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__6);
}
  if (((llvm_cbe_tmp__6) == (((l_struct_OC__IO_FILE *)/*NULL*/0)))) {
    goto llvm_cbe_tmp__56;
  } else {
    goto llvm_cbe_tmp__57;
  }

llvm_cbe_tmp__56:
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @aesl_internal_.str4, i64 0, i64 0), i8* %%7) nounwind, !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_71_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 25
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__7);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !16 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_72_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__57:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = bitcast i32* %%num_points to i8*, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__8 = ( char *)(( char *)llvm_cbe_num_points);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call i64 @fread(i8* %%14, i64 4, i64 1, %%struct._IO_FILE* %%9) nounwind, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__9 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__8, 4ull, 1ull, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",4ull);
printf("\nArgument  = 0x%llX",1ull);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__9);
}
  if (((llvm_cbe_tmp__9&18446744073709551615ULL) == (1ull&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__58;
  } else {
    goto llvm_cbe_tmp__59;
  }

llvm_cbe_tmp__59:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([41 x i8]* @aesl_internal_.str5, i64 0, i64 0), i8* %%7) nounwind, !dbg !14 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_80_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str5[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 41
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__10);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !16 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_81_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__58:
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = bitcast i32* %%num_classes to i8*, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__11 = ( char *)(( char *)llvm_cbe_num_classes);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = tail call i64 @fread(i8* %%20, i64 4, i64 1, %%struct._IO_FILE* %%9) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__12 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__11, 4ull, 1ull, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",4ull);
printf("\nArgument  = 0x%llX",1ull);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__12);
}
  if (((llvm_cbe_tmp__12&18446744073709551615ULL) == (1ull&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__60;
  } else {
    goto llvm_cbe_tmp__61;
  }

llvm_cbe_tmp__61:
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @aesl_internal_.str6, i64 0, i64 0), i8* %%7) nounwind, !dbg !15 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_89_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str6[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 42
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__13);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_90_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__60:
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = bitcast i32* %%num_new_points to i8*, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__14 = ( char *)(( char *)llvm_cbe_num_new_points);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = tail call i64 @fread(i8* %%26, i64 4, i64 1, %%struct._IO_FILE* %%9) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_93_count);
  llvm_cbe_tmp__15 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__14, 4ull, 1ull, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",4ull);
printf("\nArgument  = 0x%llX",1ull);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__15);
}
  if (((llvm_cbe_tmp__15&18446744073709551615ULL) == (1ull&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__62;
  } else {
    goto llvm_cbe_tmp__63;
  }

llvm_cbe_tmp__63:
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([45 x i8]* @aesl_internal_.str7, i64 0, i64 0), i8* %%7) nounwind, !dbg !15 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_98_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str7[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 45
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__16);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_99_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__62:
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = bitcast i32* %%k to i8*, !dbg !13 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__17 = ( char *)(( char *)llvm_cbe_k);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = tail call i64 @fread(i8* %%32, i64 4, i64 1, %%struct._IO_FILE* %%9) nounwind, !dbg !13 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__18 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__17, 4ull, 1ull, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",4ull);
printf("\nArgument  = 0x%llX",1ull);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__18);
}
  if (((llvm_cbe_tmp__18&18446744073709551615ULL) == (1ull&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__64;
  } else {
    goto llvm_cbe_tmp__65;
  }

llvm_cbe_tmp__65:
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @aesl_internal_.str8, i64 0, i64 0), i8* %%7) nounwind, !dbg !15 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_107_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str8[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 32
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__19);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_108_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__64:
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__20 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = sext i32 %%38 to i64, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__21 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = mul i64 %%39, 352, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__22 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__21&18446744073709551615ull)) * ((unsigned long long )(352ull&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__22&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = tail call noalias i8* @malloc(i64 %%40) nounwind, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__23 = ( char *) /*tail*/ ( char *)malloc(llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__22);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__23);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = bitcast i8* %%41 to %%struct.Point*, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__24 = (l_struct_OC_Point *)((l_struct_OC_Point *)llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  store %%struct.Point* %%42, %%struct.Point** %%known_points, align 8, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_115_count);
  *llvm_cbe_known_points = (l_struct_OC_Point *)llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = load i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__25 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = sext i32 %%43 to i64, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__26 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = tail call i64 @fread(i8* %%41, i64 352, i64 %%44, %%struct._IO_FILE* %%9) nounwind, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__27 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__23, 352ull, llvm_cbe_tmp__26, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",352ull);
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__26);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__27);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = load i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__28 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = sext i32 %%46 to i64, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_122_count);
  llvm_cbe_tmp__29 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__29);
  if (((llvm_cbe_tmp__27&18446744073709551615ULL) == (llvm_cbe_tmp__29&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__66;
  } else {
    goto llvm_cbe_tmp__67;
  }

llvm_cbe_tmp__67:
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([43 x i8]* @aesl_internal_.str9, i64 0, i64 0), i8* %%7) nounwind, !dbg !15 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_125_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str9[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 43
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__30);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_126_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__66:
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__31 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = sext i32 %%52 to i64, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__32 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = mul i64 %%53, 352, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_130_count);
  llvm_cbe_tmp__33 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__32&18446744073709551615ull)) * ((unsigned long long )(352ull&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__33&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = tail call noalias i8* @malloc(i64 %%54) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__34 = ( char *) /*tail*/ ( char *)malloc(llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__33);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__34);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = bitcast i8* %%55 to %%struct.Point*, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__35 = (l_struct_OC_Point *)((l_struct_OC_Point *)llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  store %%struct.Point* %%56, %%struct.Point** %%new_points, align 8, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_133_count);
  *llvm_cbe_new_points = (l_struct_OC_Point *)llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__36 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = sext i32 %%57 to i64, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__37 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = tail call i64 @fread(i8* %%55, i64 352, i64 %%58, %%struct._IO_FILE* %%9) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__38 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__34, 352ull, llvm_cbe_tmp__37, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",352ull);
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__37);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__38);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__39 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = sext i32 %%60 to i64, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__40 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__40);
  if (((llvm_cbe_tmp__38&18446744073709551615ULL) == (llvm_cbe_tmp__40&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__68;
  } else {
    goto llvm_cbe_tmp__69;
  }

llvm_cbe_tmp__69:
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([41 x i8]* @aesl_internal_.str10, i64 0, i64 0), i8* %%7) nounwind, !dbg !15 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_143_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str10[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 41
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_144_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__68:
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = tail call noalias i8* @malloc(i64 %%59) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_146_count);
  llvm_cbe_tmp__42 = ( char *) /*tail*/ ( char *)malloc(llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__38);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__42);
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8* %%66, i8** %%key, align 8, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_147_count);
  *llvm_cbe_key = ( char *)llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__43 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = sext i32 %%67 to i64, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__44 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = tail call i64 @fread(i8* %%66, i64 1, i64 %%68, %%struct._IO_FILE* %%9) nounwind, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__45 = (unsigned long long ) /*tail*/ fread(( char *)llvm_cbe_tmp__42, 1ull, llvm_cbe_tmp__44, (l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",1ull);
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__44);
printf("\nReturn  = 0x%llX",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_153_count);
  llvm_cbe_tmp__46 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = sext i32 %%70 to i64, !dbg !12 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_154_count);
  llvm_cbe_tmp__47 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__47);
  if (((llvm_cbe_tmp__45&18446744073709551615ULL) == (llvm_cbe_tmp__47&18446744073709551615ULL))) {
    goto llvm_cbe_tmp__70;
  } else {
    goto llvm_cbe_tmp__71;
  }

llvm_cbe_tmp__71:
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([34 x i8]* @aesl_internal_.str11, i64 0, i64 0), i8* %%7) nounwind, !dbg !16 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_157_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str11[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 34
#endif
])), ( char *)llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !17 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_158_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__70:
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = load i32* %%k, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_160_count);
  llvm_cbe_tmp__49 = (unsigned int )*llvm_cbe_k;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = load i32* %%num_classes, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_161_count);
  llvm_cbe_tmp__50 = (unsigned int )*llvm_cbe_num_classes;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = load i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__51 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([69 x i8]* @aesl_internal_.str12, i64 0, i64 0), i32 %%76, i32 %%77, i32 %%78, i32 %%num_features, i32 %%70) nounwind, !dbg !11 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_163_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str12[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 69
#endif
])), llvm_cbe_tmp__49, llvm_cbe_tmp__50, llvm_cbe_tmp__51, llvm_cbe_num_features, llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__49);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__50);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__51);
printf("\nArgument num_features = 0x%X",llvm_cbe_num_features);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__46);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__52);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = tail call i32 @fclose(%%struct._IO_FILE* %%9) nounwind, !dbg !16 for 0x%llxth hint within @read_data  --> \n", ++aesl_llvm_cbe_164_count);
   /*tail*/ fclose((l_struct_OC__IO_FILE *)llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__53);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @read_data}\n");
  return;
}


void generate_random_data(signed int llvm_cbe_argc,  char **llvm_cbe_argv, signed int *llvm_cbe_num_points, signed int *llvm_cbe_num_classes, signed int *llvm_cbe_num_new_points, signed int *llvm_cbe_k, l_struct_OC_Point **llvm_cbe_known_points, l_struct_OC_Point **llvm_cbe_new_points,  char **llvm_cbe_key, signed int llvm_cbe_num_features) {
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
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_puts_count = 0;
  unsigned int llvm_cbe_puts;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
   char *llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
   char **llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
   char *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
   char *llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  unsigned int llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  unsigned int llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  unsigned int llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  unsigned int llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  unsigned int llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  unsigned long long llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  unsigned long long llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
   char *llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  l_struct_OC_Point *llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  unsigned int llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  unsigned int llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  unsigned int llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  unsigned long long llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  unsigned long long llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
   char *llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  l_struct_OC_Point *llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  unsigned int llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  unsigned int llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  unsigned int llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  unsigned int llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  unsigned int llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  unsigned int llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @generate_random_data\n");
  if (((llvm_cbe_argc&4294967295U) == (2u&4294967295U))) {
    goto llvm_cbe_tmp__100;
  } else {
    goto llvm_cbe_tmp__101;
  }

llvm_cbe_tmp__101:
if (AESL_DEBUG_TRACE)
printf("\n  %%puts = tail call i32 @puts(i8* getelementptr inbounds ([60 x i8]* @aesl_internal_str1, i64 0, i64 0)), !dbg !14 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_puts_count);
   /*tail*/ puts(( char *)((&aesl_internal_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 60
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn puts = 0x%X",llvm_cbe_puts);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i8** %%argv, align 8, !dbg !10 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_210_count);
  llvm_cbe_tmp__72 = ( char *)*llvm_cbe_argv;
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([20 x i8]* @aesl_internal_.str14, i64 0, i64 0), i8* %%3) nounwind, !dbg !10 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_211_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str14[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 20
#endif
])), ( char *)llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__73);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !14 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_212_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__100:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds i8** %%argv, i64 1, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_214_count);
  llvm_cbe_tmp__74 = ( char **)(&llvm_cbe_argv[(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load i8** %%6, align 8, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_215_count);
  llvm_cbe_tmp__75 = ( char *)*llvm_cbe_tmp__74;
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call noalias i8* @strdup(i8* %%7) nounwind, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_216_count);
  llvm_cbe_tmp__76 = ( char *) /*tail*/ ( char *)strdup(( char *)llvm_cbe_tmp__75);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__76);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = tail call i32 @strcmp(i8* %%8, i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str15, i64 0, i64 0)) nounwind readonly, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_224_count);
  llvm_cbe_tmp__77 = (unsigned int ) /*tail*/ strcmp(( char *)llvm_cbe_tmp__76, ( char *)((&aesl_internal__OC_str15[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__77);
}
  if (((llvm_cbe_tmp__77&4294967295U) == (0u&4294967295U))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )10000u;   /* for PHI node */
    goto llvm_cbe_tmp__102;
  } else {
    goto llvm_cbe_tmp__103;
  }

llvm_cbe_tmp__103:
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = tail call i32 @strcmp(i8* %%8, i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str16, i64 0, i64 0)) nounwind readonly, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_227_count);
  llvm_cbe_tmp__78 = (unsigned int ) /*tail*/ strcmp(( char *)llvm_cbe_tmp__76, ( char *)((&aesl_internal__OC_str16[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__78);
}
  if (((llvm_cbe_tmp__78&4294967295U) == (0u&4294967295U))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )250000u;   /* for PHI node */
    goto llvm_cbe_tmp__102;
  } else {
    goto llvm_cbe_tmp__104;
  }

llvm_cbe_tmp__104:
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call i32 @strcmp(i8* %%8, i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str17, i64 0, i64 0)) nounwind readonly, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_230_count);
  llvm_cbe_tmp__79 = (unsigned int ) /*tail*/ strcmp(( char *)llvm_cbe_tmp__76, ( char *)((&aesl_internal__OC_str17[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__79);
}
  if (((llvm_cbe_tmp__79&4294967295U) == (0u&4294967295U))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )1000000u;   /* for PHI node */
    goto llvm_cbe_tmp__102;
  } else {
    goto llvm_cbe_tmp__105;
  }

llvm_cbe_tmp__105:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([41 x i8]* @aesl_internal_.str18, i64 0, i64 0), i8* %%8) nounwind, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_233_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str18[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 41
#endif
])), ( char *)llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__80);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 1) noreturn nounwind, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_234_count);
   /*tail*/ exit(1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
}
  /*UNREACHABLE*/;
llvm_cbe_tmp__102:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 10000, %%5 ], [ 250000, %%11 ], [ 1000000, %%14  for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",10000u);
printf("\n = 0x%X",250000u);
printf("\n = 0x%X",1000000u);
}
if (AESL_DEBUG_TRACE)
printf("\n  store i32 15, i32* %%k, align 4, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_236_count);
  *llvm_cbe_k = 15u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 15u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 8, i32* %%num_classes, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_237_count);
  *llvm_cbe_num_classes = 8u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 8u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%storemerge1, i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_238_count);
  *llvm_cbe_num_points = llvm_cbe_storemerge1;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge1 = 0x%X\n", llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 100, i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_239_count);
  *llvm_cbe_num_new_points = 100u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 100u);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @aesl_internal_.str19, i64 0, i64 0), i8* %%8) nounwind, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_240_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str19[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 25
#endif
])), ( char *)llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__81);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @free(i8* %%8) nounwind, !dbg !15 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_241_count);
   /*tail*/ free(( char *)llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  store i8* null, i8** %%key, align 8, !dbg !14 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_242_count);
  *llvm_cbe_key = ( char *)(( char *)/*NULL*/0);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load i32* %%num_points, align 4, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_243_count);
  llvm_cbe_tmp__82 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = sext i32 %%21 to i64, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_244_count);
  llvm_cbe_tmp__83 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__83);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = mul i64 %%22, 352, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_245_count);
  llvm_cbe_tmp__84 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__83&18446744073709551615ull)) * ((unsigned long long )(352ull&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__84&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = tail call noalias i8* @malloc(i64 %%23) nounwind, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_246_count);
  llvm_cbe_tmp__85 = ( char *) /*tail*/ ( char *)malloc(llvm_cbe_tmp__84);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__84);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__85);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = bitcast i8* %%24 to %%struct.Point*, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_247_count);
  llvm_cbe_tmp__86 = (l_struct_OC_Point *)((l_struct_OC_Point *)llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n  store %%struct.Point* %%25, %%struct.Point** %%known_points, align 8, !dbg !11 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_248_count);
  *llvm_cbe_known_points = (l_struct_OC_Point *)llvm_cbe_tmp__86;
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load i32* %%num_points, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_249_count);
  llvm_cbe_tmp__87 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__87);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load i32* %%num_classes, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_250_count);
  llvm_cbe_tmp__88 = (unsigned int )*llvm_cbe_num_classes;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @initialize_known_points(i32 %%26, %%struct.Point* %%25, i32 %%27, i32 %%num_features) nounwind, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_251_count);
   /*tail*/ initialize_known_points(llvm_cbe_tmp__87, (l_struct_OC_Point *)llvm_cbe_tmp__86, llvm_cbe_tmp__88, llvm_cbe_num_features);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__87);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__88);
printf("\nArgument num_features = 0x%X",llvm_cbe_num_features);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i32* %%num_new_points, align 4, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_252_count);
  llvm_cbe_tmp__89 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = sext i32 %%28 to i64, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_253_count);
  llvm_cbe_tmp__90 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", llvm_cbe_tmp__90);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = mul i64 %%29, 352, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_254_count);
  llvm_cbe_tmp__91 = (unsigned long long )((unsigned long long )(llvm_cbe_tmp__90&18446744073709551615ull)) * ((unsigned long long )(352ull&18446744073709551615ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%llX\n", ((unsigned long long )(llvm_cbe_tmp__91&18446744073709551615ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = tail call noalias i8* @malloc(i64 %%30) nounwind, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_255_count);
  llvm_cbe_tmp__92 = ( char *) /*tail*/ ( char *)malloc(llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%llX",llvm_cbe_tmp__91);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__92);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = bitcast i8* %%31 to %%struct.Point*, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_256_count);
  llvm_cbe_tmp__93 = (l_struct_OC_Point *)((l_struct_OC_Point *)llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE)
printf("\n  store %%struct.Point* %%32, %%struct.Point** %%new_points, align 8, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_257_count);
  *llvm_cbe_new_points = (l_struct_OC_Point *)llvm_cbe_tmp__93;
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i32* %%num_new_points, align 4, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_258_count);
  llvm_cbe_tmp__94 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @initialize_new_points(i32 %%33, %%struct.Point* %%32, i32 %%num_features) nounwind, !dbg !13 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_259_count);
   /*tail*/ initialize_new_points(llvm_cbe_tmp__94, (l_struct_OC_Point *)llvm_cbe_tmp__93, llvm_cbe_num_features);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__94);
printf("\nArgument num_features = 0x%X",llvm_cbe_num_features);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load i32* %%k, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_260_count);
  llvm_cbe_tmp__95 = (unsigned int )*llvm_cbe_k;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__95);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load i32* %%num_classes, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_261_count);
  llvm_cbe_tmp__96 = (unsigned int )*llvm_cbe_num_classes;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__96);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = load i32* %%num_points, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_262_count);
  llvm_cbe_tmp__97 = (unsigned int )*llvm_cbe_num_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = load i32* %%num_new_points, align 4, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_263_count);
  llvm_cbe_tmp__98 = (unsigned int )*llvm_cbe_num_new_points;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__98);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([69 x i8]* @aesl_internal_.str12, i64 0, i64 0), i32 %%34, i32 %%35, i32 %%36, i32 %%num_features, i32 %%37) nounwind, !dbg !12 for 0x%llxth hint within @generate_random_data  --> \n", ++aesl_llvm_cbe_264_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str12[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 69
#endif
])), llvm_cbe_tmp__95, llvm_cbe_tmp__96, llvm_cbe_tmp__97, llvm_cbe_num_features, llvm_cbe_tmp__98);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__95);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__96);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__97);
printf("\nArgument num_features = 0x%X",llvm_cbe_num_features);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__98);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__99);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @generate_random_data}\n");
  return;
}

