
#include <stdint.h>

func is_mask_correct_faster(uint32_t ip_mask){
    if(!ip_mask) return 0;
    while( ip_mask){
        if(!(ip_mask&(1<<31)) && (ip_mask&(1<<(30))) )
            return 0;
        ip_mask=ip_mask<<1;
    }
    return 1;
}

func is_mask_correct(uint32_t ip_mask){
    for(uint8_t i = 31; i > 0; i++ )
        if(!(ip_mask&(1<<i)) && (ip_mask&(1<<(i-1))) )
            return 0;
    return 1;
}


uint8_t test_half_byte(uint8_t half_byte);
int is_correct_ip_mask(uint32_t ip_mask);
int main(int val){
    is_correct_ip_mask(val);
}
//является ли маска верной если непрерывный ряд "1"
//имеет нулевую длинну? Пусть будет да.
//так же можно просто написать свитч кейс, взяв все возможные ответы оттуда
//https://ru.wikipedia.org/wiki/Маска_подсети

int is_correct_ip_mask(uint32_t ip_mask){

    uint8_t byte_hh_h = test_half_byte((ip_mask >> (8*3 + 4)) & 0xf);
    uint8_t byte_hh_l = test_half_byte((ip_mask >> (8*3)) & 0xf);

    uint8_t byte_hl_h = test_half_byte((ip_mask >> (8*2 +4)) & 0xf);
    uint8_t byte_hl_l = test_half_byte((ip_mask >> (8*2)) & 0xf);

    uint8_t byte_lh_h = test_half_byte((ip_mask >> (8*1 + 4)) & 0xf);
    uint8_t byte_lh_l = test_half_byte((ip_mask >> (8*1)) & 0xf);

    uint8_t byte_ll_h = test_half_byte((ip_mask >> (8*0 + 4)) & 0xf);
    uint8_t byte_ll_l = test_half_byte((ip_mask >> (8*0)) & 0xf);

    if(byte_ll_l && !byte_ll_h  || \
       byte_lh_l && !byte_lh_h  || \
       byte_hl_l && !byte_hl_h  || \
       byte_hh_l && !byte_hh_h  )
        return 0;
    if(byte_ll_h && !byte_lh_l || \
       byte_lh_h && !byte_hl_l || \
       byte_hl_h && !byte_hh_l){
        return 0;
    }
    return 1;
}

/*
 * 0 0000   YEAH
 * 1 0001   NO
 * 2 0010   NO
 * 3 0011   NO
 * 4 0100   NO
 * 5 0101   NO
 * 6 0110   NO
 * 7 0111   NO
 * 8 1000   YEAH
 * 9 1001   NO
 * A 1010   NO
 * B 1011   NO
 * C 1100   YEAH
 * D 1101   NO
 * E 1110   YEAH
 * F 1111   YEAH
 *
 * 0, 8, C, E,F
 */
uint8_t test_half_byte(uint8_t half_byte){
    switch(half_byte){
    case 0x0:
    case 0x8:
    case 0xC:
    case 0xE:
    case 0xF:
        return 1;
    default:
        return 0;
    }
}
