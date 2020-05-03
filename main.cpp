//main.cpp
//Ben Talotta
//cs372 final part c
//referenced refactoring.guru for how to write chain of responsibility
#include<iostream>
#include<string>
#include<vector>

class Handler {
 public:
  virtual Handler *nextHandle(Handler *handler) = 0;
  virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler {
 private:
  Handler *next_handler_;
 public:
  AbstractHandler() : next_handler_(nullptr) {
  }
  Handler *nextHandle(Handler *handler) override {
    this->next_handler_ = handler;
    return handler;
  }
  std::string Handle(std::string request) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request);
    }
    return {};
  }
};

class PickyHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "plain") {
      return "picky eater:  I only want a " + request + " pizza.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class thatGuylHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "pineapple") {
      return "enlightend thinker: It does belong on Pizza, I want " + request + " on it.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class StandardHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "pepperoni") {
      return "bob:    I'm fine with getting a " + request + " pizza.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class everythingHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "combo") {
      return "angry guy: I'm fine with getting a " + request + " any pizza without pineapple is a good pizza.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
void ClientCode(Handler &handler) {
  std::vector<std::string> food = {"plain", "pineapple", "pepperoni", "combo"};
  for (const std::string &f : food) {
    std::cout << "Client: what kind of pizza should we get? " << "\n";
    const std::string result = handler.Handle(f);
    if (!result.empty()) {
      std::cout << result;
    } else {
      std::cout << "Result: Nobody wanted " << f << " pizza.\n";
    }
  }
}
int main() {
  PickyHandler *picky = new PickyHandler;
  thatGuylHandler *pineappleDude = new thatGuylHandler;
  StandardHandler *bob = new StandardHandler;
  everythingHandler *angry =new everythingHandler;
  picky->nextHandle(pineappleDude)->nextHandle(bob)->nextHandle(angry);
  std::cout << "Chain: all handles\n\n";
  ClientCode(*picky);
  std::cout << "\n";
  std::cout << "Subchain: just pepperoni and combo handle\n\n";
  ClientCode(*pineappleDude);
  delete picky;
  delete pineappleDude;
  delete bob;
  delete angry;
  return 0;
}