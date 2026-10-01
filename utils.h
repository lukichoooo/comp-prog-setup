#pragma once

#include <bits/stdc++.h>

namespace _utils
{
static uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

struct custom_hash
{
    template <typename T>
    static void hash_combine(size_t &seed, const T &val)
    {
        static const _utils::custom_hash hasher;
        seed ^= hasher(val)
                + 0x9e3779b97f4a7c15ULL
                + (seed << 6)
                + (seed >> 2);
    }

    template <typename T>
    size_t operator()(const T &x) const
    {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(std::hash<T>{}(x) + FIXED_RANDOM);
    }

    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2> &p) const
    {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }

    template <typename... Args>
    size_t operator()(const std::tuple<Args...> &t) const
    {
        size_t seed = 0;
        std::apply([&seed](const auto &...args) { (hash_combine(seed, args), ...); }, t);
        return seed;
    }

    template <typename T, typename Hash, typename Eq, typename Alloc>
    size_t operator()(const std::unordered_set<T, Hash, Eq, Alloc> &s) const
    {
        size_t seed = 0;
        for (const auto &x : s)
            hash_combine(seed, x);
        return seed;
    }
};
} // namespace _utils

template <typename T>
static void hash_combine(size_t &seed, const T &val) { _utils::custom_hash::hash_combine(seed, val); }

#define _MAIN_START \
    int main()      \
    {               \
        cin.tie({})->sync_with_stdio({});

#define _MAIN_END }

using ull = unsigned long long;
using ll = long long;

#define len(x) (ll) x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define endl '\n'

#define setOkAndBreak(x) ({ ok = x; break; })
#define iterate(x) for (ll __i{}; __i < x; ++__i)

template <class... Args>
void print(const Args &...args) { (std::cout << ... << args); }
template <class... Args>
void read(Args &...args) { (std::cin >> ... >> args); }


template <typename K, typename V>
using umap = std::unordered_map<K, V, _utils::custom_hash>;

template <typename K>
using uset = std::unordered_set<K, _utils::custom_hash>;

template <std::ranges::input_range R, class F>
    requires std::invocable<F, std::ranges::range_reference_t<R>>
auto operator|(R &&r, F f)
{
    using T = std::invoke_result_t<F, std::ranges::range_reference_t<R>>;
    std::vector<T> res;
    if constexpr (std::ranges::sized_range<R>)
        res.reserve(std::ranges::size(r));
    std::ranges::transform(r, std::back_inserter(res), f);
    return res;
}

template <typename TR, std::ranges::input_range T>
TR allAs(T &&range) { return TR(all(range)); }


inline std::vector<ll> generatePrimes(ll maxVal)
{
    ll limit = sqrt(maxVal) + 1;
    std::vector<bool> isPrime(limit, 1);
    isPrime[0] = isPrime[1] = 0;
    for (ll p = 2; p * p < limit; ++p)
        if (isPrime[p])
            for (ll i = 2 * p; i < limit; i += p)
                isPrime[i] = 0;
    std::vector<ll> primes;
    for (ll p = 2; p < limit; ++p)
        if (isPrime[p])
            primes.push_back(p);
    return primes;
}

inline std::vector<std::pair<ll, ll>> getPrimeFactors(ll a, const std::vector<ll> &primes)
{
    std::vector<std::pair<ll, ll>> factors;
    for (ll p : primes)
    {
        if (p * p > a)
            break;

        ll cnt{};
        while (a % p == 0)
        {
            cnt++;
            a /= p;
        }
        if (cnt)
            factors.push_back({p, cnt});
    }
    if (a != 1)
        factors.push_back({a, 1});
    return factors;
};
