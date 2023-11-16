#include<iostream>
#include<stdint.h>
#include<NTL/ZZ.h>
#include<NTL/vector.h>

using namespace std;
using namespace NTL;

ZZ powermod(const ZZ& a, const ZZ& e, const ZZ& n);
ZZ reconstruct(const uint64_t *party, Vec<ZZ>& c, uint64_t t, ZZ p);
Vec<ZZ> share(const Vec<ZZ>& a, uint64_t n, uint64_t t, ZZ& p);
