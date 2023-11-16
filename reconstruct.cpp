#include "header.h"


ZZ reconstruct(const uint64_t *party, Vec<ZZ>& c, uint64_t t, ZZ p){
    ZZ secret;
    secret = 0;
    uint64_t i=0, j;
    ZZ delta, x, y;
    delta = 1;

    while(i < t+1){
        j = 0;
        x = 1;
        y = 1;
        while(j < t +1){
            if(j != i){
                x = (x * party[j]) % p;
                if(party[i] > party[j])
                     y = (y * (party[i] - party[j])) % p;
                else
                     y = (y * (p + party[i] - party[j])) % p;
            }
            j++;
        }
        if((t & 1) == 1)
            x = (p - x);
        delta = (x * InvMod(y, p)) % p;
        delta = (delta * c[i]) % p;
        secret = (secret + delta) % p;
        i++;
    }
    return secret;
}
