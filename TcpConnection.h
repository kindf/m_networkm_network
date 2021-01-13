#ifndef __TCPCONNECTION__H
#define __TCPCONNECTION__H

#include <string>
#include <memory>

#include "Channel.h"
#include "Callback.h"
#include "Channel.h"

using namespace network;

namespace network
{
	class Eventloop;

	class TcpConnection:public std::enable_shared_from_this<TcpConnection>
	{
	public:
		TcpConnection(EventLoop* loop, int fd, std::string name);
		~TcpConnection(){};

		static const int MAX_INPUT_BUFFER_SIZE = 65535;
		static const int MAX_OUTPUT_BUFFER_SIZE = 65535;

	public:
		void HandleRead();
		void ConnectEstablished();
		void ConnectDestroyed();
		const string& GetName()const{return m_name;};
	private:
		TcpConnection(const TcpConnection&);
		TcpConnection& operator= (const TcpConnection&);

		int OnReadFd();

	private:
		const string				m_name;
		ConnectionCallback			m_connection_callback;
		CloseCallback				m_close_callback;
		WriteCompleteCallback		m_write_callback;
		MessageCallback				m_message_callback;


		EventLoop*					m_loop;
		std::unique_ptr<Channel>	m_channel_ptr;
		std::string					m_input_buff;
		std::string					m_output_buff;
	};
}

#endif