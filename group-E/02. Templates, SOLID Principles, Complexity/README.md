# Шаблони, SOLID принципи, Сложност

[Задача за Optional](https://github.com/semerdzhiev/sdp-2021-22/blob/main/group-E/02.%20Templates%2C%20SOLID%20Principles%2C%20Complexity/task.md)

[Запис](https://drive.google.com/file/d/1Z4MAfQUgWzEiPJy0AArdc36TUfM_lA_N/view?usp=sharing)
## Шаблони
- Generic programming - защо?
- Шаблони в C++
    - функции
    - класове
    - как компилатора на C++ работи с шаблони
    - `using` vs. `typedef`
     
[Templates and generic programming](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#t-templates-and-generic-programming)
## SOLID принципи
**S**ingle Responsibility Principle

**O**pen-closed Principle

**L**ishkov Substitution Principle

**I**nterface Segregation Principle

**D**ependency Inversion Principle
## Сложност. Нотация big-O. Времена и пространствена сложност
`O(f) = { g | g ≼ f }`

`g ≼ f` означава, че `g` расте *не по-бързо* от `f`.
Тоест, `O(f)` е множеството от всички функции, които растат не по-бързо от `f`.

Да пишем `g=O(f)` означава същото като `g∈O(f)` и казваме, че `f` е асимптотична горна граница за `g`.

[Big-O Cheat Sheet](https://www.bigocheatsheet.com/)

Има и други нотации - Θ (Big-Theta), Ω (Big Omega), o (Small Oh), ω (Small Omega). Нас най-често ни интересува O нотацията обаче, защото ако `g=O(f)`, то `f` в някакъв смисъл е възможно най-лошото (по големина) **приближение** до `g`.

```c++
int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
```
Bonus: Какъв е проблема в този код?
