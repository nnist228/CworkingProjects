#ifndef EOCDR_H
#define EOCDR_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define EOCDR_BASE_SZ 22
#define ECODR_SIGNATURE 0x06054b50


#pragma pack(push,1)
struct eocdr{
    uint16_t disk_nbr;
    uint16_t cd_start_disk;
    uint16_t disk_cd_entries;
    uint16_t cd_entries;
    uint32_t cd_size;
    uint32_t cd_offset;
    uint16_t comment_len;
    const uint8_t *comment;

}__attribute__((packed));// отключение выравнивания для Linux 
#pragma pack(pop)   // для Windows 

 bool fine_ecodr(struct eocdr *, const uint8_t*, size_t); // Прототип для функции чтения eocdr 
#endif