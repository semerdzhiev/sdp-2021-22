# Хеширане. Хеш-таблици

## Хеширане
Хеширането е преобразуване на данни с произволна големина до данни с фиксирана големина, което се случва посредством хеш-функция. Входните данни се наричат ключове, а изходните - хешове.
<img src="https://cryptobook.nakov.com/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-LhlOQMrG9bRiqWpegM0%2Fuploads%2Fgit-blob-117671d5576ceee0211790605de60e2c17219521%2Fcrypto-hash-function.jpg?alt=media" alt="hash-function" width="400"/>

### Колизии и справяне с тях
Тъй като ограниченито до фиксиран размер на хешовете предполага, че възможните стойности на ключовете са повече от възможните стойности на хешовете, то следва, че е възможно два различни ключа да имат еднакъв хеш. Тези ситуации се наричат колизии. 
Най-хубавия начин да намалим с колизиите е да ползваме "по-добра" (откъм наличие на колизии) хешираща функция. Но дори и те да станат по-голяма рядкост, няма как да ги избегнем напълно, затова трябва да намерим друч начин да се справим с тях.

Нека разгледаме следната хешираща функция: `hash(key) = key % 7`

#### Separate chaining
<img src="https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/07/hashChaining1.png" alt="separate-chaining" width="400"/>

#### Linear probing
<img src="https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/08/openAddressing1.png" alt="linear-probing" width="400"/>

## STL (since C++11)
- `unordered_map` - пази двойки ключ-стойност, неповтарящи се ключове, ключовете се хешират
- `unordered_set` - пази неповтарящи се ключове, ключовете се хешират
- `unordered_multiset` - пази ключове, ключовете се хешират 
- `unordered_multimap` - пази двойки ключ-стойност, ключовете се хешират

## std::hash