#include "../include/defs.h"
#include "../include/cpu_info.h"



char* edx_features[FEATURES_COUNT]={"FPU","VME","DE","PSE","TSC","MSR","PAE","MCE","CX8","APIC","-","SEP","MTRR","PGE","MCA","CMOV","PAT","PSE36","PSN","CLFSH",
			"-","DS","ACPI","MMX","FXSR","SSE","SSE2","SS","HTT","TM","-","PBE"};

char* ecx_features[FEATURES_COUNT]={"SSE3","PCLMULDQ","DTES64","MONITR","DSCPL","VMX","SMX","EST","TM2","SSSE3","CNXTID","-","-","CX16","XTPR","PDCM","-","-","DCA","SSE4.1",
			"SSE4.2","X2APIC","MOVBE","POPCNT","-","AES","XSAVE","OXSAVE","-","-","-","-"};


char* edx_features_description[FEATURES_COUNT]={	"Floating-point unit on-chip",
							"Virtual mode extension",
							"Debugging Extension",
							"Page Size Extension",
							"Time Stamp Counter",
							"Model Specific Registers",
							"Physical Address Extension",
							"Machine-check Exception",
							"CMPXCHG8 Instruction",
							"On-chip APIC Hardware",
							"-",
							"Fast System Call",
							"Memory Type Range Registers",
							"Page Global Enable",
							"Machine-Check Architecture",
							"Conditional Move Instruction",
							"Page Attribute Table",
							"36-bit Page Size Extension",
							"Processor serial number is present and enabled",
							"CLFLUSH Instruction",
							"-",
							"Debug Store",
							"Thermal Monitor and Software Controlled Clock Facilities",
							"MMX technology",
							"FXSAVE and FXSTOR Instructions",
							"Streaming SIMD Extensions",
							"Streaming SIMD Extensions 2",
							"Self-Snoop",
							"Multi-Threading",
							"Thermal Monitor",
							"-",
							"Pending Break Enable"};


char* ecx_features_description[FEATURES_COUNT]={	"Streaming SIMD Extensions 3",
							"PCLMULDQ Instruction",
							"64-Bit Debug Store",
							"MONITOR/MWAIT",
							"CPL Qualified Debug Store",
							"Virtual Machine Extensions",
							"Safer Mode Extensions",
							"Enhanced Intel SpeedStep® Technology",
							"Thermal Monitor 2",
							"Supplemental Streaming SIMD Extensions 3",
							"L1 Context ID",
							"-",
							"-",
							"CMPXCHG16B",
							"xTPR Update Control",
							"Perfmon and Debug Capability",
							"-",
							"-",
							"Direct Cache Access",
							"Streaming SIMD Extensions 4.1",
							"Streaming SIMD Extensions 4.2",
							"Extended xAPIC Support",
							"MOVBE Instruction",
							"POPCNT Instruction",
							"-",
							"AES Instruction",
							"XSAVE/XSTOR States",
							"OS-Enabled Extended State Management",
							"-",
							"-",
							"-",
							"-"};



void cpuid(){
	char* str;
	char* high;
	char* mid;
	char* low;
	int model,features,i;
	feature f_edx[FEATURES_COUNT];	
	feature f_ecx[FEATURES_COUNT];

	str = (char*)_vendor_id();
	print_enter();
	print_enter();	

	printf("Manufacturer ID: %s",str);

	print_enter();
	print_enter();

	high = (char*)_brand_string(HIGH_BRAND_STR_PARAM);
	printf("BRAND: %s",high);
	mid = (char*)_brand_string(MID_BRAND_STR_PARAM);
	printf("%s",mid);	
	low = (char*)_brand_string(LOW_BRAND_STR_PARAM);
	printf("%s",low);

	print_enter();
	print_enter();

	features = (int)_edx_features();
	get_features(f_edx,features,EDX);
	
	
	for(i=0;i<FEATURES_COUNT;i++){
		if (f_edx[i].name != 0){
			printf("Feature(%d): %s",(i+1),f_edx[i].name);
			print_tab();
//			print_tab();			
//			printf("Description: %s",f_edx[i].description);
//			print_enter();
		}	
	}

	features = (int)_ecx_features();
	get_features(f_ecx,features,ECX);
	
	
	for(i=0;i<FEATURES_COUNT;i++){
		if (f_ecx[i].name != 0){
			printf("Feature(%d): %s",(i+1+32),f_ecx[i].name);
			print_tab();
//			print_tab();
//			printf("Description: %s",f_ecx[i].description);
//			print_enter();		
		}	
	}

	print_enter();
	print_enter();
	print_enter();
	print_enter();
}

void print_feature(int index){
	int ind = index-1;
	
	print_enter();	
	if(ind < 32){
		printf("Description: %s",edx_features_description[ind]);
	}
	else if(ind < 64){
		printf("Description: %s",ecx_features_description[ind-32]);
	}	
	print_enter();	

}

void get_features(feature* f, int features, int from){
	
	int i=0;
	int current_feature;
		
	current_feature = 0x00000001;

	if (from == EDX){	
		for(i=0;i<FEATURES_COUNT;i++){
			if (current_feature & features){
				f[i].name = edx_features[i];
				f[i].description = edx_features_description[i];	
			}
			else{
				f[i].name = 0;		
				f[i].description = 0;
			}
			current_feature = current_feature<<1;
		}
	}else if (from==ECX){
		for(i=0;i<FEATURES_COUNT;i++){
			if (current_feature & features){
				f[i].name = ecx_features[i];
				f[i].description = ecx_features_description[i];
			}
			else{
				f[i].name = 0;		
				f[i].description = 0;
			}
			current_feature = current_feature<<1;
		}
	}
		
}

