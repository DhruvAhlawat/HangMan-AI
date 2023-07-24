#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<deque>
#include<queue>
#include<stack>
#define ll long long
#define pint pair<int,int>
#define int long long // for huge inputs,outputs, can be removed for space
using namespace std;

const long long MOD = 1000000007;
#define all(x) (x).begin(), (x).end()
#define FASTINOUT cin.tie(0); ios::sync_with_stdio(false);
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
void Yes()
{
    cout << "YES" << endl;
}
void No()
{
    cout << "NO" << endl;
}
//sort(all(vec));
//vec.resize(unique(all(vec)) - vec.begin());
//rotate(vec.begin(), vec.begin() + k, vec.end());
void printVectorArray(vector<int> a)
{
    for(int i = 0;i < a.size();i++)
    {
        cout << a[i] << " "; 
    }
    cout << "\n";
}
int GCD(int a, int b)
{
   if (b == 0) return a;
   return GCD(b, a%b);
}
int LCM(int a,int b)
{
    return (a/GCD(a,b))*b;
}


long long binExpMod(long long n,long long r,long long modulus)
{
if(modulus <= 0)
{
    if(r%2 == 0)
    {
        int k = binExpMod(n,(r/2),modulus);
        return ((k)*(k));
    }
    else
    {
        return ((binExpMod(n,r-1,modulus)*n));
    }
}
    n = (n%modulus);
    if(n == 0)
        return 0;
    if(n==1)
        return 1;
    if(r == 0)
        return 1;
    if(r == 1)
        return n;
    
    if(r%2 == 0)
    {
        int k = binExpMod(n,(r/2),modulus);
        return ((k)*(k))%modulus;
    }
    else
    {
        return ((binExpMod(n,r-1,modulus)*n)%modulus);
    }
}

int nCr(int a,int b,int modulus)
{
    int ans = 1;
    b = min(b,a-b);
    for (int i = 0; i < b; i++)
    {
        ans = (ans*(a-i))%modulus;
        ans = ans*binExpMod(i+1,modulus-2,modulus);
        ans %= modulus;
    }
    return ans;
}
int ExtendedEuclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ExtendedEuclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
int sqrtFloored(int x)
{
    int k = sqrt(x);
    if(k*k == x)
        return k;
    if(k*k <= x)
    {
        if((k+1)*(k+1) <= x)
        {
            return k+1;
        }
        return k;
    }
    else
    {
        return k-1;
    }
}
void printVectorGrid(vector<vector<ll>> a)
{
    for(int j = 0;j < a.size();j++) {
        for(int i = 0;i < a[j].size();i++)
        {
            cout << a[j][i] << " "; 
        }
        cout << "\n";
    }
}
signed main()
{
    FASTINOUT;
    int t;
    cin >> t;
    for(int testCase = 0;testCase < t;testCase++)
    {
        int n;
        cin >> n;
        vector<int> a(n,0);
        vector<pint> b(n,make_pair(0,0));
        for(int i = 0;i < n;i++)
        {
            cin >> a[i];
            b[i].first = a[i];
            b[i].second = i; 
        }
        set<int> allowed; 
        for(int i = 0; i < n; i++)
        {
            allowed.insert(i+1);
        }
        sort(all(b), greater<pint>()); 
        if(b[0].first == 0)
        {
            //all are negative.
            Yes();
            for(int i = 0; i < n; i++)
            {
                cout << -1 << " ";
            }
            cout << endl;
            continue;
        }
        //now we need to decide where the - actually starts from and then we can decide on the answer.
        //if we turn negative then we cannot bond with stuff that are ahead of us, naturally.
        int curConnections = 0; 
        stack<int> endConnections;
        //so normally we have the first one done here.
        endConnections.push(b[0].first);  //ASSUMING THE FIRST NUMBER IS POSITIVE IN OUR CASE.
        curConnections++; 
        vector<bool> positives(n,0); 
        bool canDo = true; 
        //int gotOutOf = 0; 
        bool intoNegative = false;
        vector<int> ans(n,0);
        for(int i = 1; i < n; i++)
        {
            int gotOutOf = 0;
            while(endConnections.size() > 0 && endConnections.top() == i)
            {
                curConnections--;
                gotOutOf++; 
                endConnections.pop();
            }
            //cout << curConnections << "," << b[i].first << endl;
            if(curConnections > b[i].first)
            {
                canDo = false;
                break;
            }
            if(intoNegative)
            {
                if(curConnections != b[i].first)
                {
                    canDo = false;
                    break;
                }
                if(gotOutOf == 0)
                ans[i] = ans[i-1];
                else
                ans[i] = ans[i-1] - 2;
                allowed.erase(-ans[i]); 
                continue;
            }
            if(gotOutOf > 0)
            {
                if(b[i-1].first == b[i].first)
                {
                    canDo = false;
                    break;
                }
            }
            if(curConnections == b[i].first)
            {
                positives[i] = false;
                intoNegative = true;
                if(gotOutOf > 0)
                {
                    ans[i] = -2;
                    allowed.erase(2);
                }
                else
                {
                    ans[i] = -1;
                    allowed.erase(1); 
                }
                //then at this point we should stop makign it positive, and make it negative instead.
                //all following ones are also obviously negative as well.
            }
            else
            {
                if(gotOutOf > 0)
                {
                    canDo = false;
                    break;
                }
                if(curConnections > b[i].first)
                {
                    canDo = false;
                    break; 
                }
                //lets say curConnections is instead now equal to 0. In this case what we should do?.
                if(curConnections == 0)
                {
                    canDo = false;
                    break;
                }
                positives[i] = true;
                //we keep it positive at this point.
                int extraNeeded = b[i].first - curConnections; 
                endConnections.push(i + extraNeeded); //and then reduce over here.
                curConnections++; //and increase the number of stuff that we have. 
            }
            
        }
        if(canDo)
        {
            Yes();
            //now we set the answer for the remaining positive ones
            for(int i = n-1; i >= 0; i--)
            {
                if(ans[i] == 0)
                {
                    if(i != n-1 && b[i].first == b[i+1].first)
                    {
                        ans[i] = ans[i+1]; 
                    }
                    else
                    {
                        ans[i] = *allowed.begin();
                        allowed.erase(allowed.begin());
                    }
                }
            }
            vector<int> actualAns(n,0);
            for(int i = 0; i < n; i++)
            {
                actualAns[b[i].second] = ans[i];
            }
            printVectorArray(actualAns); 
        }
        else
        {
            No();
        }


    }
 
}