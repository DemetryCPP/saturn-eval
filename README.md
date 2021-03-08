Вычесление математического выражения.

Имеется всего 5 операторов: 
- сложение "+"
- вычитание "-"
- умножение "*"
- деление "/"
- деление по модулю "%"
- деление нацело "\\"
- возведение в степень "^"

Скобочные группы: "( expression )".
Вещественные числа: "1.2".
Константы: число эйлера ("e") и число пи ("pi").
Возможность задавать свои переменные через флаг -d: "-dvarname=value"

# Лексер
Присваивает каждому символу в выражении токен (тип), и получается лексема. Используется 4 токена:

- Число (0-9);
- Десятичный Разделитель '.';
- Оператор '+', '-', '*', '/';
- Скобка '(', ')';

После лексинга, парсер работает с массивом лексем.

# Парсер
В начале ищется позиция для деления, это позиция какого то оператора в выражении. Ищется он следующим образом: выбирается оператор, с самым низким приоритетом, который ближе к началу, операторы в скобках игнорируются.

Если позиция не была найдена (т.е. равна -1), возможно, выражение заключено в скобки, и скобки убираются из выражения.
Иначе, если выражение не заключено в скобки, "ветка" превращется в "лист", т.е. ветка не имеет развлетвлений.
Дальше происходит инициализация производных веток.

# Получение конечного значение
В конце концов из дерева получается конечное значение. Простой обход дерева.

# Описание файлов
все функции находятся в хедерах.

- lexer/check_valid.h - проверка массива лексем на неправильную последовательность лексем, например "1++" (2 оператора подряд), "2(" (скобка после числа) и т.д.
- lexer/lexer.h - лексер, и функция логирования лексемы (не используется, но раскоментировав можно увидеть логи).
- lexer/data.h - структура лексемы.

- parser/parser.h - парсер.
- parser/free_tree.h - функция очистки памяти, занятой ветками дерева парсинга.
- parser/find_divider_pos.h - функция поиска позиции оператора, по которому будет делится выражение.
- parser/data.h - структура ветки.

- mini.h - функция, выполняющая действие оператора для 2х операндов.
- solve.h - функция обхода дерева, получающая результат.