# Обобщение - Дървета, Unit тестве

```c++
struct node
{
    node(int v): value{v} {}
    int value;
    std::vector<node*> children;
};
```

# Задача 1
По даден корен на n-ично дърво с елементи естествени числа, заместете стойността на всеки връх със сумата на стойностите на елемените във всички негови поддървета и неговата стойност

```c++
//                       1
//                    /  |  \
//                   2   3    4
//                  /\ \
//                  5 6 7
node* n1 = new node(1);
node* n2 = new node(2);
node* n3 = new node(3);
node* n4 = new node(4);
node* n5 = new node(5);
node* n6 = new node(6);
node* n7 = new node(7);

n1->children.push_back(n2);
n1->children.push_back(n3);
n1->children.push_back(n4);
n2->children.push_back(n5);
n2->children.push_back(n6);
n2->children.push_back(n7);
```

# Задача 2
Дадени са корен на n-ично дърво с елементи естествени числа и число. Ако това число съществува в дървото, изведете броя на елементите в поддървото му. Ако стоността не е част от дървото, изведете -1.
```c++
//                       1
//                    /  |  \
//                   2   3    4
//                  /\ \     / \
//                  5 6 7   8   9
node* n1 = new node(1);
node* n2 = new node(2);
node* n3 = new node(3);
node* n4 = new node(4);
node* n5 = new node(5);
node* n6 = new node(6);
node* n7 = new node(7);
node* n8 = new node(8);
node* n9 = new node(9);

n1->children.push_back(n2);
n1->children.push_back(n3);
n1->children.push_back(n4);
n2->children.push_back(n5);
n2->children.push_back(n6);
n2->children.push_back(n7);
n4->children.push_back(n8);
n4->children.push_back(n9);

std::cout<<count_subtree_elements(4)<<std::endl; // 2
std::cout<<count_subtree_elements(2)<<std::endl; // 3
std::cout<<count_subtree_elements(1)<<std::endl; // 8
std::cout<<count_subtree_elements(10)<<std::endl; //-1
```
