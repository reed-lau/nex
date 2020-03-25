#include <uv.h>

#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <vector>

namespace nex {

class BackBone {
 public:
  BackBone();
  bool Init();
  void Run();
  void Stop();

 private:
  uv_loop_t *loop;
};

class Role {
 public:
  using OnReadFunc = std::function<void(std::vector<uint8_t>, int, void *)>;

  Role(const char *ip, int port, const OnReadFunc &cb, void *ud);
  void Write(const char *data, size_t size);

 private:
  using RoleContext = struct {
    uv_tcp_t server;
    std::list<uv_tcp_t> client;
    std::string ip;
    int port;
    struct sockaddr_in addr;
  };
  RoleContext context_;
};

Role::Role(const char *ip, int port, const OnReadFunc &cb, void *ud) {
  uv_ip4_addr(ip, port, &(context_.addr));
}

}  // namespace nex

int main() {}
