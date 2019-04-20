#include<iostream>
#include<Windows.h>
#include<thread>
#include<mutex>

#include"Channel.h"
#include"Sender.h"
#include"Receiver.h"
int main() {
	std::cout << "Hello Sliding Window Protocol\n";

	FullDuplexChannel fullDuplexChannel;
	Sender sender(&fullDuplexChannel);
	Receiver receiver(&fullDuplexChannel);

	sender.SetData("Do not go gentle into that good night");

	std::thread sender_thread(Module::Run, &sender);
	std::thread receiver_thread(Module::Run, &receiver);
	std::thread channel1_thread(Module::Run, &fullDuplexChannel.GetChannel1());
	std::thread channel2_thread(Module::Run, &fullDuplexChannel.GetChannel2());

	std::cout << "We are all ready!\n";

	channel1_thread.join();
	channel2_thread.join();
	receiver_thread.join();
	sender_thread.join();

	std::cout << "Goodbye!\n";
	system("pause");
	return 0;
}