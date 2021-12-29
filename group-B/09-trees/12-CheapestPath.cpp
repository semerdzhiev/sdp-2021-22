#include <iostream>
#include <vector>
#include <limits>

struct Node {
    int value;
    std::vector<Node> children;
};

using NodePtrVec = std::vector< const Node* >;

void fcpRec( const Node* root, NodePtrVec& currPath, int currValue, NodePtrVec& outResPath, int& outMin )
{
    currValue += root->value;
    currPath.push_back( root );

    if ( currValue < outMin )
    {
        if ( root->children.empty() )
        {
            outMin      = currValue;
            outResPath  = currPath;
        }
        else
        {
            for ( const Node& child : root->children )
                fcpRec( &child, currPath, currValue, outResPath, outMin );
        }
    }

    currPath.pop_back();
}

NodePtrVec findCheapestPath( const Node* root )
{
    int         min     = std::numeric_limits<int>::max();
    NodePtrVec  path;
    NodePtrVec  currPath;
    fcpRec( root, currPath, 0, path, min );
    return path;
}


int main()
{
    Node root =
    { 5,
        {
        { 10 },
        { 6, 
            { { 3 } } 
        },
        { 2,
            {
            { 3, 
                { { 2 } }
            }
            }
        }
        }
    };

    NodePtrVec result = findCheapestPath( &root );

    for ( const Node* node : result )
        std::cout << node->value << " ";

    return 0;
}
