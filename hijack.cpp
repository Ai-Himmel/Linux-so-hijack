#include "PatternSearch.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>
#ifdef __x86_64
#define ADDRLEN 12
#elif
#define ADDRLEN 8
#endif
__attribute__((constructor))
void hijack() {
    
    std::string line;
    std::string name = "dummy";
    std::string maps = "/proc/self/maps";
    std::fstream fs(maps, std::ios::in);
    PatternSearch ps{"original"};
    while (std::getline(fs, line)) {
        if (line.find(name) != std::string::npos) {
            int prot = PROT_READ;
            unsigned long long start, end;
            std::vector<ptr_t> ptr;
            start = std::stoull(line.substr(0, ADDRLEN), 0, 16);
            end = std::stoull(line.substr(ADDRLEN + 1, ADDRLEN), 0, 16);
            ps.Search((void *)start, end - start, ptr);
            if (line[2 * ADDRLEN + 3] == 'w')
                prot |= PROT_WRITE;
            if (line[2 * ADDRLEN + 4] == 'x')
                prot |= PROT_EXEC;
            if (not(prot & PROT_WRITE)) {
                mprotect((void *)start, end - start, prot | PROT_WRITE);
            }
            for (auto &n : ptr) {
                std::memcpy((void *)n, "hooooook", 8);
            }
            if (not(prot & PROT_WRITE)) {
                mprotect((void *)start, end - start, prot);
            }
        }
    }
    
   
}