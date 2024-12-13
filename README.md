# Строковый калькулятор на языке C++
## Требования
По запросу с клавиатуры в консольном приложении вводится строка, которая может содержать: знаки операций `+`, `-`, `*`, `/`; константы (целые или вещественные). Строка задает некоторое правильное математическое выражение (формулу в инфиксной форме), программа вычисляет значение, выдает результат.

В формуле дополнительно использовать скобки `()` для задания приоритета операций, имена функций `sin`, `cos`, `tg`, `ctg`, `exp`, переменную `x`, а также проверку правильности введенного выражения, в случае ошибок ввода выдавать сообщения об ошибках.
## Принцип работы программы
### Ввод выражения и его проверка
На вход подается строка, которая проверяется на предмет:
+ Наличия неизвестных символов;
+ Корректности ввода чисел (количество разделителей `.`; `,`) и наличия допустимых символов после чисел (после числа должен быть знак операции (за исключением `(`));
+ Корректности ввода тригонометрических функций и экспонеты (они не могут быть последними в выражении и после них должен быть символ `(` или число);
+ Корректности ввода знаков операций `+`, `-`, `*`, `/` (после них не должно быть символов `+`, `-`, `*`, `/`, `)`);
+ Корректности ввода знаков операций `(`, `)` (их должно быть равное количество в выражении; символ `(` не может быть последним в выражении; количество символов `)` всегда должно быть не больше чем количество символов `(`; после символа `(` не может быть знаков `+`, `*`, `/`, `)`; после символа `)` могут быть только знаки операций `+`, `-`, `*`, `/`, `)`);
### Обработка выражения
+ Программа разбивает строку на массив из строк, в котором каждый элемент является операндом или оператором;
+ Далее реализуется основной алгоритм работы калькулятора:
  + Идем слева направо по массиву в поиске закрывающей скобки;
  + При нахождении закрывающей скобки (пусть на месте `k2`) начинаем идти в обратную сторону и ищем открывающую;
  + При нахождении открывающей скобки (пусть на месте `k1`) мы получаем отрезок выражения (с `k1` по `k2`), свободный от скобочек, который можем легко упростить и удалить найденную пару скобок;
+ Данный алгоритм повторяется пока в выражении есть скобки. В итоге мы получим выражение без скобочек, упростив которое, получим ответ.
### Советы по использованию
+ Калькулятор поддерживает в виде разделителей чисел как `.`, так и `,`;
+ Выражение можно вводить с пробелами, программа их удалит;
+ Параметры тригонометрических функций задаются в радианах;
+ Если параметр тригонометрической функции или экспоненты это одно число (а не выражение), то допустимо писать число без скобочек, например, `cos2` или `exp5`, но если параметр отрицателен, то придется его обособить скобками (`cos(-2)` и `exp(-5)`);

Контрольные расчеты находятся в файле `tests.txt`.
