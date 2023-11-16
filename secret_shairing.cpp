//shamir (n,t) secret shairing scheam

#include<iostream>
#include<stdint.h>
#include<NTL/ZZ.h>
#include<NTL/vector.h>

using namespace std;
using namespace NTL;

Vec<ZZ> share(const Vec<ZZ>& a, uint64_t n, uint64_t t, ZZ& p);
ZZ reconstruct(const uint64_t *party, Vec<ZZ>& c, uint64_t t, ZZ p);
ZZ powermod(const ZZ& a, const ZZ& e, const ZZ& n);
int main(){
    uint64_t n = 10;
    uint64_t t = 6;
    ZZ prime;
    cout << "Enter a Prime Number = ";
    cin >> prime;
    //Secret
    ZZ s;
    cout << "Enter the secret : ";
    cin >> s;
    //choosing a random polynomial f of order t modulo p with constant s
    Vec<ZZ> a;
    a.SetLength(t+1);
    a[0] = s;
    uint64_t i=1;
    while(i < t+1){
	a[i] = RandomBnd(prime);
	i++;
    }
    //Random Polynomial 
    cout << "Random Polynomial : ";
    i=0;
    while(i < t){
	cout << a[i] <<" X^" << i << "+ ";
	i++;
    }
    cout << a[t] << " X^" << t << endl;
    //secret shares of the parties
    Vec<ZZ> b;
    b = share(a, n, t, prime);
    i=0;
    cout << "Secret Shares of each party : "<< endl;
    while(i < n){
	cout << "P" << i+1 << "-->" << b[i] << endl;
	i++;
    }
    //Reconstruction
    ZZ secret;
    Vec<ZZ> c;
    uint64_t party[t+1];
    //party.SetLength(t+1);
    c.SetLength(t+1);
    cout << "Enter " << t+1 << "-secret shares to reconstruct the secret: " << endl;
    i = 0;
    while(i < t+1){
	cout << "Enter Party : ";
	cin >> party[i];
	cout << "share : ";
	cin >> c[i];
	i++;
    }
    secret = reconstruct(party, c, t, prime);
    cout << "Secret = " << secret << endl;
    return 0;
}
Vec<ZZ> share(const Vec<ZZ>& a, uint64_t n, uint64_t t, ZZ& p){
    Vec<ZZ> b;
    b.SetLength(n);
    ZZ k;
    uint64_t i=0, j;
    while(i < n){
	b[i] = a[0];
	j = 1;
	while(j <= t){
	    k = powermod(ZZ(i+1), ZZ(j), p);
	    k = MulMod(k, a[j], p);
	    b[i] = (b[i] + k) % p;
	    j++;
	}
	i++;
    }
    return b;
}

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
