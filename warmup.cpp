// warmup.cpp
#include <iosteam>
#include <unistd.h>
#include <cstring.h>
#include <sys/mman.h>
using namespace std;

int main() {
    // Part 1 :
    cout << "PID: " << getpid();
    
    cout << "\nPress Enter to Continue";
    cin.get();

    // Part 2 :
    size_t pagesize = sysconf(_SC_PAGESIZE);
    void *p = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    cout << "\nMapped new page...";
    cin.get();
   
    // Part 3 :

    cout << "\nWrite data to mapped page");
    memset(p, 0xAB, pagesize);

    cout << "\nPage touched (written)\n");
    cin.get();

    sleep(10);

    // cleaning data
    munmap(p, page_size)
    
    return 0;
}
