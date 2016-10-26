/* FEATURE  */
typedef struct {
  char* name;
  char* description;
} feature;


//*******************************************

#define FEATURES_COUNT 32
#define EDX 0
#define ECX 1

//*******************************************

#define HIGH_BRAND_STR_PARAM 0x80000002
#define MID_BRAND_STR_PARAM 0x80000003
#define LOW_BRAND_STR_PARAM 0x80000004


extern int _vendor_id();
extern int _model();
extern int _edx_features();
extern int _ecx_features();
extern int _brand_string(int code);
void cpuid();
void get_features(feature* f, int features, int from);
