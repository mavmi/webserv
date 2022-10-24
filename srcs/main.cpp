#include "../include/utils.hpp"
#include "../include/configuration.hpp"

#include <algorithm>
#include <iterator>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

void TEST_CONFIGURATION_HOST(){
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

int main(int argc, char** argv){
    (void)argc; (void)argv;

    TEST_CONFIGURATION_HOST();
}
