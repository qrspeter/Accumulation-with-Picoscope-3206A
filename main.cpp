/*================================
// для 32 и 64 разрадных версий надо брать свои библиотечные файлы (из соответствующих SDK) и соответствующий компилятор.
// с 32-разрядным C:\mingw32\mingw32 или 64-битным  C:\Program Files\CodeBlocks\MinGW\
// конкретно 32-битный называется mingw-w64-install.exe, при установке надо указать х686.
*/

// In block averaging the memory must be allocated once and be in use.

// error in c++: if (strlen(line) == 8 || line[3] != '4') - errors in first part
// and if (strlen(line) >= 7)
// and if(strcmp(line + 4, "MSO") == 0 || strcmp(line + 5, "MSO") == 0 )
// std::strlen - https://en.cppreference.com/w/cpp/string/byte/strlen
// std::strcmp - https://en.cppreference.com/w/cpp/string/byte/strcmp

// https://www.codegrepper.com/code-examples/cpp/length+of+char+array+c%2B%2B
//  use strlen(string_name) with the header file #include <cstring>

// https://stackoverflow.com/questions/27638533/finding-the-length-of-a-character-array-in-c
// don't use a char* at all, but a std::string (may create a temporary):

// https://www.cplusplus.com/reference/cstring/strlen/
//  char mystr[100]="test string";
// sizeof(mystr) evaluates to 100, strlen(mystr) returns 11



// also: scanf_s  - was not declare
// and fscanf_s
// different format and using:
//  https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/scanf-s-scanf-s-l-wscanf-s-wscanf-s-l?view=msvc-170
// https://coderoad.ru/28647256/
// https://stackoverflow.com/questions/23378636/string-input-using-c-scanf-s
// or add size parameter http://port70.net/~nsz/c/c11/n1570.html#K.3.5.3.2 https://coderoad.ru/21434735/
// and https://stackoverflow.com/questions/21434735/difference-between-scanf-and-scanf-s


// resolved (at least no compilator errors):
// and min( ) was not declared:
// The min() function is for C programs only. For C++ programs, use the __min() macro. https://www.qnx.com/developers/docs/6.4.1/neutrino/lib_ref/m/min.html
// https://stackoverflow.com/questions/3437404/min-and-max-in-c
// std::min: https://en.cppreference.com/w/cpp/algorithm/min


// не хватает пункта меню и функции "параметры", где можно поменять все то, что есть в структуре настроек

// как хранить данные в CSV https://www.geeksforgeeks.org/csv-file-management-using-c/?ref=lbp


/*******************************************************************************
 *
 * Filename: ps3000aCon.c
 *
 * Description:
 *   This is a console mode program that demonstrates how to use the
 *   PicoScope 3000 Series (ps3000a) driver functions.
 *
 *	Supported PicoScope models:
 *
 *    PicoScope 3203A/B/D
 *		PicoScope 3204A/B/D
 *		PicoScope 3205A/B/D
 *		PicoScope 3206A/B/D
 *		PicoScope 3207A/B
 *		PicoScope 3203D MSO
 *		PicoScope 3204 MSO & D MSO
 *		PicoScope 3205 MSO & D MSO
 *		PicoScope 3206 MSO & D MSO
 *		PicoScope 3403D/D MSO
 *		PicoScope 3404A/B/D/D MSO
 *		PicoScope 3405A/B/D/D MSO
 *		PicoScope 3406A/B/D/D MSO
 *
 * Examples:
 *    Collect a block of samples immediately
 *    Collect a block of samples when a trigger event occurs
 *	  Collect a block of samples using Equivalent Time Sampling (ETS)
 *    Collect samples using a rapid block capture with trigger
 *    Collect a stream of data immediately
 *    Collect a stream of data when a trigger event occurs
 *    Set Signal Generator, using standard or custom signals
 *    Change timebase & voltage scales
 *    Display data in mV or ADC counts
 *    Handle power source changes (PicoScope 34XXA/B, 32XX D/D MSO, &
 *		34XX D/D MSO devices only)
 *
 * Digital Examples (MSO variants only):
 *    Collect a block of digital samples immediately
 *    Collect a block of digital samples when a trigger event occurs
 *    Collect a block of analogue & digital samples when analogue AND digital trigger events occurs
 *    Collect a block of analogue & digital samples when analogue OR digital trigger events occurs
 *    Collect a stream of digital data immediately
 *    Collect a stream of digital data and show aggregated values
 *
 *
 *	To build this application:
 *
 *		If Microsoft Visual Studio (including Express) is being used:
 *
 *			Select the solution configuration (Debug/Release) and platform (x86/x64)
 *			Ensure that the 32-/64-bit ps3000a.lib can be located
 *			Ensure that the ps3000aApi.h and PicoStatus.h files can be located
 *
 *		Otherwise:
 *
 *			 Set up a project for a 32-/64-bit console mode application
 *			 Add this file to the project
 *			 Add 32-/64-bit ps3000a.lib to the project
 *			 Add ps3000aApi.h and PicoStatus.h to the project
 *			 Build the project
 *
 *
 * Copyright (C) 2011-2018 Pico Technology Ltd. See LICENSE file for terms.
 *
 ******************************************************************************/

//#include <stdio.h>
#include <iostream>
#include <algorithm>    // std::min, std::max
// #include <cstring> // exclude string.h... change to vector?

#include <fstream>
#include <string>


//#define __STDC_WANT_LIB_EXT1__ 1 // for scanf_s

//using namespace std;

/* Headers for Windows */
#ifdef _WIN32 			// _WIN32 Defined for applications for Win32 and Win64.
#include "windows.h"
#include <conio.h>
#include "ps3000aApi.h"


#else
#include <sys/types.h>
//#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <libps3000a-1.1/ps3000aApi.h>
#ifndef PICO_STATUS
#include <libps3000a-1.1/PicoStatus.h>
#endif

#define Sleep(a) usleep(1000*a)
#define scanf_s scanf
#define fscanf_s fscanf
#define memcpy_s(a,b,c,d) memcpy(a,c,d)





typedef enum enBOOL{FALSE,TRUE} BOOL;

// A function to detect a keyboard press on Linux
int32_t _getch()
{
	struct termios oldt, newt;
	int32_t ch;
	int32_t bytesWaiting;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	setbuf(stdin, NULL);
	do {
		ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
		if (bytesWaiting)
			getchar();
	} while (bytesWaiting);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

int32_t _kbhit()
{
	struct termios oldt, newt;
	int32_t bytesWaiting;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	setbuf(stdin, NULL);
	ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return bytesWaiting;
}

int32_t fopen_s(FILE ** a, const char * b, const char * c)
{
	FILE * fp = fopen(b,c);
	*a = fp;
	return (fp>0)?0:-1;
}

// A function to get a single character on Linux
#define max(a,b) ((a) > (b) ? a : b)
#define min(a,b) ((a) < (b) ? a : b)
#endif





#define PREF4 __stdcall

int32_t cycles = 0;

#define BUFFER_SIZE 	1024

#define QUAD_SCOPE		4
#define DUAL_SCOPE		2

// AWG Parameters

#define AWG_DAC_FREQUENCY			20e6
#define AWG_DAC_FREQUENCY_PS3207B	100e6
#define	AWG_PHASE_ACCUMULATOR		4294967296.0


// Peter. setting structure
// Its better to initialize data right here (not in the OpenDevice) using typedef:
// https://learnc.info/c/structures.html#initialization
// https://coderoad.ru/7691187/

// Peter. Change data types!!! And check them too. Esp. type of PS3000A_FALLING, char is bad type here
struct ps3000aSetting {
	int16_t percTimeShift; // delay from the frame start in percent (unused)
	uint16_t nBufferSize;// The Buffer Size (default=1024)
	int16_t nTriggerLevel;// The Trigger Level, mV (default=-100)
	PS3000A_THRESHOLD_DIRECTION bEdgeSelect;// Select of signal edge - fall/rise (default=PS3000A_FALLING) type is enPS3000AThresholdDirection
	uint16_t nWaveForms;// The Number of wave forms (default=25000)
	uint32_t timeBase;// Time base scale,  0 - 2ns, 1 - 4ns, 2 - 8ns, 3 - 16 ns, 4 - 32ns (default=1).
	// setting for the channels
	uint16_t channelRange;// The Channel range, PS3000A_50MV, ...100,200,500..., PS3000A_1V, ...5,10...PS3000A_20V (default=PS3000A_500MV)
	BOOL channelDCcoupled;// The Channel mode, DC/AC=TRUE/FALSE (default=TRUE)
	BOOL switchChannelA;// Channel A switch, on/off=TRUE/FALSE (default=TRUE)
	BOOL switchChannelB;// Channel B switch, on/off=TRUE/FALSE (default=FALSE)
} mySetting;





// Peter. change to strings?
char cFileName[30] = "Nrapidblock_average.txt"; // The name of the output file for averaging data.
char cSettingFile[20] = "piqo_setting.dat"; // The name of the setting file.
std::string settingFile("piqo_setting.ini"); // The name of the setting file.



typedef enum
{
	ANALOGUE,
	DIGITAL,
	AGGREGATED,
	MIXED
}MODE;


typedef struct
{
	int16_t DCcoupled;
	int16_t range;
	int16_t enabled;
}CHANNEL_SETTINGS;

typedef enum
{
	SIGGEN_NONE = 0,
	SIGGEN_FUNCTGEN = 1,
	SIGGEN_AWG = 2
} SIGGEN_TYPE;

typedef struct tTriggerDirections
{
	PS3000A_THRESHOLD_DIRECTION channelA;
	PS3000A_THRESHOLD_DIRECTION channelB;
	PS3000A_THRESHOLD_DIRECTION channelC;
	PS3000A_THRESHOLD_DIRECTION channelD;
	PS3000A_THRESHOLD_DIRECTION ext;
	PS3000A_THRESHOLD_DIRECTION aux;
}TRIGGER_DIRECTIONS;

typedef struct tPwq
{
	PS3000A_PWQ_CONDITIONS_V2 * conditions;
	int16_t nConditions;
	PS3000A_THRESHOLD_DIRECTION direction;
	uint32_t lower;
	uint32_t upper;
	PS3000A_PULSE_WIDTH_TYPE type;
}PWQ;

typedef struct
{
	int16_t					handle;
	int8_t					model[8];
	PS3000A_RANGE			firstRange ;
	PS3000A_RANGE			lastRange;
	int16_t					channelCount;
	int16_t					maxValue;
	int16_t					sigGen;
	int16_t					ETS;
	int32_t					AWGFileSize;
	CHANNEL_SETTINGS		channelSettings [PS3000A_MAX_CHANNELS];
	int16_t					digitalPorts;
}UNIT;

uint32_t	timebase = 8;
int16_t     oversample = 1;
BOOL		scaleVoltages = TRUE;

uint16_t inputRanges [PS3000A_MAX_RANGES] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000};

BOOL     	g_ready = FALSE;
int32_t 	g_times [PS3000A_MAX_CHANNELS] = {0, 0, 0, 0};
int16_t     g_timeUnit;
int32_t     g_sampleCount;
uint32_t	g_startIndex;
int16_t		g_autoStopped;
int16_t		g_trig = 0;
uint32_t	g_trigAt = 0;

char BlockFile[20]		= "block.txt";
char DigiBlockFile[20]	= "digiBlock.txt";
char StreamFile[20]		= "stream.txt";

typedef struct tBufferInfo
{
	UNIT * unit;
	MODE mode;
	int16_t **driverBuffers;
	int16_t **appBuffers;
	int16_t **driverDigBuffers;
	int16_t **appDigBuffers;

} BUFFER_INFO;




//****************************************************************************
//* Streaming callback
//* Used by ps3000a data streaming collection calls, on receipt of data.
//* Used to set global flags etc. checked by user routines
//****************************************************************************
void PREF4 callBackStreaming(	int16_t handle,
	int32_t		noOfSamples,
	uint32_t	startIndex,
	int16_t		overflow,
	uint32_t	triggerAt,
	int16_t		triggered,
	int16_t		autoStop,
	void		*pParameter)
{
	int32_t channel;
	BUFFER_INFO * bufferInfo = NULL;

	if (pParameter != NULL)
	{
		bufferInfo = (BUFFER_INFO *) pParameter;
	}

	// used for streaming
	g_sampleCount	= noOfSamples;
	g_startIndex	= startIndex;
	g_autoStopped	= autoStop;

	// flag to say done reading data
	g_ready = TRUE;

	// flags to show if & where a trigger has occurred
	g_trig = triggered;
	g_trigAt = triggerAt;

	if (bufferInfo != NULL && noOfSamples)
	{
		if (bufferInfo->mode == ANALOGUE)
		{
			for (channel = 0; channel < bufferInfo->unit->channelCount; channel++)
			{
				if (bufferInfo->unit->channelSettings[channel].enabled)
				{
					if (bufferInfo->appBuffers && bufferInfo->driverBuffers)
					{
						if (bufferInfo->appBuffers[channel * 2]  && bufferInfo->driverBuffers[channel * 2])
						{
							memcpy_s (&bufferInfo->appBuffers[channel * 2][startIndex], noOfSamples * sizeof(int16_t),
								&bufferInfo->driverBuffers[channel * 2][startIndex], noOfSamples * sizeof(int16_t));
						}
						if (bufferInfo->appBuffers[channel * 2 + 1] && bufferInfo->driverBuffers[channel * 2 + 1])
						{
							memcpy_s (&bufferInfo->appBuffers[channel * 2 + 1][startIndex], noOfSamples * sizeof(int16_t),
								&bufferInfo->driverBuffers[channel * 2 + 1][startIndex], noOfSamples * sizeof(int16_t));
						}
					}
				}
			}
		}
		else if (bufferInfo->mode == AGGREGATED)
		{
			for (channel = 0; channel < bufferInfo->unit->digitalPorts; channel++)
			{
				if (bufferInfo->appDigBuffers && bufferInfo->driverDigBuffers)
				{
					if (bufferInfo->appDigBuffers[channel * 2] && bufferInfo->driverDigBuffers[channel * 2])
					{
						memcpy_s (&bufferInfo->appDigBuffers[channel * 2][startIndex], noOfSamples * sizeof(int16_t),
							&bufferInfo->driverDigBuffers[channel * 2][startIndex], noOfSamples * sizeof(int16_t));
					}
					if (bufferInfo->appDigBuffers[channel * 2 + 1] && bufferInfo->driverDigBuffers[channel * 2 + 1])
					{
						memcpy_s (&bufferInfo->appDigBuffers[channel * 2 + 1][startIndex], noOfSamples * sizeof(int16_t),
							&bufferInfo->driverDigBuffers[channel * 2 + 1][startIndex], noOfSamples * sizeof(int16_t));
					}
				}
			}
		}
		else if (bufferInfo->mode == DIGITAL)
		{
			for (channel = 0; channel < bufferInfo->unit->digitalPorts; channel++)
			{
				if (bufferInfo->appDigBuffers && bufferInfo->driverDigBuffers)
				{
					if (bufferInfo->appDigBuffers[channel] && bufferInfo->driverDigBuffers[channel])
					{
						memcpy_s (&bufferInfo->appDigBuffers[channel][startIndex], noOfSamples * sizeof(int16_t),
							&bufferInfo->driverDigBuffers[channel][startIndex], noOfSamples * sizeof(int16_t));
					}
				}
			}
		}
	}
}



//****************************************************************************
//* Block Callback
//* used by ps3000a data block collection calls, on receipt of data.
//* used to set global flags etc checked by user routines
//****************************************************************************
void PREF4 callBackBlock( int16_t handle, PICO_STATUS status, void * pParameter)
{
	if (status != PICO_CANCELLED)
	{
		g_ready = TRUE;
	}
}



//****************************************************************************
//* setDefaults - restore default settings
//****************************************************************************
void setDefaults(UNIT * unit)
{
	int32_t i;
	PICO_STATUS status;

	status = ps3000aSetEts(unit->handle, PS3000A_ETS_OFF, 0, 0, NULL);	// Turn off ETS
	printf(status?"SetDefaults:ps3000aSetEts------ 0x%08x \n":"", status);

	for (i = 0; i < unit->channelCount; i++) // reset channels to most recent settings
	{
		status = ps3000aSetChannel(unit->handle, (PS3000A_CHANNEL)(PS3000A_CHANNEL_A + i),
			unit->channelSettings[PS3000A_CHANNEL_A + i].enabled,
			(PS3000A_COUPLING)unit->channelSettings[PS3000A_CHANNEL_A + i].DCcoupled,
			(PS3000A_RANGE)unit->channelSettings[PS3000A_CHANNEL_A + i].range, 0);

		printf(status?"SetDefaults:ps3000aSetChannel------ 0x%08x \n":"", status);
	}
}



// Peter. USELESS FUNCTIONS FOR PS3206A - setdigital, disable analogue, restoreAnalogue,


//****************************************************************************
//* setDigitals - enable or disable Digital Channels
//****************************************************************************
PICO_STATUS setDigitals(UNIT *unit, int16_t state)
{
	PICO_STATUS status;

	int16_t logicLevel;
	float logicVoltage = 1.5;
	int16_t maxLogicVoltage = 5;

	//int16_t timebase = 1;
	int16_t port;


	// Set logic threshold
	logicLevel =  (int16_t) ((logicVoltage / maxLogicVoltage) * PS3000A_MAX_LOGIC_LEVEL);

	// Enable Digital ports
	for (port = PS3000A_DIGITAL_PORT0; port <= PS3000A_DIGITAL_PORT1; port++)
	{
		status = ps3000aSetDigitalPort(unit->handle, (PS3000A_DIGITAL_PORT)port, state, logicLevel);
		printf(status?"SetDigitals:PS3000ASetDigitalPort(Port 0x%X) ------ 0x%08x \n":"", port, status);
	}

	return status;
}


// Peter. Useleff function for 3026A

//****************************************************************************
//* disableAnalogue - Disable Analogue Channels
//****************************************************************************
PICO_STATUS disableAnalogue(UNIT *unit)
{
	PICO_STATUS status{0};
	int16_t ch;

	// Turn off analogue channels, keeping settings
	for (ch = 0; ch < unit->channelCount; ch++)
	{
		unit->channelSettings[ch].enabled = FALSE;

		status = ps3000aSetChannel(unit->handle, (PS3000A_CHANNEL) ch, unit->channelSettings[ch].enabled, (PS3000A_COUPLING) unit->channelSettings[ch].DCcoupled,
			(PS3000A_RANGE) unit->channelSettings[ch].range, 0);

		if(status != PICO_OK)
		{
			printf("disableAnalogue:ps3000aSetChannel(channel %d) ------ 0x%08x \n", ch, status);
		}
	}
	return status;
}

//****************************************************************************
//* restoreAnalogueSettings - Restores Analogue Channel settings
//****************************************************************************
PICO_STATUS restoreAnalogueSettings(UNIT *unit)
{
	PICO_STATUS status{0};
	int16_t ch;

	// Turn on analogue channels using previous settings
	for (ch = 0; ch < unit->channelCount; ch++)
	{
		status = ps3000aSetChannel(unit->handle, (PS3000A_CHANNEL) ch, unit->channelSettings[ch].enabled, (PS3000A_COUPLING) unit->channelSettings[ch].DCcoupled,
			(PS3000A_RANGE) unit->channelSettings[ch].range, 0);

		if(status != PICO_OK)
		{
			printf("restoreAnalogueSettings:ps3000aSetChannel(channel %d) ------ 0x%08x \n", ch, status);
		}
	}
	return status;
}


//****************************************************************************
//* adc_to_mv
//* Convert an 16-bit ADC count into millivolts
//****************************************************************************
int32_t adc_to_mv(int32_t raw, int32_t ch, UNIT * unit)
{
	return (raw * inputRanges[ch]) / unit->maxValue;
}


// Peter. My function, used in  BlockDataHandler etc instead of  adc_to_mv... check later

double dAdc_to_mv(double dRaw, int ch, UNIT * unit)
{
    return (dRaw * (double)inputRanges[ch]) / unit->maxValue;
}





//****************************************************************************
//* mv_to_adc
//*
//* Convert a millivolt value into a 16-bit ADC count
//*
//*  (useful for setting trigger thresholds)
//****************************************************************************
int16_t mv_to_adc(int16_t mv, int16_t ch, UNIT * unit)
{
	return (mv * unit->maxValue) / inputRanges[ch];
}




// Peter. USELESS FUNCTION FOR PS3206A

//****************************************************************************************
//* changePowerSource - function to handle switches between +5 V supply, and USB-only power
//* Only applies to PicoScope 34xxA/B/D/D MSO units
//******************************************************************************************
PICO_STATUS changePowerSource(int16_t handle, PICO_STATUS status)
{
	char ch;

	switch (status)
	{
		case PICO_POWER_SUPPLY_NOT_CONNECTED:			// User must acknowledge they want to power via USB

			do
			{
				printf("\n5 V power supply not connected");
				printf("\nDo you want to run using USB only Y/N?\n");
				ch = toupper(_getch());
				if(ch == 'Y')
				{
					printf("\nPowering the unit via USB\n");
					status = ps3000aChangePowerSource(handle, PICO_POWER_SUPPLY_NOT_CONNECTED);		// Tell the driver that's ok

					if (status == PICO_POWER_SUPPLY_UNDERVOLTAGE)
					{
						status = changePowerSource(handle, status);
					}
				}
			}
			while(ch != 'Y' && ch != 'N');

			printf(ch == 'N'?"Please use the +5 V power supply to power this unit\n":"");
			break;

		case PICO_POWER_SUPPLY_CONNECTED:

			printf("\nUsing +5V power supply voltage\n");
			status = ps3000aChangePowerSource(handle, PICO_POWER_SUPPLY_CONNECTED);	// Tell the driver we are powered from +5 V supply
			break;

		case PICO_USB3_0_DEVICE_NON_USB3_0_PORT:

			printf("\nUSB 3.0 device on non-USB 3.0 port.\n");
			status = ps3000aChangePowerSource(handle, PICO_USB3_0_DEVICE_NON_USB3_0_PORT);	// Tell the driver that it is ok for the device to be on a non-USB 3.0 port

			break;

		case PICO_POWER_SUPPLY_UNDERVOLTAGE:

			do
			{
				printf("\nUSB not supplying required voltage");
				printf("\nPlease plug in the +5 V power supply\n");
				printf("\nHit any key to continue, or Esc to exit...\n");
				ch = _getch();

				if (ch == 0x1B)	// ESC key
				{
					exit(0);
				}
				else
				{
					status = ps3000aChangePowerSource(handle, PICO_POWER_SUPPLY_CONNECTED);		// Tell the driver that's ok
				}
			}
			while (status == PICO_POWER_SUPPLY_REQUEST_INVALID);
			break;

	}
	return status;
}



// Peter. New function, setDataBuffers was earlier only

//****************************************************************************
//* clearDataBuffers
//*
//* stops GetData writing values to memory that has been released
//****************************************************************************
PICO_STATUS clearDataBuffers(UNIT * unit)
{
	int32_t i;
	PICO_STATUS status{0};

	for (i = 0; i < unit->channelCount; i++)
	{
		if((status = ps3000aSetDataBuffers(unit->handle, (PS3000A_CHANNEL) i, NULL, NULL, 0, 0, PS3000A_RATIO_MODE_NONE)) != PICO_OK)
		{
			printf("ClearDataBuffers:ps3000aSetDataBuffers(channel %d) ------ 0x%08x \n", i, status);
		}
	}


	for (i= 0; i < unit->digitalPorts; i++)
	{
		if((status = ps3000aSetDataBuffer(unit->handle, (PS3000A_CHANNEL) (i + PS3000A_DIGITAL_PORT0), NULL, 0, 0, PS3000A_RATIO_MODE_NONE))!= PICO_OK)
		{
			printf("ClearDataBuffers:ps3000aSetDataBuffer(port 0x%X) ------ 0x%08x \n", i + PS3000A_DIGITAL_PORT0, status);
		}
	}

	return status;
}

//****************************************************************************
//* blockDataHandler
//* - Used by all block data routines
//* - acquires data (user sets trigger mode before calling), displays 10 items
//*   and saves all to block.txt
//* Input :
//* - unit : the unit to use.
//* - text : the text to display before the display of data slice
//* - offset : the offset into the data buffer to start the display's slice.
//****************************************************************************
void blockDataHandler(UNIT * unit, const char * text, int32_t offset, MODE mode)
{
	int16_t retry;
	int16_t bit;

	uint16_t bitValue;
	uint16_t digiValue;

	int16_t * buffers[PS3000A_MAX_CHANNEL_BUFFERS];
	int16_t * digiBuffer[PS3000A_MAX_DIGITAL_PORTS];

	int32_t i, j;
	int32_t timeInterval;
	int32_t sampleCount = BUFFER_SIZE;
	int32_t maxSamples;
	int32_t timeIndisposed;

	FILE * fp = NULL;
	FILE * digiFp = NULL;

	PICO_STATUS status;
	PS3000A_RATIO_MODE ratioMode = PS3000A_RATIO_MODE_NONE;

	if (mode == ANALOGUE || mode == MIXED)		// Analogue or (MSO Only) MIXED
	{
		for (i = 0; i < unit->channelCount; i++)
		{
			if(unit->channelSettings[i].enabled)
			{
				buffers[i * 2] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
				buffers[i * 2 + 1] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

				status = ps3000aSetDataBuffers(unit->handle, (PS3000A_CHANNEL)i, buffers[i * 2], buffers[i * 2 + 1], sampleCount, 0, ratioMode);

				printf(status?"BlockDataHandler:ps3000aSetDataBuffers(channel %d) ------ 0x%08x \n":"", i, status);
			}
		}
	}

	if (mode == DIGITAL || mode == MIXED)		// (MSO Only) Digital or MIXED
	{
		for (i= 0; i < unit->digitalPorts; i++)
		{
			digiBuffer[i] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

			status = ps3000aSetDataBuffer(unit->handle, (PS3000A_CHANNEL) (i + PS3000A_DIGITAL_PORT0), digiBuffer[i], sampleCount, 0, ratioMode);

			printf(status?"BlockDataHandler:ps3000aSetDataBuffer(port 0x%X) ------ 0x%08x \n":"", i + PS3000A_DIGITAL_PORT0, status);
		}
	}

	// Find the maximum number of samples and the time interval (in nanoseconds)
	while (ps3000aGetTimebase(unit->handle, timebase, sampleCount, &timeInterval, oversample, &maxSamples, 0))
	{
		timebase++;
	}

	printf("\nTimebase: %u  Sample interval: %d ns \n", timebase, timeInterval);

	// Start the device collecting, then wait for completion
	g_ready = FALSE;


	do
	{
		retry = 0;

		status = ps3000aRunBlock(unit->handle, 0, sampleCount, timebase, oversample, &timeIndisposed, 0, callBackBlock, NULL);

		if (status != PICO_OK)
		{
			if (status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED ||
				status == PICO_POWER_SUPPLY_UNDERVOLTAGE)       // PicoScope 340XA/B/D/D MSO devices...+5 V PSU connected or removed
			{
				status = changePowerSource(unit->handle, status);
				retry = 1;
			}
			else
			{
//				printf("BlockDataHandler:ps3000aRunBlock ------ 0x%08lx \n", status);
				return;
			}
		}
	}
	while (retry);

	printf("Waiting for trigger...Press a key to abort\n");

	while (!g_ready && !_kbhit())
	{
		Sleep(0);
	}

	if (g_ready)
	{
		status = ps3000aGetValues(unit->handle, 0, (uint32_t*) &sampleCount, 1, ratioMode, 0, NULL);

		if (status != PICO_OK)
		{
			if (status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED || status == PICO_POWER_SUPPLY_UNDERVOLTAGE)
			{
				if (status == PICO_POWER_SUPPLY_UNDERVOLTAGE)
				{
					changePowerSource(unit->handle, status);
				}
				else
				{
					printf("\nPower Source Changed. Data collection aborted.\n");
				}
			}
			else
			{
//				printf("BlockDataHandler:ps3000aGetValues ------ 0x%08lx \n", status);
			}
		}
		else
		{
			// Print out the first 10 readings, converting the readings to mV if required
			printf("%s\n",text);

			if (mode == ANALOGUE || mode == MIXED)		// If we are capturing analogue or MIXED (analogue + digital) data
			{
				printf("Channels are in %s\n\n", ( scaleVoltages ) ? ("mV") : ("ADC Counts"));

				for (j = 0; j < unit->channelCount; j++)
				{
					if (unit->channelSettings[j].enabled)
					{
						printf("Channel %c:    ", 'A' + j);
					}
				}

				printf("\n");
			}

			if (mode == DIGITAL || mode == MIXED)	// If we are capturing digital or MIXED data
			{
				printf("Digital\n");
			}

			printf("\n");

			for (i = offset; i < offset+10; i++)
			{
				if (mode == ANALOGUE || mode == MIXED)	// If we are capturing analogue or MIXED data
				{
					for (j = 0; j < unit->channelCount; j++)
					{
						if (unit->channelSettings[j].enabled)
						{
							printf("  %d     ", scaleVoltages ?
								adc_to_mv(buffers[j * 2][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit)	// If scaleVoltages, print mV value
								: buffers[j * 2][i]);																	// else print ADC Count
						}
					}
				}
				if (mode == DIGITAL || mode == MIXED)	// If we're doing digital or MIXED
				{
					digiValue = 0x00ff & digiBuffer[1][i];	// Mask Port 1 values to get lower 8 bits
					digiValue <<= 8;						// Shift by 8 bits to place in upper 8 bits of 16-bit word
					digiValue |= digiBuffer[0][i];			// Mask Port 0 values to get lower 8 bits and apply bitwise inclusive OR to combine with Port 1 values
					printf("0x%04X", digiValue);

				}
				printf("\n");
			}

			if (mode == ANALOGUE || mode == MIXED)		// If we're doing analogue or MIXED
			{
				sampleCount = std::min(sampleCount, BUFFER_SIZE);

				fopen_s(&fp, BlockFile, "w");

				if (fp != NULL)
				{
					fprintf(fp, "Block Data log\n\n");
					fprintf(fp,"Results shown for the %d Channels.\n",unit->channelCount);
//					fprintf(fp,"Maximum Aggregated value ADC Count & mV, Minimum Aggregated value ADC Count & mV\n\n");

					fprintf(fp, "Time");

					for (i = 0; i < unit->channelCount; i++)
					{
						if (unit->channelSettings[i].enabled)
						{
							fprintf(fp,"  Voltage");
						}
					}
					fprintf(fp,"\n");

					fprintf(fp,	"ns");


					for (i = 0; i < unit->channelCount; i++)
					{
						if (unit->channelSettings[i].enabled)
						{
							fprintf(fp,"		mV");
						}
					}
					fprintf(fp,"\n");





					for (i = 0; i < sampleCount; i++)
					{
						fprintf(fp, "%d ", g_times[0] + (int32_t)(i * timeInterval));

						for (j = 0; j < unit->channelCount; j++)
						{
							if (unit->channelSettings[j].enabled)
							{

								fprintf(	fp, "  %+d", adc_to_mv(buffers[j * 2][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit));
//								fprintf(	fp,
//									"Ch%C  %d = %+dmV, %d = %+dmV   ",
//									'A' + j,
//									buffers[j * 2][i],
//									adc_to_mv(buffers[j * 2][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit),
//									buffers[j * 2 + 1][i],
//									adc_to_mv(buffers[j * 2 + 1][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit));
							}
						}
						fprintf(fp, "\n");
					}
				}
				else
				{
					printf(	"Cannot open the file %s for writing.\n"
						"Please ensure that you have permission to access.\n", BlockFile);
				}
			}

			// Output digital values to separate file
			if (mode == DIGITAL || mode == MIXED)
			{
				fopen_s(&digiFp, DigiBlockFile, "w");

				if (digiFp != NULL)
				{
					fprintf(digiFp, "Block Digital Data log\n");
					fprintf(digiFp, "Digital Channels will be in the order D15...D0\n");

					fprintf(digiFp, "\n");

					for (i = 0; i < sampleCount; i++)
					{
						digiValue = 0x00ff & digiBuffer[1][i];	// Mask Port 1 values to get lower 8 bits
						digiValue <<= 8;						// Shift by 8 bits to place in upper 8 bits of 16-bit word
						digiValue |= digiBuffer[0][i];			// Mask Port 0 values to get lower 8 bits and apply bitwise inclusive OR to combine with Port 1 values

						// Output data in binary form
						for (bit = 0; bit < 16; bit++)
						{
							// Shift value (32768 - binary 1000 0000 0000 0000), AND with value to get 1 or 0 for channel
							// Order will be D15 to D8, then D7 to D0

							bitValue = (0x8000 >> bit) & digiValue? 1 : 0;
							fprintf(digiFp, "%d, ", bitValue);
						}

						fprintf(digiFp, "\n");

					}
				}
			}

		}
	}
	else
	{
		printf("\nData collection aborted.\n");
		_getch();
	}

	if ((status = ps3000aStop(unit->handle)) != PICO_OK)
	{
		printf("BlockDataHandler:ps3000aStop ------ 0x%08x \n", status);
	}

	if (fp != NULL)
	{
		fclose(fp);
	}

	if (digiFp != NULL)
	{
		fclose(digiFp);
	}

	if (mode == ANALOGUE || mode == MIXED)		// Only if we allocated these buffers
	{
		for (i = 0; i < unit->channelCount; i++)
		{
			if(unit->channelSettings[i].enabled)
			{
				free(buffers[i * 2]);
				free(buffers[i * 2 + 1]);

			}
		}
	}

	if (mode == DIGITAL || mode == MIXED)		// Only if we allocated these buffers
	{
		for (i = 0; i < unit->digitalPorts; i++)
		{
			free(digiBuffer[i]);
		}
	}

	clearDataBuffers(unit);
}



// Peter. We did not use next function, but need if stream functions are used

//****************************************************************************
//* Stream Data Handler
//* - Used by the two stream data examples - untriggered and triggered
//* Inputs:
//* - unit - the unit to sample on
//* - preTrigger - the number of samples in the pre-trigger phase
//*					(0 if no trigger has been set)
//***************************************************************************
void streamDataHandler(UNIT * unit, uint32_t preTrigger, MODE mode)
{
	int16_t autostop;
	int16_t retry = 0;
	int16_t powerChange = 0;

	uint16_t portValue, portValueOR, portValueAND;

	int32_t i, j;
	int32_t bit;
	int32_t index = 0;
	int32_t totalSamples;

	uint32_t postTrigger;
	uint32_t sampleCount = 100000; // Make sure buffer large enough
	uint32_t sampleInterval;
	uint32_t downsampleRatio;
	uint32_t triggeredAt = 0;

	int16_t * buffers[PS3000A_MAX_CHANNEL_BUFFERS];
	int16_t * appBuffers[PS3000A_MAX_CHANNEL_BUFFERS];
	int16_t * digiBuffers[PS3000A_MAX_DIGITAL_PORTS];
	int16_t * appDigiBuffers[PS3000A_MAX_DIGITAL_PORTS];

	PICO_STATUS status;

	PS3000A_TIME_UNITS timeUnits;
	PS3000A_RATIO_MODE ratioMode;

	BUFFER_INFO bufferInfo;
	FILE * fp = NULL;


	if (mode == ANALOGUE)		// Analogue - collect raw data
	{
		for (i = 0; i < unit->channelCount; i++)
		{
			if(unit->channelSettings[i].enabled)
			{
				buffers[i * 2] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
				buffers[i * 2 + 1] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

				status = ps3000aSetDataBuffers(unit->handle, (PS3000A_CHANNEL)i, buffers[i * 2], buffers[i * 2 + 1], sampleCount, 0, PS3000A_RATIO_MODE_NONE);

				appBuffers[i * 2] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
				appBuffers[i * 2 + 1] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

				printf(status ? "StreamDataHandler:ps3000aSetDataBuffers(channel %d) ------ 0x%08x \n":"", i, status);
			}
		}

		downsampleRatio = 1;
		timeUnits = PS3000A_US;
		sampleInterval = 10;
		ratioMode = PS3000A_RATIO_MODE_NONE;
		postTrigger = 1000000;
		autostop = TRUE;
	}

	bufferInfo.unit = unit;
	bufferInfo.mode = mode;
	bufferInfo.driverBuffers = buffers;
	bufferInfo.appBuffers = appBuffers;
	bufferInfo.driverDigBuffers = digiBuffers;
	bufferInfo.appDigBuffers = appDigiBuffers;

	if (mode == AGGREGATED)		// (MSO Only) AGGREGATED
	{
		for (i= 0; i < unit->digitalPorts; i++)
		{
			digiBuffers[i * 2] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
			digiBuffers[i * 2 + 1] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

			status = ps3000aSetDataBuffers(unit->handle, (PS3000A_CHANNEL) (i + PS3000A_DIGITAL_PORT0), digiBuffers[i * 2], digiBuffers[i * 2 + 1], sampleCount, 0, PS3000A_RATIO_MODE_AGGREGATE);

			appDigiBuffers[i * 2] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
			appDigiBuffers[i * 2 + 1] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

			printf(status?"StreamDataHandler:ps3000aSetDataBuffer(channel %d) ------ 0x%08x \n":"", i, status);
		}

		downsampleRatio = 10;
		timeUnits = PS3000A_MS;
		sampleInterval = 10;
		ratioMode = PS3000A_RATIO_MODE_AGGREGATE;
		postTrigger = 10;
		autostop = FALSE;
	}

	if (mode == DIGITAL)		// (MSO Only) Digital
	{
		for (i= 0; i < unit->digitalPorts; i++)
		{
			digiBuffers[i] = (int16_t*) calloc(sampleCount, sizeof(int16_t));
			status = ps3000aSetDataBuffer(unit->handle, (PS3000A_CHANNEL) (i + PS3000A_DIGITAL_PORT0), digiBuffers[i], sampleCount, 0, PS3000A_RATIO_MODE_NONE);

			appDigiBuffers[i] = (int16_t*) calloc(sampleCount, sizeof(int16_t));

			printf(status?"StreamDataHandler:ps3000aSetDataBuffer(channel %d) ------ 0x%08x \n":"", i, status);
		}

		downsampleRatio = 1;
		timeUnits = PS3000A_MS;
		sampleInterval = 10;
		ratioMode = PS3000A_RATIO_MODE_NONE;
		postTrigger = 10;
		autostop = FALSE;
	}

	if (autostop)
	{
		printf("\nStreaming Data for %u samples", postTrigger / downsampleRatio);

		if (preTrigger)	// we pass 0 for preTrigger if we're not setting up a trigger
		{
			printf(" after the trigger occurs\nNote: %u Pre Trigger samples before Trigger arms\n\n", preTrigger / downsampleRatio);
		}
		else
		{
			printf("\n\n");
		}
	}
	else
	{
		printf("\nStreaming Data continually.\n\n");
	}

	g_autoStopped = FALSE;

	do
	{
		retry = 0;

		status = ps3000aRunStreaming(unit->handle, &sampleInterval, timeUnits, preTrigger, postTrigger, autostop, downsampleRatio,
			ratioMode, sampleCount);

		if(status != PICO_OK)
		{
			if(status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED || status == PICO_POWER_SUPPLY_UNDERVOLTAGE)
			{
				status = changePowerSource(unit->handle, status);
				retry = 1;
			}
			else
			{
				printf("StreamDataHandler:ps3000aRunStreaming ------ 0x%08x \n", status);
				return;
			}
		}
	}
	while(retry);

	printf("Streaming data...Press a key to stop\n");

	if (mode == ANALOGUE)
	{
		fopen_s(&fp, StreamFile, "w");

		if (fp != NULL)
		{
			fprintf(fp,"For each of the %d Channels, results shown are....\n",unit->channelCount);
//			fprintf(fp,"Maximum Aggregated value ADC Count & mV, Minimum Aggregated value ADC Count & mV\n\n");
			fprintf(fp,"Maximum Aggregated value mV, Minimum Aggregated value mV\n\n");

			for (i = 0; i < unit->channelCount; i++)
			{
				if (unit->channelSettings[i].enabled)
				{
//					fprintf(fp,"Ch  Max ADC  Max mV  Min ADC  Min mV   ");
					fprintf(fp,"Ch   Max mV   Min mV   ");
				}
			}
			fprintf(fp, "\n");
		}
	}

	totalSamples = 0;

	while (!_kbhit() && !g_autoStopped)
	{
		// Register callback function with driver and check if data has been received
		g_ready = FALSE;

		status = ps3000aGetStreamingLatestValues(unit->handle, callBackStreaming, &bufferInfo);

		if (status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED ||
			status == PICO_POWER_SUPPLY_UNDERVOLTAGE) // PicoScope 340XA/B/D/D MSO devices...+5 V PSU connected or removed
		{
			if (status == PICO_POWER_SUPPLY_UNDERVOLTAGE)
			{
				changePowerSource(unit->handle, status);
			}
			printf("\n\nPower Source Change");
			powerChange = 1;
		}

		index ++;

		if (g_ready && g_sampleCount > 0) // can be ready and have no data, if autoStop has fired
		{
			if (g_trig)
			{
				triggeredAt = totalSamples + g_trigAt;		// calculate where the trigger occurred in the total samples collected
			}

			totalSamples += g_sampleCount;

			printf("\nCollected %i samples, index = %u, Total: %d samples ", g_sampleCount, g_startIndex, totalSamples);

			if (g_trig)
			{
				printf("Trig. at index %u", triggeredAt);	// show where trigger occurred
			}

			for (i = g_startIndex; i < (int32_t)(g_startIndex + g_sampleCount); i++)
			{
				if (mode == ANALOGUE)
				{
					if(fp != NULL)
					{
						for (j = 0; j < unit->channelCount; j++)
						{
							if (unit->channelSettings[j].enabled)
							{

// Peter. Add timescale here... sometimes.
								fprintf(	fp,
//									"Ch%C  %d = %+dmV, %d = %+dmV   ",
									"Ch%C   %+d mV,  %+d mV   ",
									(char)('A' + j),
//									appBuffers[j * 2][i],
									adc_to_mv(appBuffers[j * 2][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit),
//									appBuffers[j * 2 + 1][i],
									adc_to_mv(appBuffers[j * 2 + 1][i], unit->channelSettings[PS3000A_CHANNEL_A + j].range, unit));
							}
						}

						fprintf(fp, "\n");
					}
					else
					{
						printf("Cannot open the file %s for writing.\n", StreamFile);
					}
				}

				if (mode == DIGITAL)
				{
					portValue = 0x00ff & appDigiBuffers[1][i];	// Mask Port 1 values to get lower 8 bits
					portValue <<= 8;							// Shift by 8 bits to place in upper 8 bits of 16-bit word
					portValue |= 0x00ff & appDigiBuffers[0][i]; // Mask Port 0 values to get lower 8 bits and apply bitwise inclusive OR to combine with Port 1 values

					printf("\nIndex=%04u: Value = 0x%04X  =  ", i, portValue);

					// Shift value (32768 - binary 1000 0000 0000 0000), AND with value to get 1 or 0 for channel
					// Order will be D15 to D8, then D7 to D0
					for (bit = 0; bit < 16; bit++)
					{
						printf( (0x8000 >> bit) & portValue? "1 " : "0 ");
					}
				}

				if (mode == AGGREGATED)
				{
					portValueOR = 0x00ff & appDigiBuffers[2][i];
					portValueOR <<= 8;
					portValueOR |= 0x00ff & appDigiBuffers[0][i];

					portValueAND = 0x00ff & appDigiBuffers[3][i];
					portValueAND <<= 8;
					portValueAND |= 0x00ff & appDigiBuffers[1][i];

					printf("\nIndex=%04u: Bitwise  OR of last %d readings = 0x%04X ", i,  downsampleRatio, portValueOR);
					printf("\nIndex=%04u: Bitwise AND of last %d readings = 0x%04X ", i,  downsampleRatio, portValueAND);
				}
			}
		}
	}

	ps3000aStop(unit->handle);

	if (!g_autoStopped && !powerChange)
	{
		printf("\nData collection aborted.\n");
		_getch();
	}

	if(fp != NULL)
	{
		fclose(fp);
	}

	if (mode == ANALOGUE)		// Only if we allocated these buffers
	{
		for (i = 0; i < unit->channelCount; i++)
		{
			if(unit->channelSettings[i].enabled)
			{
				free(buffers[i * 2]);
				free(buffers[i * 2 + 1]);

				free(appBuffers[i * 2]);
				free(appBuffers[i * 2 + 1]);
			}
		}
	}

	if (mode == DIGITAL) 		// Only if we allocated these buffers
	{
		for (i = 0; i < unit->digitalPorts; i++)
		{
			free(digiBuffers[i]);
			free(appDigiBuffers[i]);
		}

	}

	if (mode == AGGREGATED) 		// Only if we allocated these buffers
	{
		for (i = 0; i < unit->digitalPorts * 2; i++)
		{
			free(digiBuffers[i]);
			free(appDigiBuffers[i]);
		}
	}

	clearDataBuffers(unit);
}


// Peter. We can change trigger only from setting txt file. Its better to move it to main menue

//****************************************************************************
//* setTrigger
//*
//* - Used to call all the functions required to set up triggering
//*
//***************************************************************************
PICO_STATUS setTrigger(	UNIT * unit,

						struct tPS3000ATriggerChannelProperties * channelProperties,
							int16_t nChannelProperties,
							PS3000A_TRIGGER_CONDITIONS_V2 * triggerConditionsV2,
							int16_t nTriggerConditions,
							TRIGGER_DIRECTIONS * directions,

						struct tPwq * pwq,
							uint32_t delay,
							int16_t auxOutputEnabled,
							int32_t autoTriggerMs,
							PS3000A_DIGITAL_CHANNEL_DIRECTIONS * digitalDirections,
							int16_t nDigitalDirections)
{
	PICO_STATUS status;

	if ((status = ps3000aSetTriggerChannelProperties(unit->handle,
		channelProperties,
		nChannelProperties,
		auxOutputEnabled,
		autoTriggerMs)) != PICO_OK)
	{
		printf("SetTrigger:ps3000aSetTriggerChannelProperties ------ Ox%08x \n", status);
		printf("SetTrigger:ps3000aSetTriggerChannelProperties ------ Ox%08x \n", status);
		return status;
	}

	if ((status = ps3000aSetTriggerChannelConditionsV2(unit->handle, triggerConditionsV2, nTriggerConditions)) != PICO_OK)
	{
		printf("SetTrigger:ps3000aSetTriggerChannelConditions ------ 0x%08x \n", status);
		return status;
	}

	if ((status = ps3000aSetTriggerChannelDirections(unit->handle,
		directions->channelA,
		directions->channelB,
		directions->channelC,
		directions->channelD,
		directions->ext,
		directions->aux)) != PICO_OK)
	{
		printf("SetTrigger:ps3000aSetTriggerChannelDirections ------ 0x%08x \n", status);
		return status;
	}

	if ((status = ps3000aSetTriggerDelay(unit->handle, delay)) != PICO_OK)
	{
		printf("SetTrigger:ps3000aSetTriggerDelay ------ 0x%08x \n", status);
		return status;
	}

	if((status = ps3000aSetPulseWidthQualifierV2(unit->handle,
		pwq->conditions,
		pwq->nConditions,
		pwq->direction,
		pwq->lower,
		pwq->upper,
		pwq->type)) != PICO_OK)
	{
		printf("SetTrigger:ps3000aSetPulseWidthQualifier ------ 0x%08x \n", status);
		return status;
	}

	if (unit->digitalPorts)
	{
		if((status = ps3000aSetTriggerDigitalPortProperties(unit->handle, digitalDirections, nDigitalDirections)) != PICO_OK)
		{
			printf("SetTrigger:ps3000aSetTriggerDigitalPortProperties ------ 0x%08x \n", status); //
			return status;
		}
	}
	return status;
}

//****************************************************************************
//* collectBlockImmediate
//*  this function demonstrates how to collect a single block of data
//*  from the unit (start collecting immediately)
//****************************************************************************
void collectBlockImmediate(UNIT * unit)
{
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	memset(&directions, 0, sizeof(struct tTriggerDirections));
	memset(&pulseWidth, 0, sizeof(struct tPwq));

	printf("Collect block immediate...\n");
	printf("Press a key to start\n");
	_getch();

	setDefaults(unit);

	// Trigger disabled
	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, 0, 0);


	// Peter. В чем смысл передавать текст про 10 измерений, если там в функции blockDataHandler число "10" прописано и так? Можно текст прямо там вписать.

	blockDataHandler(unit, "\nFirst 10 readings:\n", 0, ANALOGUE);
}



// Peter. We not use next function

//****************************************************************************
//* collectBlockEts
//*  this function demonstrates how to collect a block of
//*  data using equivalent time sampling (ETS).
//****************************************************************************
void collectBlockEts(UNIT * unit)
{
	//PICO_STATUS status;
	int32_t ets_sampletime;
	int16_t	triggerVoltage = mv_to_adc((int16_t)mySetting.nTriggerLevel,	unit->channelSettings[PS3000A_CHANNEL_A].range, unit);
	uint32_t delay = 0;
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	struct tPS3000ATriggerChannelProperties sourceDetails = {	triggerVoltage,
																256 * 10,
																triggerVoltage,
																256 * 10,
																PS3000A_CHANNEL_A,
																PS3000A_LEVEL };

	struct tPS3000ATriggerConditionsV2 conditions = {	PS3000A_CONDITION_TRUE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE };


	memset(&pulseWidth, 0, sizeof(struct tPwq));
	memset(&directions, 0, sizeof(struct tTriggerDirections));
	directions.channelA = PS3000A_RISING;

	printf("Collect ETS block...\n");

	printf("Collects when value rises past %d", scaleVoltages?
		adc_to_mv(sourceDetails.thresholdUpper,	unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print mV value
		: sourceDetails.thresholdUpper);																// else print ADC Count

	printf(scaleVoltages? "mV\n" : "ADC Counts\n");
	printf("Press a key to start...\n");
	_getch();

	setDefaults(unit);

	// Trigger enabled
	// Rising edge
	// Threshold = 1000mV
	setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, delay, 0, 0, 0, 0);
	//status = setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, delay, 0, 0, 0, 0);

	ps3000aSetEts(unit->handle, PS3000A_ETS_FAST, 20, 4, &ets_sampletime);
	//status = ps3000aSetEts(unit->handle, PS3000A_ETS_FAST, 20, 4, &ets_sampletime);
	printf("ETS Sample Time is: %i\n", ets_sampletime); // %ld

	blockDataHandler(unit, "Ten readings after trigger:\n", BUFFER_SIZE / 10 - 5, ANALOGUE); // 10% of data is pre-trigger

	ps3000aSetEts(unit->handle, PS3000A_ETS_OFF, 0, 0, &ets_sampletime);
	//status = ps3000aSetEts(unit->handle, PS3000A_ETS_OFF, 0, 0, &ets_sampletime);
}


//****************************************************************************
//* collectBlockTriggered
//*  this function demonstrates how to collect a single block of data from the
//*  unit, when a trigger event occurs.
//****************************************************************************
void collectBlockTriggered(UNIT * unit)
{

	int16_t triggerVoltage = mv_to_adc((int16_t)mySetting.nTriggerLevel, unit->channelSettings[PS3000A_CHANNEL_A].range, unit);

	struct tPS3000ATriggerChannelProperties sourceDetails = {	triggerVoltage,
																256 * 10,
																triggerVoltage,
																256 * 10,
																PS3000A_EXTERNAL, // There was "PS3000A_CHANNEL_A" in original file, but we use External input to synchronize. PS3000A_CHANNEL_A,
																PS3000A_LEVEL};

	struct tPS3000ATriggerConditionsV2 conditions = {	PS3000A_CONDITION_DONT_CARE, // It is channelA, there was "PS3000A_CONDITION_TRUE" PS3000A_CONDITION_TRUE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_TRUE, // this is External input PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE,
														PS3000A_CONDITION_DONT_CARE};

	struct tPwq pulseWidth;

	struct tTriggerDirections directions = {	PS3000A_RISING,
												PS3000A_NONE,
												PS3000A_NONE,
												PS3000A_NONE,
												mySetting.bEdgeSelect, //this is External input PS3000A_NONE,
												PS3000A_NONE };

	memset(&pulseWidth, 0, sizeof(struct tPwq));

	printf("Collect block triggered...\n");
	printf("Collects when value rises past %d", scaleVoltages?
		adc_to_mv(sourceDetails.thresholdUpper, unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print mV value
		: sourceDetails.thresholdUpper);																// else print ADC Count

	printf(scaleVoltages?"mV\n" : "ADC Counts\n");

	printf("Press a key to start...\n");
	_getch();

	setDefaults(unit);

	//* Trigger enabled
	//* Rising edge
	//* Threshold = 1000mV
	setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	blockDataHandler(unit, "Ten readings after trigger:\n", 0, ANALOGUE);
}





//****************************************************************************
//* collectRapidBlock
//*  this function demonstrates how to collect a set of captures using
//*  rapid block mode.
//****************************************************************************
void collectRapidBlock(UNIT * unit, uint32_t nBlocks)
{
//	int16_t i;
	int16_t retry; // what the purpose? power supply checking
	int16_t channel;
	int16_t *overflow;
	int16_t ***rapidBuffers;

	int32_t nMaxSamples;
	int32_t timeIndisposed;
	int32_t timeIntervalNs;
	int32_t maxSamples;

//	uint32_t nSegments; // кажется ненужная переменная
	auto nCaptures = mySetting.nWaveForms;  // default = 25000
//	uint32_t capture;
	uint32_t nSamples = mySetting.nBufferSize; // The Buffer Size (default=1024)
	uint32_t nCompletedCaptures;
	uint32_t maxSegments;

	PICO_STATUS status;

// Peter. Do we need B channel for triggering?

	// Set level trigger on Channel A. Why? We need set trigger on Trig!

	int16_t	triggerVoltage = mv_to_adc((int16_t)mySetting.nTriggerLevel, unit->channelSettings[PS3000A_CHANNEL_A].range, unit);

	struct tPS3000ATriggerChannelProperties sourceDetails = {	triggerVoltage,
		256 * 10,
		triggerVoltage,
		256 * 10,
		PS3000A_EXTERNAL, //PS3000A_CHANNEL_A,
		PS3000A_LEVEL};

	struct tPS3000ATriggerConditionsV2 conditions = {	PS3000A_CONDITION_DONT_CARE, // It is channelA, there was "PS3000A_CONDITION_TRUE"
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_TRUE, // this is External input
        PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE};

	struct tPwq pulseWidth;

	struct tTriggerDirections directions = {	PS3000A_NONE, // It is channelA, there was PS3000A_RISING
												PS3000A_NONE,
												PS3000A_NONE,
												PS3000A_NONE,
												mySetting.bEdgeSelect, //this is External input PS3000A_NONE,
												PS3000A_NONE };

	memset(&pulseWidth, 0, sizeof(struct tPwq));

	printf("Collect rapid block triggered...\n");
	printf("Collects when value rises past %d",	scaleVoltages?
		adc_to_mv(sourceDetails.thresholdUpper, unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print mV value
		: sourceDetails.thresholdUpper);																// else print ADC Count

	printf(scaleVoltages?"mV\n" : "ADC Counts\n");
	printf("Press any key to abort\n");

	setDefaults(unit);

	// Trigger enabled
	setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	// Find the maximum number of segments
	status = ps3000aGetMaxSegments(unit->handle, &maxSegments);

//	printf("Max. number of segments for device: %d\n", maxSegments);


	// Peter. что это за переменная nSegments? Можно понять из описания ps3000aMemorySegments

	// Set the number of segments
//	nSegments = 64;

	// Set the number of captures
//	nCaptures = 10;

	// Segment the memory
	status = ps3000aMemorySegments(unit->handle, nCaptures, &nMaxSamples);
// Peter. 2012 - status = ps3000aMemorySegments(unit->handle, nCaptures, &nMaxSamples),
// где nCaptures = mySetting.nWaveForms;	int nWaveForms;// The Number of wave forms (default=25000)
// и далее - (status = ps3000aSetNoOfCaptures(unit->handle, nCaptures).
// то есть    nSegments== nCaptures в случае 2012. А тут почему разное?
// For our PS300A oscillograph internal memory the maximum is 25000 frames at 1024 points per frame


	// Set the number of captures
	status = ps3000aSetNoOfCaptures(unit->handle, nCaptures);

	// Verify timebase index is valid, sample interval will be device dependent
	timebase = mySetting.timeBase; //10;

	// Find the maximum number of samples and the time interval (in nanoseconds)

	status = PICO_INVALID_TIMEBASE;

	do
	{
		status = ps3000aGetTimebase(unit->handle, timebase, nSamples, &timeIntervalNs, oversample, &maxSamples, 0);

		if (status != PICO_OK)
		{
			timebase++;
		}
	}
	while (status != PICO_OK);

	printf("\nTimebase: %u  Sample interval: %i ns\n Max samples per channel per segment: %i\n", timebase, timeIntervalNs, maxSamples); // %lu %ld %ld

	printf("Starting data capture for %d waveforms...\n", nCaptures);


	//Allocate memory

	rapidBuffers = (int16_t ***) calloc(unit->channelCount, sizeof(int16_t*));
	overflow = (int16_t *) calloc(unit->channelCount * nCaptures, sizeof(int16_t));

	for (channel = 0; channel < unit->channelCount; channel++)
	{
		if(unit->channelSettings[channel].enabled)
		{
			rapidBuffers[channel] = (int16_t **) calloc(nCaptures, sizeof(int16_t*));
		}
		else
		{
			rapidBuffers[channel] = NULL;
		}
	}

	for (channel = 0; channel < unit->channelCount; channel++)
	{
		if(unit->channelSettings[channel].enabled)
		{
			for (int16_t capture = 0; capture < nCaptures; capture++)
			{
				rapidBuffers[channel][capture] = (int16_t *) calloc(nSamples, sizeof(int16_t));
			}
		}
	}

// Peter. Вот выше блок один измерили и создали под него массивы в памяти, а я ниже как-то начинаю их получать в цикле? Хахха.
// где в цикле функция ps3000aRunBlock????

	// Peter. вот тут надо брать массив rapidBuffers** и усреднять. И пускать в цикл в этой же функции, с последующим усреднением.
	// и выводить на экран меняющиеся числа.
	// и записывать в файл тут же. все в одной функции.
	// а то тут блок получили и ... очистили.
	// а может где-то тут или еще где заполнять массив на 1024 и выводить на экран.
	// Это во всех функциях нужно, может массив сделать глобальным...
	// только понять что это за функция nSegments

	//from old code:
    double *dNBlockAveraged; // for dinamic array for collect data
    dNBlockAveraged =(double*)calloc(nSamples,sizeof(*dNBlockAveraged));
    if(dNBlockAveraged == 0)
    {
            printf("Memory for dNBlockAveraged hasn't been allocated.");
            printf("\nPress any key...\n\n");
            _getch();
            exit(0);
    }

  	for(uint32_t j = 0; j < nBlocks; j++) // It is bad idea to allocate the memory by cycles. One must be allocated one time and be in use. But I couldn't have done it....
    {

// from 2012 code, check the functions
		if(j == 0) // Logs' output on screen for first block only.
		{
			printf("Collects will be started when voltage rises past %d",	scaleVoltages?
				adc_to_mv(sourceDetails.thresholdUpper, unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print value in mV
				: sourceDetails.thresholdUpper);																// else print ADC Count
			printf(scaleVoltages?"mV\n" : "ADC Counts\n");
			printf("Press any key to abort\n");
		}


// проверить соответствие со старой функцией CollectRapidNBlock, откуда я вынул освобождение памяти
// (оно выше этого цикла? до того происходило в каждой итерации)
// и попробовать не фрагментировать память устройства много раз, может достаточно раз до цокла






// еще можно каждые 10 блоков записывать данные в файл на случай потери напряжения и пр.









    // Peter. Тут начинается получнеие блока данных.

	do
	{
		retry = 0;

		status = ps3000aRunBlock(unit->handle, 0, nSamples, timebase, 1, &timeIndisposed, 0, callBackBlock, NULL);

		if(status != PICO_OK)
		{
			if(status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED)
			{
				status = changePowerSource(unit->handle, status);
				retry = 1;
			}
			else
			{
				printf("RapidBlockDataHandler:ps3000aRunBlock ------ 0x%08u \n", status); // %08lx
				printf("Press any key to continue (data collection will be aborted).\n");
			}
		}
	}
	while(retry);

	//Wait until data ready
	g_ready = 0;

	if(j == 0)
	printf("Waiting for the trigger... ");

	while(!g_ready && !_kbhit())
	{
		Sleep(0);
	}

	if (!g_ready)
	{
		_getch();
		status = ps3000aStop(unit->handle);
		status = ps3000aGetNoOfCaptures(unit->handle, &nCompletedCaptures);
		printf("Rapid capture aborted. %u complete blocks were captured\n", nCompletedCaptures); // %lu
		printf("\nPress any key...\n\n");
		_getch();

		if(nCompletedCaptures == 0)
		{
			return;
		}

		// Only display the blocks that were captured
		nCaptures = nCompletedCaptures;
	}






















        for (channel = 0; channel < unit->channelCount; channel++)
        {
            if(unit->channelSettings[channel].enabled)
            {
                for (auto capture = 0; capture < nCaptures; capture++)
                {
                    status = ps3000aSetDataBuffer(unit->handle, (PS3000A_CHANNEL)channel, rapidBuffers[channel][capture], nSamples, capture, PS3000A_RATIO_MODE_NONE);
                }
            }
        }

        // Retrieve data
        status = ps3000aGetValuesBulk(unit->handle, &nSamples, 0, nCaptures - 1, 1, PS3000A_RATIO_MODE_NONE, overflow);

        if (status == PICO_POWER_SUPPLY_CONNECTED || status == PICO_POWER_SUPPLY_NOT_CONNECTED)
        {
            printf("\nPower Source Changed. Data collection aborted.\n");
        }

        // from 2012 code
   		//Stop пока останавливаем после цикла
//		status = ps3000aStop(unit->handle);



// ------> averaging in the current rapidBuffers and addition to the current dNBlockAveraged <-------------------------


        double dAverage;
        uint32_t iSumm;
        for(uint32_t i = 0; i < nSamples; i++)
        {
                    iSumm = 0;
 					for (int capture = 0; capture < nCaptures; capture++)
					{
						iSumm = iSumm + rapidBuffers[0][capture][i];
					}
					dAverage = (double)iSumm / (double)nCaptures;

                    dNBlockAveraged[i] =+ dAverage;

        }


    }



	if (status == PICO_OK)
	{

// блок из старого файла, можно привести функции в соответствие с записью в файл парой функций выше и проверить dAdc_to_mv
        FILE * fp = NULL;

		fopen_s(&fp, "Nrapidblock_average.txt", "w");
		if (fp != NULL)
		{

//			double dAverage;
//			long iSumm; // or int?
			double dAverageVoltage;

			fprintf(fp,"Results for CollectRapidBlockTriggered of the %d Channels are shown\n\n",unit->channelCount);
			fprintf(fp, "Time Voltage\n");
			fprintf(	fp,	"ns		mV\n");
			for(uint32_t i = 0; i < nSamples; i++)
			{


                fprintf(fp, "%6ld ", (long)(g_times[0] + (i * timeIntervalNs))); // %5lld %I64
                dAverageVoltage=dAdc_to_mv(dNBlockAveraged[i]/nSamples,unit->channelSettings[PS3000A_CHANNEL_A].range, unit);
                fprintf(fp, "   %lf       \n", dAverageVoltage);

/*				iSumm=0;
				if(unit->channelSettings[channel=0].enabled)
				{
					for (capture = 0; capture < nCaptures; capture++)
					{
						iSumm=iSumm+rapidBuffers[0][capture][i];
					}

				}

				dAverage=(double)iSumm/(double)nCaptures;

				fprintf(fp, "%5lld ", g_times[0] + (long long)(i * timeIntervalNs));

				dAverageVoltage=dAdc_to_mv(dAverage,unit->channelSettings[PS3000A_CHANNEL_A].range, unit);
				fprintf(fp, "   %lf       \n", dAverageVoltage);
				*/
			}
		}
		else
		printf(	"Cannot open the file rapidblock_average.txt for writing.\n"
			"Please ensure that you have permission to access.\n");


		if (fp != NULL)
		fclose(fp);





/*		//print first 10 samples from each capture
		for (capture = 0; capture < nCaptures; capture++)
		{
			printf("\nCapture %d:-\n\n", capture + 1);

			for (channel = 0; channel < unit->channelCount; channel++)
			{
				if(unit->channelSettings[channel].enabled)
				{
					printf("Channel %c:\t", 'A' + channel);
				}
			}

			printf("\n");

			for(i = 0; i < 10; i++)
			{
				for (channel = 0; channel < unit->channelCount; channel++)
				{
					if(unit->channelSettings[channel].enabled)
					{
						printf("   %6d       ", scaleVoltages ?
							adc_to_mv(rapidBuffers[channel][capture][i], unit->channelSettings[PS3000A_CHANNEL_A +channel].range, unit)	// If scaleVoltages, print mV value
							: rapidBuffers[channel][capture][i]);																		// else print ADC Count
					}
				}
				printf("\n");
			}
		}
*/
	}




	// Stop
	status = ps3000aStop(unit->handle);

	//Free memory
	free(overflow);

	for (channel = 0; channel < unit->channelCount; channel++)
	{
		if (unit->channelSettings[channel].enabled)
		{
			for (auto capture = 0; capture < nCaptures; capture++)
			{
				free(rapidBuffers[channel][capture]);
			}
		}
	}

	for (channel = 0; channel < unit->channelCount; channel++)
	{
		if (unit->channelSettings[channel].enabled)
		{
			free(rapidBuffers[channel]);
		}
	}

	free(dNBlockAveraged);

	free(rapidBuffers);

	// Set number of segments and captures back to 1
	status = ps3000aMemorySegments(unit->handle, (uint32_t) 1, &nMaxSamples);
	status = ps3000aSetNoOfCaptures(unit->handle, 1);
}


// <<<< =========== compared 2021 vs. 2012 code until here =================>>>>>


//****************************************************************************
//* Initialise unit' structure with Variant specific defaults
//****************************************************************************
void get_info(UNIT * unit)
{
	char description [11][25] = { "Driver Version",
		"USB Version",
		"Hardware Version",
		"Variant Info",
		"Serial",
		"Cal Date",
		"Kernel",
		"Digital H/W",
		"Analogue H/W",
		"Firmware 1",
		"Firmware 2"};

	int16_t i, r = 0;
	int8_t line [80];

	// Variables used for arbitrary waveform parameters
	int16_t			minArbitraryWaveformValue = 0;
	int16_t			maxArbitraryWaveformValue = 0;
	uint32_t		minArbitraryWaveformSize = 0;
	uint32_t		maxArbitraryWaveformSize = 0;

	//PICO_STATUS status = PICO_OK;

	//Initialise default unit properties and change when required
	unit->sigGen		= SIGGEN_FUNCTGEN;
	unit->firstRange	= PS3000A_50MV;
	unit->lastRange		= PS3000A_20V;
	unit->channelCount	= DUAL_SCOPE;
	unit->ETS			= FALSE;
	unit->AWGFileSize	= MIN_SIG_GEN_BUFFER_SIZE;
	unit->digitalPorts	= 0;

	if (unit->handle)
	{
		for (i = 0; i < 11; i++) // 2012 version i < 5 only
		{
			ps3000aGetUnitInfo(unit->handle, line, sizeof (line), &r, i);
			//status = ps3000aGetUnitInfo(unit->handle, line, sizeof (line), &r, i);

			if (i == 3)
			{
				memcpy(unit->model, line, strlen((char*)(line))+1);

				// If 4 (analogue) channel variant
				if (line[1] == '4')
				{
					unit->channelCount = QUAD_SCOPE;
				}

				// If ETS mode is enabled
				if (strlen((char*)(line)) == 8 || line[3] != '4')
				{
					unit->ETS	= TRUE;
				}


				if (line[4] != 'A')
				{
					// Set Signal generator type if the device is not an 'A' model
					unit->sigGen = SIGGEN_AWG;

					// PicoScope 3000D and 3000D MSO models have a lower range of +/- 20mV
					if (line[4] == 'D')
					{
						unit->firstRange = PS3000A_20MV;
					}
				}

				// Check if MSO device
				if (strlen((char*)(line)) >= 7)
				{
					line[4] = toupper(line[4]);
					line[5] = toupper(line[5]);
					line[6] = toupper(line[6]);

					if(strcmp((char*)(line) + 4, "MSO") == 0 || strcmp((char*)(line) + 5, "MSO") == 0 )
					{
						unit->digitalPorts = 2;
						unit->sigGen = SIGGEN_AWG;
					}
				}

				// If device has Arbitrary Waveform Generator, find the maximum AWG buffer size
				if (unit->sigGen == SIGGEN_AWG)
				{
					ps3000aSigGenArbitraryMinMaxValues(unit->handle, &minArbitraryWaveformValue, &maxArbitraryWaveformValue, &minArbitraryWaveformSize, &maxArbitraryWaveformSize);
					unit->AWGFileSize = maxArbitraryWaveformSize;
				}
			}
			printf("%s: %s\n", description[i], line);
		}
	}
}

//****************************************************************************
//* setVoltages
//* Select input voltage ranges for channels
//****************************************************************************
void setVoltages(UNIT * unit)
{
	int32_t i, ch;
	int32_t count = 0;

	// See what ranges are available...
	for (i = unit->firstRange; i <= unit->lastRange; i++)
	{
		printf("%d -> %d mV\n", i, inputRanges[i]);
	}

	do
	{
		// Ask the user to select a range
		printf("Specify voltage range (%d..%d)\n", unit->firstRange, unit->lastRange);
		printf("99 - switches channel off\n");

		for (ch = 0; ch < unit->channelCount; ch++)
		{
			printf("\n");
			do
			{
				printf("Channel %c: ", 'A' + ch);
				std::cin >> unit->channelSettings[ch].range;
//				fflush(stdin);
//				scanf_s("%hd", &unit->channelSettings[ch].range);
				// "h" modifier indicates that it's reading a short integer, which your variable choice just happens to be. So the "%hd" is necessary to write only two bytes (on most machines) instead of the 4 bytes that "%d" writes.

			} while (unit->channelSettings[ch].range != 99 && (unit->channelSettings[ch].range < unit->firstRange || unit->channelSettings[ch].range > unit->lastRange));

			if (unit->channelSettings[ch].range != 99)
			{
				printf(" - %d mV\n", inputRanges[unit->channelSettings[ch].range]);
				unit->channelSettings[ch].enabled = TRUE;

				count++;
			}
			else
			{
				printf("Channel Switched off\n");
				unit->channelSettings[ch].enabled = FALSE;
				unit->channelSettings[ch].range = PS3000A_MAX_RANGES-1;
			}
		}
		printf(count == 0? "\n** At least 1 channel must be enabled **\n\n":"");
	}
	while(count == 0);	// must have at least one channel enabled

	mySetting.channelRange = inputRanges[unit->channelSettings[0].range]; // for A channel
	setDefaults(unit);	// Put these changes into effect
}

//****************************************************************************
//*
//* Select timebase, set oversample to on and time units as nano seconds
//*
//****************************************************************************
void setTimebase(UNIT * unit)
{
	int32_t timeInterval = 0;
	int32_t maxSamples = 0;

	PICO_STATUS status = PICO_INVALID_TIMEBASE; // added in 2016 to check if time base is correct

	printf("0 -> 2 ns, 1 -> 4 ns, 2 -> 8 ns, 3 -> 16 ns, 4 -> 32 ns, ... max 2^32-1 -> ~ 68.7 s.\n ");

	printf("Specify desired timebase: ");
    std::cin >> timebase;
//	fflush(stdin);
//	scanf_s("%lud", &timebase);

	do
	{
		status = ps3000aGetTimebase(unit->handle, timebase, BUFFER_SIZE, &timeInterval, 1, &maxSamples, 0);

		if (status != PICO_OK)
		{
			if(status == PICO_INVALID_CHANNEL)
			{
				printf("ps3000aGetTimebase: Status Error 0x%x\n", status);
//				printf("Please enable an analogue channel (option V from the main menu)."); // Peter. We already have analogue channels only
				return;

			}
			else
			{
				timebase++;  // Increase timebase if the one specified can't be used.
			}
		}
	}
	while(status != PICO_OK);

	printf("Timebase used %u = %d ns sample interval\n", timebase, timeInterval); // %lu %ld
	oversample = TRUE;

	mySetting.timeBase = timebase;

}

// Peter. We did nor use this function. But we have Sig output in the oscillograph!

//****************************************************************************
//* Sets the signal generator
//* - allows user to set frequency and waveform
//* - allows for custom waveform (values -32768..32767)
//* - of up to 8192 samples long (PicoScope 3x04B & PS3x05B),
//*	or 16384 samples long (PicoScope 3x06B),
//*   or 32768 samples long (PicoScope 3207B, 3X0X D & D MSO devices)
//******************************************************************************
void setSignalGenerator(UNIT unit)
{
	char ch;
	char fileName [128];

	int16_t waveform;
	//int16_t choice;
	int16_t *arbitraryWaveform;

	int32_t waveformSize = 0;
	int32_t offset = 0;

	uint32_t pkpk = 4000000; // +/- 2 V
	uint32_t delta = 0;

	double frequency = 1.0;

	FILE * fp = NULL;
	PICO_STATUS status;


	while (_kbhit())			// use up keypress
	{
		_getch();
	}

	do
	{
		printf("\nSignal Generator\n================\n");
		printf("0 - SINE         1 - SQUARE\n");
		printf("2 - TRIANGLE     3 - DC VOLTAGE\n");

		if(unit.sigGen == SIGGEN_AWG)
		{
			printf("4 - RAMP UP      5 - RAMP DOWN\n");
			printf("6 - SINC         7 - GAUSSIAN\n");
			printf("8 - HALF SINE    A - AWG WAVEFORM\n");
		}

		printf("F - SigGen Off\n\n");

		ch = _getch();

/*		if (ch >= '0' && ch <='9')
		{
			//choice = ch -'0';
		}
		else
		{
			ch = toupper(ch);
		}
*/
    ch = toupper(ch);
	}
//	while(unit.sigGen == SIGGEN_FUNCTGEN && ch != 'F' && (ch < '0' || ch > '3') ||
//			unit.sigGen == SIGGEN_AWG && ch != 'A' && ch != 'F' && (ch < '0' || ch > '8')  );
	while( (unit.sigGen == SIGGEN_FUNCTGEN && ch != 'F' && (ch < '0' || ch > '3') ) ||
			(unit.sigGen == SIGGEN_AWG && ch != 'A' && ch != 'F' && (ch < '0' || ch > '8') )  );

	if (ch == 'F')	// If we're going to turn off siggen
	{
		printf("Signal generator Off\n");
		waveform = 8;		// DC Voltage
		pkpk = 0;			// 0 V
		waveformSize = 0;
	}
	else
	{
		if (ch == 'A' && unit.sigGen == SIGGEN_AWG)		// Set the AWG
		{
			arbitraryWaveform = (int16_t*) malloc( unit.AWGFileSize * sizeof(int16_t));
			memset(arbitraryWaveform, 0, unit.AWGFileSize * sizeof(int16_t));

			waveformSize = 0;

			printf("Select a waveform file to load: ");
            std::cin >> fileName;
//			scanf_s("%s", fileName, 128);

			if (fopen_s(&fp, fileName, "r") == 0)
			{
				// Having opened file, read in data - one number per line (max 8192 lines for
				// PicoScope 3X04B & 3X05B devices, 16384 for PicoScope 3X06B devices, 32768 for PicoScope 3207B,
				// 3X0XD and 3X0XD MSO devices), with values in the range -32768..+32767
				while (EOF != fscanf(fp, "%hi", (arbitraryWaveform + waveformSize))&& waveformSize++ < unit.AWGFileSize - 1); // fscanf_s
				fclose(fp);
				printf("File successfully loaded\n");
			}
			else
			{
				printf("Invalid filename\n");
				return;
			}
		}
		else			// Set one of the built in waveforms
		{
			switch (ch)
			{
				case '0':
					waveform = PS3000A_SINE;
					break;

				case '1':
					waveform = PS3000A_SQUARE;
					break;

				case '2':
					waveform = PS3000A_TRIANGLE;
					break;

				case '3':
					waveform = PS3000A_DC_VOLTAGE;
					do
					{
						printf("\nEnter offset in uV: (0 to 2000000)\n"); // Ask user to enter DC offset level;
						std::cin >> offset;
//						scanf_s("%lu", &offset);
					} while (offset < 0 || offset > 2000000);
					break;

				case '4':
					waveform = PS3000A_RAMP_UP;
					break;

				case '5':
					waveform = PS3000A_RAMP_DOWN;
					break;

				case '6':
					waveform = PS3000A_SINC;
					break;

				case '7':
					waveform = PS3000A_GAUSSIAN;
					break;

				case '8':
					waveform = PS3000A_HALF_SINE;
					break;

				default:
					waveform = PS3000A_SINE;
					break;
			}
		}

		if(waveform < 8 || (ch == 'A' && unit.sigGen == SIGGEN_AWG))	// Find out frequency if required
		{
			do
			{
				printf("\nEnter frequency in Hz: (1 to 1000000)\n");	// Ask user to enter signal frequency;
				std::cin >> frequency;
//				scanf_s("%lf", &frequency);
			} while (frequency <= 0 || frequency > 1000000);
		}

		if (waveformSize > 0)
		{
			ps3000aSigGenFrequencyToPhase(unit.handle, frequency, PS3000A_SINGLE, waveformSize, &delta);

			status = ps3000aSetSigGenArbitrary(	unit.handle,
				0,				// offset voltage
				pkpk,			// PkToPk in microvolts. Max = 4000000 uV  (±2 V)
				delta,			// start delta
				delta,			// stop delta
				0,
				0,
				arbitraryWaveform,
				waveformSize,
				(PS3000A_SWEEP_TYPE)0,
				(PS3000A_EXTRA_OPERATIONS)0,
				PS3000A_SINGLE,
				0,
				0,
				PS3000A_SIGGEN_RISING,
				PS3000A_SIGGEN_NONE,
				0);

			// If status != PICO_OK, show the error
			printf(status? "\nps3000aSetSigGenArbitrary: Status Error 0x%x \n":"", (uint32_t) status);
		}
		else
		{
			status = ps3000aSetSigGenBuiltInV2(unit.handle,
				offset,
				pkpk,
				waveform,
				(double) frequency,
				(double) frequency,
				0,
				0,
				(PS3000A_SWEEP_TYPE)0,
				(PS3000A_EXTRA_OPERATIONS)0,
				0,
				0,
				(PS3000A_SIGGEN_TRIG_TYPE)0,
				(PS3000A_SIGGEN_TRIG_SOURCE)0,
				0);

			// If status != PICO_OK, show the error
			printf(status?"\nps3000aSetSigGenBuiltIn: Status Error 0x%x \n":"", (uint32_t)status);
		}
	}
}


// Peter. We did nor use this function,
// but it is useful

//****************************************************************************
//* collectStreamingImmediate
//*  this function demonstrates how to collect a stream of data
//*  from the unit (start collecting immediately)
//***************************************************************************
void collectStreamingImmediate(UNIT * unit)
{
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	memset(&pulseWidth, 0, sizeof(struct tPwq));
	memset(&directions, 0, sizeof(struct tTriggerDirections));

	setDefaults(unit);

	printf("Collect streaming...\n");
	printf("Data is written to disk file (stream.txt)\n");
	printf("Press a key to start\n");
	_getch();

	// Trigger disabled
	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	streamDataHandler(unit, 0, ANALOGUE);
}


// Peter. We did nor use this function
// And must include	"int16_t	triggerVoltage" etc for success using (instead of constant 1000mV level)

//****************************************************************************
//* collectStreamingTriggered
//*  this function demonstrates how to collect a stream of data
//*  from the unit (start collecting on trigger)
// 	int16_t	triggerVoltage = mv_to_adc((int16_t)mySetting.nTriggerLevel,	unit->channelSettings[PS3000A_CHANNEL_A].range, unit);


//***************************************************************************
void collectStreamingTriggered(UNIT * unit)
{
	int16_t triggerVoltage = mv_to_adc(1000, unit->channelSettings[PS3000A_CHANNEL_A].range, unit); // ChannelInfo stores ADC counts
//	int16_t	triggerVoltage = mv_to_adc((int16_t)mySetting.nTriggerLevel,	unit->channelSettings[PS3000A_CHANNEL_A].range, unit);

	struct tPwq pulseWidth;

	struct tPS3000ATriggerChannelProperties sourceDetails = {	triggerVoltage,
		256 * 10,
		triggerVoltage,
		256 * 10,
		PS3000A_EXTERNAL, // There was "PS3000A_CHANNEL_A" in original file, but we use External input to synchronize.PS3000A_CHANNEL_A,
		PS3000A_LEVEL };

	struct tPS3000ATriggerConditionsV2 conditions = {	PS3000A_CONDITION_DONT_CARE, // PS3000A_CONDITION_TRUE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_TRUE, // PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE,
		PS3000A_CONDITION_DONT_CARE };

	struct tTriggerDirections directions = {	PS3000A_NONE, // PS3000A_RISING,
		PS3000A_NONE,
		PS3000A_NONE,
		PS3000A_NONE,
		mySetting.bEdgeSelect, //PS3000A_NONE,
		PS3000A_NONE };

	memset(&pulseWidth, 0, sizeof(struct tPwq));

	printf("Collect streaming triggered...\n");
	printf("Data is written to disk file (stream.txt)\n");
	printf("Press a key to start\n");
	_getch();

	setDefaults(unit);

	// Trigger enabled
	// Rising edge
	// Threshold = 1000mV
	setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	streamDataHandler(unit, 10000, ANALOGUE);
}


//****************************************************************************
//* displaySettings
//* Displays information about the user configurable settings in this example
//* Parameters
//* - unit        pointer to the UNIT structure
//*
//* Returns       none
//***************************************************************************
void displaySettings(UNIT *unit)
{
	int32_t ch;
	int32_t voltage;


    // from 2012.
	//=== to display parameters. Peter. 2012
	int32_t timeInterval;
	int32_t sampleCount= mySetting.nBufferSize; // or BUFFER_SIZE;?
	int32_t maxSamples;


	printf("\n\nReadings will be scaled in (%s)\n\n", (scaleVoltages)? ("mV") : ("ADC counts"));

	for (ch = 0; ch < unit->channelCount; ch++)
	{
		if (!(unit->channelSettings[ch].enabled))
		{
			printf("Channel %c Voltage Range = Off\n", 'A' + ch);
		}
		else
		{
			voltage = inputRanges[unit->channelSettings[ch].range];
			printf("Channel %c Voltage Range = ", 'A' + ch);

			if (voltage < 1000)
			{
				printf("%dmV\n", voltage);
			}
			else
			{
				printf("%dV\n", voltage / 1000);
			}
		}
	}

	 // 2012
	while (ps3000aGetTimebase(unit->handle, timebase, sampleCount, &timeInterval, oversample, &maxSamples, 0))
	{
		timebase++;
	}
	printf("Timebase = %u, SampleInterval: %d ns, Trigger = %d mV.\n", timebase, timeInterval, mySetting.nTriggerLevel); // %lu / %ld // (unsigned int -  %u) / (int - %d %i)


	printf("\n");

	if(unit->digitalPorts > 0)
	{
		printf("Digital ports switched off.");
	}

	printf("\n");
}


void changeParameters(UNIT *unit)
{

    char ch = 0;
	while (ch != 'X')
    {

    	printf("V - Set Voltage\n");
		printf("T - Set Timebase\n");
		printf("S - Set Time Shift\n");
		printf("W - Set Length of Waveform\n");
		printf("L - Set Trigger Level\n");
		printf("R - Set Trigger - Rise/Fall\n");
		printf("N - Set Number of waveforms in Block\n");
    	printf("D - Set DC or AC mode\n");
    	printf("A - on/off Channel A \n");
    	printf("B - on/off Channel B\n");
    	printf("X - Exit");
		printf("Operation:");

        ch = toupper(_getch());
		printf("\n");
		switch (ch)
		{
                case 'V':
                    setVoltages(unit);
                    break;

                case 'T':
                    setTimebase(unit);
                    break;

				case 'S':
                    printf("Do not made yet... \n");

                    break;

                case 'W':
                    printf("Do not made yet... \n");
                    break;

                case 'L':
                    printf("Do not made yet... \n");
                    break;

                case 'R':
                    printf("Do not made yet... \n");
                    break;

                case 'N':
                    printf("Do not made yet... \n");
                    break;

                case 'D':
                    printf("Do not made yet... \n");
                    break;

                case 'A':
                    printf("Do not made yet... \n");
                    break;

                case 'B':
                    printf("Do not made yet... \n");
                    break;

		}

    }


}

void restoreParameters()
{

    	mySetting.percTimeShift = 10;
		mySetting.nBufferSize = 1024;
		mySetting.nTriggerLevel = 200; //100
		mySetting.bEdgeSelect = PS3000A_FALLING; // PS3000A_RISING
		mySetting.nWaveForms = 25000;
		mySetting.timeBase = 1;  // 0 - 2ns, 1 - 4ns, 2 - 8ns, 3 - 16 ns, 4 - 32ns.
		mySetting.channelRange = PS3000A_500MV; // PS3000A_50MV, ...100,200,500..., PS3000A_1V, ...5,10...PS3000A_20V
		mySetting.channelDCcoupled = TRUE;
		mySetting.switchChannelA = TRUE;
		mySetting.switchChannelB = FALSE;

/*
    struct	ps3000aSetting mySetting {
		.percTimeShift = 10,
		.nBufferSize = 1024,
		.nTriggerLevel = -20, //100
		.bEdgeSelect = PS3000A_FALLING,
		.nWaveForms = 25000,
		.timeBase = 1,  // 0 - 2ns, 1 - 4ns, 2 - 8ns, 3 - 16 ns, 4 - 32ns.
		.channelRange = PS3000A_500MV, // PS3000A_50MV, ...100,200,500..., PS3000A_1V, ...5,10...PS3000A_20V
		.channelDCcoupled = TRUE,
		.switchChannelA = TRUE,
		.switchChannelB = FALSE};
    };
*/

}

void saveParameters()
{
// переместить запись в функцию сохранения настроек, чего просто так создавать при открытии?
		// Load default setting and save them to file
		std::ofstream fileSaveSet;
		fileSaveSet.open (settingFile, std::ios::out | std::ios::binary);  // м.б. не хватает ("students.data", ios::binary)
		if (fileSaveSet.is_open())  // или if (fset.is_open())
		{
            std::cout << "Settings are saving into " << settingFile << ".\n";
            fileSaveSet.write(reinterpret_cast<char*> (&mySetting), sizeof(ps3000aSetting)); // (char*)  or sizeof(ps3000aSetting
            fileSaveSet.close();
		}
        else
        {
            std::cout << "error writing setting file. " << std::endl;
        }

}


//****************************************************************************
//* openDevice
//* Parameters
//* - unit        pointer to the UNIT structure, where the handle will be stored
//*
//* Returns
//* - PICO_STATUS to indicate success, or if an error occurred

//* 2012_ADDITIONS:
//* Reading setting from the file (or function load default setting and create new setting file).
// rewrite read/write functions, they are too big. And resolve the double reading of every string!
// and add checking of input parameters, If any wrong and out of range - load default.
// I even do not need make "load default function", the parameters already exist while DeviceOpened
// and change fwrite to fwrite
// and create strings [] for every text string that is written into file! It will be easier! - smth like fprintf(file1, "%s", a)

//***************************************************************************
PICO_STATUS openDevice(UNIT *unit)
{
	int16_t value = 0;
	int32_t i;
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	// 2012. for setting from and into the file
//	FILE * fset = NULL;
//	int buf; // for clean the string buffer
//	char buffer[100];


	PICO_STATUS status = ps3000aOpenUnit(&(unit->handle), NULL);

	if (status == PICO_POWER_SUPPLY_NOT_CONNECTED || status == PICO_USB3_0_DEVICE_NON_USB3_0_PORT )
	{
		status = changePowerSource(unit->handle, status);
	}

	printf("\nHandle: %d\n", unit->handle);

	if (status != PICO_OK)
	{
		printf("Unable to open device\n");
		printf("Error code : 0x%08u\n", status); //  %08lx  (unsigned int - %u)
		while(!_kbhit());
		exit(99); // exit program
	}

	printf("Device opened successfully, cycle %d\n\n", ++cycles);



// 2021 два способа чтения из файла, первый – используя операцию передачи в поток, второй – используя функцию getline().... http://cppstudio.com/post/446/
// В программе показаны два способа чтения из файла, первый – используя операцию передачи в поток, второй – используя функцию getline().
// В первом случае считывается только первое слово, а во втором случае считывается строка, длинной 50 символов.
// fin >> buff;
// fset.getline(buff, 50); // считали строку из файла

// https://stackoverflow.com/questions/5844309/trying-to-use-int-in-getline
// Note that just inputting std::std::cin directly into totalquestions does not work; it will leave the trailing '\n' character in the buffer,
// which will desynchronize all of the following input. It's possible to avoid this by adding a call to std::std::cin.ignore,
// but this would still miss the error due to trailing garbage. If you're doing line oriented input, stick with getline, and use std::istringstream for any necessary conversions.

// http://www.cplusplus.com/forum/articles/6046/
// Using the >> operator opens you up to alot of problems.
// A more elegant solution, and much easier to use is the getline(); function. The example below shows you how to load information, and convert it between types.
//  string input = "";
//     getline(std::cin, input);
//   stringstream myStream(input);
//   if (myStream >> myNumber)
//   break;
//   std::cout << "Invalid number, please try again" << std::endl;
// (if your having problems, before the 2nd getline(); try putting std::cin.clear();)


// Почему getline здесь быстрее, чем scanf?
// https://coderoad.ru/26392367/

/*

    std::ifstream fset(settingFile); // открыли файл для чтения // ofstream output_file("students.data", ios::binary);
    if (!fset.is_open()) // если файл не открыт
    {
        std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
    }
    else
    {
        fin >>
        // or
        fwrite (mySetting, sizeof(mySetting), 1, fset);

    }

*/
// or filename.append(".txt");
// file.open(filename.c_str());


// fname, dname, and ename are variables of type std::string, by default.
// However, the fstream::open requires a const char * value passed to it for a filename
// istream.open(fname.c_str()); nstream.open(ename.c_str());


// reinterpret_cast<char*> (&mySetting) небезопасно, см.  https://ru.stackoverflow.com/questions/716240/
// http://www.cplusplus.com/forum/general/127483/ - in.read(reinterpret_cast<char*>(&structs[0]), sizeof(MyStructure) * 10);

    // еще вариант https://www.geeksforgeeks.org/file-handling-c-classes/?ref=lbp :
//    #include <fstream>
    std::ifstream fileLoadSet;
    fileLoadSet.open(settingFile, std::ios::in | std::ios::binary);
    if(fileLoadSet) // или if (fset.is_open())
    {
        std::cout << "Reading setting from " << settingFile << std::endl;
        fileLoadSet.read(reinterpret_cast<char*> (&mySetting), sizeof(ps3000aSetting)); // (char*) or sizeof(ps3000aSetting)
        fileLoadSet.close();
    }
    else
    {
        std::cout << "Setting file is not found. Loading of default setting" << std::endl;

        restoreParameters();

    }





	// setup devices
	get_info(unit);
	timebase = mySetting.timeBase; // 1

	ps3000aMaximumValue(unit->handle, &value);
	unit->maxValue = value;

	for ( i = 0; i < unit->channelCount; i++)
	{
		unit->channelSettings[i].enabled = FALSE;
		unit->channelSettings[i].DCcoupled = TRUE;
		unit->channelSettings[i].range = PS3000A_500MV;
	}

	unit->channelSettings[0].enabled = TRUE; // chA enabled


	memset(&directions, 0, sizeof(struct tTriggerDirections));
	memset(&pulseWidth, 0, sizeof(struct tPwq));

	setDefaults(unit);

	// Trigger disabled
	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, 0, 0);
// 2012:
//	SetTrigger(unit->handle, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0);



	return status;
}


//****************************************************************************
//* closeDevice
//****************************************************************************
void closeDevice(UNIT *unit)
{
	ps3000aCloseUnit(unit->handle);
}


// Peter. We do nor use this function

//****************************************************************************
//* andAnalogueDigital
//* This function shows how to collect a block of data from the analogue
//* ports and the digital ports at the same time, triggering when the
//* digital conditions AND the analogue conditions are met
//*
//* Returns       none
//***************************************************************************
void andAnalogueDigitalTriggered(UNIT * unit)
{
	int32_t channel = 0;

	int16_t	triggerVoltage = mv_to_adc(1000, unit->channelSettings[PS3000A_CHANNEL_A].range, unit);

	PS3000A_TRIGGER_CHANNEL_PROPERTIES sourceDetails = {	triggerVoltage,			// thresholdUpper
															256 * 10,				// thresholdUpper Hysteresis
															triggerVoltage,			// thresholdLower
															256 * 10,				// thresholdLower Hysteresis
															PS3000A_CHANNEL_A,		// channel
															PS3000A_LEVEL};			// mode

	PS3000A_TRIGGER_CONDITIONS_V2 conditions = {
													PS3000A_CONDITION_TRUE,					// Channel A
													PS3000A_CONDITION_DONT_CARE,			// Channel B
													PS3000A_CONDITION_DONT_CARE,			// Channel C
													PS3000A_CONDITION_DONT_CARE,			// Channel D
													PS3000A_CONDITION_DONT_CARE,			// external
													PS3000A_CONDITION_DONT_CARE,			// aux
													PS3000A_CONDITION_DONT_CARE,			// pwq
													PS3000A_CONDITION_TRUE					// digital
												};

	TRIGGER_DIRECTIONS directions = {
										PS3000A_ABOVE,				// Channel A
										PS3000A_NONE,				// Channel B
										PS3000A_NONE,				// Channel C
										PS3000A_NONE,				// Channel D
										PS3000A_NONE,				// external
										PS3000A_NONE };				// aux

		PS3000A_DIGITAL_CHANNEL_DIRECTIONS digDirections[2];		// Array size can be up to 16, an entry for each digital bit

		PWQ pulseWidth;
		memset(&pulseWidth, 0, sizeof(PWQ));

		// Set the Digital trigger so it will trigger when bit 15 is HIGH and bit 13 is HIGH
		// All non-declared bits are taken as PS3000A_DIGITAL_DONT_CARE
		//

		digDirections[0].channel = PS3000A_DIGITAL_CHANNEL_0;
		digDirections[0].direction = PS3000A_DIGITAL_DIRECTION_RISING;

		digDirections[1].channel = PS3000A_DIGITAL_CHANNEL_4;
		digDirections[1].direction = PS3000A_DIGITAL_DIRECTION_HIGH;

		printf("\nCombination Block Triggered\n");
		printf("Collects when value is above %d", scaleVoltages?
			adc_to_mv(sourceDetails.thresholdUpper, unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print mV value
			: sourceDetails.thresholdUpper);																// else print ADC Count

		printf(scaleVoltages?"mV\n" : "ADC Counts\n");

		printf("AND \n");
		printf("Digital Channel  0   --- Rising\n");
		printf("Digital Channel  4   --- High\n");
		printf("Other Digital Channels - Don't Care\n");

		printf("Press a key to start...\n");
		_getch();

		for (channel = 0; channel < unit->channelCount; channel++)
		{
			unit->channelSettings[channel].enabled = TRUE;
		}

		setDefaults(unit);					// Enable Analogue channels.

		// Trigger enabled
		// Rising edge
		// Threshold = 100mV

		if (setTrigger(unit, &sourceDetails, 1, &conditions, 1, &directions, &pulseWidth, 0, 0, 0, digDirections, 2) == PICO_OK)
		{
			blockDataHandler(unit, "\nFirst 10 readings:\n", 0, MIXED);
		}

		disableAnalogue(unit);			// Disable Analogue ports when finished
}


// Peter. We do nor use this function

//****************************************************************************
//* orAnalogueDigital
//* This function shows how to collect a block of data from the analogue
//* ports and the digital ports at the same time, triggering when either the
//* digital conditions OR the analogue conditions are met
//*
//* Returns       none
//***************************************************************************
void orAnalogueDigitalTriggered(UNIT * unit)
{
	int32_t channel = 0;

	int16_t	triggerVoltage = mv_to_adc(1000, unit->channelSettings[PS3000A_CHANNEL_A].range, unit);

	PS3000A_TRIGGER_CHANNEL_PROPERTIES sourceDetails = {	triggerVoltage,			// thresholdUpper
															256 * 10,				// thresholdUpper Hysteresis
															triggerVoltage,			// thresholdLower
															256 * 10,				// thresholdLower Hysteresis
															PS3000A_CHANNEL_A,		// channel
															PS3000A_LEVEL};			// mode

	PS3000A_TRIGGER_CONDITIONS_V2 conditions[2];

	TRIGGER_DIRECTIONS directions = {	PS3000A_RISING,			// Channel A
										PS3000A_NONE,			// Channel B
										PS3000A_NONE,			// Channel C
										PS3000A_NONE,			// Channel D
										PS3000A_NONE,			// external
										PS3000A_NONE };			// aux

	PS3000A_DIGITAL_CHANNEL_DIRECTIONS digDirections[2];		// Array size can be up to 16, an entry for each digital bit

	PWQ pulseWidth;

	conditions[0].channelA				= PS3000A_CONDITION_TRUE;					// Channel A
	conditions[0].channelB				= PS3000A_CONDITION_DONT_CARE;				// Channel B
	conditions[0].channelC				= PS3000A_CONDITION_DONT_CARE;				// Channel C
	conditions[0].channelD				= PS3000A_CONDITION_DONT_CARE;				// Channel D
	conditions[0].external				= PS3000A_CONDITION_DONT_CARE;				// external
	conditions[0].aux					= PS3000A_CONDITION_DONT_CARE;				// aux
	conditions[0].pulseWidthQualifier	= PS3000A_CONDITION_DONT_CARE;				// pwq
	conditions[0].digital				= PS3000A_CONDITION_DONT_CARE;				// digital

	conditions[1].channelA				= PS3000A_CONDITION_DONT_CARE;				// Channel A
	conditions[1].channelB				= PS3000A_CONDITION_DONT_CARE;				// Channel B
	conditions[1].channelC				= PS3000A_CONDITION_DONT_CARE;				// Channel C
	conditions[1].channelD				= PS3000A_CONDITION_DONT_CARE;				// Channel D
	conditions[1].external				= PS3000A_CONDITION_DONT_CARE;				// external
	conditions[1].aux					= PS3000A_CONDITION_DONT_CARE;				// aux
	conditions[1].pulseWidthQualifier	= PS3000A_CONDITION_DONT_CARE;				// pwq
	conditions[1].digital				= PS3000A_CONDITION_TRUE;					// digital

	memset(&pulseWidth, 0, sizeof(PWQ));

	// Set the Digital trigger so it will trigger when bit 15 is HIGH and bit 13 is HIGH
	// All non-declared bits are taken as PS3000A_DIGITAL_DONT_CARE
	//

	digDirections[0].channel = PS3000A_DIGITAL_CHANNEL_0;
	digDirections[0].direction = PS3000A_DIGITAL_DIRECTION_RISING;

	digDirections[1].channel = PS3000A_DIGITAL_CHANNEL_4;
	digDirections[1].direction = PS3000A_DIGITAL_DIRECTION_HIGH;

	printf("\nCombination Block Triggered\n");
	printf("Collects when value rises past %d", scaleVoltages?
		adc_to_mv(sourceDetails.thresholdUpper, unit->channelSettings[PS3000A_CHANNEL_A].range, unit)	// If scaleVoltages, print mV value
		: sourceDetails.thresholdUpper);																// else print ADC Count

	printf(scaleVoltages?"mV\n" : "ADC Counts\n");

	printf("OR \n");
	printf("Digital Channel  0   --- Rising\n");
	printf("Digital Channel  4   --- High\n");
	printf("Other Digital Channels - Don't Care\n");

	printf("Press a key to start...\n");
	_getch();

	for (channel = 0; channel < unit->channelCount; channel++)
	{
		unit->channelSettings[channel].enabled = TRUE;
	}

	setDefaults(unit); // Enable analogue channels

	// Trigger enabled
	// Rising edge
	// Threshold = 1000mV

	if (setTrigger(unit, &sourceDetails, 1, conditions, 2, &directions, &pulseWidth, 0, 0, 0, digDirections, 2) == PICO_OK)
	{

		blockDataHandler(unit, "\nFirst 10 readings:\n", 0, MIXED);
	}

	disableAnalogue(unit); // Disable Analogue ports when finished;
}

//****************************************************************************
//* digitalBlockTriggered
//* This function shows how to collect a block of data from the digital ports
//* with triggering enabled
//*
//* Returns       none
//***************************************************************************


// Peter. We do nor use this function

void digitalBlockTriggered(UNIT * unit)
{
	PWQ pulseWidth;
	TRIGGER_DIRECTIONS directions;

	PS3000A_DIGITAL_CHANNEL_DIRECTIONS digDirections[16];		// Array size can be up to 16, an entry for each digital bit

	PS3000A_TRIGGER_CONDITIONS_V2 conditions = {
		PS3000A_CONDITION_DONT_CARE,		// Channel A
		PS3000A_CONDITION_DONT_CARE,		// Channel B
		PS3000A_CONDITION_DONT_CARE,		// Channel C
		PS3000A_CONDITION_DONT_CARE,		// Channel D
		PS3000A_CONDITION_DONT_CARE,		// external
		PS3000A_CONDITION_DONT_CARE,		// aux
		PS3000A_CONDITION_DONT_CARE,		// pwq
		PS3000A_CONDITION_TRUE				// digital
	};


	printf("\nDigital Block Triggered\n");

	memset(&directions, 0, sizeof(TRIGGER_DIRECTIONS));
	memset(&pulseWidth, 0, sizeof(PWQ));

	printf("Collect block of data when the trigger occurs...\n");
	printf("Digital Channel  0   --- Rising\n");
	printf("Digital Channel 4   --- High\n");
	printf("Other Digital Channels - Don't Care\n");


	digDirections[1].channel = PS3000A_DIGITAL_CHANNEL_0;
	digDirections[1].direction = PS3000A_DIGITAL_DIRECTION_RISING;

	digDirections[0].channel = PS3000A_DIGITAL_CHANNEL_4;
	digDirections[0].direction = PS3000A_DIGITAL_DIRECTION_HIGH;


	if (setTrigger(unit, NULL, 0, &conditions, 1, &directions, &pulseWidth, 0, 0, 0, digDirections, 2) == PICO_OK)
	{
		printf("Press a key to start...\n");
		_getch();
		blockDataHandler(unit, "\nFirst 10 readings:\n", 0, DIGITAL);
	}
}


// Peter. We do nor use this function

//****************************************************************************
//* digitalBlockImmediate
//* This function shows how to collect a block of data from the digital ports
//* with triggering disabled
//*
//* Returns       none
//***************************************************************************
void digitalBlockImmediate(UNIT *unit)
{
	PWQ pulseWidth;
	TRIGGER_DIRECTIONS directions;
	PS3000A_DIGITAL_CHANNEL_DIRECTIONS digDirections;

	printf("\nDigital Block Immediate\n");
	memset(&directions, 0, sizeof(TRIGGER_DIRECTIONS));
	memset(&pulseWidth, 0, sizeof(PWQ));
	memset(&digDirections, 0, sizeof(PS3000A_DIGITAL_CHANNEL_DIRECTIONS));

	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, &digDirections, 0);

	printf("Press a key to start...\n");
	_getch();

	blockDataHandler(unit, "\nFirst 10 readings:\n", 0, DIGITAL);
}


// Peter. We do nor use this function

//****************************************************************************
//*  digitalStreamingAggregated
//*  this function demonstrates how to collect a stream of Aggregated data
//*  from the unit's Digital inputs (start collecting immediately)
//***************************************************************************
void digitalStreamingAggregated(UNIT * unit)
{
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	memset(&pulseWidth, 0, sizeof(struct tPwq));
	memset(&directions, 0, sizeof(struct tTriggerDirections));


	printf("Digital streaming with Aggregation...\n");
	printf("Press a key to start...\n");
	_getch();

	// Trigger disabled
	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	streamDataHandler(unit, 0, AGGREGATED);
}


// Peter. We do nor use this function

//****************************************************************************
//*  digitalStreamingImmediate
//*  this function demonstrates how to collect a stream of data
//*  from the unit's Digital inputs (start collecting immediately)
//***************************************************************************
void digitalStreamingImmediate(UNIT * unit)
{
	struct tPwq pulseWidth;
	struct tTriggerDirections directions;

	memset(&pulseWidth, 0, sizeof(struct tPwq));
	memset(&directions, 0, sizeof(struct tTriggerDirections));

	printf("Digital streaming...\n");
	printf("Press a key to start...\n");
	_getch();

	// Trigger disabled
	setTrigger(unit, NULL, 0, NULL, 0, &directions, &pulseWidth, 0, 0, 0, 0, 0);

	streamDataHandler(unit, 0, DIGITAL);
}


// Peter. We do nor use this function

//****************************************************************************
//* digitalMenu
//* Displays digital examples available
//* Parameters
//* - unit        pointer to the UNIT structure
//*
//* Returns       none
//***************************************************************************
void digitalMenu(UNIT *unit)
{
	char ch;
	int16_t enabled = TRUE;
	int16_t disabled = !enabled;

	disableAnalogue(unit);					// Disable Analogue ports;
	setDigitals(unit, enabled);				// Enable Digital ports

	ch = ' ';
	while (ch != 'X')
	{
		printf("\n");
		printf("\nDigital Port Menu\n\n");
		printf("B - Digital Block Immediate\n");
		printf("T - Digital Block Triggered\n");
		printf("A - Analogue 'AND' Digital Triggered Block\n");
		printf("O - Analogue 'OR'  Digital Triggered Block\n");
		printf("S - Digital Streaming Mode\n");
		printf("V - Digital Streaming Aggregated\n");
		printf("X - Return to previous menu\n\n");
		printf("Operation:");

		ch = toupper(_getch());

		printf("\n\n");
		switch (ch)
		{
			case 'B':
				digitalBlockImmediate(unit);
				break;

			case 'T':
				digitalBlockTriggered(unit);
				break;

			case 'A':
				andAnalogueDigitalTriggered(unit);
				break;

			case 'O':
				orAnalogueDigitalTriggered(unit);
				break;

			case 'S':
				digitalStreamingImmediate(unit);
				break;

			case 'V':
				digitalStreamingAggregated(unit);
				break;
		}
	}

	setDigitals(unit, disabled);		// Disable Digital ports when finished
	restoreAnalogueSettings(unit);		// Restore analogue channel settings
}

/*

*/

/****************************************************************************
* main
*
***************************************************************************/
// int32_t main(void)
int main(void)
{
	char ch;
	UNIT unit;

    uint32_t nBlocks; // to write number of blocks after asking


	printf("Picoscope averager for PS3000A. Version 1.9.\n");
	printf("\nOpening the device...\n");

	//PICO_STATUS status;
	//status = openDevice(&unit);
	openDevice(&unit);

	ch = '.';

	while (ch != 'X')
	{
		displaySettings(&unit);

		printf("\n\n");
		printf("Please select one of the following options:\n\n");
		printf("S - Single triggered sample             A - Average of %d samples\n", mySetting.nWaveForms);
		printf("U - Untriggered sample                  N - Average of N * %d samples\n", mySetting.nWaveForms); // %ld // %ld   (int / signed int - %i или %d)
		printf("I - Immediate streaming                         V - Voltage range (mV)\n");
		printf("W - Triggered streaming                         T - Timebase\n");

		if(unit.sigGen != SIGGEN_NONE)
		{
			printf("G - Signal generator\n");
		}

		if(unit.digitalPorts > 0)
		{
			printf("D - Digital Ports menu\n");
		}

		printf("                                              P - Parameters/setting\n");
		printf("                                              	X - Exit\n");
		printf("Operation: ");

		ch = toupper(_getch());

//		printf("\n\n");

		switch (ch)
		{
			case 'U':
				collectBlockImmediate(&unit);
				break;

			case 'S':
				collectBlockTriggered(&unit);
				break;

            case 'A':
                collectRapidBlock(&unit, 1);
                break;

			case 'N':
                // Request the number of required blocks (1 block = 25000 frames, 1 frames = 1024 samples)
                printf("\n");
                printf("Enter the number of blocks (each block is %u frames): ", mySetting.nWaveForms); // %lu (unsigned long)
                std::cin >> nBlocks;
//                fflush(stdin);
//                scanf_s("%lud", &nBlocks);
			    collectRapidBlock(&unit, nBlocks);
				break;

			case 'P':
			    printf("C - change parameters, D - restore default, S - save current\n");
				ch = toupper(_getch());
				switch(ch)
				{
				    case 'C':
				        changeParameters(&unit);
				        break;
                    case 'D':
                        restoreParameters();
                        break;
                    case 'S':
                        saveParameters();
                        break;

				}
				break;

            case 'I':
				collectStreamingImmediate(&unit);
				break;


			case 'W':
				collectStreamingTriggered(&unit);
				break;

			case 'E':

				if (unit.ETS == FALSE)
				{
					printf("This model does not support ETS\n\n");
					break;
				}

				collectBlockEts(&unit);
				break;

			case 'G':

				if (unit.sigGen == SIGGEN_NONE)
				{
					printf("This model does not have a signal generator.\n\n");
					break;
				}

				setSignalGenerator(unit);
				break;

			case 'V':
				setVoltages(&unit);
				break;

			case 'T':
				setTimebase(&unit);
				break;

			case 'D':

				if (unit.digitalPorts)
				{
					digitalMenu(&unit);
				}
				break;

			case 'X':
				break;

			default:
				printf("Invalid operation\n");
				break;
		}
	}

	closeDevice(&unit);

	return 0;
}
