#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

// Memory leak detection define and libraries
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Basic binary tree node structure
struct BTreeNode
{
    BTreeNode( int data = {}, BTreeNode* left = nullptr, BTreeNode* right = nullptr )
        : fData( data )
        , fpLeft( left )
        , fpRight( right )
    {}

    int         fData;
    BTreeNode*  fpLeft;
    BTreeNode*  fpRight;
};

// Task 1
void printInorder( const BTreeNode* root );
void printPreorder( const BTreeNode* root );
void printPostorder( const BTreeNode* root );
void eraseTree( BTreeNode*& root );

// Task 4
void trim( BTreeNode*& root );

// Get node with min property in BST
BTreeNode* getMinBST( BTreeNode* bstRoot );

// Basic general tree node structure
struct TreeNode
{
    int                     fData;
    std::vector<TreeNode*>  fChildren;
};

void printGeneralTree( const TreeNode* root );
void eraseTree( TreeNode*& root );
void printGeneralTreeByLevels( const TreeNode* root );

// Task 7
int treeHeight( const TreeNode* root );

// Task 8
int branchingFactor( const TreeNode* root );

// Task 9
void printLevel( const TreeNode* root, unsigned level );

//------------------------------------------------------------------------------
int main()
{
    std::cout
        << "----------------------------------------------\n"
        << " Binary Tree\n"
        << "----------------------------------------------\n";

    BTreeNode*   btRoot     = new BTreeNode( 1 );

    btRoot->fpLeft          = new BTreeNode( 2 );
    btRoot->fpRight         = new BTreeNode( 3 );

    btRoot->fpLeft->fpLeft  = new BTreeNode( 4 );
    btRoot->fpLeft->fpRight = new BTreeNode( 5 );

    std::cout << "Inorder:\t";
    printInorder( btRoot );
    std::cout << "\nPreorder:\t";
    printPreorder( btRoot );
    std::cout << "\nPostorder:\t";
    printPostorder( btRoot );

    eraseTree( btRoot );    // !!!


    std::cout << "\n\n"
        << "----------------------------------------------\n"
        << " General Tree\n"
        << "----------------------------------------------\n";

    TreeNode*    gtRoot     = new TreeNode
    {
        5, {
            new TreeNode{2, { new TreeNode{4, {} }}},
            new TreeNode{3, { new TreeNode{6, {} }}},
            new TreeNode{9, {}},
            new TreeNode{6, {}}
        }
    };

    std::cout << "PrintGeneralTree:\t";
    printGeneralTree( gtRoot );
    std::cout << '\n';

    std::cout << "Printed by levels:\t";
    printGeneralTreeByLevels( gtRoot );
    std::cout << '\n';

    std::cout << "Height:\t\t\t" << treeHeight(gtRoot) << '\n';
    std::cout << "Level 2:\t\t";
    printLevel( gtRoot, 2 );

    eraseTree( gtRoot );    // !!!


    std::cout << "\n\n"
        << "----------------------------------------------\n"
        << " STL Containers\n"
        << "----------------------------------------------\n";

    // unnamed scope so that containers call their destructors before dumping leaks
    {
        using FN_t      = int;
        using name_t    = std::string;

        std::multimap<FN_t, name_t>   map;
        for ( size_t i = 0; i < 10; i++ )
        {
            map.insert( { rand() % 10, std::string( "Georgi" ) + std::to_string( i ) } );
        }

        //std::map<FN_t, name_t>::iterator    it  = map.find( 0 );
        //if ( it != map.end() )
        //{
        //    std::pair<FN_t, name_t> res = *it;
        //    std::cout << res.second;
        //}

        for ( std::pair<FN_t, name_t> elem : map )
            std::cout << elem.first << ", " << elem.second << '\n';

        //std::set<int>   set;
        //for ( size_t i = 0; i < 10; i++ )
        //{
        //    set.insert( rand() % 10 );
        //}

        //for ( int elem : set )            // linear
        //    std::cout << elem << ' ';     // traversal

        //std::cout << '\n';

        //std::cout << *set.begin() << '\n';    // min elem in constant time
        //std::cout << *set.rbegin();           // max elem in constant time
    }

    // Detect and dump in the Output window any memory that hasn't been deleted
    _CrtDumpMemoryLeaks();

    return 0;
}
//------------------------------------------------------------------------------


// Left Root Right
void printInorder( const BTreeNode* root )
{
    if ( !root )
        return;

    printInorder( root->fpLeft );
    std::cout << root->fData << ' ';
    printInorder( root->fpRight );
}

// Root Left Right
void printPreorder( const BTreeNode* root )
{
    if ( !root )
        return;

    std::cout << root->fData << ' ';
    printPreorder( root->fpLeft );
    printPreorder( root->fpRight );
}

// Left Right Root
void printPostorder( const BTreeNode* root )
{
    if ( !root )
        return;

    printPostorder( root->fpLeft );
    printPostorder( root->fpRight );
    std::cout << root->fData << ' ';
}

void eraseTree( BTreeNode*& root )
{
    if ( !root )
        return;

    eraseTree( root->fpLeft );
    eraseTree( root->fpRight );

    // delete root must be the last operation
    delete root;
    root = nullptr;
}

void trim( BTreeNode*& root )
{
    if ( !root )
        return;

    if ( root->fpLeft == nullptr && root->fpRight == nullptr )
    {
        delete root;
        root = nullptr;
    }
    else
    {
        trim( root->fpLeft );
        trim( root->fpRight );
    }
}

BTreeNode* getMinBST( BTreeNode* root )
{
    if ( !root )
        return nullptr;

    if ( root->fpLeft )
        return getMinBST( root->fpLeft );

    return root;
}

//------------------------------------------------------------------------------
void printGeneralTree( const TreeNode* root )
{
    if ( !root )
        return;

    for ( TreeNode* child : root->fChildren )
        printGeneralTree( child );

    std::cout << root->fData << ' ';
}

void eraseTree( TreeNode*& root )
{
    if ( !root )
        return;

    for ( TreeNode*& child : root->fChildren )
        eraseTree( child );

    // delete root must be the last operation
    delete root;
    root = nullptr;
}

void printGeneralTreeByLevels( const TreeNode* root )
{
    if ( !root )
        return;

    std::queue<const TreeNode*>   wave;
    wave.push( root );

    while ( !wave.empty() )
    {
        const TreeNode* curr    = wave.front();
        wave.pop();

        std::cout << curr->fData << ' ';

        for ( const TreeNode* child : curr->fChildren )
            wave.push( child );
    }
}

int treeHeight( const TreeNode* root )
{
    if ( !root )
        return 0;

    int maxHeight = 0;
    for ( const TreeNode* node : root->fChildren )
    {
        int childHeight = treeHeight( node );
        if ( childHeight > maxHeight )
            maxHeight = childHeight;
    }

    return 1 + maxHeight;
}

int branchingFactor( const TreeNode* root )
{
    if ( !root )
        return 0;

    int maxBF = root->fChildren.size();
    for ( const TreeNode* node : root->fChildren )
    {
        int childBF = branchingFactor( node );
        if ( childBF > maxBF )
            maxBF = childBF;
    }

    return maxBF;
}

void printLevel( const TreeNode* root, unsigned level )
{
    if ( !root )
        return;

    if ( level > 0 )
    {
        for ( const TreeNode* node : root->fChildren )
            printLevel( node, level - 1 );
    }
    else
    {
        std::cout << root->fData << ' ';
    }
}
