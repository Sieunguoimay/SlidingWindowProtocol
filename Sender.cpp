#include "Sender.h"
#include<iostream>
#include<thread>
#include<chrono>

Sender::Sender(FullDuplexChannel*pChannel)
	:m_pChannel(pChannel)
{
}


Sender::~Sender()
{
	m_pChannel = NULL;
}

void Sender::Update()
{
	int counter = SIMULATION_TIME;
	bool oneTimeFlag = true;

	int data_counter = 0;
	int window_counter = 0;
	int buffer_counter = 0;
	while (m_running) {
		if (counter-- == 0) m_running = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(SENDER_DELAY_TIME));


		if (m_pChannel->GetChannel2().HasPacketArrived()) {
			Packet ack = m_pChannel->GetChannel2().GetPacket();
			m_buffer[ack.data[0]-'0'] = '_';
			std::cout << "Sender: ACKed: " << ack.data << "->" << "(" << m_buffer << ")" << '\n';
			window_counter--;
		}

		//Sliding window protocol..
		if ((window_counter < WINDOW_SIZE)&&
			(data_counter < m_dataTobeSent.length())&&
			(m_pChannel->GetChannel1().IsIdle())) {
			
			char data = m_dataTobeSent[data_counter];
			Packet frame = { std::string(2,data),1,m_id };
			frame.data[1] = buffer_counter+'0';
			m_buffer[buffer_counter] = data;

			m_pChannel->GetChannel1().Send(frame);

			data_counter++;
			buffer_counter++;
			window_counter++;

			if (buffer_counter >= BUFFER_SIZE) buffer_counter = 0;

			std::cout << "Sender: SENT: " << frame.data <<"<-"<< "(" << m_buffer << ")\n";
		}

	}
	std::cout << "Sender terminated\n";
}
/*

if (oneTimeFlag) {
Packet packet = { "This is data bro", 1 , m_id};
m_pChannel->Send(packet);
oneTimeFlag = false;

std::cout << "Sender: Sent data! "<<packet.data<<'\n';
}*/