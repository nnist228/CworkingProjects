#include "cfh.h"
#include "readBits.h"
#include "eocdr.h"
#include <assert.h>
#include <stdio.h>

 bool read_cfh(struct cfh *cfh, const uint8_t *src, size_t src_len,  size_t* offset) // Чтение одного центрального каталога зараз
{
    const uint8_t *p;
    uint32_t signature;

    if(*offset > src_len || src_len - *offset < CFH_BASE_SZ){
        return false;
    }

    p = &src[*offset];
    signature = read32Bits(&p);
    
    if(signature != CFH_SIGNATURE){       
        puts("Can not find a signature for Central directory");
        return false;
    }
    
    cfh->made_by_ver = read16Bits(&p);
    cfh->extract_var = read16Bits(&p);
    cfh->gp_flag = read16Bits(&p);
    cfh->method = read16Bits(&p);
    cfh->mod_time = read16Bits(&p);
    cfh->mod_date = read16Bits(&p);
    cfh->crc32 = read32Bits(&p);
    cfh->comp_size =read32Bits(&p);
    cfh->uncomp_size = read32Bits(&p);
    cfh->name_len = read16Bits(&p);
    cfh->extra_len = read16Bits(&p);
    cfh->comment_len = read16Bits(&p);
    cfh->disk_nbr_start = read16Bits(&p);
    cfh->int_attrs = read16Bits(&p);
    cfh->ext_attrs = read32Bits(&p);
    cfh->lfh_offset = read32Bits(&p);
    cfh->name = p;
    cfh->extra = cfh->name + cfh->name_len;
    cfh->comment = cfh->extra + cfh->extra_len;
    
    assert(p == &src[*offset + CFH_BASE_SZ] && "All fields read.");


    if(*offset + CFH_BASE_SZ + cfh->name_len + cfh->extra_len + cfh->comment_len > src_len){
        return false;
    }

    *offset += CFH_BASE_SZ + cfh->name_len + cfh->extra_len + cfh->comment_len;

    return true;
}
