#include "utils.h"
constexpr ll INF = INT_MAX - 10;
constexpr ll mod = 1e9 + 7;
_MAIN_START


ll tt = 1;
read(tt);
while (tt--)
{
    ll n;
    read(n);
    vector<ll> A(n);
    for (ll i{}; i < n; ++i)
        read(A[i]);

    struct Node
    {
        ll lastAddedFreq{};
        ll lastSubbedFreq{};
    };

    umap<ll, Node> sums;
    sums.max_load_factor(0.8f);
    sums[0] = Node{0, 1};

    for (ll a : A)
    {
        vector<pair<ll, ll>> add;
        vector<pair<ll, ll>> sub;

        for (const auto &[s, prev] : sums)
        {
            add.push_back({s + a, prev.lastSubbedFreq});
            sub.push_back({s - a, prev.lastAddedFreq});
        }

        for (auto [s, f] : add)
            sums[s].lastAddedFreq = (sums[s].lastAddedFreq + f) % mod;
        for (auto [s, f] : sub)
            sums[s].lastSubbedFreq = (sums[s].lastSubbedFreq + f) % mod;
    }

    print((sums[0].lastAddedFreq + sums[0].lastSubbedFreq) % mod);
    print(endl);
}


_MAIN_END
