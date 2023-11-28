#include "eocdr.h"
#include "readBits.h"


bool fine_ecodr(struct eocdr *r, const uint8_t*src, size_t src_len) // Нахождение сигнатры eocdr и чтение eocdr
{
    size_t comment_len;
    const uint8_t *p;
    uint32_t signature;

    for(comment_len = 0; comment_len <= UINT16_MAX; comment_len++){
        if(src_len < EOCDR_BASE_SZ + comment_len){
            break;
        }

        p = &src[src_len - EOCDR_BASE_SZ - comment_len];
        signature = read32Bits(&p);

        
        if(signature == ECODR_SIGNATURE){   //Чтение верное, алгоритм рабочий!
            r->disk_nbr = read16Bits(&p);
            r->cd_start_disk = read16Bits(&p);
            r->disk_cd_entries = read16Bits(&p);
            r->cd_entries = read16Bits(&p);
            r->cd_size = read32Bits(&p);
            r->cd_offset = read32Bits(&p);
            r->comment_len = read16Bits(&p);
            r->comment = p;
            assert(p == &src[src_len - comment_len] && "All fields read.");

            if(r->comment_len == comment_len) {
                return true;
            }
        }
    }
    return false;
}