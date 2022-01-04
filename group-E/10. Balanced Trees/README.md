# Самобалансиращи дървета. Балансирани дървета

[Запис](https://drive.google.com/file/d/1Z5F-IofrEhmsKNTdHUE9TycSsv-ZOZ0j/view?usp=sharing)

## Балансирано дърво
Наредено дърво. Стремим се максималната височина на дървото да е `O(logn)`, така че операции като добавяне, премахване и търсене да работят със сложност `O(logn)` в най-лошия случай.

## Самобалансиращи се дървета
### AVL (Adelson, Velski & Landis)

За всеки елемент от дървото:
- разликата между височината на лявото и дясното му поддърво е **най-много** 1
- лявото му поддърво е балансирано
- дясното му поддърво е балансирано

`Баланс фактор - разликата между височината на лявото и дясното поддърво на един връх. За балансирано дърво тази разлика е в интервала [-1; 1]`

<img src="https://miro.medium.com/max/1024/0*Vi3aQ9sY9Yu4VNpa.png" alt="avl" width="400"/>

От тази дефиниция следва, че височината на дървото е `log(n)`

<img src="https://media.geeksforgeeks.org/wp-content/uploads/tree.jpg" alt="balanced-vs-non-balanced" width="400"/>

- лява и дясна ротация
```
      x                          y
     / \     Лява ротация       / \
    T1  y   - - - - - - - >    x  T3 
       / \  < - - - - - - -   / \
      T2 T3  Дясна ротация   T1 T2
```
За алгоритъма използваме: лява, дясна, ляво-дясна, дясно-лява
<img src="https://i.ytimg.com/vi/_nyt5QYel3Q/maxresdefault.jpg" alt="avl-rotations" width="700"/>

- добавяне
    - елемента се добавя чрез стандартния алгоритъм
    - връщаме се нагоре, докато не стигнем небалнсиран връх
    - прилагаме подходяща ротация, така че да балансираме дървото
        - ако баланс факторът е `> 1`, то лявото поддърво **L** е с по-голяма височина. Тогава
            - ако новодобавения елемент е част от лявото поддърво на **L**,  то прилагаме дясна ротация
            - иначе (новодобавения елемент е част от дясното поддърво на **L**) - ляво-дясна ротация
        - ако баланс факторът е `< -1`, то дясното поддърво **R** е с по-голяма височина. Тогава
            - ако новодобавения елемент е част от лявото поддърво на **R**,  то прилагаме ляво-дясна ротация
            - иначе (новодобавения елемент е част от дясното поддърво на **R**) - лява ротация
- премахване
    - елемента се премахва чрез стандартния алгоритъм
    - връщаме се нагоре, докато не стигнем небалнсиран връх
    - прилагаме подходяща ротация, така че да балансираме дървото
        - ако баланс факторът е `> 1`, то лявото поддърво **L** е с по-голяма височина. Тогава взимаме баланс фактора на **L** и 
            - ако е `>= 0`, дясна ротация
            - иначе ляво-дясна ротация
        - ако баланс факторът е `< -1`, то дясното поддърво **R** е с по-голяма височина. Тогава взимаме баланс фактора на **R** и 
            - ако е `<= 0`, лява ротация
            - иначе дясно-лява ротация
            
### Red-black
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Red-black_tree_example.svg/316px-Red-black_tree_example.svg.png" alt="red-black" width="350"/>

### Splay
<img src="https://www.researchgate.net/profile/Zouheir-Trabelsi/publication/281734426/figure/fig1/AS:284596265603074@1444864445524/Splay-tree-basic-rotations-splaying-node-x-to-the-root.png" alt="splay-tree" width="250"/>