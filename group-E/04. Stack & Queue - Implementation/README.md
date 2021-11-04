# Стек и опашка - видове реализации

[Запис](https://drive.google.com/file/d/1dxhPQ_lq5wzkrdKDxnfk1MlRDdIQ2nHx/view?usp=sharing)

## Стек
### LIFO / FILO 
(**L**ast **I**n **F**irst **O**ut / **F**irst **I**n **L**ast **O**ut)

<img src="https://www.tutorialspoint.com/data_structures_algorithms/images/stack_representation.jpg" alt="stack" width="400"/>

#### Основни методи
- `push` - добавя елемент на върха
- `pop` - премахва елемента на върха
- `top` - връща референция към елемента на върха
- `size` - връща размера на стека
- `empty` - връща дали стека е празен
- оператори за сравнение - **работят с линейна сложност** (защо?)


## Опашка
### FIFO / LILO
(**F**irst **I**n **F**irst **O**ut / **L**ast **I**n **L**ast **O**ut)

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/1200px-Data_Queue.svg.png" alt="queue" width="400"/>

#### Основни методи
- `push` / `enqueue` - добавя елемент най-отзад
- `pop` / `dequeue` - премахва елемента най-отпред
- `front` - връща референция към елемента най-отпред
- `back` - връща референция към елемента най-отзад
- `size` - връща размера 
- `empty` - връща дали стека е празен
- оператори за сравнение - отново **работят с линейна сложност**

---

### За домашно 
Реализация на стек с допълнителен шаблонен аргумент за контейнера, в който се съхраняват елеменетите:

```c++
template<class T, class Container = std::vector<T>>
class stack;
```
