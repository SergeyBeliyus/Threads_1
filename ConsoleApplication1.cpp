#include <iostream>
#include <thread>
#include <chrono>

void client(int duration, bool &full_capacity , int &clientsToDo, int& clients) {
	while (!full_capacity) {
		if (clients < clientsToDo) {
			full_capacity = false;
			clients++;
			std::cout << "Пришел клиент " << clients << "\n";
		}
		else {
			full_capacity = true;
		}
		std::this_thread::sleep_for(std::chrono::seconds(duration));
	}
}

void operationist(int duration, int& clientsToDo, int& clients) {
	while (clients >= 0) {
		clients--;
		std::this_thread::sleep_for(std::chrono::seconds(duration));
	}
}

int main() {
	int clients = 0;
	int clients_toDo = 0;
	bool full_capacity = false;

	std::cout << "Введите число клиентов: ";
	std::cin >> clients_toDo;


	std::thread th1(client, 1, std::ref(full_capacity), std::ref(clients_toDo), std::ref(clients));
	std::thread th2(operationist, 2, std::ref(clients_toDo), std::ref(clients));


	th1.join();
	std::cout << "Пришло максимальное колиество клиентов\n";

	th2.join();
	std::cout << "Обслуживание завершено\n";

	return 0;
}