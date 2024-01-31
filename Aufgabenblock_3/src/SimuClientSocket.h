#pragma once

#include <string>
#include <sstream>
#include <boost/asio.hpp>

#ifndef DEBUG
#define DEBUG 0
#endif

using boost::asio::ip::tcp;

class SimuClientSocket {
public:
  SimuClientSocket();
  virtual ~SimuClientSocket() = default;
  bool Create();
  bool Connect(std::string address, std::string port);
  void Send(std::stringstream& msg);
  void Close();
private:
  boost::asio::io_context io_context;
  tcp::socket socket;
};
