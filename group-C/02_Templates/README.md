## Темплейти

### За какво си говорихме(накратко) :
- какво представляват темплейтите
- какво правим, ако искаме дадена функция или клас да имат различно поведение за конкретен тип
- какво се генерира и какво не


### 1. Какво представляват темплейтите? - highlights
- позволяват ни да разпишем дадена функционалност с еднакво поведение за различни типове само веднъж
- вид полиморфизъм
- разделната компилация води до грешка - linker error  
 ```Примери: ```  
Функция:
```cpp
//...
template <typename Type>
Type add(Type lhs, Type rhs)
{
    return lhs + rhs;
}

int main()
{
    std::cout << add(5, 6) << std::endl;
    std::cout << add(5.8, 10) << std::endl;

    return 0;
}
```
Клас :
```cpp
//...
const size_t MAX_SIZE = 256;
template <typename Type>
class Container {
private:
    Type data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0)
    {       
    }

    Type get_at(size_t index) const 
    {
        if(index < size)
            return data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type&);
};

template <typename Type>
void Container<Type>::add(const Type& new_elem)
{
    if(size == MAX_SIZE)
        throw std::out_of_range("There is not enough space!");
    data[size++] = new_elem;
}
```

### 2. Как можем да конкретизираме поведение?
Функция:
```cpp
//...
template <typename Type>
Type add(Type lhs, Type rhs)
{
    return lhs + rhs;
}

template <>
double add(double lhs, double rhs)
{
    std::cout << "Type: double" << std::endl;
    return lhs + rhs;
}
```
Клас :
- членовете на специализацията могат да бъдат различни
```cpp
//...
const size_t MAX_SIZE = 256;
template <typename Type>
class Container {
private:
    Type data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0)
    {       
    }

    Type get_at(size_t index) const
    {
        if(index < size)
            return data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type&)
    {
        if(size == MAX_SIZE)
            throw std::out_of_range("There is not enough space!");
        data[size++] = new_elem;
    }
    
};

template <>
class Container {
private:
    int data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0)
    {

    }

    //int get_at(size_t index) - махаме функционалност
    //добавяме нова
    void display_at(size_t index) const
    {
        if(index < size)
            std::cout << data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type&)
    {
        if(size == MAX_SIZE)
            throw std::out_of_range("There is not enough space!");
        data[size++] = new_elem;
    }
}
```

### 3. Какво се генерира и как да проверим?
- генерират се само функциите, които използваме
- ```g++ -S <filename>.cpp``` - compile only, do not assemble or link, резултат - assembler code файл - ```<filename>.s```

```cpp
//...
const size_t MAX_SIZE = 256;
template <typename Type>
class Container {
private:
    Type data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0)
    {       
    }

    Type get_at(size_t index) const
    {
        if(index < size)
            return data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type& new_elem)
    {
        if(size == MAX_SIZE)
            throw std::out_of_range("There is not enough space!");
        data[size++] = new_elem;
    }
    
};
```

```cpp
int main()
{
    Container<int> obj;
    obj.add(10);

    return 0;
}
```

- [Резултат](https://godbolt.org/z/cWWsa1obP) - add() е генерирана, get_at() липсва


