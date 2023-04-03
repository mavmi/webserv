## WEBSERV

- [Парсер конфигурационного файла](#парсер-конфигурационного-файла)
- [HTTP-заголовки](#http-заголовки)
- [Парсер HTTP запроса](#парсер-http-запроса)
- [Генератор HTTP ответа](#генератор-http-ответа)
- [Утилсы](#утилсы)

***

### Иерархия файлов
<корень проета>\
&emsp;|_ *ConfigFiles/* - Папка с конфигурационными файлами.\
&emsp;&emsp;|_ *invalid/* - Конфиги с ошибками. Сделано в первую очередь для тестов.\
&emsp;&emsp;|_ *valid/* - Валидные конфиги.\
&emsp;&emsp;|_ *How_to.txt* - Файл с общим описанием правил заполнения полей конфиг файла.\
&emsp;|_ *DefaultServer/* - Папка с сервером по умолчанию.\
&emsp;|../includes/* - Папка с хидерами сервера.\
&emsp;|_ *srcs/* - Папка с исходным кодом сервера.\
&emsp;&emsp;|_ *main.cpp* - Мейник проекта.\
&emsp;|_ *test/* - Все про тесты.\
&emsp;&emsp;|../includes/* - Хидеры для тестов.\
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
- *.o* и *.d* файлы помещаются в папку *tmp_files*.

***

## Парсер конфигурационного файла

<details><summary>Info</summary>

### Классы
- *Parser* - оболочка вокруг класса *Configuration* для получения доступа к данным конфигурационного файла.
- *Configuration* - Основной класс парсера. Содержит в себе всю информацию из конфигурационного файла.
- *ServerConfiguration* - Хранит информацию об очередном сервере, которая состоит из конфигов самого сервера и ряда роутов.
- *RouteConfiguration* - Собственно, роут. Их может быть ноль или более в рамках одного сервера.
- *ConfigurationHost* - Хранит информацию о хосте. Имеет метод *toString()*, который возращает строковое представление IP адреса.

### В общем и целом
- Основной точкой входа в содержимое распершенного файла является класс *Parser*. Это - оболочка вокруг класса *Configuration*.
- Все вспомогательные классы (все, кроме класса *Parser*) помещены в namespace *configuration*.
- Если класс имеет геттер для какого-то элемента, то этот метод может выбросить одноименное с этим классом исключение при условии, что предварительно для этого же элемента не был вызван сеттер. Например, класс *ServerConfiguration* имеет метод *getServerName()*, который выкинет исключение, если до этого не был вызван метод *setServerName()*.
- У класса *Parser* есть метод *parseFile()*, который принимает путь к конфигурационному файлу и парсит его. Может выбросить исключение, если файл невалидный, или его не удалось открыть.
- *Parser* имеет перегрузку оператора *->* и метод *getConfiguration()*. Они оба возвращают **константную** ссылку на объект класса *Configuration*.

### Структура конфигурационного файла
// Начало сервера.\
{

&emsp;// Номер порта. Число в диапазоне 0-65535.\
&emsp;port:            80;                 [1]

&emsp;// IP хоста. 4 числа 0-255, разделенных точками.\
&emsp;host:            127.0.0.1;          [1]

&emsp;// Имя хоста.\
&emsp;server_name:     SERVER_NAME;        [0-1]

&emsp;// Массив страниц с информацией об ошибках.\
&emsp;error_pages:     path1,path2;        [1]

&emsp;// Размер тела сообщения. Число > 0. По умолчанию 0.\
&emsp;body_size:       10000000;           [1]

&emsp;// Начало роута.\
&emsp;[
&emsp;&emsp;// Массив методов роута.\
&emsp;&emsp;methods:             GET,POST,DELETE;    [1](GET POST DELETE)

&emsp;&emsp;// HTTP redirection.\
&emsp;&emsp;redir:               path1;              [1]

&emsp;&emsp;// Путь к корневой папке роута.\
&emsp;&emsp;dir:                 path1;              [1]

&emsp;&emsp;// Обрабатываем или нет обращение к дериктории. По умолчанию false.\
&emsp;&emsp;dir_listening:       true/false;         [0-1]

&emsp;&emsp;// Путь к странице-ответу, если запрос был к дериктории.\
&emsp;&emsp;def_if_dir:          path1;              [0-1]

&emsp;&emsp;// Путь к CGI скрипту.\
&emsp;&emsp;cgi_script:          path1;              [0-1]

&emsp;&emsp;// Путь к CGI бинарнику.\
&emsp;&emsp;cgi_bin:             path;               [0-1]

&emsp;&emsp;// Имеет ли возможность роут сохранять загружаемые файлы. По умолчанию false.\
&emsp;&emsp;save_files:          true/false;         [0-1]

&emsp;&emsp;// Путь, куда роут будет сохранять загружаемые файлы.\
&emsp;&emsp;save_to:             path1;              [0-1]

&emsp;// Конец роута.\
&emsp;]

// Конец сервера.\
}

### Правила составления конфигурационного файла
- Обязательные поля **сервера**:
    - port
    - host
    - error_pages
    - body_size
- Обязательные поля **роута**:
    - methods
    - redir
    - dir
- Дополнительные требования к **роуту**:
    - если *dir_listening* == *true*, то должно быть определено значение *def_if_dir*
    - если *save_files* == *true*, то должно быть определено значение *save_to*
    - если определен *cgi_script*, то должен быть определен *cgi_bin*

</details>

****

## HTTP-заголовки

<details><summary>Info</summary>

### Классы
- *HttpGeneralHeaders* - общие заголовки.
- *HttpCommonHeaders* - заголовки, которые есть и в запросе, и в ответе.
- *HttpRequestHeaders* - заголовки запроса.
- *HttpResponseHeaders* - заголовки ответа.
- *HttpRequestStatusLine* - старотовая строка запроса.
- *HttpResponseStatusLine* - стартовая строка ответа.

Все классы имеют сеттеры и геттеры на свои элементы. Геттеры полей, которые не были просетаны, выкидывают одноименное с калссом исключение.
Сеттеры заголовков могут выбросить исключение, если произошла попытка просетать заголовок, который не относится к текущей версии HTTP.

</details>

****

## Парсер HTTP запроса

<details><summary>Info</summary>

### Классы
- *HttpRequest* - класс-оболочка вокруг *HttpRequestParser*. Содержит метод *getHttpRequest* и перегрузку оператора *operator->* для получения константной ссылки на объект *HttpRequestParser*. Метод *parseHttpRequest* и конструктор принимают в качестве аргумента данные из сокета, помещенные в объект *wsrv::utils::BytesContainer*, и парсят их, формируя объект *HttpRequestParser*.
- *HttpRequestParser* - хранилище распаршенных данных из сокета. Содержит поля *wsrv::http_headers::HttpRequestStatusLine*, *wsrv::http_headers::HttpGeneralHeaders* и *wsrv::http_headers::HttpRequestHeaders* и геттеры для них. Контент запроса хранится в поле типа *std::vector<<std::string>>*. Имеет метод *parseHttpRequest* для парсинга данных из сокета, помещенных в объект *wsrv::utils::BytesContainer*.

</details>

****

## Генератор HTTP ответа

<details><summary>Info</summary>

### Классы
- *HttpResponseGenerator*. Содержит поля классов *HttpResponseStatusLine* и *HttpResponseHeaders* для заголовков и *std::vector<<std::string>>* для контента. Все поля имеют геттеры. Имеется метод *toBytes* для перевода содержимого полей в объект класса *wsrv::utils::BytesContainer*.

</details>

****

## Утилсы

<details><summary>Info</summary>

### Классы
- *Wrapper* - Класс-оболочка вокруг полей классов парсера. Хранит в себе содержимое поле и его состояние (определено/не определено).
- *Container* - Собственный простенький контейнер, построенный по аналогии с вектором.
- *Exception* - Базовый класс-исключение.
- *BytesContainer* - Хранилище для данных в виде вектора массивов чаров(байтов).

</details>

****


Links to the examples:
https://github.com/smdyan/webserv
https://github.com/AYoungSn/webServ_42

About http client/server comunication:
https://developer.mozilla.org/ru/docs/Learn/Forms/Sending_and_retrieving_form_data

Delete in php:
https://www.php.net/manual/en/function.delete.php
