#include <iostream>

int main() {
    unsigned int n;
    int count = 0;
    std::cin >> n;
    while (n != 0) {
        if (n & 1) count++;
        n >>= 2;
    }
    std::cout << count;
    return 0;
}
