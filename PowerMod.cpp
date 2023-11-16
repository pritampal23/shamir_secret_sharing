#include "header.h"

ZZ powermod(const ZZ& a, const ZZ& e, const ZZ& n){
    if(e == 0)
        return ZZ(1);
    ZZ res;
    long k = NumBits(e);

    res = 1;
    long i = k-1;
    while(i >= 0){
        //res = (res * res) % n;
        SqrMod(res,res,n);
        if(bit(e,  i) == 1){
            //res = (res * a) % n;
            res = MulMod(res,a,n);
        }
        i--;
    }
    if(e < 0)
        return InvMod(res, n);
    else
        return res;
}
