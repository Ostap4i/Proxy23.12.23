#include <iostream>
#include <string>
#include <unordered_map>


class Document {
public:
    virtual std::string readDocument() const = 0;
    virtual void writeDocument(const std::string& content) = 0;
};

class ConcreteDocument : public Document {
private:
    std::string content;

public:
    std::string readDocument() const override {
        return content;
    }

    void writeDocument(const std::string& newContent) override {
        content = newContent;
    }
};


class DocumentAccess {
public:
    virtual std::string readDocument() const = 0;
    virtual void writeDocument(const std::string& content) = 0;
};


class RealDocumentAccess : public DocumentAccess {
private:
    ConcreteDocument document;

public:
    std::string readDocument() const override {
        return document.readDocument();
    }

    void writeDocument(const std::string& content) override {
        document.writeDocument(content);
    }
};


class ProxyDocumentAccess : public DocumentAccess {
private:
    RealDocumentAccess realAccess;
    std::unordered_map<std::string, std::string> accessControl; 

public:
    std::string readDocument() const override {
        
        if (accessControl.find("allowed_document") != accessControl.end()) {
            return realAccess.readDocument();
        }
        else {
            return "Access denied.";
        }
    }

    void writeDocument(const std::string& content) override {
        if (accessControl.find("allowed_document") != accessControl.end()) {
            realAccess.writeDocument(content);
        }
        else {
            std::cout << "Write access denied." << std::endl;
        }
    }
};

int main() {
    RealDocumentAccess realAccess;
    ProxyDocumentAccess proxyAccess;


    std::cout << "Real Document Access:" << std::endl;
    realAccess.writeDocument("This is a real document.");
    std::cout << "Read document: " << realAccess.readDocument() << std::endl;


    std::cout << "\nProxy Document Access:" << std::endl;
    proxyAccess.writeDocument("This is a proxy document.");
    std::cout << "Read document: " << proxyAccess.readDocument() << std::endl;

    return 0;
}