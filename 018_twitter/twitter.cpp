#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>

class Message {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;
public:
    Message(int id, const std::string& username, const std::string& msg) : id{id}, username{username}, msg{msg} {
    }
    int getId() const {
        return this->id;
    }
    void like(const std::string& username){
        likes.insert(username);
    }
    friend std::ostream& operator<<(std::ostream& os, const Message& msg){
        os << msg.id << ":" << msg.username << " (" << msg.msg << ")\t[ ";
        if (!msg.likes.empty())
            for (auto like : msg.likes)
                os << like << " ";
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
        for (auto& msg : unread) {
            messages.push_back(msg.second);
            //this->storeReaded(msg.second);
        }
        unread.clear();
        if (messages.size() == 0)
            throw std::runtime_error("[caixa de entrada vazia]");
        return messages;
    }
    std::vector<Message*> getAll() const {
        std::vector<Message*> messages;
        for (auto& msg : this->allMsgs)
            messages.push_back(msg.second);
        return messages;
    }
    Message* getTweet(int id){
        auto message = allMsgs.find(id);
        if (message == allMsgs.end()) {
            throw std::runtime_error("fail: Tweet nao encontrado");
            return nullptr;
        }
        return message->second;
    }
    void storeUnread(Message* tweet){
        this->unread[tweet->getId()] = tweet;
        this->storeReaded(tweet);
    }
    void storeReaded(Message* tweet){
        this->allMsgs[tweet->getId()] = tweet;
    }
    friend std::ostream& operator<<(std::ostream& os, Inbox& inbox){
        for (auto msg : inbox.getUnread())
            os << "\t" << *msg;
        return os;
    }
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
public:
    User(const std::string& username) : username(username) {
    }
    void sendTweet(Message* msg){
        inbox.storeUnread(msg);
        for (auto& user : followers)
            user.second->getInbox().storeUnread(msg);
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
    void like(int twId){
        Message* message = inbox.getTweet(twId);
        message->like(this->username);
    }
    Inbox& getInbox(){
        return this->inbox;
    }
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
std::ostream& operator<<(std::ostream& os, const User& user){
    os << user.username << "\n  seguidos\t[ ";
    for (auto follow : user.following)
        os << follow.second->username << " ";
    
    os << "]\n  seguidores\t[ ";
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
        Message* message = new Message(nextTweetId, username, msg);
        tweets[nextTweetId] = std::make_shared<Message>(nextTweetId, username, msg);
        nextTweetId++;
        return message;
    }
public:
    Controller(){
    }
    void addUser(std::string username){
        auto user = users.find(username);
        if (user != users.end())
            throw std::runtime_error("fail: Nome de usuario ja usado");
        else
            users[username] = std::make_shared<User>(username);
    }
    User* getUser(std::string username){
        auto user = users.find(username);
        if (user == users.end()) {
            throw std::runtime_error("fail: usuario nao encontrado");
            return nullptr;
        }
        return user->second.get();
    }
    void sendTweet(std::string username, std::string msg){
        User* user = this->getUser(username);
        if (user != nullptr) {
            Message* message = createMsg(username, msg);
            user->sendTweet(message);
        }   
    }
    void timeline(std::string user){
        std::vector<Message*> messages = this->getUser(user)->getInbox().getAll();
        for (auto msg : messages)
            std::cout << *msg << std::endl;
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
            else if (cmd == "add") {
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
            else if (cmd == "timeline") {
                std::string userName;
                ss >> userName;
                control.timeline(userName);
            }
            else if (cmd == "like") {
                std::string userName;
                int id;
                ss >> userName >> id;
                control.getUser(userName)->like(id);
            }
            else {
                std::cout << "fail: Comando invalido" << std::endl;
            }
        }
        catch(std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}