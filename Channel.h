#pragma once
#include"stdafx.h"
#include<string>
#include"Module.h"

struct Packet {
	std::string data;
	int toId;
	int fromId;
};
class Channel: public Module
{
	bool m_packetArrived = false;
	int m_trasmitting = 0;
	bool m_idle;
	Packet m_buffer;
	const int m_delay = 3;

	int counter = SIMULATION_TIME;
	bool flag = false;
public:
	Channel();
	~Channel();
	bool IsIdle() const;
	void Send(const Packet& packet);

	Packet GetPacket();
	bool HasPacketArrived()const { return m_packetArrived; }

	void Update()override;
};

class FullDuplexChannel{
	Channel m_channel1;
	Channel m_channel2;
public:
	Channel& GetChannel1() { return m_channel1; }
	Channel& GetChannel2(){ return m_channel2; }
};
