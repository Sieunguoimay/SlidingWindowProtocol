#pragma once
#include"stdafx.h"
#include"Module.h"
#include"Channel.h"
class Receiver: public Module
{
	FullDuplexChannel*m_pChannel;
	const int m_id = 1;

	char m_buffer[BUFFER_SIZE];
	int buffer_counter = 0;
	int ack_counter = 0;

public:
	Receiver(FullDuplexChannel*pChannel);
	~Receiver();
	void Update() override;
};

