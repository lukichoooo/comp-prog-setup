#pragma once

// --- Utils:

#include <bits/stdc++.h>

#define _MAIN_START \
    int main()      \
    {               \
        cin.tie({})->sync_with_stdio({});

#define _MAIN_END }

using namespace std;
using ull = unsigned long long;
using ll = long long;

#define len(x) (ll) x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define endl '\n'

#define setOkAndBreak(x) \
    do                   \
    {                    \
        ok = x;          \
        break;           \
    } while (0)


template <class... Args>
void print(const Args &...args) { (cout << ... << args); }
template <class... Args>
void read(Args &...args) { (cin >> ... >> args); }

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    template <typename T>
    size_t operator()(T const &x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(hash<T>{}(x) + FIXED_RANDOM);
    }
};

template <typename K, typename V>
using umap = unordered_map<K, V, custom_hash>;

template <typename K>
using uset = unordered_set<K, custom_hash>;

template <typename T>
inline void hash_combine(size_t &seed, const T &val)
{
    static const custom_hash hasher;
    seed ^= hasher(val) + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}
struct TupleHash
{
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }

    template <typename... Args>
    size_t operator()(const tuple<Args...> &t) const
    {
        size_t seed = 0;
        std::apply([&seed](const auto &...args) { (hash_combine(seed, args), ...); }, t);
        return seed;
    }
};
// --- Code:
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
