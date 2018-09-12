//#include <stdlib.h>
//#include <stdio.h>
#include "edid.h"

static int TotalBlocks = 0;

static CBIOS_Module_EDID_ESTTIMINGS EstTiming[] = {
//ProtocolIndex 0:VESA 1:Apple/Mac II 2:IBM/VGA 3:IBM/XGA2 4:IBM

    { 0x2D0, 0x190, 7000, 2},// EDID23h[7]: 720x400@70Hz
    { 0x2D0, 0x190, 8800, 3},// EDID23h[6]: 720x400@88Hz
    { 0x280, 0x1E0, 6000, 2},// EDID23h[5]: 640x480@60Hz
    { 0x280, 0x1E0, 6700, 1},// EDID23h[4]: 640x480@67Hz
    { 0x280, 0x1E0, 7200, 0},// EDID23h[3]: 640x480@72Hz
    { 0x280, 0x1E0, 7500, 0},// EDID23h[2]: 640x480@75Hz
    { 0x320, 0x258, 5600, 0},// EDID23h[1]: 800x600@56Hz
    { 0x320, 0x258, 6000, 0},// EDID23h[0]: 800x600@60Hz

    { 0x320, 0x258, 7200, 0},// EDID24h[7]: 800x600@72Hz
    { 0x320, 0x258, 7500, 0},// EDID24h[6]: 800x600@75Hz
    { 0x340, 0x270, 7500, 1},// EDID24h[5]: 832x624@75Hz
    { 0x400, 0x300, 8700, 4},// EDID24h[4]: 1024x768@87HzInterlace
    { 0x400, 0x300, 6000, 0},// EDID24h[3]: 1024x768@60Hz
    { 0x400, 0x300, 7000, 0},// EDID24h[2]: 1024x768@70Hz
    { 0x400, 0x300, 7500, 0},// EDID24h[1]: 1024x768@75Hz
    { 0x500, 0x400, 7500, 0},// EDID24h[0]: 1280x1024@75Hz
 
    { 0x480, 0x366, 7500, 1},// EDID25h[7]: 1152x870@75Hz
};

CBIOS_HDMI_FORMAT_MTX CEAVideoFormatTable[] =
{
//               1:interlace      0: 4:3; 1: 16:9; 2: 64:27; 3: 256:135
// Video          interlace       Aspect
// codes   H     V        V freq  Ratio
    //normal VICs
    {1,   640,  480, 0, { 6000, 5994},0, 1},
    {2,   720,  480, 0, { 6000, 5994},0, 1},
    {3,   720,  480, 0, { 6000, 5994},1, 1},
    {4,  1280,  720, 0, { 6000, 5994},1, 0},
    {5,  1920, 1080, 1, { 6000, 5994},1, 0},
    {6,   720,  480, 1, { 6000, 5994},0, 1},
    {7,   720,  480, 1, { 6000, 5994},1, 1},
    {8,   720,  240, 0, { 6000, 5994},0, 1},
    {9,   720,  240, 0, { 6000, 5994},1, 1},
    {10, 1440,  480, 1, { 6000, 5994},0, 1},
    {11, 1440,  480, 1, { 6000, 5994},1, 1},
    {12, 1440,  240, 0, { 6000, 5994},0, 1},
    {13, 1440,  240, 0, { 6000, 5994},1, 1},
    {14, 1440,  480, 0, { 6000, 5994},0, 1},
    {15, 1440,  480, 0, { 6000, 5994},1, 1},
    {16, 1920, 1080, 0, { 6000, 5994},1, 0},
    {17,  720,  576, 0, { 5000, 0000},0, 0},
    {18,  720,  576, 0, { 5000, 0000},1, 0},
    {19, 1280,  720, 0, { 5000, 0000},1, 0},
    {20, 1920, 1080, 1, { 5000, 0000},1, 0},
    {21,  720,  576, 1, { 5000, 0000},0, 0},
    {22,  720,  576, 1, { 5000, 0000},1, 0},
    {23,  720,  288, 0, { 5000, 0000},0, 0},
    {24,  720,  288, 0, { 5000, 0000},1, 0},
    {25, 1440,  576, 1, { 5000, 0000},0, 0},
    {26, 1440,  576, 1, { 5000, 0000},1, 0},
    {27, 1440,  288, 0, { 5000, 0000},0, 0},
    {28, 1440,  288, 0, { 5000, 0000},1, 0},
    {29, 1440,  576, 0, { 5000, 0000},0, 0},
    {30, 1440,  576, 0, { 5000, 0000},1, 0},
    {31, 1920, 1080, 0, { 5000, 0000},1, 0},
    {32, 1920, 1080, 0, { 2400, 2397},1, 0},    
    {33, 1920, 1080, 0, { 2500, 0000},1, 0},    
    {34, 1920, 1080, 0, { 3000, 2997},1, 0},
    {35, 2880, 480,  0, { 6000, 5994},0, 1},
    {36, 2880, 480,  0, { 6000, 5994},1, 1},
    {37, 2880, 576,  0, { 5000, 0000},0, 0},
    {38, 2880, 576,  0, { 5000, 0000},1, 0},
    {39, 1920, 1080 ,1, { 5000, 0000},1, 0},
    {40, 1920, 1080, 1, {10000, 0000},1, 0},
    {41, 1280,  720, 0, {10000, 0000},1, 0},
    {42,  720,  576, 0, {10000, 0000},0, 0},
    {43,  720,  576, 0, {10000, 0000},1, 0},
    {44,  720,  576, 1, {10000, 0000},0, 0},
    {45,  720,  576, 1, {10000, 0000},1, 0},
    {46, 1920, 1080, 1, {12000,11988},1, 0},
    {47, 1280,  720, 0, {12000,11988},1, 0},
    {48,  720,  480, 0, {12000,11988},0, 1},
    {49,  720,  480, 0, {12000,11988},1, 1},
    {50,  720,  480, 1, {12000,11988},0, 1},
    {51,  720,  480, 1, {12000,11988},1, 1},
    {52,  720,  576, 0, {20000, 0000},0, 0},
    {53,  720,  576, 0, {20000, 0000},1, 0},
    {54,  720,  576, 1, {20000, 0000},0, 0},
    {55,  720,  576, 1, {20000, 0000},1, 0},
    {56,  720,  480, 0, {24000,23976},0, 1},
    {57,  720,  480, 0, {24000,23976},1, 1},
    {58,  720,  480, 1, {24000,23976},0, 1},
    {59,  720,  480, 1, {24000,23976},1, 1},
    {60, 1280,  720, 0, { 2400, 2398},1, 0},
    {61, 1280,  720, 0, { 2500, 0000},1, 0},
    {62, 1280,  720, 0, { 3000, 2997},1, 0},
    {63, 1920, 1080, 0, {12000,11988},1, 0},
    {64, 1920, 1080, 0, {10000, 0000},1, 0},
// CEA-861-F
    {65, 1280,  720, 0, { 2400, 2398},2, 0},
    {66, 1280,  720, 0, { 2500, 0000},2, 0},
    {67, 1280,  720, 0, { 3000, 2997},2, 0},
    {68, 1280,  720, 0, { 5000, 0000},2, 0},
    {69, 1280,  720, 0, { 6000, 5994},2, 0},
    {70, 1280,  720, 0, {10000, 0000},2, 0},
    {71, 1280,  720, 0, {12000,11988},2, 0},
    {72, 1920, 1080, 0, { 2400, 2398},2, 0},
    {73, 1920, 1080, 0, { 2500, 0000},2, 0},
    {74, 1920, 1080, 0, { 3000, 2997},2, 0},
    {75, 1920, 1080, 0, { 5000, 0000},2, 0},
    {76, 1920, 1080, 0, { 6000, 5994},2, 0},
    {77, 1920, 1080, 0, {10000, 0000},2, 0},
    {78, 1920, 1080, 0, {12000,11988},2, 0},
    {79, 1680,  720, 0, { 2400, 2398},2, 0},
    {80, 1680,  720, 0, { 2500, 0000},2, 0},
    {81, 1680,  720, 0, { 3000, 2997},2, 0},
    {82, 1680,  720, 0, { 5000, 0000},2, 0},
    {83, 1680,  720, 0, { 6000, 5994},2, 0},
    {84, 1680,  720, 0, {10000, 0000},2, 0},
    {85, 1680,  720, 0, {12000,11988},2, 0},
    {86, 2560, 1080, 0, { 2400, 2398},2, 0},
    {87, 2560, 1080, 0, { 2500, 0000},2, 0},
    {88, 2560, 1080, 0, { 3000, 2997},2, 0},
    {89, 2560, 1080, 0, { 5000, 0000},2, 0},
    {90, 2560, 1080, 0, { 6000, 5994},2, 0},
    {91, 2560, 1080, 0, {10000, 0000},2, 0},
    {92, 2560, 1080, 0, {12000,11988},2, 0},
    {93, 3840, 2160, 0, { 2400, 2398},1, 0},
    {94, 3840, 2160, 0, { 2500, 0000},1, 0},
    {95, 3840, 2160, 0, { 3000, 2997},1, 0},
    {96, 3840, 2160, 0, { 5000, 0000},1, 0},
    {97, 3840, 2160, 0, { 6000, 5994},1, 0},
    {98, 4096, 2160, 0, { 2400, 2398},3, 0},
    {99, 4096, 2160, 0, { 2500, 0000},3, 0},
    {100,4096, 2160, 0, { 3000, 2997},3, 0},
    {101,4096, 2160, 0, { 5000, 0000},3, 0},
    {102,4096, 2160, 0, { 6000, 5994},3, 0},
    {103,3840, 2160, 0, { 2400, 2398},2, 0},
    {104,3840, 2160, 0, { 2500, 0000},2, 0},
    {105,3840, 2160, 0, { 3000, 2997},2, 0},
    {106,3840, 2160, 0, { 5000, 0000},2, 0},
    {107,3840, 2160, 0, { 6000, 5994},2, 0},

    //normal VIC end
    //extened VIC begin
    { CBIOS_HDMI_NORMAL_VIC_COUNTS + 1, 3840, 2160, 0, { 3000, 2997},1, 0},
    { CBIOS_HDMI_NORMAL_VIC_COUNTS + 2, 3840, 2160, 0, { 2500, 0000},1, 0},
    { CBIOS_HDMI_NORMAL_VIC_COUNTS + 3, 3840, 2160, 0, { 2400, 2397},1, 0},
    { CBIOS_HDMI_NORMAL_VIC_COUNTS + 4, 4096, 2160, 0, { 2400, 0000},1, 0},
    //extened VIC end
    
};

/*
int ParseEdid(pVirtBase_Para virtualBase)
{
    unsigned char *pEdid = NULL;

    pEdid = (unsigned char*)calloc(EDID_SIZE , sizeof(unsigned char));

    if(pEdid && DisplayReadEDID(virtualBase, pEdid))
    {   
        DisplayParseEdid(pEdid);
    }
    else
    {
        printf("Read EDID Failed\n");
    }

    if (pEdid)
    {
        free(pEdid);
    }

}

int DisplayReadEDID(pVirtBase_Para virtualBase,unsigned char *pEdid)
{

    I2C_PARAMS I2CParams = {0};
    int ret = 0;
  
    I2CParams.SlaveAddress = I2C_SLAVEADDRESS;
    I2CParams.Buffer = pEdid;
    I2CParams.BufferLen = EDID_SIZE;    //read 256 byte
    I2CParams.I2CBusNum = I2C_NUM_HDMI;

    if(I2CReadData(virtualBase, &I2CParams))
    {
        DisplayEdidRawData(pEdid);
        ret =  1;
    }
    else
    {
        ret =  0;
    }
    return ret;

}

void DisplayEdidRawData(unsigned char *pEdid)
{
    int i = 0;

    for(i = 0; i < EDID_SIZE; i++)
    {
        printf("%02X ",*pEdid++);

        if(i % 16 == 15)
            printf("\n");
    }
}
*/

int IsEDIDValid(unsigned char *pEdid, int Len)
{
	int i = 0, j = 0;
	unsigned char sum = 0;
	unsigned char edidHeader[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};
	if(pEdid == NULL)
	{
		return 0;
	}

	if((Len%128) != 0)
	{
		return 0;
	}

	if(memcmp(edidHeader, pEdid, 8) != 0)
	{
		return 0;
	}

	for(i = 0; i < Len/128; i++)
	{
		sum = 0;
		for(j = 0; j < 128; j++)
		{
			sum += pEdid[i*128 + j];
		}
		if(sum != 0x00)
		{
			return 0;
		}
	}

	return 1;
}

void DisplayParseEdid(unsigned char *pEdid)
{  
    char *EdidInfo = (char *)pEdid;
    DisplayEdidHeader(EdidInfo);
    DisplayEdidVendorIdenti(EdidInfo);
    DisplayEdidEDIDversion(EdidInfo);
    DisplayEdidDisplayParams(EdidInfo);
    DisplayEdidColorCharacters(EdidInfo);
    DisplayEdidEstTimings(EdidInfo);
    DisplayEdidStdTimings(EdidInfo);
    DisplayEdidDetailedTimings(EdidInfo);
    DisplayEdidExtFlagandChecksum(EdidInfo);
    DisplayCEA861(EdidInfo);
}

void DisplayEdidHeader(char *pEdidInfo)
{
    printf("<---Header--->\n");
    int i = 0;
    unsigned char *pEdid = pEdidInfo;
    for(i = 0; i < 8; i++)
    {
        printf("%02x ", (unsigned char)pEdid[i]);
    }
    printf("\n");
    printf("-------------------------------------\n");
}

void DisplayEdidVendorIdenti(char *pEdidInfo)
{
    printf("<---Vendor/Product Identification--->\n");
    
    int i = 0;
    char Ascii[32] = "0ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_";

    char *pEdid = pEdidInfo + MONITORIDINDEX;
 
    char Man1 = Ascii[((pEdid[0]&0x7C)>>2)];
    char Man2 = Ascii[(((pEdid[0]&0x03)<<3)|((pEdid[1]&0xE0)>>5))];
    char Man3 = Ascii[(pEdid[1]&0x1F)];
    
    printf("Manufacture Name:             %c%c%c\n",Man1,Man2,Man3); 
    
    printf("Product Code:                 %02X%02X\n",pEdid[3],pEdid[2]);

    printf("Serial Number:                %02X%02X%02X%02X\n",pEdid[7],pEdid[6],pEdid[5],pEdid[4]);
    
    printf("Week of Manufacturer:         %d\n",pEdid[8]);
    printf("Year of Manufacturer:         %d\n",pEdid[9]+1990);

    printf("-------------------------------------\n");
}


void DisplayEdidEDIDversion(char *pEdidInfo)
{
    printf("<---EDID Structer Version/Revision--->\n");
    unsigned char *pEdid = pEdidInfo + VERSIONINDEX;

    printf("EDID Version:                 %d\n",pEdid[0]);
    printf("EDID Revision:                %d\n",pEdid[1]);

    printf("-------------------------------------\n");
}

void DisplayEdidDisplayParams(char *pEdidInfo)
{
    printf("<---Basic Dispaly Parameters and Features--->\n");
    
    unsigned char *pEdid = pEdidInfo + DISPLAYPARAINDEX;

    if(pEdid[0]&0x80)
    {
        printf("Input signal type:            Digital\n");   
    }
    else
    {
        printf("Input signal type:            Analog\n");
    } 

   if(pEdid[0]&0x10)
    {
        printf("Setup:                        balnk-to-blank expected\n");
    } 
    else
    {
        printf("Setup:                        balnk-to-blank not expected\n");
    }

    if(pEdid[0]&0x08)
    {
        printf("Separate syncs. supported:    YES\n");
    } 
    else
    {
        printf("Separate syncs. supported:    NO\n");
    }

    if(pEdid[0]&0x04)
    {
        printf("Composite sync. supported:    YES\n");
    } 
    else
    {
        printf("Composite sync. supported:    NO\n");
    }

    if(pEdid[0]&0x02)
    {
        printf("SOG supported:                YES\n");
    } 
    else
    {
        printf("SOG supported:                NO\n");
    }

    if(pEdid[0]&0x01)
    {
        printf("Vsync. Pulse:                 serration required\n");
    } 
    else
    {
        printf("Vsync. Pulse:                 serration not required\n");
    }
   
    printf("Max Horizontal Image Size:    %d cm\n",pEdid[1]);
    printf("Max Vertical Image Size:      %d cm\n",pEdid[2]);
    int Gamma = pEdid[3]+100;
    printf("Display Gamma:                %.1f\n",(float)Gamma/100);
    
    int flag = pEdid[4]&24;

    if(flag == 0x00)
    {
        printf("Display Type:                 Monochrome/Grayscale Display");
    }
    else if(flag == 0x08)
    {
        printf("Display Type:                 RGB Color Display");
    }
    else if(flag == 0x10)
    {
        printf("Display Type:                 Non RGB Multicolor Display");
    }
    else if(flag == 0x18)
    {
        printf("Display Type:                 Undefined");
    }
    printf("\n");
   
    
    if(pEdid[4]&0x80)
    {
        printf("DPMS Support Stand-by:        YES\n");
    }
    else
    {
        printf("DPMS Support Stand-by:        NO\n");
    }

    if(pEdid[4]&0x40)
    {
        printf("DPMS Support Suspend:         YES\n");
    }
    else
    {
        printf("DPMS Support Suspend:         NO\n");
    }

    if(pEdid[4]&0x20)
    {
        printf("DPMS Support Active Off:      YES\n");
    }
    else
    {
        printf("DPMS Support Active Off:      NO\n");
    }
 
    if(pEdid[4]&0x04)
    {
        printf("Use Default Color Space:      YES\n");
    }
    else
    {
        printf("Use Default Color Space:      NO\n");
    }

    if(pEdid[4]&0x02)
    {
        printf("Preferred Timing In FDB:      YES\n");
    }
    else
    {
        printf("Preferred Timing In FDB:      NO\n");
    }

    if(pEdid[4]&0x01)
    {
        printf("Features,GTF support:         YES\n");
    }
    else
    {
        printf("Features,GTF support:         NO\n");
    }
   
    printf("-------------------------------------\n");
}

void DisplayEdidColorCharacters(char *pEdidInfo)
{
    printf("<---Color Characteristic--->\n");

    unsigned char *pEdid = pEdidInfo + COLORCHARACTERINDEX;

    int Total;
    Total = pEdid[2]<<2 | (pEdid[0]>>6);
    printf("Red_X:                        %f\n",(float)Total/1024);

    Total = pEdid[3]<<2 | ((pEdid[0]>>4)&0x03);
    printf("Red_Y:                        %f\n",(float)Total/1024);

    Total = pEdid[4]<<2 | ((pEdid[0]>>2)&0x03);
    printf("Green_X:                      %f\n",(float)Total/1024);

    Total = pEdid[5]<<2 | (pEdid[0]&3);
    printf("Green_Y:                      %f\n",(float)Total/1024);

    Total = pEdid[6]<<2 | (pEdid[1]>>6);
    printf("Blue_X:                       %f\n",(float)Total/1024);

    Total = pEdid[7]<<2 | ((pEdid[1]>>4)&3);
    printf("Blue_Y:                       %f\n",(float)Total/1024);

    Total = pEdid[8]<<2 | ((pEdid[1]>>2)&0x03);
    printf("White_X:                      %f\n",(float)Total/1024);

    Total = pEdid[9]<<2 | (pEdid[1]&0x03);
    printf("White_Y:                      %f\n",(float)Total/1024);

    printf("-------------------------------------\n");
}


void DisplayEdidEstTimings(char *pEdidInfo)
{
    printf("<---Established Timings--->\n");

    unsigned char *pEdid = pEdidInfo + ESTABLISH_TIMINGS_INDEX;
    int umax = 0x01<<16; 
    int i;
    int bits = (pEdid[0]<<9) | (pEdid[1]<<1) | pEdid[2];
  
    for(i = 0; i < 17; i++)
    {
        if(bits & umax>>i)
        {
            printf("%4d x %4d  @  %dHz",EstTiming[i].XResolution,EstTiming[i].YResolution,EstTiming[i].RefreshRate/100);

            if(EstTiming[i].Protocol == 0)
            {
                printf("  -  VESA");
            }
            else if(EstTiming[i].Protocol == 1)
            {
                printf("  -  Apple/Mac II");
            }
            else if(EstTiming[i].Protocol == 2)
            {
                printf("  -  IBM/VGA");
            }
            else if(EstTiming[i].Protocol == 3)
            {
                printf("  -  IBM/XGA2");
            }
            else if(EstTiming[i].Protocol == 4)
            {
                printf("  -  IBM");
            }
            printf("\n");
        }
    }

    printf("-------------------------------------\n");
}

void DisplayEdidStdTimings(char *pEdidInfo)
{
    printf("<---Standard Timing Identification--->\n");

    unsigned char *pEdid = pEdidInfo + STANDARD_TIMINGS_INDEX;
    int Hor,Ver,Freq,Flag;
    int i;
    
    for(i = 0; i < 16; i=i+2)
    {
        if(((pEdid[i] ^ 1) | (pEdid[i+1] ^ 1)) && ((pEdid[i] ^ 0 ) | (pEdid[i+1] ^ 0)))
        {
            Hor = (pEdid[i]+31)*8;
            Flag = pEdid[i+1]>>6;
            if(Flag == 0)
            {
                Ver = Hor*10/16;
            }
            else if(Flag == 1)
            {
                Ver = Hor*3/4;
            }  
            else if(Flag == 2)
            {
                Ver = Hor*4/5;
            }
            else if(Flag == 3)
            {
                Ver = Hor*9/16;
            }
            Freq = (pEdid[i+1]&0x3F) + 60;
            printf("%4d x %4d  @  %dHz  -  VESA\n",Hor,Ver,Freq);
        }
    }
    printf("-------------------------------------\n");
}

void ParseDTLTiming(unsigned char *pEdid, int dtlTimIndex)
{
    unsigned int Clock;
    unsigned int HActive,HBlank,HSyncOffset,HSyncPulseWidth;
    unsigned int VActive,VBlank,VSyncOffset,VSyncPulseWidth;
    unsigned int HImageSize,VImageSize,HBorder,VBorder;
    int i,j;

    if(pEdid[0] == 0x00 && pEdid[1] == 0x00)
        return;

    Clock = pEdid[1]<<8 | pEdid[0];
    
    HActive = (pEdid[4]>>4)<<8 | pEdid[2];
    HBlank = (pEdid[4]&0x0F)<<8 | pEdid[+3];
        
    VActive = (pEdid[7]>>4)<<8 | pEdid[5];
    VBlank = (pEdid[7]&0x0F)<<8 | pEdid[6];

    HSyncOffset = (pEdid[11]>>6)<<8 | pEdid[8];
    HSyncPulseWidth = (pEdid[11]&0x30)<<4 | pEdid[9];
    
    VSyncOffset = (pEdid[11]&0x0C)<<2 | pEdid[10]>>4;
    VSyncPulseWidth = (pEdid[11]&0x03)<<4 | (pEdid[10]&0x0F);

    if(pEdid[17] & 0x80)
    {
        printf("Detailed Timing%d:             %d x %di  @  %.0fHz\n",dtlTimIndex+1,HActive,2*VActive,(float)Clock*10000/((HActive + HBlank)*(VActive + VBlank)));    
    }
    else
    {
        printf("Detailed Timing%d:             %d x %dp  @  %.0fHz\n",dtlTimIndex+1,HActive,VActive,(float)Clock*10000/((HActive + HBlank)*(VActive + VBlank)));   
    } 

    printf("Clock:                        %.3f MHz\n",(float)Clock/100);

    printf("Horizontal Active:            %d pixels\nHorizontal Blanking:          %d pixels\nHorizontal Sync. Offset:      %d pixels\nHorizontal Sync Pulse Width:  %d pixels\n",HActive,HBlank,HSyncOffset,HSyncPulseWidth);
    
    printf("Vertical Active:              %d lines\nVertical Blanking:            %d lines\nVertical Sync. Offset:        %d lines\nVertical Sync Pulse Width:    %d lines\n",VActive,VBlank,VSyncOffset,VSyncPulseWidth);

    HImageSize = (pEdid[14]>>4)<<8 | pEdid[12];
    VImageSize = (pEdid[14]&0x0F)<<8 | pEdid[13];

    printf("Horizontal Image Size:        %d mm\nVertical Image Size:          %d mm\n",HImageSize,VImageSize);

    HBorder = pEdid[15];
    VBorder = pEdid[16];
            
    printf("Horizontal Border:            %d mm\nVertical Border:              %d lines\n",HBorder,VBorder);


    if(pEdid[17] & 0x80)
    {
        printf("Interlaced\n");
    }
    else
    {
        printf("Non-interlaced\n");
    }
    if(pEdid[17] & 0x60)
    {
        if((pEdid[17] & 0x60) == 0x20)   //01
        {
            if(pEdid[17] & 0x01)
            {
                printf("2-way interleaved stereo,right image on even lines");
            }
            else
            {    
                printf("field sequential stereo,right image when stereo sync. = 1");
            }
        }
        else if((pEdid[17] & 0x60) == 0x40)  //10
        {
            if(pEdid[17] & 0x01)
            {
                printf("2-way interleaved stereo,left image on even lines");
            }
            else
            {    
                printf("field sequential stereo,left image when stereo sync. = 1");
            }
        }
        else if((pEdid[17] & 0x60) == 0x60)  //11
        {
            if(pEdid[17] & 0x01)
            {
                printf("side-by-side interleaved stereo");
            }
            else  
            {  
                printf("4-way interleaved stereo");
            }
        }
        printf("\n");
    }
    else
    {
        printf("Normal Display,No Stereo\n");
    }
            
    if((pEdid[17] & 0x18) == 0x00)
    {
        printf("Analog Composite Syncs\n");
        printf("Hsync signal polarity:        Negative\n");
        printf("Vsync signal polarity:        Negative\n");
    }
    else if((pEdid[17] & 0x18) == 0x08)
    {
        printf("Bipolar Analog Composite Syncs\n");
        printf("Hsync signal polarity:        Negative\n");
        printf("Vsync signal polarity:        Negative\n");
    }
    else if((pEdid[17] & 0x18) == 0x10)
    {
        printf("Digtal Composite Syncs\n");
        printf("Hsync signal polarity:        Negative\n");
        printf("Vsync signal polarity:        Negative\n");
    }
    else if((pEdid[17] & 0x18) == 0x18)
    {
        printf("Digtal Separate Syncs\n");
        if((pEdid[17] & 0x06) == 0x06)
        {
            printf("Hsync signal polarity:        Positive\n");
            printf("Vsync signal polarity:        Positive\n");
        }
        else if((pEdid[17] & 0x06) == 0x04)
        {
            printf("Hsync signal polarity:        Negative\n");
            printf("Vsync signal polarity:        Positive\n");
        }
        else if((pEdid[17] & 0x06) == 0x02)
        {
            printf("Hsync signal polarity:        Positive\n");
            printf("Vsync signal polarity:        Negative\n");
        }
        else if((pEdid[17] & 0x06) == 0x00)
        {
            printf("Hsync signal polarity:        Negative\n");
            printf("Vsync signal polarity:        Negative\n");
        }
    }
    printf("\n");
}

void DisplayEdidDetailedTimings(char *pEdidInfo)
{
    printf("<---Detailed Timing Descriptions--->\n");
    unsigned char *pEdid = pEdidInfo + DETAILED_TIMINGS_INDEX;
    int i,j;

    for(i = 0; i< 4; i++)
    {
        if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
          (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFF))
        {
            printf("Detailed Timing%d:             FF(Monitor S/N)\n",i+1);
            printf("Serial Number: ");
            for(j = 5; j < 18; j++)
            {
                if(pEdid[i*18+j] == 0x0A) break;
                else 
                {
                    printf("%c",pEdid[i*18+j]);
                }
            }
            printf("\n\n");    
        }
        else if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFE))
        {
            printf("Detailed Timing%d:             FE(ASCII Data String)\n",i+1);
            printf("Data String: ");
            for(j = 5; j < 18; j++)
            {
                if(pEdid[i*18+j] == 0x0A) break;
                else 
                {
                    printf("%c",pEdid[i*18+j]);
                }
            }
            printf("\n\n");    
        }
        else if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFD))
        {
            printf("Detailed Timing%d:             FD(Monitor Range Limits)\n",i+1);
            printf("Monitor Limits:\n");
            printf("Vertical Rate:                %d - %dHz\n",pEdid[i*18+5],pEdid[i*18+6]);
            printf("Horizontal Rate:              %d - %dKHz\n",pEdid[i*18+7],pEdid[i*18+8]);
            printf("Max Support Clock:            %dMHz\n",pEdid[i*18+9]*10);
            
            if(pEdid[i*18+10] == 0x00)
            {
                printf("No Secondary Timing formula supported");
            }
            else if(pEdid[i*18+10] == 0x02)
            {
                printf("Secondary GTF Supported");
            }
            
            printf("\n");    
        }
        else if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFC))
        {
            printf("Detailed Timing%d:             FC(Monitor Name)\n",i+1);
            printf("Monitor Name:                 ");
            for(j = 5; j < 18; j++)
            {
                if(pEdid[i*18+j] == 0x0A) break;
                else 
                {
                    printf("%c",pEdid[i*18+j]);
                }
            }
            printf("\n\n");    
        }
        else if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFB))
        {
            int Total,Gamma;
            printf("Detailed Timing%d:             FB(Color Point)\n",i+1);
            
            if(pEdid[i*18+5] != 0x00)
            {
                printf("White Point Index Number:     %d\n",pEdid[i*18+5]);

                Total = pEdid[i*18+7]<<2 | ((pEdid[i*18+6]&0x0C)>>2);
                printf("White_X:                      %f\n",(float)Total/1024);

                Total = pEdid[i*18+8]<<2 | (pEdid[i*18+6]&0x03);
                printf("White_Y:                      %f\n",(float)Total/1024);

                Gamma = pEdid[i*18+9]+100;
                printf("White Gamma:                  %.1f\n",(float)Gamma/100);
            }

            if(pEdid[i*18+10] != 0x00)
            {
                printf("White Point Index Number:     %d\n",pEdid[i*18+10]);

                Total = pEdid[i*18+12]<<2 | ((pEdid[i*18+11]&0x0C)>>2);
                printf("White_X:                      %f\n",(float)Total/1024);

                Total = pEdid[i*18+13]<<2 | (pEdid[i*18+11]&0x03);
                printf("White_Y:                      %f\n",(float)Total/1024);

                Gamma = pEdid[i*18+14]+100;
                printf("White Gamma:                  %.1f\n",(float)Gamma/100);
            }
            
            printf("\n\n"); 
        }
        else if((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[3+i*18] == 0xFA))
        {
            printf("Detailed Timing%d:             FA(Standard Timing Identifiers)\n",i+1);
            int Hor,Ver,Freq,Flag;
    
            for(j = 0; j < 12; j=j+2)
            {
                if((pEdid[i*18+5+j] != 0x0A) && (pEdid[i*18+j+5+1] != 0x0A))
                {
                    Hor = (pEdid[i*18+5+j]+31)*8;
                    Flag = pEdid[i*18+j+5+1]>>6;
                    if(Flag == 0)
                    {
                        Ver = Hor*10/16;
                    }
                    else if(Flag == 1)
                    {
                        Ver = Hor*3/4;
                    }  
                    else if(Flag == 2)
                    {
                        Ver = Hor*4/5;
                    }
                    else if(Flag == 3)
                    {
                        Ver = Hor*9/16;
                    }
                    Freq = (pEdid[i*18+j+5+1]&0x3F) + 60;
                    printf("%4d x %4d  @  %dHz  -  VESA\n",Hor,Ver,Freq);
                }
            }

            printf("\n"); 
        }
        else if(!((pEdid[i*18] == 0x00)&&(pEdid[1+i*18] == 0x00)&&
               (pEdid[2+i*18] == 0x00)&&(pEdid[4+i*18] == 0x00)))
        {
            ParseDTLTiming(&pEdid[i*18], i);
        }
    }
    printf("-------------------------------------\n");
}

void DisplayEdidExtFlagandChecksum(char *pEdidInfo)
{
    printf("<---EDID Extension Flag And Checksum--->\n");

    unsigned char *pEdid = pEdidInfo + EXTENSION_FLAG_INDEX;
    TotalBlocks = pEdid[0] + 1;
    printf("Extension Flag:               %02X\n",pEdid[0]);
    printf("Checksum:                     %02X\n",pEdid[1]);

    printf("-------------------------------------\n");
}

int GetFmtIdxFromSVD(int SVD, int *pFormatIdx)
{
    int bRet = 1;

/*
According to CEA-861-F:
    If SVD >=1 and SVD <=64 then  
        7-bit VIC is defined (7-LSB\u2019s) and NOT a native code 
    Elseif SVD >=65 and SVD <=127 then  
        8-bit VIC is defined (from first new set)
    Elseif SVD >=129 and SVD <=192 then  
        7-bit VIC is defined (7-LSB\u2019s) and IS a native code 
    Elseif SVD >=193 and SVD <=253 then  
        8-bit VIC is defined (from second new set) 
    Elseif SVD == 0/128/254/255 then
        Reserved
    End if
*/
    if (SVD >=1 && SVD <= 64)
    {
        *pFormatIdx = SVD & 0x7F;
    }
    else if (SVD >= 65 && SVD <= 127)
    {
        *pFormatIdx = SVD;
    }
    else if (SVD >= 129 && SVD <= 192)
    {
        *pFormatIdx = SVD & 0x7F;
    }
    else if ((SVD >= 193) && (SVD <= 253))
    {
        *pFormatIdx = SVD;
    }
    else
    {
        printf("GetFmtIdxFromSVD: SVD = %d which is a reserved SVD code\n", SVD);
        bRet = 0;
    }

    if ((*pFormatIdx == 0) || (*pFormatIdx > CBIOS_HDMI_NORMAL_VIC_COUNTS))
    {
        printf("cbEDIDModule_GetFmtIdxFromSVD: FormatIdx = %d which is invalid\n", *pFormatIdx);
        bRet = 0;
    }

    return bRet;
}

void PrintCEAModeInfo(int FormatIndex, char *otherStr)
{
	if(CEAVideoFormatTable[FormatIndex-1].Interlace == 1)
	{
		printf("vic:%3d %4d x %4di	@  %.0fHz",FormatIndex,CEAVideoFormatTable[FormatIndex-1].XRes,
			CEAVideoFormatTable[FormatIndex-1].YRes,(float)CEAVideoFormatTable[FormatIndex-1].RefRate[0]/100);
	}
	else 
	{
		printf("vic:%3d %4d x %4dp	@  %.0fHz",FormatIndex,CEAVideoFormatTable[FormatIndex-1].XRes,
			CEAVideoFormatTable[FormatIndex-1].YRes,(float)CEAVideoFormatTable[FormatIndex-1].RefRate[0]/100);
	}
	if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 0)
	{
		printf("    4:3");
	}
	else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 1)
	{
		printf("   16:9");
	}
	else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 2)
	{
		printf("   64:27");
	}
	else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 3)
	{
		printf("  256:135");
	}

	printf("   %s\n", otherStr);

}

void DisplayCEA861(char *pEdidInfo)
{
    printf("<---EIA/CEA-861 Information-->\n");
    
    int i = 0;
    int BlockIndex = 0;
    int DetailedTimingOffset = 0;
    unsigned char *pEdid,*pEdid2;
    int Len = 0;
    int ExtTag = 0;
    int SVD = 0;
    int status = 0;
    int FormatIndex = 0;
    int SVD_mode[CBIOS_HDMI_NORMAL_VIC_COUNTS] = {0};
    int SVD_mode_num = 0;
    int SVD_num = 0;

    if(TotalBlocks > MAX_EDID_BLOCK_NUM)
    {
        printf("Total %d blocks but currently only parse 4 blocks\n",TotalBlocks);
        TotalBlocks = MAX_EDID_BLOCK_NUM;
    }
    
    for(BlockIndex = 1; BlockIndex < TotalBlocks; BlockIndex++)
    {
        pEdid = pEdidInfo + BlockIndex * 128;
        if(pEdid[0] != CEA_TAG)
        {
            continue;
        }
        printf("Revision Number:              %d\n",pEdid[1]);
        DetailedTimingOffset = pEdid[2];
        if(DetailedTimingOffset == 0)
        {
            continue;
        }

        if(pEdid[3] & 0x80)
        {
            printf("IT Underscan                  Supported\n");
        }
        else
        {
            printf("IT Underscan                  Not Supported\n");
        }

        if(pEdid[3] & 0x40)
        {
            printf("Basic Audio                   Supported\n");
        }
        else
        {
            printf("Basic Audio                   Not Supported\n");
        }

        if(pEdid[3] & 0x20)
        {
            printf("YCbCr 4:4:4                   Supported\n");
        }
        else
        {
            printf("YCbCr 4:4:4                   Not Supported\n");
        }

        if(pEdid[3] & 0x10)
        {
            printf("YCbCr 4:2:2                   Supported\n");
        }
        else
        {
            printf("YCbCr 4:2:2                   Not Supported\n");
        }
        printf("Native Formants:              %d\n",pEdid[3]&0x0F);
        printf("\n");
        for(i = 4; i < DetailedTimingOffset;)
        {
            if(((pEdid[i]>>5) & 0x07) == AUDIO_DATA_BLOCK_TAG)
            {
                printf("<---CE Audio Data--->\n");              
                Len = pEdid[i++] & 0x1F;
                pEdid2 = pEdid + i;

                ParseAUDIO_DATA_BLOCK(pEdid2,Len);

                printf("-------------------------------------\n");          
                i += Len;
            }
            else if(((pEdid[i]>>5) & 0x07) == VIDEO_DATA_BLOCK_TAG)
            {
                printf("<---Video Data Block--->\n");
                Len = pEdid[i++] & 0x1F;
                pEdid2 = pEdid + i;

                ParseVIDEO_DATA_BLOCK(pEdid2,Len, SVD_mode, &SVD_mode_num);
                SVD_num = Len;
                printf("-------------------------------------\n");
                i += Len;

            }
            else if(((pEdid[i]>>5) & 0x07) == VENDOR_SPECIFIC_DATA_BLOCK_TAG)
            {
                if((pEdid[i+1] == 0x03) && (pEdid[i+2] == 0x0C) && (pEdid[i+3] == 0x00))
                {
                    printf("<---Vendor-Specific Data Block--->\n");     
                    Len = pEdid[i++] & 0x1F;
                    pEdid2 = pEdid + i;

                    ParseVSDB(pEdid2, Len, SVD_mode, &SVD_mode_num);

                    printf("-------------------------------------\n");
                    i += Len;
                }
                if((pEdid[i+1] == 0xD8) && (pEdid[i+2] == 0x5D) && (pEdid[i+3] == 0xC4))
                {
                    printf("<---HDMI Forum Vendor-Specific Data Block--->\n");     
                    Len = pEdid[i++] & 0x1F;
                    pEdid2 = pEdid + i;

                    ParseHFVSDB(pEdid2, Len);

                    printf("------------------------------------------\n");
                    i += Len;
                }
            }
            else if(((pEdid[i]>>5) & 0x07) == SPEAKER_ALLOCATION_DATA_BLOCK_TAG)
            {
                printf("<---CE Speaker Allocation Data--->\n");
                Len = pEdid[i++] & 0x1F;
                pEdid2 = pEdid + i;

                ParseSpeakerAllocation(pEdid2, Len);

                printf("-------------------------------------\n");
                i += Len;
            }
            else if(((pEdid[i]>>5) & 0x07) == CEA_EXTENDED_BLOCK_TAG)
            {
                unsigned int j = 0;
                Len = pEdid[i++] & 0x1F;
                ExtTag = pEdid[i];

                if(ExtTag == YCBCR420_VIDEO_DATA_BLOCK)
                {
                    printf("<---YCBCR420 VIDEO DATA BLOCK,Only support 420 format----> \n");
                    for (j = 0; j < Len - 1; j++)
                    {
                        SVD = pEdid[i + 1 + j];
                        status = GetFmtIdxFromSVD(SVD, &FormatIndex);
                        if (!status)
                        {
                            continue;
                        }                    
                        PrintCEAModeInfo(FormatIndex, "");
                    }

                    printf("-------------------------------------\n");
                }
                else if(ExtTag == YCBCR420_CAP_MAP_DATA_BLOCK)
                {
                    unsigned char YCbCr420CapMap = 0;
                    unsigned char Step = 0;
                    unsigned char j = 0,k = 0;

                    printf("<----YCBCR 420 CAP Map Data Block --->\n");
                    if (Len == 1)
                    {
                        printf("All Supported SVD Mode support 420 format !!!!!\n");
                    }
                    else
                    {
                        printf("All those mode support 420 format and other format \n");
                        for (k = 0; k < Len - 1; k++)
                        {
                            YCbCr420CapMap = pEdid[i + 1 + k];

                            for (j = 0; j < 8; j++)
                            {
                                if (((YCbCr420CapMap >> j) & 0x1) && (j + Step < SVD_num))
                                {
                                    SVD = SVD_mode[j+Step];
                                    status = GetFmtIdxFromSVD(SVD, &FormatIndex);
                                    if (!status)
                                    {
                                        continue;
                                    }
                                    PrintCEAModeInfo(FormatIndex, "");
                                }
                            }
                            Step += 8;
                        }
                    }
                    printf("-------------------------------------\n");
                }
                else if(ExtTag == COLORIMETRY_DATA_BLOCK_TAG)
                {
                    printf("<----CEA Colorimetry Data Block ---->\n");
                    if(Len != 3)
                    {
                        printf("ParseCEAExtBlock:Colorimetry data block lenght error \n");
                    }
                    else
                    {
                        if(pEdid[i+1] & 0x01)
                        {
                            printf("Monitor support xvYCC601 \n");
                        }
                        if(pEdid[i+1] & 0x02)
                        {
                            printf("Monitor support xvYCC709 \n");
                        }
                        if(pEdid[i+1] & 0x04)
                        {
                            printf("Monitor support sYCC601 \n");
                        }
                        if(pEdid[i+1] & 0x08)
                        {
                            printf("Monitor support AdobeYCC601 \n");
                        }
                        if(pEdid[i+1] & 0x10)
                        {
                            printf("Monitor support AdobeRGB \n");
                        }
                        if(pEdid[i+1] & 0x20)
                        {
                            printf("Monitor support BT2020cYcc \n");
                        }
                        if(pEdid[i+1] & 0x40)
                        {
                            printf("Monitor support BT2020Ycc  \n");
                        }
                        if(pEdid[i+1] & 0x80)
                        {
                            printf("Monitor support BT2020RGB \n");
                        }

                        printf("Monitor MD0-MD3 is 0x%x \n",pEdid[i+2] & 0xf);
                        printf("-------------------------------------\n");
                    }
                }

                else if(ExtTag == HDR_STATIC_METADATA_DATA_BLOCK)
                {
                    printf("<----HDR STATIC METADATA DATA BLOCK---->\n");
                    if(Len < 3 || Len > 6)
                    {
                        printf("ParseCEAExtBlock:hdr medata data block lenght error ");
                    }
                    else
                    {
                        if(pEdid[i+1] & 0x01)
                        {
                            printf("Monitor support Traditional gamma,SDR Luminance Range\n");
                        }
                        if(pEdid[i+1] & 0x02)
                        {
                            printf("Monitor support Traditional gamma,HDR Luminance Range\n");
                        }
                        if(pEdid[i+1] & 0x04)
                        {
                            printf("Monitor support SMPTE ST 2084\n");
                        }
                        if(pEdid[i+1] & 0x10)
                        {
                            printf("Monitor support Future EOTF\n");
                        }

                        if(pEdid[i+1] & 0x01)
                        {
                            printf("Monitor support Static Metadata Type 1 \n");
                        }
                        if(Len == 4)
                        {
                            printf("Monitor Desired content Max Lum Data is 0x%x\n",pEdid[i +3]);
                        }
                        else if(Len == 5)
                        {
                            printf("Monitor Desired content Max Lum Data is 0x%x\n",pEdid[i + 3]);
                            printf("Monitor Desired content Max Frame-average Lum Data is 0x%x\n",pEdid[i + 4]);
                        }
                        else
                        {
                            printf("Monitor Desired content Max Lum Data is 0x%x\n",pEdid[i + 3]);
                            printf("Monitor Desired content Max Frame-average Lum Data is 0x%x\n",pEdid[i + 4]);
                            printf("Monitor Desired content Min Lum Data is 0x%x\n",pEdid[i + 5]);

                        }
                        printf("-------------------------------------\n");
                    }
                }
                else if(ExtTag == VIDEO_CAPABILITY_DATA_BLOCK_TAG)
                {
                    printf("<---Video Capability Data Block----> \n");
                    for (j = 0; j < Len - 1; j++)
                    {
                        printf("%02x ", (unsigned char)pEdid[i + 1 + j]);
                    }
                    printf("\n");

                    printf("------------------------------  -\n");
                }
                else if(ExtTag == VENDOR_SPECIFIC_VIDEO_DATA_BLOCK_TAG)
                {
                    printf("<---Vendor-Specific Video Data Block----> \n");
                    for (j = 0; j < Len - 1; j++)
                    {
                        printf("%02x ", (unsigned char)pEdid[i + 1 + j]);
                    }
                    printf("\n");

                    printf("------------------------------  -\n");
                }
                else if(ExtTag == VESA_VIDEO_DISPLAY_DEVICE_DATA_BLOCK_TAG)
                {
                    printf("<---VESA Display Device Data Block----> \n");
                    for (j = 0; j < Len - 1; j++)
                    {
                        printf("%02x ", (unsigned char)pEdid[i + 1 + j]);
                    }
                    printf("\n");

                    printf("----------------------------------- -\n");
                }
                else if(ExtTag == RSVD_VESA_VIDEO_TIMING_DATA_BLOCK_TAG)
                {
                    printf("<---VESA Video Timing Block Extension----> \n");
                    for (j = 0; j < Len - 1; j++)
                    {
                        printf("%02x ", (unsigned char)pEdid[i + 1 + j]);
                    }
                    printf("\n");

                    printf("------------------------------  -\n");
                }
                else
                {
                    printf("<---Other Extension Data Block----> \n");
                    printf("%02x ", (unsigned char)ExtTag);
                    for (j = 0; j < Len - 1; j++)
                    {
                        printf("%02x ", (unsigned char)pEdid[i + 1 + j]);
                    }
                    printf("\n");

                    printf("------------------------------  -\n");
                }
                i += Len;
            }
            else if(((pEdid[i]>>5)&0x07) == VESA_DTC_DATA_BLOCK_TAG)
            {
                unsigned int j = 0;
                printf("<---VESA Display Transfer Characteristic Data Block--->\n");     
                Len = pEdid[i++] & 0x1F;

                for(j = 0; j < Len; j++)
                {
                    printf("%02x ", (unsigned char)pEdid[i + j]);
                }
                printf("\n");

                printf("-------------------------------------------------\n");

                i += Len;
            }
            else
            {
                unsigned int j = 0;
                printf("<---Other Data Block--->\n");     
                Len = pEdid[i++] & 0x1F;
                printf("%x ", (unsigned char)pEdid[i - 1]);
                for(j = 0; j < Len; j++)
                {
                    printf("%02x ", (unsigned char)pEdid[i + j]);
                }
                printf("\n");

                printf("-------------------------------------------------\n");
    
                i += Len;
            }
        }
        ParseDetailedTiming(pEdid,DetailedTimingOffset);
    }
}
void ParseDetailedTiming(char *pEdidInfo,int Offset)
{
    int i = Offset;
    int dtlIndex = 0;
    unsigned char *pEdid = pEdidInfo;
    while((i+18) < 128)
    {
        ParseDTLTiming(&pEdid[i], dtlIndex);
        i += 18;
        dtlIndex++;
    }
}
void ParseAUDIO_DATA_BLOCK(char *pEdidInfo,int Length)
{
    int i = 0,j = 0, Len = Length;
    unsigned char *pEdid = pEdidInfo;
    int AudioFormatCode = 0;
    int MaxChannelNum = 0;
    int umax;
    float Freq[8] = {32, 44.1, 48, 88.2, 96, 176.4, 192, 0};
    char *AudioFormatName[] = {"Refer to Stream Header", "L-PCM", "AC-3", "MPEG-1", "MP3","MPEG2", "AAC LC", "DTS", "ATRAC", 
        "One Bit Audio", "Enhanced AC-3","DTS-HD", "MAT", "DST", "WMA Pro", "Refer to Audio Coding Extension Type(CXT) field in Data Byte 3"};

    for(j = 0; j < Len/3; j++)
    {
        AudioFormatCode = (pEdid[j*3]>>3)&0x0F;
        MaxChannelNum = (pEdid[j*3]&0x07)+1;

        printf("Audio Format:                 %s\n", AudioFormatName[AudioFormatCode]);
        printf("Channel Num:                  %d\n",MaxChannelNum);

        if(AudioFormatCode == 1)
        {
            printf("Supported Freq:               ");

            umax = 0x01;
            for(i = 0; i < 8; i++)
            {
                if(pEdid[j*3+1] & umax)
                {
                    printf("%.1f kHz, ",Freq[i]);
                }
                umax = umax<<1;
            }
            printf("\n");
            
            printf("Supported Bit Depths:         ");

            if(pEdid[j*3+2] & 0x01)
            {
                printf("%d bit, ",16);
            }
            if(pEdid[j*3+2] & 0x02)
            {
                printf("%d bit, ",20);
            }
            if(pEdid[j*3+2] & 0x04)
            {
                printf("%d bit, ",24);
            }
            printf("\n");                   
        }
        else if(AudioFormatCode >= 2 && AudioFormatCode <= 8)
        {
            printf("Supported Freq:               ");

            umax = 0x01;
            for(i = 0; i < 8; i++)
            {
                if(pEdid[j*3+1] & umax)
                {
                    printf("%.1f kHz, ",Freq[i]);
                }
                umax = umax<<1;
            }
            printf("\n");
            printf("Maxinum bit rate:             %d kHz\n",pEdid[j*3+2]<<3);
        }
        else if(AudioFormatCode >= 9 && AudioFormatCode <= 13)
        {
            printf("Supported Freq:               ");

            umax = 0x01;
            for(i = 0; i < 8; i++)
            {
                if(pEdid[j*3+1] & umax)
                {
                    printf("%.1f kHz, ",Freq[i]);
                }
                umax = umax<<1;
            }
            printf("\n");
            printf("Audio Format Code Dependent Value\n");   //: %d\n",pEdid[j*3+2]);
        }
        else if(AudioFormatCode == 14)
        {
            printf("Supported Freq:               ");

            umax = 0x01;
            for(i = 0; i < 8; i++)
            {
                if(pEdid[j*3+1] & umax)
                {
                    printf("%.1f kHz, ",Freq[i]);
                }
                umax = umax<<1;
            }
            printf("\n");
            printf("Profile:                      %d\n",pEdid[j*3+2]&0x07);
        }
        else if(AudioFormatCode == 15)
        {
            printf("Supported Freq:               ");

            umax = 0x01;
            for(i = 0; i < 8; i++)
            {
                if(pEdid[j*3+1] & umax)
                {
                    printf("%.1f kHz, ",Freq[i]);
                }
                umax = umax<<1;
            }
            printf("\n");

            if((pEdid[j*3+2]&0xF8)>=4 && (pEdid[j*3+2]&0xF8) <=6)
            {
                if(pEdid[j*3+2]&0x02)
                {
                    printf("%d_TL",960);
                }
                if(pEdid[j*3+2]&0x04)
                {
                    printf("%d_TL",1024);
                }
                printf("\n");
            }
            else if((pEdid[j*3+2]&0xF8) == 8 || (pEdid[j*3+2]&0xF8) == 10)
            {
                printf("Supported AAC Frame Length: ");
                if(pEdid[j*3+2]&0x01)
                {
                    printf("MPEG Surround ");
                }
                if(pEdid[j*3+2]&0x02)
                {
                    printf("%d_TL",960);
                }
                if(pEdid[j*3+2]&0x04)
                {
                    printf("%d_TL",1024);
                }
                printf("\n");
            }
        }
    }    
}

void ParseSpeakerAllocation(char *pEdidInfo, int Length)
{
    int j = 0, Len = Length;
    unsigned char *pEdid = pEdidInfo;
    unsigned int umax = 0;
    unsigned short pload = *(unsigned short*)pEdid;

    char *speakerAllocation[] = {"Front Left/Right", "Low Frequency Effect", "Front Center", "Rear Left/Right",
                            "Rear Center", "Front Left/Right Center", "Rear Left/Right Center", "Front Left/Right Wide",
                            "Front Left/Right High", "Top Center", "Front Center High"};

    umax = 0x01;
    for(j = 0; j < 11; j++)
    {
        if(pload & umax)
        {
            printf("%s\n", speakerAllocation[j]);
        }
        umax = umax << 1;
    }
}

void ParseHFVSDB(char *pEdidInfo, int Length)
{
    unsigned char *pEdid = pEdidInfo;
    
    printf("IEEE Registration Number:                                               0x%02X%02X%02X\n",pEdid[2],pEdid[1],pEdid[0]);
    printf("HF-VSDB Version:                                                        %d\n", pEdid[3]);
    printf("Max_TMDS_Character_Rate                                                 %d MHz\n", pEdid[4] * 5);

    if(pEdid[5] & 0x01)
    {
        printf("Supports receiving 3D_OSD_Disparity in HF_VSIF                          YES\n");
    }
    else
    {
        printf("Supports receiving 3D_OSD_Disparity in HF_VSIF                          NO\n");
    }

    if(pEdid[5] & 0x02)
    {
        printf("Supports receiving 3D Dual View signaling in HF_VSIF                    YES\n");
    }
    else
    {
        printf("Supports receiving 3D Dual View signaling in HF_VSIF                    NO\n");
    }

    if(pEdid[5] & 0x04)
    {
        printf("Supports receiving 3D Independent View signaling in HF_VSIF            YES\n");
    }
    else
    {
        printf("Supports receiving 3D Independent View signaling in HF_VSIF             NO\n");
    }

    if(pEdid[5] & 0x08)
    {
        printf("Supports scrambling for TMDS Character Rates at or below 340 Mcsc       YES\n");
    }
    else
    {
        printf("Supports scrambling for TMDS Character Rates at or below 340 Mcsc       NO\n");
    }

    if(pEdid[5] & 0x40)
    {
        printf("Supports SCDC Read Request                                             YES\n");
    }
    else
    {
        printf("Supports SCDC Read Request                                              NO\n");
    }

    if(pEdid[5] & 0x80)
    {
        printf("Supports SCDC                                                           YES\n");
    }
    else
    {
        printf("Supports SCDC                                                           NO\n");
    }

    if(pEdid[6] & 0x01)
    {
        printf("Supports 10 bits/component Deep Color 4:2:0 Pixel Encoding              YES\n");
    }
    else
    {
        printf("Supports 10 bits/component Deep Color 4:2:0 Pixel Encoding              NO\n");
    }

    if(pEdid[6] & 0x02)
    {
        printf("Supports 12 bits/component Deep Color 4:2:0 Pixel Encoding              YES\n");
    }
    else
    {
        printf("Support 12 bits/component Deep Color 4:2:0 Pixel Encoding               NO\n");
    }

    if(pEdid[6] & 0x04)
    {
        printf("Supports 16 bits/component Deep Color 4:2:0 Pixel Encoding              YES\n");
    }
    else
    {
        printf("Support 16 bits/component Deep Color 4:2:0 Pixel Encoding               NO\n");
    }
}

void ParseVSDB(char *pEdidInfo, int Length, int *SVD_mode, int *SVD_mode_num)
{
    int j = 0, Len = Length;
    unsigned char *pEdid = pEdidInfo;
    unsigned int FormatIndex = 0;
    int videoPayLoad = 0;
    int ThreeDPayLoad = 0;
    int ThreeDPos = 0;
    int video_present = 0;
    int VicLen = 0, ThreeDLen = 0;
    int ThreeD_Present = 0, ThreeD_Multi_present = 0;
    printf("IEEE Registration Number:     0x%02X%02X%02X\n",pEdid[2],pEdid[1],pEdid[0]);
    printf("CEC Physical Address:         %d.%d.%d.%d\n", pEdid[4]&0x0F, (pEdid[4]&0xF0)>>4, pEdid[3]&0x0F, (pEdid[3]&0xF0)>>4);

    if(Len >= 6)
    {
        if(pEdid[5] & 0x80)
        {
            printf("Supports AI:                  YES\n");
        }
        else 
        {
            printf("Supports AI:                  NO\n");
        }
        if(pEdid[5] & 0x40)
        {
            printf("Supports 48bpp                YES\n");
        }
        else 
        {
            printf("Supports 48bpp                NO\n");
        }
        if(pEdid[5] & 0x20)
        {
            printf("Supports 36bpp                YES\n");
        }
        else 
        {
            printf("Supports 36bpp                NO\n");
        }
        if(pEdid[5] & 0x10)
        {
            printf("Supports 30bpp                YES\n");
        }
        else 
        {
            printf("Supports 48bpp                NO\n");
        }
        if(pEdid[5] & 0x08)
        {
            printf("Supports YCbCr4:4:4 in deep color         YES\n");
        }
        else 
        {
            printf("Supports YCbCr 4:4:4 in deep color          NO\n");
        }
        if(pEdid[5] & 0x01)
        {
            printf("Supports Dual-link DVI        YES\n");
        }
        else 
        {
            printf("Supports Dual-link DVI        NO\n");
        }
    }
    else
    {
        return;
    }
    
    if(Len >= 7)
    {
        printf("Maxinum TMDS Clock:           %dMHz\n",5*pEdid[6]);
        videoPayLoad = 6;
    }
    else
    {
        return;
    }

    if(Len >= 8)
    {
    	videoPayLoad++;
        //Latency_Fields_Present
        if(pEdid[7]&0x80)
        {
            videoPayLoad += 2;
            //Video Latency
            if(pEdid[8] == 0)
            {
                printf("Video_Latency:                  unknown\n");
            }
            else if(pEdid[8] == 255)
            {
                printf("No video supported in this device or downstream\n");
            }
            else
            {
                printf("Video_Latency:                  %d ms\n", 2*(pEdid[8]-1));
            }
            //Audio Latency
            if(pEdid[9] == 0)
            {
                printf("Audio_Latency:                  unknown\n");
            }
            else if(pEdid[9] == 255)
            {
                printf("No audio supported in this device or downstream\n");
            }
            else
            {
                printf("Audio_Latency:                  %d ms\n", 2*(pEdid[9]-1));
            }

            //I_Latency_Fields_Present
            if(pEdid[7] & 0x40)
            {
                videoPayLoad += 2;
                //Interlaced_Video_Latency
                if(pEdid[10] == 0)
                {
                    printf("Interlaced_Video_Latency:                  unknown\n");
                }
                else if(pEdid[10] == 255)
                {
                    printf("No video supported in this device or downstream\n");
                }
                else
                {
                    printf("Interlaced_Video_Latency:                  %d ms\n", 2*(pEdid[10]-1));
                }
                //Interlaced_Audio Latency
                if(pEdid[11] == 0)
                {
                    printf("Interlaced_Audio_Latency:                  unknown\n");
                }
                else if(pEdid[11] == 255)
                {
                    printf("No audio supported in this device or downstream\n");
                }
                else
                {
                    printf("Interlaced_Audio_Latency:                  %d ms\n", 2*(pEdid[11]-1));
                }
            }
        }

        //HDMI_Video_present
        if(pEdid[7] & 0x20)
        {  
            video_present = 1;
        }

        //supported content type
        if(pEdid[7] & 0x0F != 0)
        {
            printf("Supported content type:                   ");

            if(pEdid[7] & 0x08)
            {
                printf("Graphics(text)  ");
            }
            if(pEdid[7] & 0x04)
            {
                printf("Photo  ");
            }
            if(pEdid[7] & 0x02)
            {
                printf("Cinema  ");
            }
            if(pEdid[7] & 0x01)
            {
                printf("Game");
            }

            printf("\n");
        }
    }
    else
    {
        return;
    }

    if(video_present)
    {
        unsigned int ImageSizeInfo = 0; 
        videoPayLoad += 1;
        ImageSizeInfo = (pEdid[videoPayLoad] >> 3) & 0x03;
        //printf("VSDB image size:              %x\n", (pEdid[videoPayLoad] >> 3) & 0x03);
        if(ImageSizeInfo == 0)
        {
            printf("No addition infomation for Image Size(0x15 and 0x16 in VESA E-EDID)\n");
        }
        else if(ImageSizeInfo == 1)
        {
            printf("Values in Image Size area(0x15 and 0x16 in VESA E-EDID) indicate correct aspect ratio but not the sizest\n");
        }
        else if(ImageSizeInfo == 2)
        {
            printf("Values in Image Size area(0x15 and 0x16 in VESA E-EDID) indicate correct sizes and round to nearest 1 cm\n");
        }
        else if(ImageSizeInfo == 3)
        {
            printf("Values in Image Size area(0x15 and 0x16 in VESA E-EDID) indicate correct sizes  in divided by 5 and round to nearest 5 cm\n");
        }

        ThreeD_Present = (pEdid[videoPayLoad] >> 7) & 0x01;
        ThreeD_Multi_present = (pEdid[videoPayLoad] >> 5) & 0x03;
            
        VicLen = (pEdid[videoPayLoad + 1] >> 5) & 0x07;
        ThreeDLen = pEdid[videoPayLoad + 1] & 0x1F;
        ThreeDPayLoad = videoPayLoad + 1 + VicLen + 1;
        ThreeDPos = ThreeDPayLoad;
            
        if(VicLen > 0)
        {
            printf("VSDB mode list:\n");
            for(j = 0; j < VicLen; j++)
            {
                FormatIndex = pEdid[videoPayLoad + 2 + j] + CBIOS_HDMI_NORMAL_VIC_COUNTS;
                SVD_mode[*SVD_mode_num] = FormatIndex;
                (*SVD_mode_num)++;
                PrintCEAModeInfo(FormatIndex, "");
            }
        }

        if(ThreeD_Present)
        {
            //printf("3D mode list:\n");
            if(ThreeD_Multi_present == 1 || ThreeD_Multi_present == 2)
            {
                char ThreeD_struct[256] = "";
                unsigned short treedStruct = *(unsigned short *)(&pEdid[ThreeDPayLoad]);
                if(treedStruct & 0x0001)
                {
                    strcat(ThreeD_struct, "Frame packing/");
                }
                if(treedStruct & 0x0040)
                {
                    strcat(ThreeD_struct, "Top-and-Bottom/");
                }
                if(treedStruct & 0x0100)
                {
                    strcat(ThreeD_struct, "Side-by-Side(half)");
                }
                ThreeDPayLoad += 2;

                if(ThreeD_Multi_present == 1)
                {
                    for(j = 0; j < 16 && j < *SVD_mode_num; j++)
                    {
                        FormatIndex = SVD_mode[j];
                        PrintCEAModeInfo(FormatIndex, ThreeD_struct);
                    }
                }
                else if(ThreeD_Multi_present == 2)
                {
                    unsigned int umax = 0x01;
                    for(j = 0; j < 16; j++)
                    {
                        if(pEdid[ThreeDPayLoad] & umax)
                        {
                            FormatIndex = SVD_mode[j];
                            PrintCEAModeInfo(FormatIndex, ThreeD_struct);
                        }
                        umax = umax << 1;
                    }
                    ThreeDPayLoad += 2;
                }
            }

        	//printf("ThreeDPayLoad - ThreeDPos = %d, ThreeDLen = %d\n", ThreeDPayLoad - ThreeDPos, ThreeDLen);
            if(ThreeDPayLoad - ThreeDPos < ThreeDLen)
            {
                unsigned int vicOrder = 0, vic3DStruct = 0;
                char *vic3DStructName = "";
                for(j = ThreeDPayLoad; j < Len; j++)
                {
                    vicOrder = (pEdid[ThreeDPayLoad] >> 4) & 0x0F;
                    vic3DStruct = pEdid[ThreeDPayLoad] & 0x0F;

                    if(vic3DStruct == 0)
                    {
                        vic3DStructName = "Frame packing";
                    }
                    else if(vic3DStruct == 6)
                    {
                        vic3DStructName = "Top-and-Bottom";
                    }
                    else if(vic3DStruct == 8)
                    {
                        vic3DStructName = "Side-by-Side(half)";
                    }
                    FormatIndex = SVD_mode[vicOrder];
                    PrintCEAModeInfo(FormatIndex, vic3DStructName);

                    j  += 2;
                }
            }
        } 
    }

}
void ParseVIDEO_DATA_BLOCK(char *pEdidInfo,int Length, int * SVD_mode, int *SVD_mode_num)
{
    int j = 0, Len = Length;
    int FormatIndex = 0;
    int isNative = 0;
    char *strNative = "";
    unsigned char *pEdid = pEdidInfo;
    for(j = 0; j < Len; j++)
    {
        isNative = 0;
        FormatIndex = pEdid[j];
        if(FormatIndex >= 1 && FormatIndex <= 64)
        {
            FormatIndex &= 0x7F;
        }
        else if(FormatIndex >= 129 && FormatIndex <= 192)
        {
            FormatIndex &= 0x7F;
            isNative = 1;
        }

	SVD_mode[j] = FormatIndex;
	(*SVD_mode_num)++;

	 if(isNative)
        {
            strNative = "Native";
        }
	 else
	 {
	     strNative = "";
	 }

	PrintCEAModeInfo(FormatIndex, strNative);

/*
        if(CEAVideoFormatTable[FormatIndex-1].Interlace == 1)
        {
            printf("vic:%3d %4d x %4di  @  %.0fHz",FormatIndex,CEAVideoFormatTable[FormatIndex-1].XRes,
                CEAVideoFormatTable[FormatIndex-1].YRes,(float)CEAVideoFormatTable[FormatIndex-1].RefRate[0]/100);
        }
        else 
        {
            printf("vic:%3d %4d x %4dp  @  %.0fHz",FormatIndex,CEAVideoFormatTable[FormatIndex-1].XRes,
                CEAVideoFormatTable[FormatIndex-1].YRes,(float)CEAVideoFormatTable[FormatIndex-1].RefRate[0]/100);
        }
        if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 0)
        {
            printf("    4:3");
        }
        else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 1)
        {
            printf("   16:9");
        }
        else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 2)
        {
            printf("   64:27");
        }
        else if(CEAVideoFormatTable[FormatIndex-1].AspectRatio == 3)
        {
            printf("  256:135");
        }

        if(isNative)
        {
            printf("    Native");
        }
        printf("\n");
*/
    }
    printf("NB: NTSC refresh rate = (Hz*1000)/1001\n");
}




