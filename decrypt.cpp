#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <cmath>
#include <thread>
#include <cstring>
#include <set>
#include <chrono>
#include <ctime>

#include "key.hpp"
#include "decrypt.hpp"
#include "timer.hpp" // to measure execution time

std::string me; // store executable path for error message
std::string encrypted; // code input by user
std::string table_filename; // table T
bool verbose = false;


Symbol::Symbol(const std::string &filename) {
    T.resize(N);
    std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

class key_hash
{
public:
    long operator()(const Key& x) const
    {
        long hash = 0;
        for (int i{N - 1}; i >= 0; i--)
        {
            hash = hash | x.bit(i) << i;
        }
        return hash;
    }
};

void Symbol::decrypt(const std::string &encrypted) {
    // Idea: do the brute on the first half of the table - encrypt keys of length N/2 from 0.
    // This gives every possible first-half-sum since only first N/2 keys are used.

    // For each of the N/2 first-half-sums, the second half of the encryption is done using
    // the second half of the table (do each of the N/2 possible second-half-sums and add the first-half-sum
    // and the second-half-sum together)

    // Now, imagine that you have every possible first-half-sum (N/2) saved somewhere in memory,
    // and that you can reference each of the N/2 sums somehow in a way that is querryable by each first-half-sum.
    
    // If so, and we take our value that we are trying to decrypt as E.
    // For each of the second-half-sums, look up which stored first-half-sum adds with
    // the second-half-sum to equal E ,i.e, compare second-half-sum with E-first-half-sum. (optimizable to constant complexity)

    CPU_timer t;
    t.tic();

    std::unordered_map < Key, std::vector< Key >, key_hash > first_h_keys; // first half keys
    // std::vector< Key > temp_keys;
    Key encryp = Key(encrypted);
    Key counter;

    // Fill the first half of the hash
    while( counter.m_digit[C/2 - 1] == 0 ) {
        //temp_keys.push_back(counter);
        Key subset = counter.subset_sum(T,verbose);

        //Check if that subset already exists in the hash
        if (first_h_keys.count(subset) == 1) {
            first_h_keys[subset].push_back(counter);
        } else {
            std::vector< Key > temp = { counter };
            first_h_keys.insert(make_pair(subset, temp));
        }
        counter++;
    }

    Key max_first_half = counter;


    // Check cands in first_half
    if( first_h_keys.count(encrypted) == 1 ) {
        //cout << "We have a cand in first_half" << endl;
        for( unsigned int i = 0; i < first_h_keys[encrypted].size(); ++i )
        {
            std::cout << first_h_keys[encrypted][i] << std::endl;
        }
    }


    Key zero;
    do {
        Key temp = encryp - counter.subset_sum(T,verbose);

        if ( first_h_keys.count(temp) == 1) {
            // print password when found
            for ( unsigned int i = 0; i < first_h_keys[temp].size(); ++i ) {
                std::cout << counter + first_h_keys[temp][i] << std::endl;
            }
        }
        counter = counter + max_first_half;
    } while (counter != zero);


    t.toc();
    double elapsed_secs = t.elapsed();

    std::cout << "Decryption took "
         << elapsed_secs
         << " Mill.seconds." << std::endl;
}

// Handle missing arguments and print help instructions
void usage(const std::string &error_msg = "") {
    if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
    std::cout << me << ": Symbol table-based cracking of Subset-sum password"
              << " with " << B << " bits precision\n"
              << "USAGE: " << me << " <encrypted> <table file> [options]\n"
              << "\nArguments:\n"
              << " <encrypted>:   encrypted password to crack\n"
              << " <table file>:  name of file containing the table to use\n"
              << "\nOptions:\n"
              << " -h|--help:     print this message\n"
              << " -v|--verbose:  select verbose mode\n\n";
    exit(0);
}


void initialize(int argc, char *argv[]) {
    me = argv[0];
    if (argc < 3) usage("Missing arguments");
    encrypted = argv[1];
    table_filename = argv[2];
    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") usage();
        else if (arg == "-v" || arg == "--verbose") verbose = true;
        else usage("Unrecognized argument: " + arg);
    }
}

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    Symbol b(table_filename);
    // try to decrypt
    b.decrypt(encrypted);

    return 0;
}