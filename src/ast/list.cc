#include "list.h"

ListNode::ListNode(NodeList *args) {
  this -> argv = args ? args : new NodeList();
}

ListNode::~ListNode() {
  while (!argv -> empty()) {
    AstNode *arg = argv -> front();
    argv -> pop_front();
    delete arg;
  }
  delete argv;
}

void ListNode::resolve(Func *fn) {
  NodeList::iterator it = argv -> begin();
  for (; it != argv -> end(); ++it) {
    (*it) -> resolve(fn);
  }
}

AstNode* ListNode::eval(AstNode *env[]) {

  NodeList *reduced = new NodeList();

  NodeList::iterator it = argv -> begin();
  for (; it != argv -> end(); ++it) {
    reduced -> push_back((*it) -> eval(env));
  }

  return new ListNode(reduced);
}

void ListNode::print(int fd) {

  dprintf(fd, "[");
  NodeList::iterator it = argv -> begin();
  for (; it != argv -> end(); ++it) {
    (*it) -> print(fd);
    if (it != argv -> end() - 1) {
      dprintf(fd, " ");
    }
  }
  dprintf(fd, "]");

}
