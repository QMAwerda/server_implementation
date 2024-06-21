#include "net_connection.hpp"
#include "olc_net.hpp"

#include <cstdint>
#include <iostream>

enum class CustomMsgTypes : uint32_t {
  ServerAccept,
  ServerDeny,
  ServerPing,
  MessageAll,
  ServerMessage,
};

class CustomServer : public olc::net::server_interface<CustomMsgTypes> {
public:
  CustomServer(uint16_t nPort)
      : olc::net::server_interface<CustomMsgTypes>(nPort) {}

protected:
  virtual bool OnClientConnect(
      std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) {
    return true;
  } // can't make override here, because the sinature this func and
  // virtual bool OnClientConnect(std::shared_ptr<connection<T>> client)
  //  is different (T and CustomMsgTypes)

  // Called when a client appears to have disconnected
  virtual void OnClientDisconnect(
      std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) {}

  // Called when a message arrives
  virtual void
  OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client,
            olc::net::message<CustomMsgTypes> &msg) {
    std::cout << "I Got message from client\n";
    switch (msg.header.id) {
    case CustomMsgTypes::ServerPing: {
      std::cout << "[" << client->GetID() << "] Server Ping\n";

      // Simple bounce message back to client
      client->Send(msg);
    }
    }
  }
};

int main() {
  CustomServer server(60000);
  server.Start();
  while (1) {
    server.Update();
  }
}