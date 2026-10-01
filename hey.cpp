#include "utils.h"
using namespace std;
constexpr ll INF = INT_MAX - 10;
constexpr ll mod = 676767677;


_MAIN_START


ll tt = 1;
read(tt);
while (tt--)
{
    ll n;
    read(n);

    ll nodeFurthestFromOne = 1;
    ll maxDistanceFromOne = 0;
    for (ll v = 2; v <= n; ++v)
    {
        ll isMore = 1;
        while (isMore)
        {
            print("? 1 ", v, " ", maxDistanceFromOne + 1, endl);
            cout.flush();

            read(isMore);
            if (isMore)
            {
                maxDistanceFromOne++;
                nodeFurthestFromOne = v;
            }
        }
    }

    ll furthestNodeFromFurthestNode = 1;
    ll maxDistance = maxDistanceFromOne;
    for (ll v = 2; v <= n; ++v)
    {
        if (v == nodeFurthestFromOne)
            continue;
        ll isMore = 1;
        while (isMore)
        {
            print("? ", nodeFurthestFromOne, " ", v, " ", maxDistance + 1, endl);
            cout.flush();

            read(isMore);
            if (isMore)
            {
                maxDistance++;
                furthestNodeFromFurthestNode = v;
            }
        }
    }

    print("! ", nodeFurthestFromOne, " ", furthestNodeFromFurthestNode, " ", maxDistance);
    print(endl);
    cout.flush();
}


_MAIN_END
