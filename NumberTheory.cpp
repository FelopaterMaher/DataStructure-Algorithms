// https://youtu.be/MoRLs8nT6EM?si=wN_0XLZKYaU4g8em
#include <iostream>
#include "bits/stdc++.h"
#define ll long long
 
using namespace std;
 
// Get divisors of n O(sqrt(n))
vector<ll>d;
void divisors(ll n)
{
    for(ll i=1; i*i<=n; i++)
    {
        if(n%i==0)
        {
           d.push_back(i);
           if(i!=(n/i)) // Complement , ex: 2,2 false for n=4
           {
               d.push_back(n/i);
           }
        }
    }
}
 
//Checks if number is prime O(sqrt(n))
bool isPrime(ll a)
{
    for(ll i=2; i*i<=a; i++)
    {
        if(a%i==0)
        {
            return false;
        }
    }
    return true;
}
 

// Sieve algorithm O(n*log(log(n))) => Harnonic Series
bool prime[N];
void Sieve(ll n)
{
    memset(prime,true,sizeof(prime));
    for(ll p=2; p*p<=n; p++)
    {
        if(prime[p])
        {
            // i = p*p for optimization 
            for(ll i=p*p; i<=n; i+=p)
            {
                prime[i]=false;
            }
        }
    }
}


// SPF algorithm O(n*log(log(n)))
ll spf[N];
void SPF()
{
    for(int i=1; i<N; i++)
    {
        spf[i]=i;
    }
    for(int i=2; i*i<N; i++)
    {
        if(spf[i]==i)
        {
            for(int k=i*i; k<N; k+=i)
            {
                if(spf[k]==k)
                {
                    spf[k]=i;
                }
            }
        }
    }
}


int add(int a, int b, int mod) {
    return ((a % mod) + (b % mod)) % mod;
}
 
int mul(int a, int b, int mod) {
    return ((a % mod) * (b % mod)) % mod;
}
 
int sub(int a, int b, int mod) {
    return ((a % mod) - (b % mod) + mod) % mod;
}
 
int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}
 
int LCM(int a, int b) {
    return a / GCD(a, b) * b;
}
 
int fast_power_recursive(int b, int p) {
    if (!p)
        return 1;
    int r = fast_power_recursive(b, p / 2);
    r *= r;
    if (p & 1)
        r *= b;
    return r;
}
 
int fast_power_iterative(int a, int b) {
    int ret = 1;
    while (b > 0) {
        if (b & 1)
            ret *= a;
        a = a * a;
        b /= 2;
    }
    return ret;
