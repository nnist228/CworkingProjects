#ifndef CFH_H
#define CFH_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define CFH_BASE_SZ 46
#define CFH_SIGNATURE 0x02014b50

#pragma pack(push,1)
struct cfh {
    uint16_t made_by_ver;
    uint16_t extract_var;
    uint16_t gp_flag;
    uint16_t method;
    uint16_t mod_time;
    uint16_t mod_date;
    uint32_t crc32;
    uint32_t comp_size;
    uint32_t uncomp_size;
    uint16_t name_len;
    uint16_t extra_len;
    uint16_t comment_len;
    uint16_t disk_nbr_start;
    uint16_t int_attrs;
    uint32_t ext_attrs;
    uint32_t lfh_offset;
    const uint8_t* name;
    const uint8_t* extra;
    const uint8_t* comment;

}__attribute__((packed)); //откл выравнивание для Linux 
#pragma pack(pop)   // для Windows 

 bool read_cfh(struct cfh *, const uint8_t* , size_t, size_t*); //Прототип для функции чтения cfh 
#endif

