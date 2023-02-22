#include "../../includes/configurations/configuration.hpp"

namespace MAIN_NAMESPACE{
ConfigurationException::ConfigurationException(const char* msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const std::string& msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ConfigurationException::output_() const {
    return "CONFIGURATION_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE{
Configuration::Configuration(){
    servers_ = ServersContainerType();
    hostPortPairs_ = HostPortPairsContainerType();
}
Configuration::Configuration(const Configuration& other){
    copyData_(other);
}
Configuration::~Configuration(){
    deleteData_();
}

Configuration& Configuration::operator=(const Configuration& other){
    deleteData_();
    copyData_(other);
    return *this;
}

Configuration::ServersContainerType::SizeType Configuration::getServersCount() const {
    return servers_.size();
}

Configuration::ServersContainerType& Configuration::getServers(){
    return servers_;
}
const Configuration::ServersContainerType& Configuration::getServers() const{
    return servers_;
}

Configuration::HostPortPairsContainerType& Configuration::getHostPortPairs(){
    return hostPortPairs_;
}
const Configuration::HostPortPairsContainerType& Configuration::getHostPortPairs() const{
    return hostPortPairs_;
}

const Configuration::ServerType& Configuration::getServer(ServerType::PortType port) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getPort() == port) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port", EXC_ARGS);
}
const Configuration::ServerType& Configuration::getServer(const ServerType::HostType& host) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getHost() == host) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port", EXC_ARGS);
}
const Configuration::ServerType& Configuration::getServer(ServerType::PortType port, const ServerType::HostType& host) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getPort() == port && server.getHost() == host) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port and host", EXC_ARGS);
}

void Configuration::copyData_(const Configuration& other){
    servers_ = other.servers_;
    hostPortPairs_ = other.hostPortPairs_;
}
void Configuration::deleteData_(){
    servers_ = ServersContainerType();
    hostPortPairs_ = HostPortPairsContainerType();
}
}
