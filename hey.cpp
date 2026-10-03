#include "utils.h"
using namespace std;
constexpr ll INF = INT_MAX - 10;
constexpr ll mod = 676767677;


_MAIN_START


ll tt = 1;
input(tt);
while (tt--)
{
    ll n;
    input(n);

    ll nodeFurthestFromOne = 1;
    ll maxDistanceFromOne = 0;
    for (ll v = 2; v <= n; ++v)
    {
        ll isMore = 1;
        while (isMore)
        {
            output("? 1 ", v, " ", maxDistanceFromOne + 1, endl);
            cout.flush();

            input(isMore);
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
            output("? ", nodeFurthestFromOne, " ", v, " ", maxDistance + 1, endl);
            cout.flush();

            input(isMore);
            if (isMore)
            {
                maxDistance++;
                furthestNodeFromFurthestNode = v;
            }
        }
    }

    output("! ", nodeFurthestFromOne, " ", furthestNodeFromFurthestNode, " ", maxDistance);
    output(endl);
    cout.flush();
}


_MAIN_END
