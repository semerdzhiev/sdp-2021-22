#include <iostream>

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


//------------------------------------------------------------------------------
int main()
{
    BTreeNode*   root       = new BTreeNode( 1 );

    root->fpLeft            = new BTreeNode( 2 );
    root->fpRight           = new BTreeNode( 3 );

    root->fpLeft->fpLeft    = new BTreeNode( 4 );
    root->fpLeft->fpRight   = new BTreeNode( 5 );

    std::cout << "Inorder:\t";
    printInorder( root );
    std::cout << "\nPreorder:\t";
    printPreorder( root );
    std::cout << "\nPostorder:\t";
    printPostorder( root );

    eraseTree( root );  // !!!

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
