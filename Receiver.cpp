#include "Receiver.h"
#include<iostream>
#include<thread>
#include<chrono>
#include<string>
Receiver::Receiver(FullDuplexChannel*pChannel)
	:m_pChannel(pChannel)
{
}


Receiver::~Receiver()
{
	m_pChannel = NULL;
}

void Receiver::Update()
{
	int counter = SIMULATION_TIME;
	std::string result = "";
	while (m_running) {
		if (counter-- == 0) m_running = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(RECEIVER_DELAY_TIME));

		//Sliding window protocol..
		if (m_pChannel->GetChannel1().HasPacketArrived()) {
			Packet frame = m_pChannel->GetChannel1().GetPacket();

			m_buffer[buffer_counter] = frame.data[1];
			buffer_counter = (buffer_counter+1)%BUFFER_SIZE;

			result += frame.data[0];
			std::cout << "Receiver: RECV: " << frame.data //<< " ->("<<m_buffer<<")-> "
				<<"--------------> "<<result<<'\n';


		}

		if (ack_counter != buffer_counter&&m_pChannel->GetChannel2().IsIdle()) {
			Packet ack;
			ack.data = std::to_string(m_buffer[ack_counter]-'0');
			m_buffer[ack_counter] = '_';
			ack.toId = 0;
			ack.fromId = m_id;
			m_pChannel->GetChannel2().Send(ack);
			ack_counter = (ack_counter + 1) % BUFFER_SIZE;
		}
	}
	std::cout << "Receiver terminated\n";
}

/*

if (m_pChannel->HasPacketArrived(m_id)) {
	Packet packet = m_pChannel->GetPacket();
	std::cout	<< "Reciver: This is the message that I got: "
	<< packet.data << "\n";
	m_pChannel->PacketReceived();

	packet.data = "Ack: hey man Thanks for your message";
	packet.toId = packet.fromId;
	packet.fromId = m_id;
	m_pChannel->Send(packet);
}

*/