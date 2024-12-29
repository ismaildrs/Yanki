#include <iostream>
#include <memory>
#include <vector>

namespace YANKI
{

  namespace DS
  {
    class Node
    {
    private:
      std::vector<Node> children;

    public:
      std::vector<Node> getChildren()
      {
        return children;
      }
      Node getChild(int index)
      {
        return children[index];
      }

    };
  }

}