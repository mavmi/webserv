#include "../include/test.hpp"

void test::CONFIGURATION_HOST_TESTS(){
    ___HEADER___

    {
        ConfigurationHost host(127, 0, 0, 1);
        assert(host.toString() == "127.0.0.1");
    }
    {
        ConfigurationHost host(192, 168, 0, 123);
        assert(host.toString() == "192.168.0.123");
    }
    {
        ConfigurationHost host(0, 1, 2, 3);
        assert(host.toString() == "0.1.2.3");
    }
    {
        ConfigurationHost host(0, 0, 0, 0);
        assert(host.toString() == "0.0.0.0");
    }
    {
        ConfigurationHost host(255, 255, 255, 255);
        assert(host.toString() == "255.255.255.255");
    }


    {
        std::string str = "0.0.0.0";
        ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "255.255.255.255";
        ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "0.1.2.3";
        ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "127.0.0.1";
        ConfigurationHost host(str);
        assert(host.toString() == str);
    }
    {
        std::string str = "192.168.12.34";
        ConfigurationHost host(str);
        assert(host.toString() == str);
    }   


    {
        std::string str = "127.0.0.1.";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "127.0..0.1";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = ".127.0.0.1";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "a.b.c.d";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "...";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "1.2.3.256";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
    {
        std::string str = "1000.1000.1000.1000";
        try{
            ConfigurationHost host(str);
            assert(false);
        } catch (...) {}
    }
}

void test::FILES_TESTS(){
    ___HEADER___

    // Valid files
    {
        try {
            Configuration configuration;
            configuration.parseFile("ConfigFiles/valid/1.txt");
        } catch (Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        } 

        // to do asserts
    }
    {
        try {
            Configuration configuration;
            configuration.parseFile("ConfigFiles/valid/2.txt");
        } catch (Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        } 

        // to do asserts
    }
    {
        try {
            Configuration configuration;
            configuration.parseFile("ConfigFiles/valid/3.txt");
        } catch (Exception& e){
            std::cerr << e.what() << std::endl;
            assert(false);
        } 

        // to do asserts
    }
}

void RUN_ALL_TESTS(){
    test::CONFIGURATION_HOST_TESTS();
    test::FILES_TESTS();
}
