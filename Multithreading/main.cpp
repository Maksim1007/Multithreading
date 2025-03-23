#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> client_count(0);
const int max_clients = 10;

void client_thread()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int current_count = client_count.load();
        if (current_count < max_clients) {
            client_count++;
            std::cout << "Клиент пришел. Текущее количество клиентов: " << client_count.load() << std::endl;
        }
        else {
            std::cout << "Достигнуто максимальное количество клиентов." << std::endl;
            break;
        }
    }
}

void operator_thread() 
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int current_count = client_count.load();
        if (current_count > 0) {
            client_count--;
            std::cout << "Операционист обслужил клиента. Осталось клиентов: " << client_count.load() << std::endl;
        }
        else {
            std::cout << "Все клиенты обслужены." << std::endl;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::thread client(client_thread);
    std::thread operator_(operator_thread);

    client.join();
    operator_.join();

    return 0;
}
