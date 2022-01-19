#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>

class MessageException : public std::exception {
   std::string message;
public:
    MessageException(const std::string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Message {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;
public:
    Message(int id, const std::string& username, const std::string& msg) : 
        id{id}, username{username}, msg{msg} {
    }
    int getId() const {
        return this->id;
    }
    void like(const std::string& username); 
    friend std::ostream& operator<<(std::ostream& os, const Message& msg){
        os << msg.id << ":" << msg.username << " (" << msg.msg << ") [";
        for (auto like : msg.likes) {
            os << like << " ";
        }
        os << "]\n";
        return os;
    }
};

class Inbox {
    std::map<int, Message*> unread;
    std::map<int, Message*> allMsgs;
public:
    Inbox(){
    }
    std::vector<Message*> getUnread(){
        std::vector<Message*> messages;
        for (auto msg : this->unread) {
            messages.push_back(msg.second);
            this->storeReaded(msg.second);
        }
        unread.clear();
        return messages;
    }
    std::vector<Message*> getAll() const {
    }
    Message* getTweet(int id);
    friend std::ostream& operator<<(std::ostream& os, Inbox& inbox){
        for (auto msg : inbox.getUnread())
            os << "\t" << *msg;
        return os;
    }
    void storeUnread(Message* tweet){
        this->unread[tweet->getId()] = tweet;
    }
    void storeReaded(Message* tweet){
        this->allMsgs[tweet->getId()] = tweet;
    }
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
public:
    void sendTweet(Message* msg){
        this->inbox.storeUnread(msg);
    }
    User(const std::string& username) : 
        username(username) {
    }
    void follow(User * other){
        this->following[other->username] = other;
        other->followers[this->username] = this;
    }
    void unfollow(std::string username){
        auto user = following.find(username);
        auto user2 = user->second->followers.find(this->username);
        user->second->followers.erase(user2);
        this->following.erase(user);
    }
    void like(int twId);
    Inbox& getInbox();
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
std::ostream& operator<<(std::ostream& os, const User& user){
    os << user.username << "\n\tseguidos [ ";
    for (auto follow : user.following)
        os << follow.second->username << " ";
    
    os << "]\n\tseguidores [ ";
    for (auto seguidor : user.followers)
        os << seguidor.second->username << " ";
    os << "]";
    return os;
}

class Controller {
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Message>> tweets;
    int nextTweetId { 0 };
    //create, stores and returns a new tweet object
    Message* createMsg(std::string username, std::string msg){
        tweets[nextTweetId] = std::make_shared<Message>(nextTweetId, username, msg);
        nextTweetId++;
        return tweets[nextTweetId--].get();
    }
public:
    Controller(){
    }
    void addUser(std::string username){
        auto user = users.find(username);
        if (user != users.end())
            throw std::runtime_error("fail: Usuario ja usado");
        else
            users[username] = std::make_shared<User>(username);
    }
    User* getUser(std::string username){
        auto user = users.find(username);
        if (user == users.end())
            throw std::runtime_error("fail: usuario nao encontrado");
        else
            return user->second.get();
    }
    void sendTweet(std::string username, std::string msg){
        auto user = users.find(username);
        if (user == users.end())
            throw std::runtime_error("fail: nome de usuario nao encontrado");
        else {
            user->second->sendTweet(createMsg(username, msg));
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Controller& ctrl);
};

std::ostream& operator<<(std::ostream& os, const Controller& ctrl){
    for (auto user : ctrl.users)
        os << *user.second << "\n";
    return os;
}

int main(){
    Controller control;

    std::cout << "SEU SISTEMA ESTA PRONTO" << std::endl;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        try {
            if (cmd == "end") {
                break;
            }
            else if (cmd == "show") {
                std::cout << control;
            }
            else if (cmd == "addUser") {
                std::string userName;
                ss >> userName;
                control.addUser(userName);
            }
            else if (cmd == "follow") {
                std::string seguidor, seguido;
                ss >> seguidor >> seguido;
                control.getUser(seguidor)->follow(control.getUser(seguido));
            }
            else if (cmd == "unfollow") {
                std::string seguidor, seguido;
                ss >> seguidor >> seguido;
                control.getUser(seguidor)->unfollow(seguido);
            }
            else if (cmd == "twittar") {
                std::string userName, msg;
                ss >> userName;
                getline(ss, msg);
                control.sendTweet(userName, msg.substr(1));
            }
        }
        catch(std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}