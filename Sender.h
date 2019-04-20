#pragma once
#include"stdafx.h"
#include"Module.h"
#include"Channel.h"
class Sender: public Module
{
	FullDuplexChannel*m_pChannel;
	const int m_id = 0;
	std::string m_dataTobeSent="";

	char m_buffer[BUFFER_SIZE];
public:
	Sender(FullDuplexChannel*pChannel);
	~Sender();
	void Update() override;
	void SetData(const char*data) { m_dataTobeSent = data; }
};

