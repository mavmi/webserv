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

    typedef wsrv::configuration::Configuration::ServerType                                    Server;
    typedef wsrv::configuration::Configuration::ServerType::RouteType                         Route;
    typedef wsrv::configuration::Configuration::ServerType::ErrorPageType                     ErrorPage;
    typedef wsrv::configuration::Configuration::ServerType::RouteType::MethodType             Method;

    // Valid files
    {
        wsrv::Parser parser;
        try {
            parser = wsrv::Parser::parseFile("ConfigFiles/valid/1.txt");
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        }
        const wsrv::configuration::Configuration& configuration = parser.getConfiguration();

        const MAIN_NAMESPACE::UTILS_NAMESPACE::Container<Server>& servers = configuration.getServers();
        assert(servers.size() == 1);

        const Server& server = servers.back();
        assert(server.getPort() == 80);
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
            parser = wsrv::Parser::parseFile("ConfigFiles/valid/2.txt");
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        }
        const wsrv::configuration::Configuration& configuration = parser.getConfiguration();

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

    /*{
        wsrv::Parser parser;
        try {
            parser = wsrv::Parser::parseFile("ConfigFiles/valid/3.txt");
        } catch (wsrv::configuration::Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        }
        const wsrv::configuration::Configuration& configuration = parser.getConfiguration();
        
        const wsrv::configuration::Container<Server>& servers = configuration.getServers();
        assert(servers.size() == 3);

        // server 1 
        {
            const Server& server1 = servers.front();
            assert(server1.getPort() == 1111);
            assert(server1.getHost().toString() == "192.168.10.1");
            assert(server1.getServerName() == "SERVER_NAME");

            const wsrv::configuration::Container<ErrorPage>& errorPages = server1.getErrorPages();
            assert(errorPages.size() == server1.getErrorPagesCount());
            assert(errorPages.size() == 3);
            assert(errorPages.at(0) == "path1");
            assert(errorPages.at(1) == "path2");
            assert(errorPages.at(2) == "path3");

            assert(server1.getBodySize() == 1223334444);

            const wsrv::configuration::Container<Route>& routes = server1.getRoutes();
            assert(routes.size() == 3);
        
            // route 1
            {
                const Route& route1 = routes.at(0);
                const wsrv::configuration::Container<Method>& methods = route1.getMethods();
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
                try{
                    route2.getMethods();
                    assert(false);
                } catch (...) {}
                try{
                    route2.getRedirection();
                    assert(false);
                } catch (...) {}
                try{
                    route2.getDirectory();
                    assert(false);
                } catch (...) {}
                assert(route2.getDirectoryListening() == true);
                assert(route2.getDefaultIfDirectoryResponse() == "PATH333");
                assert(route2.getCgiScriptPath() == "PATH4444");
                try{
                    route2.getCgiBinPath();
                    assert(false);
                } catch (...) {}
            }

            // route 3
            {
                const Route& route3 = routes.at(2);
                try{
                    route3.getMethods();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getRedirection();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getDirectory();
                    assert(false);
                } catch (...) {}
                assert(route3.getDirectoryListening() == false);
                try{
                    route3.getDefaultIfDirectoryResponse();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getCgiScriptPath();
                    assert(false);
                } catch (...) {}
                assert(route3.getCgiBinPath() == "PATH55555");
            }
        }

        // server 2
        {
            const Server& server2 = servers.at(1);
            assert(server2.getPort() == 80);
            assert(server2.getHost().toString() == "127.0.0.1");
            assert(server2.getServerName() == "SERVER_NAME");

            wsrv::configuration::Container<ErrorPage> errorPages = server2.getErrorPages();
            assert(errorPages.size() == server2.getErrorPagesCount());
            assert(errorPages.size() == 3);
            assert(errorPages.at(0) == "path1");
            assert(errorPages.at(1) == "path2");
            assert(errorPages.at(2) == "path3");

            assert(server2.getBodySize() == 1223335444);

            const wsrv::configuration::Container<Route>& routes = server2.getRoutes();
            assert(routes.size() == 3);
        
            // route 1
            {
                const Route& route1 = routes.at(0);
                const wsrv::configuration::Container<Method>& methods = route1.getMethods();
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
                try{
                    route2.getMethods();
                    assert(false);
                } catch (...) {}
                try{
                    route2.getRedirection();
                    assert(false);
                } catch (...) {}
                try{
                    route2.getDirectory();
                    assert(false);
                } catch (...) {}
                assert(route2.getDirectoryListening() == true);
                assert(route2.getDefaultIfDirectoryResponse() == "PATH333");
                assert(route2.getCgiScriptPath() == "PATH4444");
                try{
                    route2.getCgiBinPath();
                    assert(false);
                } catch (...) {}
            }

            // route 3
            {
                const Route& route3 = routes.at(2);
                try{
                    route3.getMethods();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getRedirection();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getDirectory();
                    assert(false);
                } catch (...) {}
                assert(route3.getDirectoryListening() == false);
                try{
                    route3.getDefaultIfDirectoryResponse();
                    assert(false);
                } catch (...) {}
                try{
                    route3.getCgiScriptPath();
                    assert(false);
                } catch (...) {}
                assert(route3.getCgiBinPath() == "PATH55555");
                assert(route3.getSaveFiles());
                assert(route3.getSaveTo() == "PATH11111");
            }
        }
    
        // server 3
        {
            const Server& server3 = servers.at(2);

            try{
                server3.getPort();
                assert(false);
            } catch (...) {}
            try{
                server3.getHost();
                assert(false);
            } catch (...) {}
            try{
                server3.getServerName();
                assert(false);
            } catch (...) {}
            try{
                server3.getErrorPages();
                assert(false);
            } catch (...) {}
            assert(server3.getBodySize() == 0);
            try{
                server3.getRoutes();
                assert(false);
            } catch (...) {}
        }
    }*/
}

void test::HTTP_REQUEST_FILE_TEST(){
    ___HEADER___

    wsrv::utils::BytesContainer content;
    
    // read http request file
    {

        int fileFd = open("/home/username/Desktop/webserv/test/httpRequest.txt", O_RDONLY);
        if (fileFd == -1){
            std::cerr << "Cannot open file" << std::endl;
            exit(1);
        }

        while(true){
            char* buffer = new char [content.bufferSize];
            size_t readCount = static_cast<size_t>(read(fileFd, buffer, content.bufferSize));
            content.bytesContainer.push_back(buffer);
            if (readCount < content.bufferSize){
                content.lastSize = readCount;
                break;
            }
        }

        std::cout << test_utils::getColor(test_utils::CYAN) << "\n\tHTTP request file content:" << std::endl;
        std::cout << "\t==========================" << std::endl;
        for (size_t i = 0; i < content.bytesContainer.size(); i++){
            for (size_t j = 0; j < (i + 1 == content.bytesContainer.size() ? content.lastSize : content.bufferSize); j++){
                std::cout << content.bytesContainer[i][j];
            }
        }
        std::cout << "\n\t==========================\n" << test_utils::getColor(test_utils::DEFAULT) << std::endl;
    }

    try{
        wsrv::HttpRequest httpRequest = wsrv::HttpRequest::parseHttpRequest(content);

        const wsrv::http_headers::HttpRequestStatusLine& statusLine = httpRequest.getHttpRequest().getStatusLine();
        assert(statusLine.getHttpVersion() == wsrv::utils::HTTP_1_1);
        assert(statusLine.getMethod() == wsrv::utils::POST);
        assert(statusLine.getUrl() == "/cgi-bin/process.cgi");

        const wsrv::http_headers::HttpGeneralHeaders& generalHeaders = httpRequest.getHttpRequest().getGeneralHeaders();
        assert(generalHeaders.getConnection() == " Keep-Alive");
        
        const wsrv::http_headers::HttpRequestHeaders& requestHeaders = httpRequest.getHttpRequest().getRequestHeaders();
        assert(requestHeaders.getHost() == " www.tutorialspoint.com");
        assert(requestHeaders.getContentType() == " text/xml; charset=utf-8");
        assert(requestHeaders.getContentLength() == " length");
        assert(requestHeaders.getAcceptLanguage() == " en-us");
        assert(requestHeaders.getAcceptEncoding() == " gzip, deflate");

        const std::vector<std::string>& httpRequestContent = httpRequest.getHttpRequest().getRequestContent();
        assert(httpRequestContent.size() == 2);
        assert(httpRequestContent[0] == "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        assert(httpRequestContent[1] == "<string xmlns=\"http://clearforest.com/\">string</string>");
    } catch (wsrv::utils::Exception& e){
        std::cout << e.what() << std::endl;
        assert(false);
    }
}

void RUN_ALL_TESTS(){
    test::CONFIGURATION_HOST_TESTS();
    test::CONFIGURATION_FILES_TESTS();
    test::HTTP_REQUEST_FILE_TEST();
}
