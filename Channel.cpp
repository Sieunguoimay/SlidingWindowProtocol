#include "Channel.h"
#include<iostream>
#include<thread>
#include<chrono>


Channel::Channel()
{
	m_idle = true;
}


Channel::~Channel()
{
}

bool Channel::IsIdle() const
{
	return m_idle;
}
void Channel::Send(const Packet & packet)
{
	m_buffer = packet; 
	m_trasmitting = m_delay;
	m_idle = false;
}



Packet Channel::GetPacket()
{
	if (m_packetArrived) {
		m_packetArrived = false;
		m_idle = true;
		return m_buffer;
	}
	return Packet();
}


void Channel::Update()
{
	int counter = SIMULATION_TIME;
	m_idle = true;
	while (m_running) {
		if (counter-- == 0) m_running = false;

		std::this_thread::sleep_for(std::chrono::milliseconds(CHANNEL_DELAY_TIME));
		if (m_trasmitting > 0) {
			//std::cout << "Channel "<<id<<": Trasmissing data..\n";
			m_trasmitting--;
			flag = true;
		}
		else {
			if (flag) {
				m_packetArrived = true;
				flag = false;
			}
		}
	}
	std::cout << "Channel terminated!\n";
}
