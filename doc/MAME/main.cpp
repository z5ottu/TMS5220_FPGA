#include <emu.h>

#define STAT_TS (1<<7)
#define STAT_BL (1<<6)
#define STAT_BE (1<<5)
#define MAX_SAMPLE 1

/**********************************************************************************************
  - Main
***********************************************************************************************/
int main(int argc, char *argv[])
{
	tms5220_device *m_tms5220;
	int sampleRate = 8000;
	int i=0, j=0, bufptr=0, s=0x60;
	int16_t buffer[MAX_SAMPLE];
	FILE *fp;
	//ces.lpc
	unsigned char data[3651]={0x80,0xd2,0x11,0xdc,0x54,0x4d,0x52,0x4a,0xb2,0x11,0x53,0xdf,0x98,0x2d,0x2d,0x4e,0x8d,0x63,0x62,0xa7,0x34,0x69,0x76,0xb3,0x72,0x1a,0xd2,0x64,0xb0,0x2c,0xd2,0x59,0x48,0xb3,0x81,0xb6,0x4a,0x67,0x25,0x29,0x86,0xc3,0x3d,0xa6,0xb4,0x64,0x38,0x16,0x0f,0xab,0x1d,0x80,0x35,0xb7,0x1d,0xb0,0xe7,0x8e,0x03,0x76,0xbf,0x71,0xc0,0x1e,0xd7,0x0e,0x58,0x65,0xab,0x48,0x5d,0x31,0x5b,0x75,0xec,0x94,0x15,0x4e,0x35,0x6d,0x54,0x42,0x5a,0x04,0x4e,0x17,0x2b,0x0d,0x62,0x14,0xd2,0x9d,0xec,0x38,0xc8,0x4e,0x65,0x79,0x9a,0x6a,0xa7,0x70,0x93,0xe5,0xe9,0x8e,0x95,0xce,0x4c,0x8e,0x35,0xbb,0x4e,0xc6,0x54,0x8e,0x62,0x6e,0xcf,0x00,0x3f,0xba,0x39,0xe0,0x6a,0xcb,0xb2,0x77,0x9b,0xe1,0xa6,0x94,0x8c,0x9b,0x58,0x58,0x9a,0x26,0x56,0xbe,0xcc,0xed,0xce,0x5a,0xc7,0x04,0x66,0x7a,0x19,0x44,0x1b,0x17,0xda,0x65,0x5a,0x58,0x75,0x42,0xe4,0xbb,0xd8,0x72,0xce,0x09,0x71,0x68,0x14,0x6b,0xd1,0x38,0xc5,0xb1,0x91,0xaf,0x65,0x92,0x90,0xc4,0xca,0xf2,0x1e,0x71,0x42,0x9a,0x1a,0xe9,0x49,0x36,0x0a,0x69,0x99,0xa4,0x4b,0x39,0x55,0xed,0xb9,0x61,0xb6,0xf6,0x12,0x24,0xa4,0x24,0x3e,0x51,0xdd,0xc8,0x35,0x92,0x67,0x9a,0xa5,0x45,0xd7,0x2c,0x91,0xab,0x92,0x04,0xd0,0xd1,0x7c,0xb8,0x6a,0xd8,0x0e,0xf1,0x08,0x5a,0x2e,0xed,0x78,0x14,0x35,0x98,0x9a,0x8e,0xad,0x52,0x54,0x27,0x2a,0xb2,0x0a,0x5d,0x11,0x05,0x65,0xf9,0xb2,0x72,0x79,0x10,0x94,0x1d,0xcb,0x3a,0xe4,0x49,0x93,0x5b,0x8f,0xa3,0x91,0xb6,0xaa,0x8a,0xd5,0x2e,0x56,0xdc,0xb3,0x3a,0x4d,0xd9,0x5c,0x61,0xf5,0x16,0x3a,0x61,0xf9,0x04,0x35,0x5a,0xe8,0x84,0x9c,0x15,0x54,0xeb,0x29,0x55,0x56,0x5a,0x5c,0xb4,0xb7,0x84,0xdb,0x29,0x79,0xb2,0x65,0x11,0x1c,0x27,0x55,0xd1,0xb6,0x45,0x60,0xdd,0xd4,0xc4,0x10,0x11,0x22,0xf1,0x42,0x1b,0x83,0x87,0x51,0x24,0x31,0x7d,0x30,0xa9,0xc1,0x1d,0x45,0x0c,0x09,0x9b,0x65,0x78,0x1c,0x04,0x1c,0x13,0x22,0x80,0xeb,0xcb,0x19,0xf0,0x5c,0x86,0x00,0xbe,0x8f,0x50,0xc0,0x33,0x95,0x02,0xf8,0x7a,0x12,0x01,0x5f,0xa7,0x13,0xe0,0xb8,0x2d,0x00,0xe4,0x0e,0x47,0x62,0xd9,0xb6,0x5d,0x31,0x02,0x8a,0xcc,0x98,0x4a,0x45,0xf7,0xa8,0x3a,0x43,0xa9,0x94,0x23,0x92,0x72,0xae,0xc5,0x56,0x8e,0x28,0x42,0x71,0x96,0x4a,0xd9,0xa2,0xb0,0xfa,0xc6,0x0a,0x55,0xb6,0xac,0x56,0x2b,0xc9,0x54,0x56,0x73,0x47,0x05,0x2d,0x55,0x49,0x23,0x1b,0x6d,0x8c,0x58,0x43,0x9c,0x4d,0x47,0xd0,0x11,0xc0,0x8a,0xe9,0xa5,0xee,0xda,0x44,0x38,0x5a,0x97,0x7a,0xa8,0x62,0x45,0x5b,0x2c,0x80,0x1f,0xb2,0x04,0xf0,0x6b,0x85,0x00,0x7e,0x49,0x17,0xc0,0x2f,0x91,0x2d,0xaa,0x32,0x2c,0xb9,0x23,0x8d,0xa8,0x19,0x29,0xd7,0x8e,0xdc,0xe2,0x62,0xb4,0xdc,0x32,0xaa,0x8b,0x93,0xc1,0x76,0xf7,0xb8,0x2a,0xf6,0x9a,0xaa,0x22,0xed,0xb0,0xd8,0x4b,0x8f,0x50,0x8f,0xed,0x92,0x50,0x54,0x33,0xbd,0x75,0x48,0x63,0x66,0x3b,0xb3,0xba,0x29,0xcf,0x45,0x68,0x53,0x16,0x95,0x22,0x67,0x96,0x0d,0x5d,0x54,0xca,0x14,0xd8,0x2e,0xb5,0x76,0xa8,0xa3,0xe7,0x98,0xb0,0xb8,0xa2,0xcb,0xc6,0xc4,0xd4,0xe2,0x88,0xb6,0x38,0x75,0x77,0x95,0xa3,0xea,0x28,0xd4,0xc2,0xdd,0x69,0x28,0x93,0x34,0x09,0xef,0x5a,0xad,0xac,0xd9,0xd8,0x75,0x1d,0xb5,0xb2,0x16,0x71,0xce,0x76,0xd8,0xca,0x5e,0xc4,0x38,0xc7,0x45,0x29,0x7b,0x25,0x95,0x5c,0x87,0xa1,0x1a,0x8d,0x98,0xfd,0x55,0x98,0x66,0x44,0x63,0x96,0xb4,0x9a,0x9e,0xd9,0x2a,0x4c,0x32,0x32,0x03,0xd6,0xda,0x60,0xc0,0x6e,0xa9,0xa1,0x1c,0x09,0x45,0x6f,0x44,0x85,0x6a,0x44,0x34,0xb9,0xa2,0x69,0x9a,0x28,0xd8,0xc7,0x1b,0x29,0x6b,0xa5,0x94,0xf3,0x34,0xce,0xa1,0x9f,0xce,0x55,0x55,0x6d,0x33,0xe0,0x96,0x28,0x01,0xbc,0xe1,0x29,0x80,0xe7,0x2b,0x19,0xb0,0x75,0x7a,0x2a,0x8b,0x91,0x92,0x58,0x47,0xa9,0xca,0x9a,0x27,0xbc,0x6c,0x9b,0x26,0x6b,0xae,0x94,0x8c,0xa2,0xba,0x62,0xd8,0xcd,0xcc,0x89,0x6b,0x93,0xe4,0xca,0xf4,0xd0,0xae,0x8d,0x42,0x32,0xc2,0xa2,0xb8,0x2e,0x6b,0xe2,0xa8,0xb6,0x1c,0xba,0xee,0x51,0xa5,0x3b,0x85,0xe9,0x47,0x02,0xd1,0x6d,0x07,0x66,0x98,0x19,0xd1,0x6a,0x6d,0x99,0x61,0x36,0x62,0xea,0x75,0xe4,0xc6,0x59,0x49,0x24,0xc7,0x96,0x9b,0x66,0x67,0xa5,0xae,0x58,0x61,0x99,0x5d,0x0c,0xa7,0x12,0xa6,0x7d,0x0e,0x35,0xea,0x4c,0x14,0xce,0x39,0xd5,0xb1,0xb3,0x71,0x38,0xe7,0xcd,0x40,0xcb,0x26,0x66,0x5c,0x37,0x1c,0xac,0xe2,0x98,0x61,0x2e,0x37,0xf4,0x8a,0xc3,0xae,0xf9,0x66,0x9a,0x2c,0x09,0x5a,0xe6,0xa9,0x32,0x74,0x29,0x04,0xd8,0xee,0x5a,0x00,0xdb,0xac,0x11,0x60,0xd9,0x35,0xf5,0x0f,0xd3,0xcc,0xa4,0xa1,0x49,0xdb,0x6d,0x30,0x63,0x84,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xcd,0x61,0x85,0x15,0x89,0x46,0xde,0x03,0x97,0x54,0x3b,0x68,0xc5,0x08,0x54,0x1a,0xe5,0xc0,0x94,0x49,0x52,0x49,0xa6,0x22,0x57,0x06,0x25,0x19,0xd1,0xb2,0x5a,0xd1,0xa2,0x18,0xfb,0xaa,0x18,0x45,0x1f,0x62,0x92,0xe3,0x62,0x14,0x7d,0xb0,0x4a,0x8f,0x83,0x51,0x8c,0x26,0xc6,0x5b,0x31,0x46,0x3e,0x2a,0x87,0x6e,0x56,0x1c,0x79,0x8b,0xdc,0xb6,0x65,0x73,0x24,0xd5,0xeb,0xd8,0x46,0xac,0x15,0x95,0xa8,0xed,0x5d,0xb2,0x47,0xd0,0x12,0x57,0x64,0xcb,0x0a,0xfe,0x48,0x69,0x66,0x6e,0x6b,0x5c,0xb3,0x6d,0x45,0xa8,0x13,0x03,0xac,0x7a,0x63,0x80,0x55,0x6f,0x0c,0xb0,0xda,0x75,0x33,0xa7,0x35,0x73,0xd7,0xc6,0xcd,0x2e,0xc6,0x5b,0x35,0x3c,0x27,0x27,0xda,0x69,0xd2,0x4e,0x5d,0xdc,0x24,0xba,0xd8,0xdb,0x75,0xf3,0x2b,0xb3,0xb4,0x68,0xd7,0x25,0xec,0x9a,0x55,0x72,0x63,0x99,0xb8,0x70,0x36,0x8f,0xb4,0x43,0x52,0xcf,0xc4,0xb2,0xda,0x8e,0x4b,0x9b,0x45,0xb5,0xa8,0x36,0x29,0x1b,0x91,0x58,0x6a,0x53,0xbb,0x7c,0x16,0x24,0xee,0x4d,0x49,0xf2,0x99,0x80,0x35,0x2a,0x31,0x01,0x76,0xcb,0x4e,0xd9,0xca,0xc2,0x98,0x15,0xbb,0x65,0x63,0x08,0x73,0x6d,0xc2,0x91,0x8f,0x65,0x86,0x3e,0x2e,0x46,0x3e,0x9a,0x3a,0x56,0x25,0x68,0xc5,0xa8,0x1c,0xd4,0x19,0xa3,0x14,0xa3,0x50,0x62,0xb5,0x0b,0x57,0x56,0x0d,0x19,0xd1,0x0e,0x53,0x39,0x03,0x2b,0xbb,0xc7,0x36,0xc0,0xe9,0x33,0x0e,0xd8,0xe5,0xc6,0x01,0xab,0xdd,0x38,0x60,0x8d,0x1b,0x07,0xac,0x7e,0x63,0x80,0x35,0xae,0x9b,0xdf,0xa3,0x32,0x7b,0xd7,0x1e,0x7e,0x0b,0x62,0x32,0x9d,0xa8,0x05,0x45,0x4b,0x44,0x96,0x5d,0x15,0xf5,0xa0,0xaa,0xea,0x72,0x90,0x3b,0x63,0x9b,0x9a,0xa7,0x66,0xc3,0x8a,0x15,0xa1,0x66,0x3b,0xe5,0xcd,0xa9,0x4a,0x54,0xec,0x52,0x8d,0x24,0x46,0xdd,0x09,0xd3,0x38,0x8a,0x98,0x54,0xc7,0x0a,0xcb,0x48,0xec,0x3c,0x2e,0x45,0xad,0x4d,0x51,0x6b,0xb1,0x63,0xb5,0x36,0x43,0xad,0x21,0x4e,0xc4,0x52,0x15,0x0d,0x17,0xa7,0x62,0x4b,0x92,0x32,0x58,0xd2,0x48,0xcc,0x45,0x51,0x73,0x73,0x2a,0xd6,0x57,0x41,0xc5,0x25,0x8e,0x48,0x57,0xb4,0x38,0x3a,0xb7,0x42,0x75,0xb7,0x96,0xe8,0xe4,0x08,0x8d,0xc3,0x7b,0x71,0xa8,0x23,0xf4,0xb7,0xd2,0xad,0x6e,0x8a,0x01,0x00,0x4c,0x3e,0x1b,0x31,0xf7,0xd8,0x4a,0xc5,0xa8,0x28,0xbc,0x65,0x31,0x95,0x23,0xb3,0xc2,0xb5,0xc4,0x50,0x35,0x47,0x46,0xdb,0x0a,0x54,0x6d,0x15,0xb7,0x77,0x32,0x52,0x75,0x50,0xd4,0x36,0xc9,0x42,0xd5,0x5e,0x73,0xe9,0xb4,0x4a,0x57,0x07,0xc3,0x9e,0xd6,0x8a,0x4a,0x5d,0xa2,0xa4,0x64,0xcb,0x6c,0x75,0x0b,0x92,0xe6,0x23,0xb9,0xd5,0xbd,0xb0,0x53,0xb5,0xa4,0x52,0xf7,0x46,0xaa,0x39,0x96,0x52,0x3d,0x1a,0xaa,0xf6,0xda,0x34,0xf5,0x28,0xa8,0x94,0xeb,0x42,0xac,0xb3,0xb4,0xb2,0xab,0xed,0x32,0xad,0x76,0xa5,0xaa,0x96,0x04,0xb0,0x67,0x27,0x03,0xce,0x4a,0x0b,0xe5,0x70,0xc8,0x31,0x4b,0x3a,0x54,0x23,0xa1,0xe8,0x0e,0x25,0xd7,0x14,0x85,0xd1,0x5d,0x88,0x54,0xa3,0x94,0x4c,0x84,0x69,0x36,0x6d,0xe0,0xea,0x5d,0xe9,0x98,0x01,0x2b,0x94,0x0b,0xe0,0xa5,0x30,0x05,0xfc,0x9c,0xa1,0x80,0x5f,0x32,0x14,0x70,0x73,0x66,0xc9,0x8b,0xd4,0x48,0x9d,0x48,0xa5,0x88,0xda,0x63,0x7c,0x2c,0x87,0x2a,0xa9,0x88,0xd6,0xb2,0x24,0xda,0x2c,0xc5,0xdd,0x2c,0xb6,0x69,0x8b,0x64,0x4f,0xf5,0xa8,0xae,0x49,0x52,0xa2,0xbc,0x02,0xab,0xc6,0x48,0xad,0xf2,0x92,0xed,0xda,0x22,0x31,0xb2,0x8a,0x92,0xeb,0xba,0x41,0x8b,0x69,0x48,0xae,0x1f,0x0e,0x55,0xb7,0x69,0x9a,0xa1,0x7b,0x54,0x9b,0xa2,0x25,0xc6,0x28,0x29,0x33,0x92,0x95,0x1a,0xa3,0xe4,0x4c,0x0d,0x27,0x61,0xa8,0x51,0x8d,0xb5,0x62,0xa5,0xa1,0x26,0x77,0x89,0x96,0x95,0xc6,0x12,0x32,0x25,0x4a,0x56,0x98,0x8a,0xcd,0xd2,0x48,0x25,0x61,0x29,0x2e,0x93,0x33,0x15,0xbb,0xad,0xf8,0x48,0xc9,0x52,0x1c,0x8e,0x1e,0xbd,0x29,0xca,0x76,0xb8,0x47,0xb1,0x16,0xad,0xd8,0x66,0xef,0xbb,0x56,0x43,0x53,0xbb,0x61,0x4c,0x6f,0xd2,0x72,0x25,0xd6,0x5e,0xd4,0x9c,0xca,0x36,0xda,0x5a,0x20,0x37,0x1e,0xc7,0xa4,0xec,0x55,0x8b,0x35,0x34,0x8b,0xac,0xd7,0xcc,0x50,0x95,0xcb,0xc6,0x51,0xd2,0x4c,0x2d,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb0,0xbf,0x5b,0x15,0x63,0x77,0x9c,0x8a,0xec,0xd4,0xd4,0x26,0xb6,0x02,0xaa,0x92,0x50,0xc0,0x8a,0x21,0x0a,0x58,0xa9,0x43,0x01,0x33,0xa6,0xa5,0x21,0x55,0xd3,0x08,0x4f,0x53,0xdc,0x52,0x5d,0x3c,0x3c,0x69,0xb3,0x6b,0x49,0x51,0x8b,0xba,0xc3,0x2a,0xce,0x59,0x23,0xe3,0x38,0xe0,0xeb,0x52,0x05,0xfc,0xb8,0xa1,0x80,0x9f,0xdb,0x18,0xf0,0x7d,0x79,0x1a,0x66,0xe8,0x0c,0x31,0x87,0xad,0x1d,0xde,0x34,0x28,0x6c,0x1e,0xab,0x3a,0x4b,0xf5,0xb1,0xb5,0xec,0x1a,0x22,0xa9,0x47,0xf2,0x70,0x4a,0x0a,0x97,0x58,0x29,0xc9,0x4d,0xda,0x92,0xb5,0x1d,0x3b,0x37,0x0a,0x6e,0xcd,0xd0,0xe0,0xbc,0xc0,0xb5,0xcd,0x53,0x51,0xf2,0x0b,0x97,0xf2,0x68,0x4b,0x2d,0xa8,0x92,0x2b,0xab,0x23,0xb5,0x28,0x2b,0xee,0x8e,0x8c,0x1a,0x62,0x1f,0x3d,0x5c,0x62,0x8e,0x49,0x4c,0x0f,0x33,0xf6,0x2c,0x26,0xb1,0x5b,0x35,0xa4,0xd2,0x84,0xd8,0x2f,0xe6,0xb5,0x68,0x9a,0x92,0x98,0xc5,0xce,0xb5,0x69,0x49,0x73,0x26,0xdf,0xf0,0x46,0x2d,0xcd,0x89,0xbd,0x23,0x52,0x95,0x24,0x05,0x89,0x0a,0x73,0x13,0x92,0xe2,0xdc,0x4d,0xd5,0x49,0x88,0x67,0xaa,0x4c,0x37,0xd9,0x69,0x28,0x31,0x55,0xc5,0xe3,0x24,0x3f,0x1f,0x8a,0x64,0x9f,0x92,0x82,0x72,0xd1,0x52,0xbc,0x49,0x89,0x6a,0x73,0x65,0xf5,0x24,0x2d,0x9d,0x7d,0xbb,0xd2,0x2c,0x2b,0x60,0xac,0x6d,0x05,0x8c,0xb9,0xa3,0x80,0xb9,0x6e,0x0c,0x30,0xd7,0xcd,0xb8,0x67,0xbf,0xae,0x49,0xcb,0x23,0xaa,0x5e,0xcd,0xbc,0x9a,0x8c,0xa8,0x68,0x0b,0xf7,0x9c,0xd2,0xe2,0xac,0xb3,0x54,0xa2,0x4a,0x89,0xa3,0xde,0xe0,0x90,0xa6,0x29,0xf6,0xae,0x22,0x8c,0xeb,0xa6,0x38,0xa9,0x28,0x49,0x6e,0x1b,0xe2,0x24,0x34,0xbc,0xd5,0x55,0x49,0x8a,0xc8,0xe0,0xcc,0x24,0x25,0x2f,0xaa,0x93,0x2c,0xa3,0x96,0xb2,0xc8,0x18,0xb1,0x0c,0x93,0xaa,0x22,0x72,0x4d,0x23,0x68,0xaa,0x93,0xee,0x16,0x8d,0x28,0xa9,0x89,0x6e,0x5a,0x35,0xac,0xa4,0x2e,0x85,0x2e,0x8e,0xb6,0x92,0xfa,0x14,0xab,0x29,0xdb,0x72,0xea,0x53,0xcc,0xe6,0x98,0xc8,0xa9,0xcf,0x2e,0x46,0x75,0x62,0xa7,0xbf,0x49,0xd3,0x50,0xb6,0x14,0xde,0x69,0x42,0x4d,0xd4,0xb2,0x4b,0x66,0x48,0x73,0x33,0x4b,0x61,0x9a,0x71,0x22,0xcc,0x6d,0x31,0x60,0xe5,0x0a,0x06,0x2c,0xd7,0xe1,0xd6,0x69,0xd3,0x5d,0xc5,0x0c,0x19,0x1b,0x75,0x8b,0xd0,0xa8,0xa8,0x0d,0xba,0x32,0x4c,0x9d,0x01,0xf2,0x9b,0x30,0x33,0x77,0xa7,0xa8,0x64,0xa9,0x2a,0x94,0x55,0x8b,0x5a,0xd4,0xc8,0x20,0x73,0xa4,0x2a,0x13,0x3b,0x99,0x22,0x59,0xaa,0xa2,0xca,0x4e,0xd6,0xba,0xad,0x2a,0xca,0x32,0x34,0xaf,0xb4,0xba,0x18,0x4b,0xb7,0x99,0xdc,0xea,0x6c,0xcd,0x3d,0xa7,0x52,0x69,0x8a,0x53,0xb7,0x9c,0x9a,0xa5,0x29,0x5a,0x5d,0xec,0x62,0xa7,0xa6,0x48,0x09,0xd7,0x8d,0x14,0x9a,0x86,0x43,0x42,0x73,0x91,0x00,0x9e,0x0e,0x13,0xc0,0x8f,0xa9,0x0c,0xf8,0x21,0xdd,0xf4,0x5d,0xb9,0x06,0xf6,0xe2,0x14,0x0c,0xbb,0xd9,0x24,0xb5,0x43,0xde,0xa3,0x39,0x65,0x27,0x2e,0x45,0xcd,0xe2,0x5a,0x9d,0xb0,0x95,0x25,0x89,0xa7,0x6f,0xca,0x52,0xd6,0x28,0x29,0x3a,0x1e,0x55,0xd3,0x92,0xba,0x71,0xa8,0x42,0x45,0xab,0x11,0xc1,0xe9,0xd5,0x14,0x33,0x65,0x94,0xb9,0x9d,0x52,0x36,0xc9,0xde,0x56,0x51,0x52,0x95,0x58,0x54,0xbb,0xc6,0x15,0x4d,0x10,0x31,0xce,0x6a,0x57,0xf4,0xd5,0x90,0x85,0x6b,0x1c,0x56,0x7b,0xad,0x1d,0x6e,0x76,0x4c,0x61,0x62,0xb6,0x09,0x2b,0x49,0x79,0xd4,0xe9,0xa9,0x5c,0xb5,0xa5,0x35,0x88,0xab,0x54,0xb5,0x12,0xb7,0xc8,0x49,0x39,0xa9,0x5d,0x5c,0x35,0x86,0xa7,0xc7,0x4a,0xf1,0x7c,0x9d,0x6a,0x6a,0xc5,0x00,0xab,0x6d,0xa7,0x7f,0xa6,0x49,0x2f,0x89,0x93,0x82,0x12,0x4c,0xd4,0x23,0x4e,0x8a,0x52,0x61,0x9e,0xf0,0x24,0x21,0x89,0x85,0xf9,0x52,0x9b,0x86,0x2c,0x35,0xe2,0x35,0x6f,0xea,0xf2,0x54,0x15,0xd6,0xb5,0xae,0x28,0x73,0x73,0x68,0xb6,0xa4,0xa8,0xa9,0xa1,0x3d,0x58,0x1c,0xa5,0xba,0xd5,0x89,0xf2,0x74,0x9c,0xde,0x9e,0xd6,0x43,0x4c,0x56,0x4a,0x7a,0x4c,0x31,0xb2,0x3a,0x25,0xaf,0x46,0x25,0xa5,0x23,0x9b,0x32,0x4a,0x8e,0x92,0x65,0x6d,0xaa,0x2c,0x30,0x3b,0xca,0x8a,0x00,0x4e,0x5c,0x17,0xc0,0x4f,0x19,0x02,0xf8,0xa1,0x4a,0x00,0x3f,0x67,0x29,0xe0,0x29,0x97,0xe2,0x57,0x25,0x9a,0x52,0x73,0x52,0x50,0x34,0x67,0x4a,0x55,0x35,0x41,0x76,0x10,0xeb,0x15,0xc6,0x84,0x39,0x40,0x8c,0x8d,0x65,0x13,0x05,0x2f,0xbe,0xec,0xe1,0x43,0x1c,0x4a,0xd0,0x3a,0x4f,0x09,0x69,0x88,0x45,0xd3,0x54,0xbb,0x64,0x31,0xba,0x6c,0x6b,0xad,0x96,0xa7,0x20,0x3d,0xe6,0x71,0x5a,0x91,0xac,0x77,0x8b,0x37,0x2d,0x45,0xd4,0xd9,0x4d,0xd1,0x24,0x14,0x51,0x76,0x25,0x66,0xbd,0x50,0x24,0x91,0xdd,0x94,0x51,0x5a,0x99,0x74,0x56,0x5a,0xc7,0x6e,0x65,0xb5,0xdc,0xe9,0x1d,0xbb,0x55,0xa3,0x1b,0x87,0xd9,0xec,0xd0,0x8e,0x50,0x1d,0x45,0x96,0xd5,0x3d,0x43,0x4e,0x34,0x4b,0x0e,0xd3,0xac,0x5e,0xd5,0xe6,0xa4,0x7d,0x23,0x4e,0x57,0x57,0xec,0xf6,0xf5,0x30,0xd5,0x65,0xa2,0xd3,0xdf,0x42,0x55,0x98,0x39,0x29,0x69,0xca,0x56,0xae,0x51,0x65,0x64,0xc5,0x69,0xb7,0x79,0xdc,0x96,0x77,0xcb,0x13,0x11,0x96,0x5b,0xde,0x83,0x34,0x77,0xc4,0x4a,0x79,0xf7,0x54,0x14,0xa5,0xb1,0x14,0x2d,0x6a,0x88,0x8c,0xab,0x56,0xf6,0xca,0x89,0xd5,0x1e,0x52,0x3d,0x16,0x05,0x4c,0xa5,0x10,0x40,0xcf,0xa4,0x0a,0xe8,0xad,0x52,0x01,0x33,0x4f,0x1b,0x60,0xe5,0x59,0x03,0xcc,0x7e,0x6d,0x80,0x39,0xae,0x0d,0x30,0xe7,0x8d,0x01,0xe6,0xb8,0x2e,0x65,0xb3,0x6a,0xea,0xd1,0xb2,0xd4,0xc5,0x48,0x54,0x76,0x98,0xd2,0x65,0x6b,0xd1,0x91,0x71,0x52,0x9f,0x5c,0x44,0x6a,0xd4,0x09,0x7d,0x0c,0x19,0x6e,0x51,0x27,0xf4,0xd1,0x65,0xab,0xe4,0x64,0xd7,0x27,0x93,0x6d,0xac,0x93,0x54,0x1f,0x5d,0x0c,0x53,0x8e,0x36,0x7d,0xb4,0x39,0x46,0x72,0x5b,0xf5,0x3e,0x57,0x13,0xc5,0x15,0xd1,0xf8,0x54,0x4d,0x14,0x67,0x48,0xe3,0xcb,0x34,0x72,0xcc,0x25,0xbd,0x0b,0x3d,0x42,0x3e,0x87,0x35,0xae,0x4f,0x30,0xdb,0x6d,0xd1,0xda,0xdd,0x2a,0x62,0xb3,0x55,0xeb,0x7a,0x46,0xa0,0xce,0x56,0xad,0xdb,0x49,0xa5,0xba,0xc8,0x74,0xa1,0x27,0x8d,0xf1,0x22,0xd3,0x85,0x1a,0x78,0xce,0x93,0x5c,0x97,0x86,0xd2,0x86,0x34,0x72,0x5d,0x6e,0x86,0xd9,0xe2,0xd6,0x74,0x79,0x2a,0xc9,0x98,0x5d,0xf6,0x97,0xd2,0x81,0xe4,0x76,0xd0,0xdf,0x5c,0xa5,0x93,0xca,0x01,0x00,0x00,0x40,0x7f,0xb3,0xe5,0x8a,0x39,0x07,0x01,0x4f,0x65,0x31,0xe0,0x87,0x4c,0x06,0xfc,0x98,0x29,0x80,0x9f,0xba,0x04,0xf0,0x73,0x95,0x00,0x7e,0xaa,0x14,0xc0,0x0f,0x1d,0x02,0x38,0x32,0x24,0x25,0x23,0x11,0x8b,0x5f,0xea,0x94,0x8e,0x8a,0xa4,0xb1,0x9d,0x43,0x36,0x2c,0x91,0x75,0x77,0x72,0xe9,0x70,0x48,0x71,0x93,0x08,0x01,0x6b,0x30,0x22,0x60,0x1d,0x42,0x04,0xac,0x89,0xe4,0x8a,0xa1,0x90,0x6b,0xdb,0x91,0x2b,0xa7,0x43,0xf2,0xab,0x58,0xa1,0x9c,0x0e,0x29,0xae,0x6d,0x87,0x62,0x7a,0x24,0x9b,0x49,0x1c,0x8a,0xd9,0x90,0xf5,0x5a,0xb1,0xab,0xe6,0x51,0x81,0xee,0xc4,0x64,0x1a,0x95,0x54,0x77,0x1b,0x92,0x71,0xee,0x1a,0x36,0x69,0x1b,0xde,0x5e,0x25,0x64,0xa3,0x4e,0x6b,0x7a,0xe0,0xb4,0xad,0xd8,0xad,0xae,0x4e,0xda,0x37,0x63,0xb5,0xa6,0x78,0xed,0x98,0x8c,0x5c,0xfa,0x1e,0xb4,0x74,0xa2,0x72,0x9b,0x5a,0x8a,0xe6,0xaa,0x26,0x69,0x6e,0xd1,0x9b,0x73,0x52,0xb9,0xb1,0x07,0x1b,0xb5,0x76,0xec,0xfe,0x6e,0xd3,0x8a,0x3d,0xb6,0x00,0x8e,0x74,0x11,0xc0,0x0f,0x16,0x0c,0xf8,0x31,0x9c,0x01,0xbf,0xb8,0x31,0xe0,0xc7,0x4c,0x06,0xfc,0x12,0xc5,0x80,0x5f,0xa3,0x18,0xf0,0x4b,0x34,0x02,0xbe,0xa9,0x14,0xe6,0x54,0x5f,0xe5,0x1e,0x09,0x3d,0x3d,0x4c,0xa5,0x66,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe4,0x8e,0x92,0x1d,0x92,0x59,0x42,0xda,0x82,0x25,0x67,0xdb,0x6c,0x79,0x4f,0xd6,0xe8,0x99,0xb0,0x14,0xcd,0x72,0xb1,0xb5,0xc2,0x90,0x47,0xa5,0xae,0x3a,0x2a,0x53,0x56,0x8c,0x3a,0xdb,0x31,0x6c,0x69,0xd7,0x92,0xae,0xab,0x60,0xa4,0xdd,0x6a,0xb8,0x8d,0xc3,0x95,0xf4,0x68,0xc5,0x3e,0x09,0x47,0xdc,0xa2,0x95,0xfa,0x26,0x49,0x4b,0x73,0xb2,0xea,0x9d,0x54,0xf9,0xd1,0x46,0xb9,0xb9,0x55,0x95,0xd8,0x50,0xa5,0x6a,0x76,0x5d,0xea,0xd2,0x14,0x71,0xc4,0x4d,0x59,0x52,0xde,0x42,0xd5,0xa4,0x64,0x45,0x9b,0x3b,0xd7,0xdc,0x96,0x35,0xa5,0xea,0xdc,0xf5,0x4a,0xde,0xb4,0x8a,0xf1,0x36,0x0d,0x45,0x55,0xa6,0x42,0x33,0xd7,0x95,0x95,0xa6,0x88,0xd4,0x2c,0x06,0x6c,0x6a,0xc6,0x80,0x1f,0x3d,0x18,0xf0,0x7d,0xa7,0x71,0xa7,0x5c,0x27,0x8c,0x4c,0x46,0x1d,0xb1,0x33,0x34,0xc8,0x98,0x60,0x16,0x11,0xb2,0x4d,0x9c,0xd2,0x59,0x45,0xd0,0x2f,0x71,0xc9,0xbb,0x27,0xea,0x18,0xb9,0x2d,0x9f,0x91,0x59,0xf5,0x64,0xb5,0x62,0x04,0x51,0x96,0x57,0x58,0xca,0xee,0xc5,0x58,0x4e,0x96,0x2b,0xa3,0x14,0x4f,0x5d,0xd5,0xa6,0x74,0x86,0x3b,0xbc,0x54,0x99,0x32,0x2a,0x2e,0xcd,0x88,0x19,0xb2,0x96,0xbc,0x49,0xad,0xb5,0x30,0x4b,0x76,0x57,0x8f,0xa6,0xc8,0xae,0xc1,0xc3,0xdd,0xe3,0x9a,0x24,0x0d,0xe1,0x35,0x5e,0x12,0x92,0x14,0x0b,0x66,0xa8,0x4e,0x4a,0xb2,0x1f,0xf0,0x95,0xd4,0x2d,0x4e,0x36,0x24,0x3b,0x12,0x8f,0xb8,0x4a,0xb1,0x8d,0x68,0x52,0xe2,0x8a,0xcd,0x2f,0x2c,0xae,0x8b,0x13,0xc9,0x6a,0x71,0xbb,0x29,0xc9,0x34,0x32,0xdc,0x93,0xb4,0xac,0xb2,0x50,0x8d,0x6a,0xd2,0x8a,0x61,0x94,0xdc,0x6a,0x4e,0xaa,0x47,0x66,0x12,0xb9,0xc6,0xa1,0x9d,0x5e,0x91,0x23,0x63,0xb1,0x69,0x5a,0x21,0x51,0xb7,0x2d,0x80,0xbd,0xa6,0x15,0xb0,0xe7,0xad,0x02,0xd6,0xf8,0x6e,0xd1,0xea,0xd7,0x19,0x22,0xb9,0x15,0x3d,0x3a,0xaa,0x65,0xe3,0x51,0x8e,0xce,0xaa,0xb6,0x89,0x46,0x39,0x06,0x9b,0xf8,0x39,0x18,0xe5,0xe8,0x6c,0x92,0x6b,0xa3,0x15,0xa3,0xb0,0x49,0xb5,0xcd,0x92,0xf7,0x8c,0x2a,0x3d,0x32,0x42,0x9e,0x14,0x55,0x46,0x33,0x76,0x79,0x54,0x1c,0xe3,0x61,0x27,0xe5,0x4d,0x32,0xe6,0x96,0x95,0x54,0x36,0x4b,0x1c,0xe3,0xb5,0x53,0x95,0x8d,0x68,0x86,0xb5,0x76,0x8d,0xb7,0xe9,0x1d,0x9c,0x52,0xb5,0x36,0x85,0x37,0xf1,0x62,0xd3,0x85,0xe8,0xb6,0xcc,0x53,0x54,0x1f,0xb3,0xc8,0x19,0xdf,0x32,0x43,0x6e,0xac,0xa7,0x3a,0xd9,0x8d,0xb9,0xb0,0x9c,0xc6,0x18,0x37,0xd6,0x2a,0x34,0x9a,0x63,0xdc,0xd8,0x06,0xab,0x69,0xc7,0x0e,0x53,0xef,0xa2,0xac,0x53,0xdb,0x4d,0xbd,0x8b,0xa8,0x4e,0xad,0x30,0xf5,0xa6,0xa2,0x52,0xb5,0xdd,0xd4,0xbc,0x9a,0x99,0x4f,0x55,0x73,0x35,0x6a,0x69,0x52,0x0b,0x2d,0xdd,0x29,0x89,0x98,0x6d,0xf6,0x77,0xeb,0x16,0xe1,0x72,0xcc,0x5d,0xbc,0x94,0xb9,0x38,0x71,0x75,0x96,0x98,0x6d,0x61,0xbb,0x34,0x45,0xab,0x95,0x95,0xa5,0xd4,0x54,0xcb,0x19,0x5e,0x92,0x4b,0xdb,0x12,0xbb,0xe4,0x48,0x4a,0x4d,0x4f,0x64,0x52,0x2b,0xd3,0x35,0xcd,0x83,0x76,0x8d,0x28,0xd1,0x16,0x89,0xd6,0xd9,0x92,0x18,0xb0,0xea,0x96,0x00,0x56,0xb9,0x60,0xc0,0xae,0x1b,0x04,0x58,0x39,0x39,0x34,0x23,0xa1,0xea,0x8c,0x28,0xd7,0x75,0x0b,0xe9,0x53,0x08,0x45,0x1f,0x24,0x75,0x7a,0xa2,0x52,0x43,0x10,0x12,0xe5,0x61,0x2b,0xf4,0xcb,0x85,0xa7,0x99,0x24,0x02,0xbc,0xa9,0xc9,0x80,0x9f,0xbd,0x18,0xf0,0x4b,0xa4,0x00,0x5e,0xc9,0x4c,0x79,0xa7,0xa6,0x6d,0xd9,0xb0,0x94,0x45,0x49,0xa5,0x6e,0xec,0x50,0x65,0xad,0xe5,0x36,0xb1,0x58,0xd7,0xa4,0x88,0xab,0x39,0x36,0x6d,0x55,0x6a,0x6e,0x1e,0xc7,0x74,0x49,0x72,0x78,0x5b,0x4d,0xd3,0x27,0x49,0x11,0x95,0xa6,0x5c,0x5f,0x35,0x99,0x67,0x5b,0x32,0x43,0x53,0x60,0xdd,0x09,0xc7,0x8c,0xc3,0x21,0x7b,0xb5,0x64,0x37,0xf6,0x80,0x1c,0xd1,0xb2,0xd4,0x58,0x24,0xa5,0x6b,0x33,0x56,0x63,0x91,0x98,0xa9,0xa5,0x38,0x0c,0xd5,0xa9,0x3b,0x8f,0xe4,0x34,0x14,0xe3,0x69,0x56,0xb2,0xd3,0x50,0x6c,0x94,0x7a,0xc9,0x76,0x63,0x72,0x15,0x1a,0xae,0x28,0x4c,0xc5,0x46,0x49,0xa4,0x15,0xb7,0x34,0x27,0xc5,0x15,0x91,0xcd,0xd6,0xb3,0x26,0xb5,0x97,0x71,0xdb,0xa8,0x92,0x94,0x19,0xd3,0xad,0x3d,0x72,0x50,0xb7,0x43,0x31,0x77,0x4f,0x41,0xde,0x0a,0xc9,0x98,0x35,0x87,0xea,0xb2,0x24,0x7e,0x8b,0x11,0x0a,0xc9,0x99,0xd5,0xc3,0x95,0x1b,0xbb,0x1c,0xf6,0x0e,0x3f,0x6e,0x66,0x4e,0xFE,0xFF
};

	struct type_wavhdr {
		unsigned char  ChunkID[4]     = {'R','I','F','F'};   // "RIFF"
		unsigned long  ChunkSize      = 0x24;                // file size (0x24 + data size in bytes)
		unsigned char  Format[4]      = {'W','A','V','E'};   // "WAVE"
		unsigned char  Subchunk1ID[4] = {'f','m','t',' '};   // "fmt "
		unsigned long  Subchunk1Size  = 16;                  // 16 (PCM)
		unsigned short AudioFormat    = 1;                   // 1 (Linear)
		unsigned short NumChannels    = 1;                   // 1 (Mono)
		unsigned long  SampleRate     = 8000;                // 8000 sampleRate
		unsigned long  ByteRate       = 16000;               // SampleRate * NumChannels * BitsPerSample/8
		unsigned short BlockAlign     = 2;                   // NumChannels * BitsPerSample/8
		unsigned short BitsPerSample  = 16;                  //  BitsPerSample
		unsigned char  Subchunk2ID[4] = {'d','a','t','a'};   // "data"
		unsigned long  Subchunk2Size  = 0;                   // NumSamples * NumChannels * BitsPerSample/8
	} wavhdr;

	m_tms5220 = new tms5220_device();
	m_tms5220->device_start();
	m_tms5220->device_reset();
	fp=fopen("out.wav", "wb");

	fwrite(&wavhdr,sizeof(wavhdr),1,fp);

	m_tms5220->data_w(0x60); // speak external command

	// send data stream
	i=0;
	while(i<sizeof(data)) {
		s = m_tms5220->status_r();
		if (s & STAT_BL) {
			m_tms5220->data_w(data[i]);
			i++;
		} else {
			m_tms5220->process((int16_t *)&buffer, MAX_SAMPLE);
			fwrite(buffer,sizeof(int16_t),MAX_SAMPLE,fp);
			bufptr += MAX_SAMPLE;
		}
	}

	m_tms5220->data_w(0xFF); // stop code
	// while talk status get remaining sound data
	while(s & STAT_TS) {
		s = m_tms5220->status_r();
		m_tms5220->process((int16_t *)&buffer, MAX_SAMPLE);
		fwrite(buffer,sizeof(int16_t),MAX_SAMPLE,fp);
		bufptr += MAX_SAMPLE;
	}

	wavhdr.Subchunk2Size = bufptr*2;
	wavhdr.ChunkSize = wavhdr.Subchunk2Size + 0x24;

	// update header
	fseek(fp,0,SEEK_SET);
	fwrite(&wavhdr,sizeof(wavhdr),1,fp);

	fclose(fp);
	delete m_tms5220;
	return(0);
}