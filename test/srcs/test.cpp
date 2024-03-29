#include "../include/test.hpp"

void test::CONFIGURATION_HOST_TESTS(){
    ___HEADER___

    {
        wsrv::configuration::ConfigurationHost host(127, 0, 0, 1);
        assert(host.toString() == "127.0.0.1");
    }
    {
        wsrv::configuration::ConfigurationHost host(192, 168, 0, 123);
        assert(host.toString() == "192.168.0.123");
    }
    {
        wsrv::configuration::ConfigurationHost host(0, 1, 2, 3);
        assert(host.toString() == "0.1.2.3");
    }
    {
        wsrv::configuration::ConfigurationHost host(0, 0, 0, 0);
        assert(host.toString() == "0.0.0.0");
    }
    {
        wsrv::configuration::ConfigurationHost host(255, 255, 255, 255);
        assert(host.toString() == "255.255.255.255");
    }


    {
        std::string str = "0.0.0.0";
        wsrv::configuration::ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "255.255.255.255";
        wsrv::configuration::ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "0.1.2.3";
        wsrv::configuration::ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "127.0.0.1";
        wsrv::configuration::ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "192.168.12.34";
        wsrv::configuration::ConfigurationHost host(str);
        assert(host.toString() == str);
    }   


    {
        std::string str = "127.0.0.1.";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "127.0..0.1";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = ".127.0.0.1";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "a.b.c.d";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "...";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "1.2.3.256";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "1000.1000.1000.1000";
        try{
            wsrv::configuration::ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
}

void test::CONFIGURATION_FILES_TESTS(){
    ___HEADER___

    typedef wsrv::configuration::ServerConfiguration    Server;
    typedef wsrv::configuration::RouteConfiguration     Route;
    typedef std::string                                 ErrorPage;
    typedef int                                         Method;

    // Valid files
    {
        wsrv::Parser parser;
        try {
            parser.parseFile("materials/config_files/valid/1.txt");
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        }
        const wsrv::Configuration& configuration = parser.getConfiguration();

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Server>& servers = configuration.getServers();
        assert(servers.size() == 1);

        const Server& server = servers.back();
        assert(server.getPort() == 800);
        assert(server.getHost().toString() == "127.0.0.1");
        assert(server.getServerName() == "SERVER_NAME");

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ErrorPage>& errorPages = server.getErrorPages();
        assert(errorPages.size() == 2);
        for (MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ErrorPage>::SizeType i = 0; i < errorPages.size(); i++){
            assert(errorPages.at(i) == server.getErrorPage(i));
        }
        assert(errorPages.at(0) == "path1");
        assert(errorPages.at(1) == "path2");
        try{
            errorPages.at(2);
            assert(false);
        } catch (...) {}

        assert(server.getBodySize() == 123456789);
        assert(server.getRoot() == "/path/to/root/folder");

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Route>& routes = server.getRoutes();
        assert(routes.size() == server.getRoutesCount());
        assert(routes.size() == 1);

        const Route& route = routes.back();
        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Method>& methods = route.getMethods();
        assert(methods.size() == route.getMethodsCount());
        assert(methods.size() == 3);

        assert(route.getRedirection() == "path3");
        assert(route.getDirectory() == "path4");
        assert(route.getDirectoryListening() == true && route.getDirectoryListening() != false);
        assert(route.getDefaultIfDirectoryResponse() == "path5");
        assert(route.getCgiScriptPath() == "path6");
        assert(route.getCgiBinPath() == "path7");
    }
    
    {
        wsrv::Parser parser;
        try {
            parser.parseFile("materials/config_files/valid/2.txt");
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        }
        const wsrv::Configuration& configuration = parser.getConfiguration();

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Server>& servers = configuration.getServers();
        assert(servers.size() == 1);

        const Server& server = servers.back();
        assert(server.getPort() == 8080);
        assert(server.getHost().toString() == "127.0.0.1");

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ErrorPage>& errorPages = server.getErrorPages();
        assert(errorPages.size() == server.getErrorPagesCount());
        assert(errorPages.size() == 3);
        assert(errorPages.at(0) == "path1");
        assert(errorPages.at(1) == "path2");
        assert(errorPages.at(2) == "path3");

        assert(server.getBodySize() == 1223334444);

        try{
            server.getServerName();
            assert(false);
        } catch (...) {}

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Route>& routes = server.getRoutes();
        assert(routes.size() == 2);

        // route 1
        {
            const Route& route1 = routes.at(0);
            const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Method>& methods = route1.getMethods();
            assert(methods.size() == 3);
            assert(route1.getRedirection() == "PATH1");
            assert(route1.getDirectory() == "PATH22");
            assert(route1.getDirectoryListening() == false);
            try{
                route1.getDefaultIfDirectoryResponse();
                assert(false);
            } catch (...) {}
            try{
                route1.getCgiScriptPath();
                assert(false);
            } catch (...) {}
            try{
                route1.getCgiBinPath();
                assert(false);
            } catch (...) {}
        }

        // route 2
        {
            const Route& route2 = routes.at(1);
            assert(route2.getMethods().size() == 2);
            assert(route2.getRedirection() == "PATH12341234");
            assert(route2.getDirectory() == "dirrrrr");
            assert(route2.getDirectoryListening());
            assert(route2.getDefaultIfDirectoryResponse() == "PATH333");
            assert(route2.getCgiScriptPath() == "PATH4444");
            assert(route2.getCgiBinPath() == "SOME_CGI_BIN_PATH");
            assert(route2.getSaveFiles() == false);
            try{
                route2.getSaveTo();
                assert(false);
            } catch (...) {}
        }
    }
}

void test::HTTP_REQUEST_FILE_TEST(){
    ___HEADER___
    const int bufferSize = 2;

    // read http request file without content
    {
        wsrv::utils::BytesContainer content;

        int fileFd = open("test/httpRequest_noContent.txt", O_RDONLY);
        if (fileFd == -1){
            std::cerr << "Cannot open file" << std::endl;
            exit(1);
        }

        srand(time(NULL));
        int lastReturn = 1, curReturn;
        while(true){
            // const int bufferSize = rand() % 400 + 1;
            char* buffer = new char[bufferSize];
            size_t readCount = static_cast<size_t>(read(fileFd, buffer, bufferSize));
            if (readCount <= 0) break;
            curReturn = content.pushBack(buffer, readCount);
            assert(lastReturn == 1);
            lastReturn = curReturn;
            if (!lastReturn) break;
        }
        assert(lastReturn == 0);

        std::cout << test_utils::getColor(test_utils::CYAN) << "\n\tHTTP request file content:" << std::endl;
        std::cout << "\t==========================" << std::endl;
        const std::vector<std::string>& strings = content.getLines();
        for (size_t i = 0; i < strings.size(); i++){
            const std::string& line = strings.at(i);
            for (size_t i = 0; i < line.size(); i++){
                std::cout << line.at(i);
            }
            std::cout << '|' << std::endl;
        }
        std::cout << "\n\t==========================\n" << test_utils::getColor(test_utils::DEFAULT) << std::endl;
    
        try{
            wsrv::http_request::HttpRequestParser httpRequestParser;
            const wsrv::http_request::HttpRequest& httpRequest = httpRequestParser.parseHttpRequest(content);

            const wsrv::http_headers::HttpRequestStatusLine& statusLine = httpRequest.getStatusLine();
            assert(statusLine.getHttpVersion() == wsrv::utils::HTTP_1_1);
            assert(statusLine.getMethod() == wsrv::utils::POST);
            assert(statusLine.getUrl() == "/cgi-bin/process.cgi");
            const wsrv::http_headers::HttpGeneralHeaders& generalHeaders = httpRequest.getGeneralHeaders();
            assert(generalHeaders.getConnection() == " Keep-Alive");

            const wsrv::http_headers::HttpRequestHeaders& requestHeaders = httpRequest.getRequestHeaders();
            assert(requestHeaders.getHost() == " www.tutorialspoint.com");
            assert(requestHeaders.getContentType() == " text/xml; charset=utf-8");
            assert(requestHeaders.getAcceptLanguage() == " en-us");
            assert(requestHeaders.getAcceptEncoding() == " gzip, deflate");

            const std::vector<std::string>& httpRequestContent = httpRequest.getRequestContent();
            assert(httpRequestContent.size() == 0);
        } catch (wsrv::utils::Exception& e){
            std::cout << e.what() << std::endl;
            assert(false);
        }
    }
    

    // read http request file with content
    {
        wsrv::utils::BytesContainer content;

        int fileFd = open("test/httpRequest.txt", O_RDONLY);
        if (fileFd == -1){
            std::cerr << "Cannot open file" << std::endl;
            exit(1);
        }

        srand(time(NULL));
        int lastReturn = 1, curReturn;
        while(true){
            // const int bufferSize = rand() % 400 + 1;
            char* buffer = new char[bufferSize];
            size_t readCount = static_cast<size_t>(read(fileFd, buffer, bufferSize));
            if (readCount <= 0) break;
            curReturn = content.pushBack(buffer, readCount);
            assert(lastReturn == 1);
            lastReturn = curReturn;
            if (!lastReturn) break;
        }
        assert(lastReturn == 0);

        std::cout << test_utils::getColor(test_utils::CYAN) << "\n\tHTTP request file content:" << std::endl;
        std::cout << "\t==========================" << std::endl;
        const std::vector<std::string>& strings = content.getLines();
        for (size_t i = 0; i < strings.size(); i++){
            const std::string& line = strings.at(i);
            for (size_t i = 0; i < line.size(); i++){
                std::cout << line.at(i);
            }
            std::cout << '|' << std::endl;
        }
        std::cout << "\n\t==========================\n" << test_utils::getColor(test_utils::DEFAULT) << std::endl;
    
        try{
            wsrv::http_request::HttpRequestParser httpRequestParser;
            const wsrv::http_request::HttpRequest& httpRequest = httpRequestParser.parseHttpRequest(content);

            const wsrv::http_headers::HttpRequestStatusLine& statusLine = httpRequest.getStatusLine();
            assert(statusLine.getHttpVersion() == wsrv::utils::HTTP_1_1);
            assert(statusLine.getMethod() == wsrv::utils::POST);
            assert(statusLine.getUrl() == "/cgi-bin/process.cgi");
            const wsrv::http_headers::HttpGeneralHeaders& generalHeaders = httpRequest.getGeneralHeaders();
            assert(generalHeaders.getConnection() == " Keep-Alive");

            const wsrv::http_headers::HttpRequestHeaders& requestHeaders = httpRequest.getRequestHeaders();
            assert(requestHeaders.getHost() == " www.tutorialspoint.com");
            assert(requestHeaders.getContentType() == " text/xml; charset=utf-8");
            assert(requestHeaders.getContentLength() == " 93");
            assert(requestHeaders.getAcceptLanguage() == " en-us");
            assert(requestHeaders.getAcceptEncoding() == " gzip, deflate");

            const std::vector<std::string>& httpRequestContent = httpRequest.getRequestContent();
            assert(httpRequestContent.size() == 2);
            assert(httpRequestContent[0] == "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
            assert(httpRequestContent[1] == "<string xmlns=\"http://clearforest.com/\">string</string>");
        } catch (wsrv::utils::Exception& e){
            std::cout << e.what() << std::endl;
            assert(false);
        }
    }
}

void test::ARRAY_CONTAINER_TEST(){
    ___HEADER___

    {
        std::string str = "ekrjghw549ghiujfLjfoijw4tojh5gouihpof34";
        wsrv::utils::ArrayContainer arrayContainer = wsrv::utils::ArrayContainer::fromString(str);
        
        assert(str.size() == arrayContainer.getSize());
        for (size_t i = 0; i < str.size(); i++){
            assert(arrayContainer.getData()[i] == str[i]);
        }
    }

    {
        for (int num = 0; num < 5000; num++){
            std::string str = wsrv::utils::utilsNumToString(num);
            wsrv::utils::ArrayContainer arrayContainer = wsrv::utils::ArrayContainer::fromNum(num);
            
            assert(str.size() == arrayContainer.getSize());
            for (size_t i = 0; i < str.size(); i++){
                assert(arrayContainer.getData()[i] == str[i]);
            }
        }
    }

    {
        const std::string ip = "192.168.0.1";
        wsrv::configuration::ConfigurationHost host(ip);
        wsrv::utils::ArrayContainer array = host.toCharArray();

        assert(array.getSize() == ip.size());
        for (size_t i = 0; i < ip.size(); i++){
            assert(array.getData()[i] == ip[i]);
        }
    }

    {
        const uint16_t portNum = 65000;
        const std::string portStr = "65000";
        wsrv::configuration::ConfigurationPort port(portNum);
        wsrv::utils::ArrayContainer array = port.toCharArray();

        assert(array.getSize() == portStr.size());
        for (size_t i = 0; i < portStr.size(); i++){
            assert(array.getData()[i] == portStr[i]);
        }
    }
}

void RUN_ALL_TESTS(){
    test::ARRAY_CONTAINER_TEST();
    test::CONFIGURATION_HOST_TESTS();
    test::CONFIGURATION_FILES_TESTS();
    test::HTTP_REQUEST_FILE_TEST();
}
