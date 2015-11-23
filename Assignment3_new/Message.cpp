#include "Message.hpp"
#include <vector>
#include <string>

std::string Message::getHTTPVersion() const {
    return _httpVersion;
}

std::vector<Header> Message::getHeaders() const {
    std::vector<Header> headers;
    for (auto it = _headers.begin(); it != _headers.end(); ++it) {
        headers.push_back(Header(it->first, it->second));
    }
    return headers;
}

std::string Message::getContent() const {
    return _content;
}


MessageBuilder& MessageBuilder::setHTTPVersion(const std::string httpVersion) {
    _httpVersion = httpVersion;
    return (*this);
}

MessageBuilder& MessageBuilder::addHeader(const Header header) {
    addHeader(header.name(), header.value());
    return (*this);
}

MessageBuilder& MessageBuilder::addHeader(const std::string name, const std::string value) {
    if (_headers.count(name)) {
        _headers[name] = value;
    } else {
        _headers.emplace(name, value);
    }
    return (*this);
}

MessageBuilder& MessageBuilder::addHeaders(const std::vector<Header> headers) {
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        addHeader(*it);
    }
    return (*this);
}

MessageBuilder& MessageBuilder::setContent(const std::string content) {
    _content = content;
    return (*this);
}

Message& MessageBuilder::build() {
    return (*this);
}
