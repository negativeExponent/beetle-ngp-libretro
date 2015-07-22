#ifndef __MDFN_ENDIAN_H
#define __MDFN_ENDIAN_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef INLINE
#define INLINE inline
#endif

#ifdef MSB_FIRST

#ifndef le32toh
#define le32toh(l)      ((((l)>>24) & 0xff) | (((l)>>8) & 0xff00) \
      | (((l)<<8) & 0xff0000) | (((l)<<24) & 0xff000000))
#endif

#ifndef le16toh
#define le16toh(l)      ((((l)>>8) & 0xff) | (((l)<<8) & 0xff00))
#endif

#else

#ifndef le32toh
#define le32toh(l)      (l)
#endif

#ifndef le16toh
#define le16toh(l)      (l)
#endif

#endif

#ifndef htole32
#define htole32 le32toh
#endif

#ifndef htole16
#define htole16 le16toh
#endif

int write16le(uint16_t b, FILE *fp);
int write32le(uint32_t b, FILE *fp);
int read32le(uint32_t *Bufo, FILE *fp);

void Endian_A16_Swap(void *src, uint32_t nelements);
void Endian_A32_Swap(void *src, uint32_t nelements);
void Endian_A64_Swap(void *src, uint32_t nelements);

void Endian_A16_NE_to_LE(void *src, uint32_t nelements);
void Endian_A32_NE_to_LE(void *src, uint32_t nelements);
void Endian_A64_NE_to_LE(void *src, uint32_t nelements);

void Endian_A16_LE_to_NE(void *src, uint32_t nelements);
void Endian_A16_BE_to_NE(void *src, uint32_t nelements);
void Endian_A32_LE_to_NE(void *src, uint32_t nelements);
void Endian_A64_LE_to_NE(void *src, uint32_t nelements);

void Endian_V_LE_to_NE(void *src, uint32_t bytesize);
void Endian_V_NE_to_LE(void *src, uint32_t bytesize);

void FlipByteOrder(uint8_t *src, uint32_t count);

// The following functions can encode/decode to unaligned addresses.

static INLINE void MDFN_en16lsb(uint8_t *buf, uint16_t morp)
{
   buf[0]=morp;
   buf[1]=morp>>8;
}

static INLINE void MDFN_en24lsb(uint8_t *buf, uint32_t morp)
{
   buf[0]=morp;
   buf[1]=morp>>8;
   buf[2]=morp>>16;
}

static INLINE void MDFN_en32lsb(uint8_t *buf, uint32_t morp)
{
   buf[0]=morp;
   buf[1]=morp>>8;
   buf[2]=morp>>16;
   buf[3]=morp>>24;
}

static INLINE void MDFN_en64lsb(uint8_t *buf, uint64_t morp)
{
   buf[0]=morp >> 0;
   buf[1]=morp >> 8;
   buf[2]=morp >> 16;
   buf[3]=morp >> 24;
   buf[4]=morp >> 32;
   buf[5]=morp >> 40;
   buf[6]=morp >> 48;
   buf[7]=morp >> 56;
}


static INLINE void MDFN_en16msb(uint8_t *buf, uint16_t morp)
{
   buf[0] = morp >> 8;
   buf[1] = morp;
}

static INLINE void MDFN_en24msb(uint8_t *buf, uint32_t morp)
{
   buf[0] = morp >> 16;
   buf[1] = morp >> 8;
   buf[2] = morp;
}

static INLINE void MDFN_en32msb(uint8_t *buf, uint32_t morp)
{
   buf[0] = morp >> 24;
   buf[1] = morp >> 16;
   buf[2] = morp >> 8;
   buf[3] = morp;
}

static INLINE void MDFN_en64msb(uint8_t *buf, uint64_t morp)
{
   buf[0] = morp >> 56;
   buf[1] = morp >> 48;
   buf[2] = morp >> 40;
   buf[3] = morp >> 32;
   buf[4] = morp >> 24;
   buf[5] = morp >> 16;
   buf[6] = morp >> 8;
   buf[7] = morp >> 0;
}

#define MDFN_enlsb16(buf, value) MDFN_en16lsb((uint8_t*)(buf), (value))

#define MDFN_enlsb32(buf, value) MDFN_en32lsb((uint8_t*)(buf), (value))

#define MDFN_enlsb64(buf, value) MDFN_en64lsb((uint8_t*)(buf), (value))

#define MDFN_de16lsb(morp)       (((morp)[0] | ((morp)[1] << 8)))
#define MDFN_de24lsb(morp)       (((morp)[0]|((morp)[1]<<8)|((morp)[2]<<16)))
#define MDFN_de32lsb(morp)       (((morp)[0]|((morp)[1]<<8)|((morp)[2]<<16)|((morp)[3]<<24)))

static inline uint64_t MDFN_de64lsb(const uint8_t *morp)
{
   uint64_t ret = (uint64_t)morp[0];

   ret |= (uint64_t)morp[1] << 8;
   ret |= (uint64_t)morp[2] << 16;
   ret |= (uint64_t)morp[3] << 24;
   ret |= (uint64_t)morp[4] << 32;
   ret |= (uint64_t)morp[5] << 40;
   ret |= (uint64_t)morp[6] << 48;
   ret |= (uint64_t)morp[7] << 56;

   return(ret);
}

#define MDFN_delsb16(buf) MDFN_de16lsb((uint8_t*)buf)

#define MDFN_delsb32(buf) MDFN_de32lsb((uint8_t*)buf)

#define MDFN_delsb64(buf) MDFN_de64lsb((uint8_t*)buf)

#define MDFN_de16msb(morp) (((morp)[1] | ((morp)[0] << 8)))

#define MDFN_de24msb(morp) (((morp)[2]<<0)|((morp)[1]<<8)|((morp)[0]<<16))

#define MDFN_de32msb(morp) (((morp)[3]|((morp)[2]<<8)|((morp)[1]<<16)|((morp)[0]<<24)))

#ifdef __cplusplus
}
#endif


#endif
