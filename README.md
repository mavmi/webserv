## WEBSERV PARSER
***

### Иерархия файлов
<корень проета>\
&emsp;|_ *ConfigFiles/* - Папка с конфигурационными файлами.\
&emsp;&emsp;|_ *invalid/* - Конфиги с ошибками. Сделано в первую очередь для тестов.\
&emsp;&emsp;|_ *valid/* - Валидные конфиги.\
&emsp;&emsp;|_ *How_to.txt* - Файл с общим описанием правил заполнения полей конфиг файла.\
&emsp;|_ *include/* - Папка с хидерами сервера.\
&emsp;|_ *srcs/* - Папка с исходным кодом сервера.\
&emsp;&emsp;|_ *main.cpp* - Мейник проекта.\
&emsp;|_ *test/* - Все про тесты.\
&emsp;&emsp;|_ *include/* - Хидеры для тестов.\
&emsp;&emsp;|_ *srcs/* - Исходный код для тестов.\
&emsp;&emsp;&emsp;|_ *main.cpp* - Мейник для тестов. Для него в мейке билдится отдельный испольняемый файл (*webserv_test* на текущий момент).\
&emsp;|_ *.gitignore*\
&emsp;|_ *Makefile*\
&emsp;|_ *README.MD*

### Makefile
- Содержит все требуемые правила: all, $(NAME), clean, fclean, re.
- При сборке создает *.d файлы. При пересборке компилит заново только изменные с момента последней сборки файлы.
- У него есть правило *test*, которое создает исполняемый файл *webserv_test*. Он прогоняет только тесты.
- В тестах испольуется *assert*. Поэтому если тест закончится с ошибкой, то информация о ней появится в терминале.

### Классы
- *Configuration* - Основной класс парсера. Содержит в себе всю информацию из конфигурационного файла.
- *ServerConfiguration* - Хранит информацию об очередном сервере, которая состоит из конфигов самого сервера и ряда роутов.
- *RouteConfiguration* - Собственно, роут. Их может быть ноль или более в рамках одного сервера.
- *ConfigurationHost* - Хранит информацию о хосте. Имеет метод *toString()*, который возращает строковое представление IP адреса.
- *Container* - Оболочка вокруг вектора (на текущий момент). Был сделан на случай, если классом-хранилищем в рамках парсера будет выбрано что-то иное, кроме вектора.
- *Exception* - Базовый класс-исключение для парсера. Его объект или любой его наследник могут быть пойманы через ***catch (Exception&)***. Все его наследники названы в честь одноименных классов парсера:
    - *ConfigurationHostException*
    - *ConfigurationException*
    - *ServerException*
    - *RouteException*

### В общем и целом
- Основным классом, который хранит в себе все, что есть в конфигурационном файле, является класс *Configuration*.
- Все классы парсера помещены в namespace *configuration*.
- Если класс имеет геттер для какого-то элемента, то этот метод может выбросить одноименное с этим классом исключение при условии, что предварительно для этого же элемента не был вызван сеттер. Например, класс *ServerConfiguration* имеет метод *getServerName()*, который выкинет исключение, если до этого не был вызван метод *setServerName()*.
- У класса *Configuration* есть метод *parseFile()*, который принимает путь к конфигурационному файлу и парсит его. Может выбросить исключение, если файл невалидный, или его не удалось открыть.

### Что осталось сделать
- ~~unsigned char -> uint8_t~~
- Определить обязательные и необязательные параметры в конфигурационном файле.
- Значения по умолчанию для необязательных полей.
- Валидаторы для сервера и роута.
- Код ошибки для исключения.
- Генератор html страницы по коду и сообщению исключения.
- ~~Исключение на конструктор хоста с числами.~~
- Геттер сервера по хосту и/или порту.
- DNS.
- ~~Регистр тайпдефов.~~
- Возможность роута сохранять файлы + путь для сохранения.
- ~~Исключения для сеттеров объектов в статусе done.~~
- ~~Typedef для исключений.~~
- Константные ссылки для геттеров.
