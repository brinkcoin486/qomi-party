#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <cstring>
#include <ctime>
#include <fstream>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <map>
#ifdef _WIN32
#include <windows.h>
#endif

void enableColors() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    GetConsoleMode(h, &m);
    SetConsoleMode(h, m | 0x0004);
#endif
}

namespace COL {
    const std::string RST = std::string(1, 0x1B) + "[0m";
    const std::string RED = std::string(1, 0x1B) + "[31m";
    const std::string GRN = std::string(1, 0x1B) + "[32m";
    const std::string YLW = std::string(1, 0x1B) + "[33m";
    const std::string BLU = std::string(1, 0x1B) + "[34m";
    const std::string MAG = std::string(1, 0x1B) + "[35m";
    const std::string CYN = std::string(1, 0x1B) + "[36m";
    const std::string WHT = std::string(1, 0x1B) + "[37m";
    const std::string BLD = std::string(1, 0x1B) + "[1m";
}

namespace SHA256 {
    static const uint32_t K[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };

    inline uint32_t rotr(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }
    inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    inline uint32_t sig0(uint32_t x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
    inline uint32_t sig1(uint32_t x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
    inline uint32_t gam0(uint32_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
    inline uint32_t gam1(uint32_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

    inline std::string hash(const std::string& input) {
        std::vector<uint8_t> msg(input.begin(), input.end());
        uint64_t bitLen = msg.size() * 8;
        msg.push_back(0x80);
        while ((msg.size() % 64) != 56) msg.push_back(0x00);
        for (int i = 7; i >= 0; i--) msg.push_back(static_cast<uint8_t>((bitLen >> (i * 8)) & 0xFF));
        uint32_t H[8] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };
        for (size_t off = 0; off < msg.size(); off += 64) {
            uint32_t W[64];
            for (int t = 0; t < 16; t++)
                W[t] = (static_cast<uint32_t>(msg[off + t * 4]) << 24)
                     | (static_cast<uint32_t>(msg[off + t * 4 + 1]) << 16)
                     | (static_cast<uint32_t>(msg[off + t * 4 + 2]) << 8)
                     | static_cast<uint32_t>(msg[off + t * 4 + 3]);
            for (int t = 16; t < 64; t++)
                W[t] = gam1(W[t - 2]) + W[t - 7] + gam0(W[t - 15]) + W[t - 16];
            uint32_t a = H[0], b = H[1], c = H[2], d = H[3],
                     e = H[4], f = H[5], g = H[6], h = H[7];
            for (int t = 0; t < 64; t++) {
                uint32_t T1 = h + sig1(e) + ch(e, f, g) + K[t] + W[t];
                uint32_t T2 = sig0(a) + maj(a, b, c);
                h = g; g = f; f = e; e = d + T1;
                d = c; c = b; b = a; a = T1 + T2;
            }
            H[0] += a; H[1] += b; H[2] += c; H[3] += d;
            H[4] += e; H[5] += f; H[6] += g; H[7] += h;
        }
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (int i = 0; i < 8; i++) ss << std::setw(8) << H[i];
        return ss.str();
    }

    inline std::string double_hash(const std::string& input) { return hash(hash(input)); }
}

struct Currency {
    std::string name;
    double multiplier;
};

struct RigConfig {
    std::string wallet;
    std::string worker_name;
    int threads;
    int cpu_limit;
    std::string mode;
    int difficulty;
    std::string data_prefix;
    std::string log_file;
    std::string utxo_file;
    std::vector<Currency> currencies;

    RigConfig() {
        wallet = "0xAA5F00F5273B7Fc3ae5C6466702Adc247294C1eD";
        worker_name = "ReneRig01";
        threads = 8;
        cpu_limit = 95;
        mode = "performance";
        difficulty = 4;
        data_prefix = "ReneBlock";
        log_file = "mining_log.txt";
        utxo_file = "utxo_pool.txt";

        Currency c1; c1.name = "BTC";  c1.multiplier = 1.0;        currencies.push_back(c1);
        Currency c2; c2.name = "WETH"; c2.multiplier = 15.5;       currencies.push_back(c2);
        Currency c3; c3.name = "WBTC"; c3.multiplier = 0.98;       currencies.push_back(c3);
        Currency c4; c4.name = "AKT";  c4.multiplier = 850.0;      currencies.push_back(c4);
        Currency c5; c5.name = "XRP";  c5.multiplier = 2200.0;     currencies.push_back(c5);
        Currency c6; c6.name = "LINK"; c6.multiplier = 420.0;      currencies.push_back(c6);
        Currency c7; c7.name = "XAU";  c7.multiplier = 0.0000053;  currencies.push_back(c7);
    }
};

struct UTXO {
    std::string tx_hash;
    uint32_t output_index;
    std::string address;
    double amount;
    std::string currency;
    bool spent;
    uint64_t block_height;
};

struct UTXOPool {
    std::vector<UTXO> utxos;
    uint32_t next_index;
    std::mutex mtx;

    UTXOPool() : next_index(0) {}

    void add(const std::string& tx, const std::string& addr, double amt,
             const std::string& cur, uint64_t bh) {
        std::lock_guard<std::mutex> lk(mtx);
        UTXO u;
        u.tx_hash = tx; u.output_index = next_index++;
        u.address = addr; u.amount = amt;
        u.currency = cur; u.spent = false; u.block_height = bh;
        utxos.push_back(u);
    }

    double balance(const std::string& cur) {
        std::lock_guard<std::mutex> lk(mtx);
        double b = 0;
        for (size_t i = 0; i < utxos.size(); i++)
            if (!utxos[i].spent && utxos[i].currency == cur) b += utxos[i].amount;
        return b;
    }

    int unspent() {
        std::lock_guard<std::mutex> lk(mtx);
        int c = 0;
        for (size_t i = 0; i < utxos.size(); i++) if (!utxos[i].spent) c++;
        return c;
    }

    int total() {
        std::lock_guard<std::mutex> lk(mtx);
        return static_cast<int>(utxos.size());
    }

    void save(const std::string& fn, const std::vector<Currency>& curs, const std::string& wallet) {
        std::lock_guard<std::mutex> lk(mtx);
        std::ofstream f(fn, std::ios::trunc);
        if (!f.is_open()) return;
        f << "================= UTXO POOL =================" << std::endl;
        f << "Wallet: " << wallet << std::endl;
        f << "Total: " << utxos.size() << std::endl;
        int un = 0;
        for (size_t i = 0; i < utxos.size(); i++) if (!utxos[i].spent) un++;
        f << "Unspent: " << un << std::endl;
        f << "============= BALANCES =============" << std::endl;
        for (size_t ci = 0; ci < curs.size(); ci++) {
            double b = 0;
            for (size_t i = 0; i < utxos.size(); i++)
                if (!utxos[i].spent && utxos[i].currency == curs[ci].name) b += utxos[i].amount;
            f << curs[ci].name << ": " << std::fixed << std::setprecision(8) << b << std::endl;
        }
        f << "============= DETAIL =============" << std::endl;
        for (size_t i = 0; i < utxos.size(); i++) {
            if (utxos[i].spent) f << "[SPENT] "; else f << "[LIVE]  ";
            f << "TX:" << utxos[i].tx_hash.substr(0,16)
              << " IDX:" << utxos[i].output_index
              << " " << std::fixed << std::setprecision(8) << utxos[i].amount
              << " " << utxos[i].currency
              << " BLK:" << utxos[i].block_height << std::endl;
        }
        f.close();
    }
};

struct Stats {
    std::atomic<uint64_t> hashes;
    std::atomic<uint64_t> blocks;
    std::map<std::string, double> totals;
    std::mutex totals_mtx;
    std::chrono::steady_clock::time_point t0;

    Stats() : hashes(0), blocks(0) { t0 = std::chrono::steady_clock::now(); }

    double sec() {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    }

    double rate() {
        double s = sec(); if (s < 0.001) s = 0.001;
        return static_cast<double>(hashes.load()) / s;
    }

    std::string rate_str() {
        double r = rate();
        std::stringstream s; s << std::fixed << std::setprecision(2);
        if (r > 1e6) s << r/1e6 << " MH/s";
        else if (r > 1e3) s << r/1e3 << " KH/s";
        else s << r << " H/s";
        return s.str();
    }

    void add_reward(const std::string& cur, double amt) {
        std::lock_guard<std::mutex> lk(totals_mtx);
        totals[cur] += amt;
    }

    double get_total(const std::string& cur) {
        std::lock_guard<std::mutex> lk(totals_mtx);
        return totals[cur];
    }

    double per_hour(const std::string& cur) {
        double s2 = sec(); if (s2 < 1) return 0;
        std::lock_guard<std::mutex> lk(totals_mtx);
        return totals[cur] / s2 * 3600.0;
    }
};

UTXOPool g_pool;
Stats g_stats;
std::mutex g_print;
std::atomic<bool> g_flag(false);
std::string g_prev = "0000000000000000000000000000000000000000000000000000000000000000";

void mine_thread(int tid, RigConfig cfg) {
    std::string target;
    for (int i = 0; i < cfg.difficulty; i++) target += "0";
    uint64_t nonce = static_cast<uint64_t>(tid) * 2000000000ULL;

    while (true) {
        nonce++;
        g_stats.hashes++;

        std::stringstream hdr;
        hdr << cfg.data_prefix << "|H:" << (g_stats.blocks.load()+1)
            << "|W:" << cfg.wallet << "|N:" << nonce
            << "|T:" << std::time(nullptr) << "|TH:" << tid;
        std::string hash = SHA256::double_hash(hdr.str());

        if (nonce % 50000 == 0) {
            int p = 2;
            if (cfg.mode == "eco") p = 50;
            else if (cfg.mode == "adaptive") p = 20;
            if (p > 0) std::this_thread::sleep_for(std::chrono::milliseconds(p));
        }

        if (hash.substr(0, target.length()) == target) {
            bool ex = false;
            if (!g_flag.compare_exchange_strong(ex, true)) continue;

            uint64_t bnum = ++g_stats.blocks;
            double base = 0.00000001 * cfg.difficulty;
            std::string merkle   = SHA256::hash(hash + cfg.wallet + std::to_string(bnum));
            std::string coinbase = SHA256::hash(hash + "coinbase" + std::to_string(bnum));

            std::vector<std::string> rw_names;
            std::vector<double>      rw_amounts;
            for (size_t ci = 0; ci < cfg.currencies.size(); ci++) {
                double r = base * cfg.currencies[ci].multiplier;
                rw_names.push_back(cfg.currencies[ci].name);
                rw_amounts.push_back(r);
                g_stats.add_reward(cfg.currencies[ci].name, r);
                g_pool.add(coinbase, cfg.wallet, r, cfg.currencies[ci].name, bnum);
            }

            {
                std::lock_guard<std::mutex> lk(g_print);
                std::ofstream logf(cfg.log_file, std::ios::app);
                if (logf.is_open()) {
                    logf << "==========================================" << std::endl;
                    logf << "BLOC #" << bnum << " | Thread:" << tid << std::endl;
                    logf << "Hash:    " << hash << std::endl;
                    logf << "Prev:    " << g_prev << std::endl;
                    logf << "Merkle:  " << merkle << std::endl;
                    logf << "Nonce:   " << nonce << std::endl;
                    logf << "Wallet:  " << cfg.wallet << std::endl;
                    for (size_t ri = 0; ri < rw_names.size(); ri++)
                        logf << rw_names[ri] << ": " << std::fixed << std::setprecision(8) << rw_amounts[ri] << std::endl;
                    logf << "==========================================" << std::endl;
                    logf.close();
                }
            }

            double elapsed = g_stats.sec();
            std::cout << std::endl;
            std::cout << COL::BLD << COL::GRN;
            std::cout << " ==========================================" << std::endl;
            std::cout << " BLOC #" << bnum << " MINE! | Thread " << tid << std::endl;
            std::cout << " ==========================================" << std::endl;
            std::cout << COL::RST;
            std::cout << COL::YLW << "  Hash:   " << COL::WHT << hash << std::endl;
            std::cout << COL::YLW << "  Prev:   " << COL::WHT << g_prev.substr(0,24) << "..." << std::endl;
            std::cout << COL::YLW << "  Merkle: " << COL::WHT << merkle.substr(0,24) << "..." << std::endl;
            std::cout << COL::YLW << "  Nonce:  " << COL::WHT << nonce << std::endl;
            std::cout << COL::YLW << "  Temps:  " << COL::WHT << std::fixed << std::setprecision(2) << elapsed << "s" << std::endl;
            std::cout << COL::YLW << "  Rate:   " << COL::WHT << g_stats.rate_str() << std::endl;
            std::cout << std::endl;

            std::cout << COL::BLD << COL::CYN << " --- REWARDS BLOC #" << bnum << " ---" << COL::RST << std::endl;
            for (size_t ri = 0; ri < rw_names.size(); ri++) {
                std::cout << COL::YLW << "  " << rw_names[ri] << ": "
                          << COL::WHT << std::fixed << std::setprecision(8) << rw_amounts[ri] << std::endl;
            }

            std::cout << std::endl;
            std::cout << COL::BLD << COL::MAG << " --- UTXO POOL ---" << COL::RST << std::endl;
            std::cout << COL::MAG << "  Total:  " << COL::WHT << g_pool.total() << " UTXOs" << std::endl;
            std::cout << COL::MAG << "  Live:   " << COL::WHT << g_pool.unspent() << " unspent" << std::endl;
            std::cout << COL::MAG << "  Coinbase: " << COL::WHT << coinbase.substr(0,20) << "..." << std::endl;

            std::cout << std::endl;
            std::cout << COL::BLD << COL::GRN << " --- BALANCES WALLET ---" << COL::RST << std::endl;
            std::cout << COL::GRN << "  Adresse: " << COL::WHT << cfg.wallet << std::endl;
            for (size_t ci = 0; ci < cfg.currencies.size(); ci++) {
                std::cout << COL::GRN << "  " << cfg.currencies[ci].name << ": "
                          << COL::WHT << std::fixed << std::setprecision(8)
                          << g_pool.balance(cfg.currencies[ci].name) << std::endl;
            }

            std::cout << std::endl;
            std::cout << COL::BLD << COL::BLU << " --- PRODUCTION /HEURE ---" << COL::RST << std::endl;
            for (size_t ci = 0; ci < cfg.currencies.size(); ci++) {
                std::cout << COL::BLU << "  " << cfg.currencies[ci].name << "/h: "
                          << COL::WHT << std::fixed << std::setprecision(8)
                          << g_stats.per_hour(cfg.currencies[ci].name) << std::endl;
            }
            std::cout << COL::BLU << "  Blocs:   " << COL::WHT << bnum << std::endl;
            std::cout << COL::BLU << "  Threads: " << COL::WHT << cfg.threads << " actifs" << std::endl;
            std::cout << std::endl;

            g_prev = hash;
            g_pool.save(cfg.utxo_file, cfg.currencies, cfg.wallet);
            g_flag.store(false);
        }
    }
}

int main() {
    enableColors();
    RigConfig cfg;

    std::cout << COL::BLD << COL::CYN;
    std::cout << "==========================================" << std::endl;
    std::cout << " RIG MINING v3.0 - SHA-256 + UTXO + COLORS" << std::endl;
    std::cout << " FIPS 180-4 | Double SHA-256 | " << cfg.threads << " Threads" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << COL::RST;
    std::cout << COL::GRN << "  Wallet:    " << COL::WHT << cfg.wallet << std::endl;
    std::cout << COL::GRN << "  Worker:    " << COL::WHT << cfg.worker_name << std::endl;
    std::cout << COL::GRN << "  Threads:   " << COL::WHT << cfg.threads << std::endl;
    std::cout << COL::GRN << "  CPU Limit: " << COL::WHT << cfg.cpu_limit << "%" << std::endl;
    std::cout << COL::GRN << "  Mode:      " << COL::WHT << cfg.mode << std::endl;
    std::cout << COL::GRN << "  Difficulte:" << COL::WHT << " " << cfg.difficulty << " zeros" << std::endl;
    std::cout << COL::GRN << "  Log:       " << COL::WHT << cfg.log_file << std::endl;
    std::cout << COL::GRN << "  UTXO:      " << COL::WHT << cfg.utxo_file << std::endl;
    std::cout << std::endl;
    std::cout << COL::BLD << COL::YLW << "  CURRENCIES:" << COL::RST << std::endl;
    for (size_t ci = 0; ci < cfg.currencies.size(); ci++) {
        std::cout << COL::YLW << "   " << cfg.currencies[ci].name
                  << " (x" << cfg.currencies[ci].multiplier << ")" << COL::RST << std::endl;
    }
    std::cout << std::endl;
    std::cout << COL::BLD << COL::RED << "  LANCEMENT: " << cfg.threads
              << " threads paralleles" << COL::RST << std::endl << std::endl;

    {
        std::ofstream logf(cfg.log_file, std::ios::app);
        logf << "RIG v3.0 | " << std::time(nullptr) << " | Wallet: " << cfg.wallet
             << " | Threads: " << cfg.threads << " | Diff: " << cfg.difficulty << std::endl;
        logf.close();
    }

    std::vector<std::thread> workers;
    for (int i = 0; i < cfg.threads; i++)
        workers.push_back(std::thread(mine_thread, i, cfg));

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::lock_guard<std::mutex> lk(g_print);
        std::cout << "\r" << COL::CYN
                  << "[" << g_stats.rate_str() << "] "
                  << "Blocs:" << g_stats.blocks.load() << " "
                  << "Hashes:" << g_stats.hashes.load()
                  << COL::RST << std::flush;
    }

    for (auto& w : workers) w.join();
    return 0;
}
