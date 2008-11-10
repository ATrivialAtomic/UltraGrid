/*
//    Part of the DVS (http://www.dvs.de) *DVS*VERSION* SDK 
//
//    This is the sv/svram program. Here you can find the source
//    code that is using most of the setup functions or control 
//    functions of DVS DDR or DVS Videocards.
//
//    SDK: Note that these functions are used by the sv program,
//         the calling convention can change, copy the routines
//         into your application if you want to use them.
//
*/

#ifndef _SV_SUPPORT_H_
#define _SV_SUPPORT_H_

#if defined(__STDC__) || defined(WIN32)
#if !defined __PROTOTYPES__
#define __PROTOTYPES__
#endif
#endif

void sv_support_preset2string(
#ifdef __PROTOTYPES__
	int         preset,
	char *      tmp,
  int         tmpsize
#endif
);


int sv_support_string2preset(
#ifdef __PROTOTYPES__
	char *  preset
#endif
);


int sv_support_string2videomode(
#ifdef __PROTOTYPES__
	char *  string,
	int	offset
#endif
);


char* sv_support_videomode2string(
#ifdef __PROTOTYPES__
	int	videomode
#endif
);

char* sv_support_iomode2string(
#ifdef __PROTOTYPES__
	int iomode,
  char * buffer,
  int buffersize
#endif
);

char* sv_support_iomode2string_mode(
#ifdef __PROTOTYPES__
	int	iomode
#endif
);

char* sv_support_colormode2string_mode(
#ifdef __PROTOTYPES__
	int	videomode
#endif
);

char* sv_support_bit2string_mode(
#ifdef __PROTOTYPES__
	int	videomode
#endif
);

int sv_support_string2syncmode(
#ifdef __PROTOTYPES__
  char *  name,
  char *  postfix
#endif
);

void sv_support_syncmode2string(
#ifdef __PROTOTYPES__
  int     syncmode, 
  char *  buffer, 
  int     buffersize
#endif
);

int sv_support_string2syncout(
#ifdef __PROTOTYPES__
  int     argc,
	char ** argv
#endif
);

void sv_support_syncout2string(
#ifdef __PROTOTYPES__
  int syncmode, 
  char * buffer, 
  int buffersize
#endif
);

void sv_support_analog2string(
#ifdef __PROTOTYPES__
  int     mode, 
  char *  string, 
  int     size
#endif
);

void sv_support_vtrinfo2string(
#ifdef __PROTOTYPES__
	char *  string,
	int	size,
	int	info
#endif
);

char * sv_support_devmode2string(
#ifdef __PROTOTYPES__
	int	devmode
#endif
);

int sv_support_string2iomode(
#ifdef __PROTOTYPES__
  char * string,
  int offset
#endif
);

char * sv_support_channel2string(
#ifdef __PROTOTYPES__
  int channel
#endif
);

#endif

