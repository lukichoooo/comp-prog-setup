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
