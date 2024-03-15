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
 