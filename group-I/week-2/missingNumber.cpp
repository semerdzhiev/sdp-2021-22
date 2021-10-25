#include <iostream>

using namespace std;

int findMissing(int arr[], int size) {
    for (int seekedNumber = 1; seekedNumber < size + 1; ++seekedNumber) {
        bool foundNumber = false;
        for (int currIndex = 0; currIndex < size; ++currIndex) {
            if (arr[currIndex] == seekedNumber) {
                foundNumber = true;
                break;
            }
        }
        if (!foundNumber) {
            return seekedNumber;
        }
    }
}

// O(n^2)
//
//Тоест за всяко число търси линейно?
//Има ли по-ефективен начин

// O(n)
//Сортираме и гледаме къде число се разминава 
//с индекса си чрез binary search?
//Ами ако записваме в булев масив всяко срещнато число и накрая намерим къде е липсващото няма ли да имаме 1 обхождане и после още част от обхождане?
//По тази логика можем да използваме число с маска и да слагаме 1 на съответната позиция - пестим памет
//това с числото май няма да стане
//колко голямо трябва да е това число наистина?
//binary search и чиста работа (Армянов хареса това 😄)

// O(n), O(1)
//Има едно мъничко решение на 1ва зад, което е без сортиране и търсене
//Предполагам това търсехте като решение миналия път
//За липсващото число от 1 до 100
//int array[] = {2, 4, 6, 8, 10, 1, 3, /*5,*/ 7, 9};
//int n = sizeof(array) / sizeof(array[0]);
//int sum = ((n + 1) * (n + 2)) / 2;
//for (int i = 0; i < n; ++i)
//    sum -= array[i];
//std::cout << sum;

// O(nlogn)
//^^ binary search ако не знаем кой индекс търсим 
//няма ли да е неефективно?
//Разминава се с 1 стойността
//Можем да използваме защото на i-ти индекс стои i+1
//std::sort (Армянов НЕ хареса това 🙄)

int main() {
    int n;
    int arr[10000];

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << findMissing(arr, n) << endl;

    return 0;
}

