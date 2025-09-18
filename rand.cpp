#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));\

    while (true) {
        int num1 = (rand() % 5000 + 1);
        std::cout << num1 << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }

    return 0;
}