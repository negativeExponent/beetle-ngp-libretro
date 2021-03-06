#ifndef __MDFN_MEDNAFEN_DRIVER_H
#define __MDFN_MEDNAFEN_DRIVER_H

#include <stdio.h>

#include "settings-common.h"

#ifdef __cplusplus
#include <vector>
#include <string>
extern std::vector<MDFNGI *>MDFNSystems;
#endif

/* Indent stdout newlines +- "indent" amount */
void MDFN_indent(int indent);


#ifdef __cplusplus
extern "C" {
#endif

void MDFN_printf(const char *format, ...);

#ifdef __cplusplus
}
#endif


#define MDFNI_printf MDFN_printf

/* Displays an error.  Can block or not. */
void MDFND_PrintError(const char *s);
void MDFND_Message(const char *s);

uint32 MDFND_GetTime(void);
void MDFND_Sleep(uint32 ms);

// Call this function as early as possible, even before MDFNI_Initialize()
bool MDFNI_InitializeModule(void);

/* allocates memory.  0 on failure, 1 on success. */
/* Also pass it the base directory to load the configuration file. */
int MDFNI_Initialize(const char *basedir);

/* Sets the base directory(save states, snapshots, etc. are saved in directories
   below this directory. */
void MDFNI_SetBaseDirectory(const char *dir);

uint32 MDFNI_CRC32(uint32 crc, uint8 *buf, uint32 len);

// NES hackish function.  Should abstract in the future.
int MDFNI_DatachSet(const uint8 *rcode);

void MDFNI_DumpModulesDef(const char *fn);


#endif
