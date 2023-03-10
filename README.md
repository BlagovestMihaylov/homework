подробно описание ще има [тук](https://github.com/BlagovestMihaylov/homework)

# homework

## “Големите числа”

са цели положителни числа, представени, без практическо ограничение за тяхната големина (освен наличната памет). Може да
се приеме, че поддържаните големи числа не могат да имат повече от 255 цифри (в съответната бройна система).

Да се реализира програма, която позволява:
въвеждане от стандартния вход на число с практически произволен брой цифри в:

#### десетична бройна система

#### шеснайсетична бройна система

#### извеждане на екрана на голямо число в:

#### десетична бройна система

#### шеснайсетична бройна система

#### събиране на две големи числа

#### изваждане на две големи числа

#### умножение на две големи числа

#### целочислено деление на две големи числа с намиране на частно и остатък

#### намиране на целочислен корен квадратен от голямо число

(можете да използвате някой от [тези методи](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots))

Програмата да поддържа текстов диалогов режим, позволяващ удобен интерактивен избор на горните операции.
Въпросните операции да са реализирани в програмата чрез ясно обособени класове и методи. Употребата на входно / изходни
операции в тялото на методите е забранена (освен при функциите за вход и изход). Т.е. функциите реализират математически
изображения, например BigNumber BigNumber::operator+ (const BugNumber& a. Да се реализират подходящи оператори за работа
с числа, включително за вход и изход в поток.

### Примери (за тестване):

"5" * "5" = "25"

"4321" - "1234" = "3087"

"1234" * "4321" = "5332114"

"12456789031415" + "98765432123456789" = "98777888912488204"

"12456789031415" * "98765432123456789" = "1230300151558439221348916026435"

"1230300151558439221348916026435" / "98765432123456789" = "12456789031415"

sqrt ("12456789031415" )=”3529417”  (всъщност точната стойност е 3529417.6617985, но работим с цели числа)

### Бонуси:

да се премахне ограничението за 255 цифри

чрез големите числа да се реализират рационални числа с голяма точност

