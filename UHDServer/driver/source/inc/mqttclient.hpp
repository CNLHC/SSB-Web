

#include "mqtt/async_client.h"
#include <atomic>
using namespace std;

class callback : public virtual mqtt::callback
{
 public:
  void connection_lost(const string& cause) override {
    cout << "\nConnection lost" << endl;
    if (!cause.empty())
      cout << "\tcause: " << cause << endl;
  }

  void delivery_complete(mqtt::delivery_token_ptr tok) override {
    cout << "\tDelivery complete for token: "
         << (tok ? tok->get_message_id() : -1) << endl;
  }
};

class action_listener : public virtual mqtt::iaction_listener
{
 protected:
  void on_failure(const mqtt::token& tok) override {
    cout << "\tListener failure for token: "
         << tok.get_message_id() << endl;
  }

  void on_success(const mqtt::token& tok) override {
    cout << "\tListener success for token: "
         << tok.get_message_id() << endl;
  }
};

class delivery_action_listener : public action_listener {
  atomic<bool> done_;

  void on_failure(const mqtt::token &tok) override {
    action_listener::on_failure(tok);
    done_ = true;
  }

  void on_success(const mqtt::token &tok) override {
    action_listener::on_success(tok);
    done_ = true;
  }

 public:
  delivery_action_listener() : done_(false) {}
  bool is_done() const { return done_; }
};




