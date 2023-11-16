//shamir (n,t) secret shairing scheam

#include "header.h"

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


