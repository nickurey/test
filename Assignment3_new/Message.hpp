#pragma once

#include <string>
#include <vector>
#include <map>

/*
  Class representing an HTTP header.
 */
class Header {
public:
    Header(std::string name, std::string value) {
        _name = name;
        _value = value;
    };

    std::string name() const {
        return _name;
    }

    std::string value() const {
        return _value;
    }

private:
    std::string _name;
    std::string _value;
};

/*
  Class representing a general HTTP message
 */
class Message {
public:
    std::string getHTTPVersion() const;
    std::vector<Header> getHeaders() const;
    std::string getContent() const;

protected:
    std::string _httpVersion;
    std::map<std::string, std::string> _headers;
    std::string _content;
};

class MessageBuilder : protected Message {
public:
    MessageBuilder& setHTTPVersion(const std::string httpVersion);

    MessageBuilder& addHeader(const Header header);
    MessageBuilder& addHeader(const std::string name, const std::string value);
    MessageBuilder& addHeaders(const std::vector<Header> headers);

    MessageBuilder& setContent(const std::string content);

    Message& build();
};