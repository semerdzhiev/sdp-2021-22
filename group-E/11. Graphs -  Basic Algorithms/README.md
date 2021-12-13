# Графи - представяния, свойства. BFS. DFS.

## Графи

**G = (V, E)** - граф `G` е наредена двойка, където `V` е множество от върхове (vertices), а `E` - множество от ребра (edges). 

## Видове графи

### Неориентиран граф
Ребрата нямат посока

<img src="https://media.geeksforgeeks.org/wp-content/cdn-uploads/undirectedgraph.png" alt="graph" width="400"/>

### Ориентиран граф
Ребрата имат посока

<img src="https://www.techiedelight.com/wp-content/uploads/Eulerian-path-for-directed-graphs.png" alt="directed-graph" width="400"/>

### Претеглен граф
Ребрата имат тегло/цена/...

<img src="https://www.researchgate.net/profile/Telmo-Peixe/publication/268748127/figure/fig2/AS:295308111171600@1447418348742/The-oriented-graph-of-ch-where-the-label-i-represents-the-edge-g-i.png" alt="weighted-graph" width="400"/>

## Видове представяния
За улеснение ще приемаме, че върховете се представят чрез числа.

<img src="https://i.ibb.co/X2gKpz1/image.png" alt="graph-example" width="400"/>

- чрез матрица на съседство
    - Представяме чрез квадратна матрица `Adj` с размер `n x n`, където `n` е броя на върховете. 
        - За непретеглен граф `Adj[i][j]` = 1, ако има път между `i` и `j`, 0 иначе
        - За претеглен граф `Adj[i][j]` = d, ако има път между `i` и `j` и той е с дължина `d`, 0 иначе
        ```
          1 2 3 4 5 6 
        1 0 1 0 0 0 0
        2 0 0 1 0 0 0
        3 0 0 0 1 0 0
        4 0 0 0 0 1 1
        5 0 0 0 0 0 0
        6 0 1 0 0 1 0
        ```
- чрез списък от съседи
    - Използваме масив от масиви `Arr`. Той има `n` елемента, където `n` е броя на върховете. `Arr[i]` е масив, който държи всички съседни елементи на `i`
        ```
        1 | 2
        2 | 3
        3 | 4
        4 | 5, 6
        5 |
        6 | 2, 5
        ```

## Алгоритми за обхождане на графи
<img src="https://vivadifferences.com/wp-content/uploads/2019/10/DFS-VS-BFS.png" alt="bfs-dfs" width="400"/>

